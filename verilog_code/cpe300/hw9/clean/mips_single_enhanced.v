/*
    original single-cycle MIPS processor with modifications
    can only implement a few instructions
    seperates memory unit into individual modules instead of using pointers on 4 GB
    no syscall to stop execution, must know intended output to determine success

    instructions added:

    "jr"  
    "lui" 
    "ori"  
    "sllv" 
*/

`timescale 1ns/1ns
`define HALF 5         // half cycle, time between posedge and negedge
`define NANO_SPIN 0    // reps until last instruction
`define SAFETY 16      // kill after this many of instructions, stops oo loop

// only use one at a time
//`define BASE_TEST_1 100
//`define BASE_TEST_2 101
//`define ORI_TEST 102
//`define JR_TEST 103
`define SLLV_LUI_TEST 104

`define DEBUG_tb 999                     // prints internals of DUT in test bench
//`define DEBUG_wave 888                   // make a vcd if you want the wave
//`define DEBUG_INITIAL 1000               // displays instructions initially read for verification
//`define DEBUG_instruction_memory 2000    // displays instructions fetched by PC on address change
//`define DEBUG_dynamic_memory 2001        // displays data read and written when address changes
//`define DEBUG_mips_dp_cu 2002            // comprehensive display of ports and signals
//`define PROBE 2003                       // general purpose temporary probe, 
                                           //    try to delete probes when done, don't make a mess
`ifdef PROBE 
    $write("\n\t*-->  PROBE sig_jr:  %1b\n", sig_jr); 
`endif                                           

