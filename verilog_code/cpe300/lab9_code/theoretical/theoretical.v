/*
    just a theoretical proof
    no FPGA 
*/

`timescale 1ns/1ns
`define HALF 50         // half cycle, time between posedge and negedge
`define NANO_SPIN 0    // reps until last instruction
`define SAFETY 30      // kill after this many of instructions

// only activate one at a time
//`define ORIGINAL_INSTRUCTIONS_FILE 100
`define ORIGINAL_INSTRUCTIONS_RAW 101


`define DEBUG_tb 999             // prints internals of DUT in test bench
`define DEBUG_wave 888           // make a vcd
//`define DEBUG_INITIAL 1000       // displays instructions read for verification
//`define DEBUG_imem 2000          // displays instructions fetched by PC on address change
//`define DEBUG_dmem 2001          // displays data read and written when address changes
//`define DEBUG_flopr 2002         // displays program counter
//`define DEBUG_mips 2003          // displays data through mips module + sub modules


// "testbench.v"  ,  file 1 of 16
////~~~~
/*
    should be updated to reflect instruction set
    control the MACROS for proper testing
    only makes DUT from top module
*/
module testbench();
    reg clk;
    reg reset;
    wire [31:0] writedata; 
    wire [31:0] dataadr;
    wire memwrite;

    top DUT (clk, reset, writedata, dataadr, memwrite);

    reg printing;
    integer idx;
    reg sim_success;
    integer play_time;
    reg access_complete;
    reg [31:0] instr_dummy;

    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, testbench);
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
        clk <= 1;
        # `HALF; 
        clk <= 0;
        # `HALF; 
    end

    always @ (posedge clk) begin
        #1
        instr_dummy = DUT.instr;
    end
    // 4-state logic check, success means M[84] = 7
    always @ (negedge clk) begin
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

    `ifdef DEBUG_tb
        always @ (negedge clk) begin
            #1;
            if (printing) begin
                $write(" %2d)  %4h_%4h  |  %4h_%4h  |  %1b  |  %4h_%4h  |  %4h_%4h        %6t ns\n",
                    idx,
                    DUT.pc[31:16], DUT.pc[15:0], 
                    DUT.instr[31:16], DUT.instr[15:0],
                    memwrite,
                    dataadr[31:16], dataadr[15:0],
                    writedata[31:16], writedata[15:0],
                    $time-1);
                idx = idx + 1;
            end

            play_time = (access_complete == 1'b1) ? play_time - 1 : play_time;

            if (play_time < 0 || idx > `SAFETY) begin
                if (sim_success == 1'b1) begin
                    $write("\n\n\tSimulation SUCCESS\n");
                end
                else begin
                    $write("\n\n\tSimulation FAIL\n");
                end
                $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %9t ns\n\n", $time);
                $finish;
            end 
        end
    `endif

endmodule


// "top.v"  ,  file 2 of 16
////~~~~
/*
    the applied microprocessor
    combines: imem, dmem, and mips
    module that should be tested
*/
module top (
                input wire clk, 
                input wire reset,
                output wire [31:0] writedata, 
                output wire [31:0] dataadr,
                output wire memwrite
            );

    wire [31:0] pc;
    wire [31:0] instr; 
    wire [31:0] readdata;

    // instantiate processor and memories
    mips mips (clk, reset, pc, instr, memwrite, dataadr, writedata, readdata);
    imem imem (pc[7:2], instr); //6-bit address
    dmem dmem (clk, memwrite, dataadr, writedata,readdata);

endmodule


// "mips.v"  ,  file 3 of 16
////~~~~
/*
    mips has 4 fundamental units: 
        program counter, instruction memory, register file, and data memory
    this module only combines the control unit and data path
    be careful for those originally missing wires (see comments)
        verify with:
            DEBUG_mips
*/
module mips (
                input wire clk, 
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

    controller CU (instr[31:26], instr[5:0], zero, memtoreg, memwrite, pcsrc, 
        alusrc, regdst, regwrite, jump, alucontrol);
    datapath DP (clk, reset, memtoreg, pcsrc, alusrc, regdst, regwrite, jump,
        alucontrol, zero, pc, instr, aluout, writedata, readdata);

    `ifdef DEBUG_mips

    `endif
endmodule


// "imem.v"  ,  file 4 of 16
////~~~~
/*
    instruction memory wouldn't really be a ROM
    drive instructions from intially reading a file
    verify with:
        DEBUG_INITIAL
        ORIGINAL_INSTRUCTIONS
        DEBUG_imem
*/
module imem (
                input wire [5:0] a, 
                output wire [31:0] rd
            );

    reg [31:0] RAM[63:0];  // limited memory

    `ifdef DEBUG_INITIAL
        reg [31:0] temp;
        integer ii;
    `endif
    
    initial begin
        `ifdef ORIGINAL_INSTRUCTIONS_FILE
            $readmemh ("memfile.dat", RAM);  // lines of test code in hex (original)
        `endif
        `ifdef ORIGINAL_INSTRUCTIONS_RAW
            RAM[0] = 32'h2002_0005;
            RAM[1] = 32'h2003_000c;
            RAM[2] = 32'h2067_fff7;
            RAM[3] = 32'h00e2_2025;
            RAM[4] = 32'h0064_2824;
            RAM[5] = 32'h00a4_2820;
            RAM[6] = 32'h10a7_000a;
            RAM[7] = 32'h0064_202a;
            RAM[8] = 32'h1080_0001;
            RAM[9] = 32'h2005_0000;
            RAM[10] = 32'h00e2_202a;
            RAM[11] = 32'h0085_3820;
            RAM[12] = 32'h00e2_3822;
            RAM[13] = 32'hac67_0044;
            RAM[14] = 32'h8c02_0050;
            RAM[15] = 32'h0800_0011;
            RAM[16] = 32'h2002_0001;
            RAM[17] = 32'hac02_0054;
        `endif
        `ifdef DEBUG_INITIAL
            $write("\n the initial instructions {imem} :\n\n");
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

    `ifdef DEBUG_imem
        always @ (a) begin
            $write("\n {imem} instruction fetched:\n");
            $write("a: %6b  ,  rd:  %4h%4h\n", 
                a, rd[31:16], rd[15:0]);
        end
    `endif
endmodule


// "dmem.v"  ,  file 5 of 16
////~~~~
/*
    data memory reads in combination
    writes synchronously on positive edge of clock
    verify with:
        DEBUG_dmem
*/
module dmem (
                input wire clk, 
                input wire we,
                input wire [31:0] a, 
                input wire [31:0] wd,
                output [31:0] rd
            );

    reg [31:0] RAM[63:0];

    assign rd = RAM[a[31:2]]; // word aligned

    always @ (posedge clk) begin
        if (we) RAM[a[31:2]] <= wd;
    end

    `ifdef DEBUG_dmem
        always @ (a) begin
            $write("\n {dmem} read out:\n");
            $write(" we:  %1b  ,  a:  %4h_%4h  ,  rd:  %4h_%4h\n",
                we, a[31:16], a[15:0]/*{a[15:2], 2'b00}*/, rd[31:16], rd[15:0]);
        end
    `endif

endmodule


// "controller.v"  ,  file 6 of 16
////~~~~
/*
    sub-components of ALU decoder and main decoder
    implies AND gate for pcsrc
    update as instruction set changes
*/
module controller (
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


// "maindec.v"  ,  file 7 of 16
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
            6'b000000 :  controls <= 9'b110000010; 		//Rtyp
            6'b100011 :  controls <= 9'b101001000; 		//LW
            6'b101011 :  controls <= 9'b001010000; 		//SW
            6'b000100 :  controls <= 9'b000100001; 		//BEQ
            6'b001000 :  controls <= 9'b101000000; 		//ADDI
            6'b000010 :  controls <= 9'b000000100; 		//J
            default   :  controls <= 9'bXXXXXXXXX; 		// any
        endcase
    end

endmodule


// "aludec.v"  ,  file 8 of 16
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


// "datapth.v"  ,  file 9 of 16
////~~~~
/*
    control signals determine operation
    conditions probe here
    the data path and control unit work together as usual
*/
module datapath (
                    input wire clk, 
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
    wire [31:0] pcnext, pcnextbr, pcplus4, pcbranch;
    wire [31:0] signimm, signimmsh;
    wire [31:0] srca, srcb;
    wire [31:0] result;

    // next PC logic
    flopr #(32) pcreg (clk, reset, pcnext, pc);
    adder pcadd1 (pc, 32'b100, pcplus4);
    sl2 immsh (signimm, signimmsh); 
    adder pcadd2 (pcplus4, signimmsh, pcbranch);
    mux2 #(32) pcbrmux (pcplus4, pcbranch, pcsrc, pcnextbr);
    mux2 #(32) pcmux (pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);

    // register file logic
    regfile RF (clk, regwrite, instr[25:21],
        instr[20:16], writereg, result, srca, writedata);
    mux2 #(5) wrmux (instr[20:16], instr[15:11],regdst, writereg);
    mux2 #(32) resmux (aluout, readdata, memtoreg, result);
    signext SE (instr[15:0], signimm);

    // ALU logic
    mux2 #(32) srcbmux (writedata, signimm, alusrc, srcb);
    alu ALU (srca, srcb, alucontrol, aluout, zero);

endmodule


// "flopr.v"  ,  file 10 of 16
////~~~~
/*
    31 D flip-flops to represent the program counter
    notice it resets to 8'h0000_0000  (change as needed)
    verify with:
        DEBUG_flopr
*/
module flopr # (parameter WIDTH = 8) (
                                        input wire clk, 
                                        input wire reset,
                                        input wire [WIDTH-1:0] d,
                                        output reg [WIDTH-1:0] q
                                    );

    always @ (posedge clk, posedge reset) begin
        q <= (reset) ? 0 : d;

        `ifdef DEBUG_flopr
            $write("\n{flpr} PC = %4h_%4h\n", q[31:16], q[15:0]);
        `endif
    end

endmodule


// "adder.v"  ,  file 11 of 16
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


// "sl2.v"  ,  file 12 of 16
////~~~~
/*
    appends two zeros from the right of LSB 
    for 26-bit immediate field provided as input
    shift left by 2 bits uses concatenation
        26 + 2 = 28 bits out [27:0]
*/
module sl2 (
                input wire [31:0] a, 
                output wire [31:0] y
            );

    assign y = {a[25:0], 2'b00};

endmodule


// "mux2.v"  ,  file 13 of 16
////~~~~
/*
    ordinary 2:1 MUX using parameterized inputs
    Please note, it is limited to 8 as both 
    addresses for instruction and data memory are limited to 6.
    data in the test code are in the range 0-255
    For the real design the width is 8
*/ 
module mux2 # (parameter WIDTH = 8) (
                                        input wire [WIDTH-1:0] d0, 
                                        input wire [WIDTH-1:0] d1, 
                                        input wire s,
                                        output wire [WIDTH-1:0] y
                                    );

    assign y = (s) ? d1 : d0;

endmodule


// "regfile.v"  ,  file 14 of 16
////~~~~
/*
    this is one of the fundamental elements of the CPU
    3-ported register file
    it reads 2 ports out in combination, 
    but writes sychrousnously (posedge)
    register 0 hardwired to 0
*/
module regfile (
                    input wire clk, 
                    input wire we3,
                    input wire [4:0] ra1, 
                    input wire [4:0] ra2, 
                    input wire [4:0] wa3,
                    input wire [31:0] wd3,
                    output wire [31:0] rd1, 
                    output wire [31:0]rd2
                );

    reg [31:0] rf[31:0];
    
    always @ (posedge clk) begin
        if (we3) rf[wa3] <= wd3;
    end

    // notice the effective hard-wire rf[0] = 0
    assign rd1 = (ra1 != 0) ? rf[ra1] : 0; 
    assign rd2 = (ra2 != 0) ? rf[ra2] : 0; 

endmodule


// "signext.v"  ,  file 15 of 16
////~~~~
/*
    effective sign externsion 
    concatenates to output a 32-bit number
    copies the 16th bit of input "a[15]"  
        to upper of output "y[31:16]"
*/
module signext (
                    input wire [15:0] a,
                    output wire [31:0] y
                );

    assign y = {{16{a[15]}}, a};

endmodule


// "alu.v"  ,  file 16 of 16
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

////////~~~~~~~~END>  fresh_v1.v
