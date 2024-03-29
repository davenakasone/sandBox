/*
    original single-cycle MIPS processor with modifications
    can only implement a few instructions
    seperates memory unit into individual modules instead of using pointers on 4 GB
    no syscall to stop execution, must know intended output to determine success

        the safe and clean case...no addtions, just 2 base cases
*/

`timescale 1ns/1ns
`define HALF 5         // half cycle, time between posedge and negedge
`define NANO_SPIN 0    // reps until last instruction
`define SAFETY 30      // kill after this many of instructions

// only use one at a time
//`define BASE_TEST_1 100
`define BASE_TEST_2 101

`define DEBUG_tb 999                       // prints internals of DUT in test bench
//`define DEBUG_wave 888                   // make a vcd if you want the wave
//`define DEBUG_INITIAL 1000               // displays instructions initially read for verification
//`define DEBUG_instruction_memory 2000    // displays instructions fetched by PC on address change
//`define DEBUG_dynamic_memory 2001        // displays data read and written when address changes


// original "testbench.v"  ,  file 1 of 16
////~~~~
/*
    should be updated to reflect instruction sets
    control the MACROS for selecting the proper instructions to test
    only makes DUT from top module, 
        member access to see internals
        or turn on individual debug macros
*/
module test_bench();
    reg clock;
    reg reset;
    wire [31:0] writedata; 
    wire [31:0] dataadr;
    wire memwrite;

    m_main DUT (clock, reset, writedata, dataadr, memwrite);

    reg printing;
    integer idx;
    reg sim_success;
    integer play_time;
    reg access_complete;

    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        printing = 1'b0;
        idx = 1;
        sim_success = 1'b0;
        access_complete = 1'b0;
        play_time = `NANO_SPIN;  // change in macro


        reset <= 1; 
        # 22; 
        reset <= 0;

        printing = 1'b1;
        `ifdef DEBUG_tb
            $write("\n         PC      |    instr    | mw  |  data addr  |  data\n");
            $write(" --------------------------------------------------------------\n");
        `endif
    end

    always begin
        clock <= 1'b0;
        # `HALF; 
        clock <= 1'b1;
        # `HALF; 
    end

    `ifdef BASE_TEST_1
        // instructions in "base_test_1.dat"  ,  success means M[84] = 7
        always @ (negedge clock) begin
            if (memwrite == 1'b1 && access_complete == 1'b0) begin 
                if (dataadr === 84 & writedata === 7) begin
                    sim_success = 1'b1;
                    access_complete = 1'b1;
                end 
                else begin
                    sim_success = 1'b0;
                end
            end
        end
    `endif

    `ifdef BASE_TEST_2
        // instructions in  "base_test_2.dat"  ,  success means M[84] = 22
        always @ (negedge clock) begin
            if (memwrite == 1'b1 && access_complete == 1'b0) begin 
                if (dataadr === 84 & writedata === 22) begin
                    sim_success = 1'b1;
                    access_complete = 1'b1;
                end 
                else begin
                    sim_success = 1'b0;
                end
            end
        end
    `endif

    always @ (negedge clock) begin
        #1;
        if (printing) begin
            `ifdef DEBUG_tb
            $write(" %2d)  %4h_%4h  |  %4h_%4h  |  %1b  |  %4h_%4h  |  %4h_%4h        %6t ns\n",
                idx,
                DUT.pc[31:16], DUT.pc[15:0], 
                DUT.instr[31:16], DUT.instr[15:0],
                memwrite,
                dataadr[31:16], dataadr[15:0],
                writedata[31:16], writedata[15:0],
                $time-1);
            `endif
            idx = idx + 1;
        end

        play_time = (access_complete == 1'b1) ? play_time - 1 : play_time;

        if (play_time < 0 || idx > `SAFETY) begin
            `ifdef DEBUG_tb
                if (sim_success == 1'b1) begin
                    $write("\n\n\tSimulation SUCCESS\n");
                end
                else begin
                    $write("\n\n\tSimulation FAIL\n");
                end
                $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %9t ns\n\n", $time);
            `endif
            $finish;
        end 
    end

endmodule


// original "top.v"  ,  file 2 of 16
////~~~~
/*
    the applied microprocessor
    combines: instruction_memory, dynamic_memory, and mips
    module that should be tested, not a diagram component
*/
module m_main (
                input wire clock, 
                input wire reset,
                output wire [31:0] writedata, 
                output wire [31:0] dataadr,
                output wire memwrite
            );

    wire [31:0] pc;
    wire [31:0] instr; 
    wire [31:0] readdata;

    // instantiate processor and memories
    mips_dp_cu mips (clock, reset, pc, instr, memwrite, dataadr, writedata, readdata);
    instruction_memory imem (pc[7:2], instr); // 6-bit address
    dynamic_memory dmem (clock, memwrite, dataadr, writedata,readdata);

endmodule


// original "mips.v"  ,  file 3 of 16
////~~~~
/*
    mips has 4 fundamental units: 
        program counter, instruction memory, register file, and data memory
    this module only combines the control unit and data path
    be careful for those originally missing wires (see comments)
        verify with:
            DEBUG_mips_dp_cu
*/
module mips_dp_cu (
                    input wire clock, 
                    input wire reset,
                    output wire [31:0] pc,
                    input wire [31:0] instr,
                    output wire memwrite,
                    output wire [31:0] aluout, 
                    output wire [31:0] writedata,
                    input wire [31:0] readdata
                );

    wire memtoreg;
    wire branch;
    wire alusrc;
    wire regdst;
    wire regwrite;
    wire jump;
    wire [2:0] alucontrol;
    wire zero; // added
    wire pcsrc; // added

    control_unit CU (instr[31:26], instr[5:0], zero, memtoreg, memwrite, pcsrc, 
        alusrc, regdst, regwrite, jump, alucontrol);
    data_path DP (clock, reset, memtoreg, pcsrc, alusrc, regdst, regwrite, jump,
        alucontrol, zero, pc, instr, aluout, writedata, readdata);

endmodule


// original "imem.v"  ,  file 4 of 16
////~~~~
/*
    instruction memory wouldn't really be a ROM
    drive instructions from intially reading a file
    verify with:
        DEBUG_INITIAL
        BASE_TEST_1
        BASE_TEST_2
        DEBUG_instruction_memory
*/
module instruction_memory (
                                input wire [5:0] a, 
                                output wire [31:0] rd
                            );

    reg [31:0] RAM[63:0];  // limited memory

    `ifdef DEBUG_INITIAL
        reg [31:0] temp;
        integer ii;
    `endif
    
    initial begin

        // instructions are given in these files
        `ifdef BASE_TEST_1
            $readmemh ("base_test_1.dat", RAM);  
        `endif
        `ifdef BASE_TEST_2
            $readmemh ("base_test_2.dat", RAM);
        `endif

        `ifdef DEBUG_INITIAL
            $write("\n {instruction_memory} initially read:\n\n");
            $write("  a  |  RAM[a]\n");
            $write(" -----------------\n");
            for (ii = 0; ii < 64; ii = ii + 1) begin
                temp = RAM[ii];
                $write(" %2d  |  %4h_%4h\n",
                    ii, temp[31:16], temp[15:0]);
            end
        `endif
    end

    assign rd = RAM[a]; // word aligned, always reads to output

    `ifdef DEBUG_instruction_memory
        always @ (a) begin
            $write("\n {instruction_memory}  fetched:\n");
            $write("a: %6b  ,  rd:  %4h%4h\n", 
                a, rd[31:16], rd[15:0]);
        end
    `endif
endmodule


// original "dmem.v"  ,  file 5 of 16
////~~~~
/*
    data memory reads in combination
    writes synchronously on positive edge of clock
    verify with:
        DEBUG_dynamic_memory
*/
module dynamic_memory (
                input wire clock, 
                input wire we,
                input wire [31:0] a, 
                input wire [31:0] wd,
                output [31:0] rd
            );

    reg [31:0] RAM[63:0];

    assign rd = RAM[a[31:2]]; // word aligned

    always @ (posedge clock) begin
        if (we) RAM[a[31:2]] <= wd;
        `ifdef DEBUG_dynamic_memory
            $write("\n {dynamic_memory} wrote in:\n");
            $write(" we:  %1b  ,  a:  %4h_%4h  ,  rd:  %4h_%4h\n",
                    we, a[31:16], a[15:0], rd[31:16], rd[15:0]);
        `endif
    end

    `ifdef DEBUG_dynamic_memory
        always @ (a) begin
            $write("\n {dynamic_memory} read out:\n");
            $write(" we:  %1b  ,  a:  %4h_%4h  ,  rd:  %4h_%4h\n",
                we, a[31:16], a[15:0], rd[31:16], rd[15:0]);
        end
    `endif

endmodule


// original "controller.v"  ,  file 6 of 16
////~~~~
/*
    sub-components of ALU decoder and main decoder
    implies AND gate for pcsrc
    update as instruction set changes
*/
module control_unit (
                    input wire [5:0] op, 
                    input wire [5:0] funct,
                    input wire zero,
                    output wire memtoreg, 
                    output wire memwrite,
                    output wire pcsrc, 
                    output wire alusrc,
                    output wire regdst, 
                    output wire regwrite,
                    output wire jump,
                    output wire [2:0] alucontrol
                );

    wire [1:0] aluop;
    wire branch;

    maindec MD (op, memtoreg, memwrite, branch, alusrc, regdst, regwrite, jump, aluop);
    aludec AD (funct, aluop, alucontrol);

    assign pcsrc = branch & zero; 

endmodule


// original "maindec.v"  ,  file 7 of 16
////~~~~
/*
    takes opcode and produces control signals except branch
    branching is done by controller module as an outside logic
    checks the opcode and produces 9 control signals {control word table}
*/
module maindec (
                    input wire [5:0] op, 
                    output wire memtoreg, 
                    output wire memwrite, 
                    output wire branch, 
                    output wire alusrc,
                    output wire regdst, 
                    output wire regwrite, 
                    output wire jump, 
                    output wire [1:0] aluop
                );

    reg [8:0] controls;

    assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, aluop} = controls;

    always @ (*) begin
        case(op)
            6'b000000 :  controls <= 9'b110000010; 		// R-type
            6'b100011 :  controls <= 9'b101001000; 		// sw
            6'b101011 :  controls <= 9'b001010000; 		// sw
            6'b000100 :  controls <= 9'b000100001; 		// beq
            6'b001000 :  controls <= 9'b101000000; 		// addi
            6'b000010 :  controls <= 9'b000000100; 		// j
            default   :  controls <= 9'bXXXXXXXXX; 		// any
        endcase
    end

endmodule


// original "aludec.v"  ,  file 8 of 16
////~~~~
/*
    removed the nested case statement
    right now, there is an empty slot, only 7/8 used
*/
module aludec (
                    input wire [5:0] funct,
                    input wire [1:0] aluop,
                    output reg [2:0] alucontrol
            );

    always @ (*) begin
        if (aluop == 2'b00) begin
            alucontrol <= 3'b010; // add
        end
        else if (aluop == 2'b01) begin
            alucontrol <= 3'b110; // sub
        end
        else begin
            case(funct) // RTYPE
                6'b100000 : alucontrol <= 3'b010; // ADD
                6'b100010 : alucontrol <= 3'b110; // SUB
                6'b100100 : alucontrol <= 3'b000; // AND
                6'b100101 : alucontrol <= 3'b001; // OR
                6'b101010 : alucontrol <= 3'b111; // SLT
                default   : alucontrol <= 3'bxxx; // ???
            endcase
        end
    end

endmodule


// original "datapth.v"  ,  file 9 of 16
////~~~~
/*
    control signals determine operation
    conditions probe here
    the data path and control unit work together as usual
*/
module data_path (
                    input wire clock, 
                    input wire reset,
                    input wire memtoreg, 
                    input wire pcsrc,
                    input wire alusrc, 
                    input wire regdst,
                    input wire regwrite, 
                    input wire jump,
                    input wire [2:0] alucontrol,
                    output wire zero,
                    output wire [31:0] pc,
                    input wire [31:0] instr,
                    output wire [31:0] aluout, 
                    output wire [31:0] writedata,
                    input wire [31:0] readdata
                );

    wire [4:0] writereg;
    wire [31:0] pcnext;
    wire [31:0] pcnextbr;
    wire [31:0] pcplus4;
    wire [31:0] pcbranch;
    wire [31:0] signimm, signimmsh;
    wire [31:0] srca;
    wire [31:0] srcb;
    wire [31:0] result;

    // next PC logic
    program_counter #(32) pcreg (clock, reset, pcnext, pc);
    adder pcadd1 (pc, 32'b100, pcplus4);
    shift_left_2 immsh (signimm, signimmsh); 
    adder pcadd2 (pcplus4, signimmsh, pcbranch);
    mux_2_to_1 #(32) pcbrmux (pcplus4, pcbranch, pcsrc, pcnextbr);
    mux_2_to_1 #(32) pcmux (pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);

    // register file logic
    register_file RF (clock, regwrite, instr[25:21],
        instr[20:16], writereg, result, srca, writedata);
    mux_2_to_1 #(5) wrmux (instr[20:16], instr[15:11],regdst, writereg);
    mux_2_to_1 #(32) resmux (aluout, readdata, memtoreg, result);
    sign_extend SE (instr[15:0], signimm);

    // ALU logic
    mux_2_to_1 #(32) srcbmux (writedata, signimm, alusrc, srcb);
    alu ALU (srca, srcb, alucontrol, aluout, zero);

endmodule


// original "flopr.v"  ,  file 10 of 16
////~~~~
/*
    31 D flip-flops to represent the program counter
    notice it resets to 8'h0000_0000  (change as needed)
*/
module program_counter # (parameter WIDTH = 8) (
                                        input wire clock, 
                                        input wire reset,
                                        input wire [WIDTH-1:0] d,
                                        output reg [WIDTH-1:0] q
                                    );

    always @ (posedge clock or posedge reset) begin
        q <= (reset) ? 0 : d;
    end

endmodule


// original "adder.v"  ,  file 11 of 16
////~~~~
/*
    there is not much going on here
    be careful for overflow
*/
module adder (
                input wire [31:0] a, 
                input wire [31:0] b, 
                output wire [31:0] y
            );

    assign y = a + b;

endmodule


// original "sl2.v"  ,  file 12 of 16
////~~~~
/*
    appends two zeros from the right of LSB 
    for 26-bit immediate field provided as input
    shift left by 2 bits uses concatenation
        26 + 2 = 28 bits out [27:0]
*/
module shift_left_2 (
                input wire [31:0] a, 
                output wire [31:0] y
            );

    assign y = {a[25:0], 2'b00};

endmodule


// original "mux2.v"  ,  file 13 of 16
////~~~~
/*
    ordinary 2:1 MUX using parameterized inputs
    Please note, it is limited to 8 as both 
    addresses for instruction and data memory are limited to 6.
    data in the test code are in the range 0-255
    For the real design the width is 8
*/ 
module mux_2_to_1 # (parameter WIDTH = 8) (
                                        input wire [WIDTH-1:0] d0, 
                                        input wire [WIDTH-1:0] d1, 
                                        input wire s,
                                        output wire [WIDTH-1:0] y
                                    );

    assign y = (s) ? d1 : d0;

endmodule


// original "regfile.v"  ,  file 14 of 16
////~~~~
/*
    this is one of the fundamental elements of the CPU
    3-ported register file
    it reads 2 ports out in combination, 
    but writes sychrousnously (posedge)
    register 0 hardwired to 0
*/
module register_file (
                        input wire clock, 
                        input wire we3,
                        input wire [4:0] ra1, 
                        input wire [4:0] ra2, 
                        input wire [4:0] wa3,
                        input wire [31:0] wd3,
                        output wire [31:0] rd1, 
                        output wire [31:0]rd2
                    );

    reg [31:0] rf[31:0];
    
    always @ (posedge clock) begin
        if (we3) rf[wa3] <= wd3;
    end

    // notice the effective hard-wire rf[0] = 0
    assign rd1 = (ra1 != 0) ? rf[ra1] : 0; 
    assign rd2 = (ra2 != 0) ? rf[ra2] : 0; 

endmodule


// original "signext.v"  ,  file 15 of 16
////~~~~
/*
    effective sign externsion 
    concatenates to output a 32-bit number
    copies the 16th bit of input "a[15]"  
        to upper of output "y[31:16]"
*/
module sign_extend (
                    input wire [15:0] a,
                    output wire [31:0] y
                );

    assign y = {{16{a[15]}}, a};

endmodule


// original "alu.v"  ,  file 16 of 16
////~~~~
/*
    ordinary ALU that also outputs zero flag
    it appears to be missing a default case right now
*/
module alu (
                input wire [31:0] a,
                input wire [31:0] b,
                input wire [2:0] sel, 
                output reg [31:0] out, 
                output reg zero
            );
  
    initial begin
        out = 0;
        zero =1'b0;
    end
    
    always @ (*) begin 
        case(sel) 
            3'b000: 
	            begin
		            out = a & b; 
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end                   
            3'b001:
	            begin
		            out= a | b; 
		            if (out == 0) zero = 1;  
		            else zero = 0; 
                end		
            3'b110: 
	            begin
		            out = a - b;  
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end              
            3'b010: 
	            begin
		            out = a + b;  
		            if (out == 0) zero = 1;  
                    else zero = 0;
                end         
            3'b111: 
                begin
		            if ( a < b) out = 1;  
		            else out = 0;
                end 
        endcase
    end

endmodule

////////~~~~~~~~END>  mips_single.v