// original "testbench.v"  ,  file 1 of 16
////~~~~
/*
    should be updated to reflect instruction sets
    control the MACROS for selecting the proper instructions to test
    only makes DUT from top module, 
        member access to see internals, or turn on individual DEBUG macros
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
            `ifdef BASE_TEST_1
                $write("\n testing verison:  \"base 1\"  ,");
                $write("  success means M[0x54] = 0x7\n");
            `endif
            `ifdef BASE_TEST_2
                $write("\n testing verison:  \"base 2\"  ,");
                $write("  success means M[0x54] = 0x16\n");
            `endif
            `ifdef ORI_TEST
                $write("\n testing verison:  \"ori\"  ,");
                $write("  success means M[0x14] = 0x5\n");
            `endif
            `ifdef JR_TEST
                $write("\n testing verison:  \"jr\"  ,");
                $write("  success means M[0x14] = 0x4\n");
            `endif
            `ifdef SLLV_LUI_TEST
                $write("\n testing verison:  \"sllv + lui\"  ,");
                $write("  success means M[0x54] = 0x1000_000\n");
            `endif

            $write("\n         PC      |    instr    | mw  |  data addr  |  data\n");
            $write(" --------------------------------------------------------------\n");
            $write(" %2d)  %4H_%4H  |  %4H_%4H  |  %1b  |  %4H_%4H  |  %4H_%4H        %6t ns\n",
                idx,
                DUT.pc[31:16], DUT.pc[15:0], 
                DUT.instr[31:16], DUT.instr[15:0],
                memwrite,
                dataadr[31:16], dataadr[15:0],
                writedata[31:16], writedata[15:0],
                $time-1);
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

    `ifdef ORI_TEST
        // instructions in  "ori_test.dat"  ,  success means M[20] = 5
        always @ (negedge clock) begin
            if (memwrite == 1'b1 && access_complete == 1'b0) begin 
                if (dataadr === 20 & writedata === 5) begin
                    sim_success = 1'b1;
                    access_complete = 1'b1;
                end 
                else begin
                    sim_success = 1'b0;
                end
            end
        end
    `endif

    `ifdef JR_TEST
        // instructions in  "jr_test.dat"  ,  success means M[20] = 4
        always @ (negedge clock) begin
            if (memwrite == 1'b1 && access_complete == 1'b0) begin 
                if (dataadr === 20 & writedata === 4) begin
                    sim_success = 1'b1;
                    access_complete = 1'b1;
                end 
                else begin
                    sim_success = 1'b0;
                end
            end
        end
    `endif

    `ifdef SLLV_LUI_TEST
        // instructions in  "sllv_lui_test.dat"  ,  success means M[84] = 0x1000_000
        always @ (negedge clock) begin
            if (memwrite == 1'b1 && access_complete == 1'b0) begin 
                if (dataadr === 84 & writedata === 32'h1000_0000) begin
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
            idx = idx + 1;
            `ifdef DEBUG_tb
                $write(" %2d)  %4H_%4H  |  %4H_%4H  |  %1b  |  %4H_%4H  |  %4H_%4H        %6t ns\n",
                    idx,
                    DUT.pc[31:16], DUT.pc[15:0], 
                    DUT.instr[31:16], DUT.instr[15:0],
                    memwrite,
                    dataadr[31:16], dataadr[15:0],
                    writedata[31:16], writedata[15:0],
                    $time-1);
            `endif
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

    mips_dp_cu mips (clock, reset, pc, instr, memwrite, dataadr, writedata, readdata);
    instruction_memory imem (pc[7:2], instr);
    dynamic_memory dmem (clock, memwrite, dataadr, writedata, readdata);

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
    wire alusrc;
    wire regdst;
    wire regwrite;
    wire jump;
    wire [2:0] alucontrol;
    wire zero;     
    wire pcsrc;    
    wire sig_ori;  
    wire sig_jr;   
    wire sig_lui;

    control_unit CU (
                    .op(instr[31:26]), 
                    .funct(instr[5:0]),
                    .zero(zero),
                    .memtoreg(memtoreg), 
                    .memwrite(memwrite),
                    .pcsrc(pcsrc), 
                    .alusrc(alusrc),
                    .regdst(regdst), 
                    .regwrite(regwrite),
                    .jump(jump),
                    .sig_ori(sig_ori),  
                    .sig_jr(sig_jr),    
                    .sig_lui(sig_lui),  
                    .alucontrol(alucontrol)
                );
    
    data_path DP (
                    .clock(clock), 
                    .reset(reset),
                    .memtoreg(memtoreg), 
                    .pcsrc(pcsrc),
                    .alusrc(alusrc), 
                    .regdst(regdst),
                    .regwrite(regwrite), 
                    .jump(jump),
                    .sig_ori(sig_ori),  
                    .sig_jr(sig_jr),    
                    .sig_lui(sig_lui),  
                    .alucontrol(alucontrol),
                    .zero(zero),
                    .pc(pc),
                    .instr(instr),
                    .aluout(aluout), 
                    .writedata(writedata),
                    .readdata(readdata)
                );
    
    `ifdef DEBUG_mips_dp_cu
        always @ (negedge clock) begin 
            #1;
            $write("\n*************************************************************\n");
            $write(" pc:     %4H_%4H    ,    pcnext:  %4H_%4H\n", 
                pc[31:16], pc[15:0], DP.pcnext[31:16], DP.pcnext[15:0]);
            $write(" instr:  %4H_%4H\n", instr[31:16], instr[15:0]);
            $write("                               op         :  %3b_%3b\n", instr[31:29], instr[28:26]);
            $write("                               func       :  %3b_%3b\n", instr[5:3], instr[2:0]);
            $write("                               ---------------------\n");
            $write("                               regwrite   :  %1b\n", regwrite);
            $write("                               regdst     :  %1b\n", regdst);
            $write("                               alusrc     :  %1b\n", alusrc);
            $write("                               branch     :  %1b\n", CU.branch);
            $write("                               memwrite   :  %1b\n", memwrite);
            $write("                               memtoreg   :  %1b\n", memtoreg);
            $write("                               aluop      :  %2b\n", CU.aluop);
            $write("                               jump       :  %1b\n", jump);
            $write("                               sig_ori    :  %1b\n", sig_ori);
            $write("                               sig_jr     :  %1b\n", sig_jr);
            $write("                               sig_lui    :  %1b\n", sig_lui);
            $write("                               zero       :  %1b\n", zero);
            $write("                               pcsrc      :  %1b\n", pcsrc);
            $write("                               alucontrol :  %3b\n", alucontrol);
            $write("                               ---------------------------\n");
            $write("                                     alu_srcA :  %4H_%4H\n", DP.srca[31:16], DP.srca[15:0]);
            $write("                                     alu_srcB :  %4H_%4H\n", DP.srcb[31:16], DP.srcb[15:0]);
            $write("                                       aluout :  %4H_%4H\n", aluout[31:16], aluout[15:0]);
            $write(" rf_a1:  %5b -> rd1:  %4h_%4h\n", instr[25:21], DP.srca[31:16], DP.srca[15:0]);
            $write(" rf_a2:  %5b -> rd2:  %4h_%4h\n", instr[20:16], writedata[31:16], writedata[15:0]);
            $write(" rf_wa:  %5b -> wd3:  %4h_%4h\n", DP.writereg, DP.write_to_rf[31:16], DP.write_to_rf[15:0]);
            $write("                                  dmem_a  :  %4h_%4h\n", aluout[31:16], aluout[15:0]);
            $write("                                  dmem_wrt:  %4h_%4h\n", writedata[31:16], writedata[15:0]);
            $write("                                  dmem_rd :  %4h_%4h\n", readdata[31:16], readdata[15:0]);
            $write("*************************************************************\n");
        end
    `endif

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
        ORI_TEST
        JR_TEST
        SLLV_LUI_TEST
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
        `ifdef ORI_TEST
            $readmemh ("ori_test.dat", RAM);
        `endif
        `ifdef JR_TEST
            $readmemh ("jr_test.dat", RAM);
        `endif
        `ifdef SLLV_LUI_TEST
            $readmemh ("sllv_lui_test.dat", RAM);
        `endif

        `ifdef DEBUG_INITIAL
            $write("\n {instruction_memory} initially read:\n\n");
            $write("  a  |  RAM[a]\n");
            $write(" -----------------\n");
            for (ii = 0; ii < 64; ii = ii + 1) begin
                temp = RAM[ii];
                $write(" %2d  |  %4H_%4H\n",
                    ii, temp[31:16], temp[15:0]);
            end
        `endif
    end

    assign rd = RAM[a];  // word aligned, always reads to output

    `ifdef DEBUG_instruction_memory
        always @ (a) begin
            $write("\n {instruction_memory}  fetched:\n");
            $write("a: %6b  ,  rd:  %4H%4H\n", 
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
            $write(" we:  %1b  ,  a:  %4H_%4H  ,  rd:  %4H_%4H\n",
                    we, a[31:16], a[15:0], rd[31:16], rd[15:0]);
        `endif
    end

    `ifdef DEBUG_dynamic_memory
        always @ (a) begin
            $write("\n {dynamic_memory} read out:\n");
            $write(" we:  %1b  ,  a:  %4H_%4H  ,  rd:  %4H_%4H\n",
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
                    output wire sig_ori,  
                    output wire sig_jr,   
                    output wire sig_lui,  
                    output wire [2:0] alucontrol
                );

    wire [1:0] aluop;
    wire branch;

    maindec MD (
                    .op(op), 
                    .funct(funct),
                    .memtoreg(memtoreg), 
                    .memwrite(memwrite), 
                    .branch(branch), 
                    .alusrc(alusrc),
                    .regdst(regdst), 
                    .regwrite(regwrite), 
                    .jump(jump), 
                    .sig_ori(sig_ori),  
                    .sig_jr(sig_jr),    
                    .sig_lui(sig_lui),  
                    .aluop(aluop)
                );

    aludec AD (funct, aluop, alucontrol);

    assign pcsrc = branch & zero;  // the AND gate in diagram

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
                    input wire [5:0] funct,
                    output wire memtoreg, 
                    output wire memwrite, 
                    output wire branch, 
                    output wire alusrc,
                    output wire regdst, 
                    output wire regwrite, 
                    output wire jump, 
                    output wire sig_ori,  
                    output wire sig_jr,   
                    output wire sig_lui,  
                    output wire [1:0] aluop
                );

    reg [11:0] controls; 

    assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, 
        aluop, jump, sig_ori, sig_jr, sig_lui} = controls; 

    always @ (*) begin // new
        case(op)
            6'b000_000 :                                       
                        begin
                            if (funct == 6'b001_000) begin
                                controls <= 12'b0_0_0_0_0_0_10_0_0_1_0; // R-type, is JR
                            end
                            else begin
                               controls <= 12'b1_1_0_0_0_0_10_0_0_0_0; // R-type, not jr 
                            end   
                        end
            6'b100_011 :  controls <= 12'b1_0_1_0_0_1_00_0_0_0_0; 	 // lw
            6'b101_011 :  controls <= 12'b0_0_1_0_1_0_00_0_0_0_0; 	 // sw
            6'b000_100 :  controls <= 12'b0_0_0_1_0_0_01_0_0_0_0; 	 // beq
            6'b001_000 :  controls <= 12'b1_0_1_0_0_0_00_0_0_0_0; 	 // addi
            6'b000_010 :  controls <= 12'b0_0_0_0_0_0_00_1_0_0_0;    // j
            6'b001_101 :  controls <= 12'b1_0_1_0_0_0_11_0_1_0_0;    // ori
            6'b001_111 :  controls <= 12'b1_0_0_0_0_0_00_0_0_0_1;    // lui
            default    :  controls <= 12'bX_X_X_X_X_X_XX_X_X_X_X; 	 // any
        endcase
    end

endmodule


// original "aludec.v"  ,  file 8 of 16
////~~~~
/*
    this will get overloaded quickly if more signals are needed
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
        else if (aluop == 2'b11) begin
            alucontrol <= 3'b001; // if more than "ori" use 2'b11, make case statement
        end
        else begin // R-type  2'b10 case
            case(funct) 
                6'b100_000 : alucontrol <= 3'b010; // add
                6'b100_010 : alucontrol <= 3'b110; // sub
                6'b100_100 : alucontrol <= 3'b000; // and
                6'b100_101 : alucontrol <= 3'b001; // or
                6'b101_010 : alucontrol <= 3'b111; // slt
                6'b000_100 : alucontrol <= 3'b101; // sllv
                default    : alucontrol <= 3'bxxx; // catch all {jr}
            endcase
        end
    end

endmodule


// original "datapth.v"  ,  file 9 of 16
////~~~~
/*
    control signals determine operation
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
                    input wire sig_ori,  
                    input wire sig_jr,   
                    input wire sig_lui, 
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
    wire [31:0] signimm;
    wire [31:0] signimmsh;
    wire [31:0] srca;
    wire [31:0] srcb;
    wire [31:0] result;
    wire [31:0] zeroXimm;        
    wire [31:0] extend_mux_out;  
    wire [31:0] jr_mux_out;      
    wire [31:0] write_to_rf;      
    wire [31:0] zero_full;       

    // next PC logic
    program_counter #(32) pcreg (clock, reset, pcnext, pc);
    adder pcadd1 (pc, 32'b100, pcplus4);
    shift_left_2 immsh (signimm, signimmsh); 
    adder pcadd2 (pcplus4, signimmsh, pcbranch);
    mux_2_to_1 #(32) pcbrmux (pcplus4, pcbranch, pcsrc, pcnextbr);
    mux_2_to_1 #(32) jr_mux (pcnextbr, srca, sig_jr, jr_mux_out); 
    mux_2_to_1 #(32) pcmux (jr_mux_out, {pcplus4[31:28], instr[25:0], 2'b00}, jump, pcnext); 

    // register file logic
    register_file RF (clock, regwrite, instr[25:21],
        instr[20:16], writereg, write_to_rf, srca, writedata); 
    mux_2_to_1 #(5) wrmux (instr[20:16], instr[15:11],regdst, writereg);
    mux_2_to_1 #(32) resmux (aluout, readdata, memtoreg, result);
    mux_2_to_1 #(32) lui_mux (result, zero_full, sig_lui, write_to_rf); 
    sign_extend SE (instr[15:0], signimm);
    zero_extend ZE (instr[15:0], zeroXimm);  
    zero_filler ZF (instr[15:0], zero_full);  

    // ALU logic
    mux_2_to_1 #(32) srcbmux (writedata, extend_mux_out, alusrc, srcb); 
    mux_2_to_1 #(32) extend_mux (signimm, zeroXimm, sig_ori, extend_mux_out);  
    alu ALU (srca, srcb, alucontrol, aluout, zero);

endmodule


// original "flopr.v"  ,  file 10 of 16
////~~~~
/*
    32 D flip-flops to represent the program counter
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
    it still has room to add more
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
            3'b000 : 
	            begin
		            out = a & b; 
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end                   
            3'b001 :
	            begin
		            out= a | b; 
		            if (out == 0) zero = 1;  
		            else zero = 0; 
                end	
            3'b010 : 
	            begin
		            out = a + b;  
		            if (out == 0) zero = 1;  
                    else zero = 0;
                end  
            3'b101 : 
	            begin
		            out = b << a;
                end  	
            3'b110 : 
	            begin
		            out = a - b;  
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end              
            3'b111 : 
                begin
		            if ( a < b) out = 1;  
		            else out = 0;
                end 
            default : 
                begin
                    out = 0;
                    zero = 0;
                end
        endcase
    end

endmodule


////~~~~
/*
    zero extends the immidate 
    from 16-bits to 32-bits by concatenation
*/
module zero_extend (
                    input wire [15:0] a,
                    output wire [31:0] y
                );

    assign y = {16'h0000, a};

endmodule


////~~~~
/*
    zero fills LSBs after immidate 
    {immediate, 16{0}}
*/
module zero_filler (
                    input wire [15:0] a,
                    output wire [31:0] y
                );

    assign y = {a,16'h0000};

endmodule


////////~~~~~~~~END>  mips_single_enhanced.v
