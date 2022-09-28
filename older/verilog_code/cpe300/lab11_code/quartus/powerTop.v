/*
    combines all sub-modules into single file
    with FPGA features
    operates according to lab11 assignment

    synchronous reset...apply reset and run clock (if needed)
*/

`timescale 1ns/1ns       // fit to timeQuest
`define HALF 5           // duration from any edge to any edge
`define PLAY_TIME 190    // ensure termination in this duration

// only use one at a time
`define TEST_CASE_1 111
//`define TEST_CASE_2 222

`define DEBUG_tb 999
//`define DEBUG_wave 998
//`define DEBUG_smp8 997
//`define DEBUG_INIT_imem 996
//`define DEBUG_INIT_dmem 995


module tb();

    reg clock;
    reg reset;
    wire sig_data_write_enable;
    wire [6:0] h6_ex;
    wire [6:0] h5_ex;
    wire [6:0] h4_ex;
    wire [6:0] h1_ex;
    wire [6:0] h0_ex;
    wire [6:0] h7_ex;
    wire [6:0] h3_ex;
    wire [6:0] h2_ex;

    reg [3:0] t6;
    reg [3:0] t5;
    reg [3:0] t4;
    reg [3:0] t1;
    reg [3:0] t0;

    powerTop DUT (
                    .clock (clock),
                    .reset (reset),
                    .sig_data_write_enable (sig_data_write_enable),   
                    .h6_ex (h6_ex),  
                    .h5_ex (h5_ex),  
                    .h4_ex (h4_ex),  
                    .h1_ex (h1_ex),  
                    .h0_ex (h0_ex),  
                    .h7_ex (h7_ex),  
                    .h3_ex (h3_ex), 
                    .h2_ex (h2_ex)           
                );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        clock = 1'b0;
            reset = 1'b0;
        //reset = 1'b1;
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        //#`HALF; #`HALF; #`HALF; #`HALF;
        //reset = 1'b0;
        #`HALF;

        `ifdef TEST_CASE_1
            $write("\n\n testing case #1, success means M[2] = 114 = 0x72\n");
        `endif
        `ifdef TEST_CASE_2
            $write("\n\n testing case #2, success means M[4] = 255 = 0xFF\n");
        `endif
        `ifdef DEBUG_tb
            $write("\n\n PC  |  Ins  |  AC\n");
            $write(" --------------------\n");
        `endif

        #`PLAY_TIME;
        $write("\n\tsimulation FAIL\n");
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %4t ns\n\n", $time);
        $finish;
    end

    always @ (negedge clock) begin
        #1;
        `ifdef DEBUG_tb
            disp_out(h6_ex, t6);
            $write("  %1h  |  ", t6);
            disp_out(h5_ex, t5);
            $write("%1h", t5);
            disp_out(h4_ex, t4);
            $write("%1h   |", t4);
            disp_out(h1_ex, t1);
            $write("  %1h", t1);
            disp_out(h0_ex, t0);
            $write("%1h  |", t0);
            $write("            %4t ns    ", $time);

            if (sig_data_write_enable) begin
                $write("  stored-->  M[%1h]\n", t4);
            end
            else begin
                $write("\n");
            end
        `endif
        `ifdef TEST_CASE_1 // validation by simulation halt
            if (sig_data_write_enable && t4 == 4'b0010) begin
                    $write("\n\tsimulation, case #1,  SUCCESS\n");
                    $write("\n\tnote instr[3] was skipped and instr[7] and instr[8] are NOP\n");
                    $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %4t ns\n\n", $time);
                    $finish;
                end
        `endif
        `ifdef TEST_CASE_2 // validation by simulation halt
            if (sig_data_write_enable && t4 == 4'b0100) begin
                    $write("\n\tsimulation, case #2,  SUCCESS\n");
                    $write("\n\tnote instr[5] was skipped and instr[8] is NOP\n");
                    $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %4t ns\n\n", $time);
                    $finish;
                end
        `endif
    end

    task automatic disp_out;
        input [6:0] seg_out;
        output [3:0] to_hex;
        begin
            case(seg_out)
                7'b1000_000 : to_hex = 4'h0;
                7'b1111_001 : to_hex = 4'h1;
                7'b0100_100 : to_hex = 4'h2;
                7'b0110_000 : to_hex = 4'h3;
                7'b0011_001 : to_hex = 4'h4;
                7'b0010_010 : to_hex = 4'h5;
                7'b0000_010 : to_hex = 4'h6;
                7'b1111_000 : to_hex = 4'h7;
                7'b0000_000 : to_hex = 4'h8;
                7'b0011_000 : to_hex = 4'h9;
                7'b0001_000 : to_hex = 4'hA;
                7'b0000_011 : to_hex = 4'hB;
                7'b1000_110 : to_hex = 4'hC;
                7'b0100_001 : to_hex = 4'hD;
                7'b0000_110 : to_hex = 4'hE;
                7'b0001_110 : to_hex = 4'hF;
                default : to_hex = 4'bXXXX;
            endcase
        end
    endtask
    
endmodule


////~~~~
/*
    module to top the previous top-level
    adapted for FPGA
*/
module powerTop (
                    input wire clock,
                    input wire reset,
                    output wire sig_data_write_enable,    // control 8, LED indicator
                    output wire [6:0] h6_ex,              // on, PC, 1 of 1
                    output wire [6:0] h5_ex,              // on, Instr, 1 of 2
                    output wire [6:0] h4_ex,              // on, Instr, 2 of 2
                    output wire [6:0] h1_ex,              // on, AC, 1 of 2
                    output wire [6:0] h0_ex,              // on, AC, 2 of 2
                    output wire [6:0] h7_ex,              // off
                    output wire [6:0] h3_ex,              // off
                    output wire [6:0] h2_ex               // off
                );

    wire [7:0] data_to_write;
    wire [3:0] pc_executing;
    wire [7:0] instruction_fetched;
    wire [7:0] pass_back_AC;

    // hex[6] = PC, hex[5:4] = instr, hex[1:0] = AC  
    // turn the rest off: hex[7], hex[3], hex[2]
    assign h7_ex = 7'b1111_111;
    assign h3_ex = 7'b1111_111;
    assign h2_ex = 7'b1111_111;


    m_main processor (
                        .clock (clock),
                        .reset (reset),
                        .sig_data_write_enable (sig_data_write_enable),  
                        .pc_executing (pc_executing),
                        .instruction_fetched (instruction_fetched),
                        .data_to_write (data_to_write),
                        .pass_back_AC (pass_back_AC)
                    );
    
    m_seg7hex hex6 (
                        .cntl (pc_executing),
                        .disp (h6_ex)
                    );
    
    m_seg7hex hex5 (
                        .cntl (instruction_fetched[7:4]),
                        .disp (h5_ex)
                    );
    
    m_seg7hex hex4 (
                        .cntl (instruction_fetched[3:0]),
                        .disp (h4_ex)
                    );
    
    m_seg7hex hex1 (
                        .cntl (pass_back_AC[7:4]),
                        .disp (h1_ex)
                    );
    
    m_seg7hex hex0 (
                        .cntl (pass_back_AC[3:0]),
                        .disp (h0_ex)
                    );

endmodule


////~~~~
/*
    get 4-bit hex to 7-segment display
*/
module m_seg7hex (
                    input [3:0] cntl,
                    output reg [6:0] disp
                );

    parameter ON = 1'b0;
    parameter OFF = 1'b1;

    always @ (*) begin
        disp = {7{OFF}};
        case (cntl)
            4'b0000 : disp[5:0] = {6{ON}};
            4'b0001 : disp[2:1] = {2{ON}};
            4'b0010 :
                begin
                    disp[1:0] = {2{ON}};
                    disp[6] = ON;
                    disp[4:3] = {2{ON}};
                end
            4'b0011 :
                begin
                    disp[3:0] = {4{ON}};
                    disp[6] = ON;
                end
            4'b0100 :
                begin
                    disp[2:1] = {2{ON}};
                    disp[6:5] = {2{ON}};
                end 
            4'b0101 :
                begin
                    disp[0] = ON;
                    disp[3:2] = {2{ON}};
                    disp[6:5] = {2{ON}};
                end
            4'b0110 :
                begin
                    disp[0] = ON;
                    disp[6:2] = {5{ON}};
                end
            4'b0111 : disp[2:0] = {3{ON}};
            4'b1000 : disp[6:0] = {7{ON}};
            4'b1001 :
                begin
                    disp[6:0] = {7{ON}};
                    disp[4:3] = {2{OFF}};
                end
            4'b1010 :
                begin
                    disp[6:0] = {7{ON}};
                    disp[3] = OFF;
                end
            4'b1011 :
                begin
                    disp[6:0] = {7{ON}};
                    disp[1:0] = {2{OFF}};
                end
            4'b1100 :
                begin
                    disp[5:3] = {3{ON}};
                    disp[0] = ON;
                end
            4'b1101 :
                begin
                    disp[4:1] = {4{ON}};
                    disp[6] = ON;
                end
            4'b1110 :
                begin
                    disp[6:3] = {4{ON}};
                    disp[0] = ON;
                end
            4'b1111 :
                begin
                    disp[6:4] = {3{ON}};
                    disp[0] = ON;
                end
        endcase
    end

endmodule


////~~~~
/*
    top-level entity
*/
module m_main (
                input wire clock,
                input wire reset,
                output wire sig_data_write_enable,  // control 8
                output wire [3:0] pc_executing,
                output wire [7:0] instruction_fetched,
                output wire [7:0] data_to_write,
                output wire [7:0] pass_back_AC
            );
    
    
    wire [7:0] data_fetched;

    m_SMP8 processor (
                        .clock (clock),
                        .reset (reset),
                        .instruction_fetched (instruction_fetched),
                        .data_fetched (data_fetched),
                        .sig_data_write_enable (sig_data_write_enable),
                        .pc_executing (pc_executing),
                        .data_to_write (data_to_write),
                        .pass_back_AC (pass_back_AC)
                    );
    m_instruction_memory IMEM (
                                .pc_executing (pc_executing),
                                .instruction_fetched (instruction_fetched)
                            );
    m_data_memory DMEM (
                            .clock (clock),
                            .reset (reset),
                            .sig_data_write_enable (sig_data_write_enable), 
                            .data_address (instruction_fetched[3:0]),
                            .data_to_write (data_to_write),
                            .data_fetched (data_fetched)
                        );
endmodule


////~~~~
/*
    combines fundamental elements of SMP8 processor
    using data path + control unit technique
*/
module m_SMP8 (
                input wire clock,
                input wire reset,
                input wire [7:0] instruction_fetched,
                input wire [7:0] data_fetched,
                output wire sig_data_write_enable,  // control 8
                output wire [3:0] pc_executing,
                output wire [7:0] data_to_write,
                output wire [7:0] pass_back_AC
            );
    
    wire sig_rf_port_A_address;    // control 1
    wire sig_rf_port_B_address;    // control 2
    wire sig_rf_write_address;     // control 3
    wire sig_rf_write_enable;      // control 4
    wire [2:0] sig_alu_op;         // control 5, 6, 7
    wire sig_data_to_rf;           // control 9
    wire condition_branch_jump;    // from control 10, 11
    wire flag_zero;
    integer ii;

    m_controller CU (
                        .op_code (instruction_fetched[7:4]),             
                        .flag_zero (flag_zero),
                        .sig_rf_port_A_address (sig_rf_port_A_address),    
                        .sig_rf_port_B_address (sig_rf_port_B_address),    
                        .sig_rf_write_address (sig_rf_write_address),     
                        .sig_rf_write_enable (sig_rf_write_enable),      
                        .sig_alu_op (sig_alu_op),              
                        .sig_data_write_enable (sig_data_write_enable), 
                        .sig_data_to_rf (sig_data_to_rf),           
                        .condition_branch_jump (condition_branch_jump)
                    );
    
    m_data_path DP (
                        .clock (clock),
                        .reset (reset),
                        .sig_rf_port_A_address (sig_rf_port_A_address),
                        .sig_rf_port_B_address (sig_rf_port_B_address),
                        .sig_rf_write_address (sig_rf_write_address),
                        .sig_rf_write_enable (sig_rf_write_enable),
                        .sig_alu_op (sig_alu_op), 
                        .sig_data_to_rf (sig_data_to_rf), 
                        .condition_branch_jump (condition_branch_jump),   
                        .data_fetched (data_fetched),
                        .instruction_fetched (instruction_fetched),
                        .flag_zero (flag_zero),
                        .pc_executing (pc_executing),
                        .data_to_write (data_to_write),
                        .pass_back_AC (pass_back_AC)
                    );
    
    `ifdef DEBUG_smp8
        always @ (negedge clock) begin
            #1;
            $write("\n********************************************************************************************* %4t {\n", $time);
            $write(" pc:  %2d  ,  instr:  %2h                                        rf[0] = %2h  ,  rf[1] = %2h\n", 
                pc_executing, instruction_fetched, DP.RF.internal_rf[0], DP.RF.internal_rf[1]);
            $write(" -->  pc_next:  %2d\n", DP.pc_next);
            $write(" \n srcA  |  srcB  |  rfWA  |  rfWE  |  alu  | datWE | to_rf | branch | jump ||>> zero | BJ | mode\n");
            $write(" ----------------------------------------------------------------------------------------------\n");
            $write("   %1b   |   %1b    |   %1b    |    %1b   |  %3b  |   %1b   |   %1b   |    %1b   |   %1b  ||>>  %1b   | %1b  |  %1b\n\n",
                sig_rf_port_A_address, sig_rf_port_B_address, sig_rf_write_address, sig_rf_write_enable,
                sig_alu_op, sig_data_write_enable, sig_data_to_rf, CU.sig_branch, CU.sig_jump, 
                flag_zero, CU.condition_branch_jump,instruction_fetched[7]);
            $write(" rf[%1b] = %2h  -> rf_port_A         dmem_adr:     %4b\n" , 
                sig_rf_port_A_address, DP.RF.internal_rf[sig_rf_port_A_address], instruction_fetched[3:0]);
            $write(" rf[%1b] = %2h  -> rf_port_B         dmem_writes:  %2h\n", 
                sig_rf_port_B_address, DP.RF.internal_rf[sig_rf_port_B_address], data_to_write);
            $write(" ------------------------         dmem_reads:   %2h    ", data_fetched);
            if (sig_data_write_enable) $write("writes to dmem\n");
            else $write("no dmem write\n");
            $write(" ALU result = %2h                                        write { %2h } -> rf[%1b]    ", 
                DP.alu_result, DP.rf_write_value, sig_rf_write_address);
            if (sig_rf_write_enable) $write("writes to RF\n");
            else $write("no RF write\n");
            $write("********************************************************************************************* }\n");
        end
    `endif

endmodule


////~~~~
/*
    control unit as a consolidated decoder
    no clock used
    application of the control word table
*/
module m_controller (
                        input wire [3:0] op_code,             // 4 MSB of instruction
                        input wire flag_zero,
                        output wire sig_rf_port_A_address,    // control 1
                        output wire sig_rf_port_B_address,    // control 2
                        output wire sig_rf_write_address,     // control 3
                        output wire sig_rf_write_enable,      // control 4
                        output wire [2:0] sig_alu_op,         // control 5, 6, 7
                        output wire sig_data_write_enable,    // control 8
                        output wire sig_data_to_rf,           // control 9
                        output wire condition_branch_jump     // internal by control 11, 12
                    );

    wire sig_branch;    // internal generation, control 10
    wire sig_jump;      // internal generation, control 11
    reg [10:0] control_signals;

    always @ (*) begin
        case(op_code)
            4'b0000 : control_signals = 11'b0_0_0_0_000_0_0_0_0;    // NOP
            4'b0001 : control_signals = 11'b0_0_0_1_000_0_1_0_0;    // LDAC
            4'b0010 : control_signals = 11'b0_0_0_0_000_1_0_0_0;    // STAC
            4'b0011 : control_signals = 11'b0_0_1_1_000_0_0_0_0;    // MVAC
            4'b0100 : control_signals = 11'b1_0_0_1_000_0_0_0_0;    // MOVR
            4'b0101 : control_signals = 11'b0_0_0_0_000_0_0_0_1;    // JUMP
            4'b0110 : control_signals = 11'b0_0_0_0_000_0_0_1_0;    // JMPZ
            4'b0111 : control_signals = 11'b0_0_0_0_001_0_0_1_0;    // JPNZ
            4'b1000 : control_signals = 11'b0_1_0_1_000_0_0_0_0;    // ADD
            4'b1001 : control_signals = 11'b0_1_0_1_001_0_0_0_0;    // SUB
            4'b1010 : control_signals = 11'b0_1_0_1_010_0_0_0_0;    // INAC
            4'b1011 : control_signals = 11'b0_1_0_1_011_0_0_0_0;    // CLAC
            4'b1100 : control_signals = 11'b0_1_0_1_100_0_0_0_0;    // AND
            4'b1101 : control_signals = 11'b0_1_0_1_101_0_0_0_0;    // OR
            4'b1110 : control_signals = 11'b0_1_0_1_110_0_0_0_0;    // XOR
            4'b1111 : control_signals = 11'b0_1_0_1_111_0_0_0_0;    // NOT
        endcase
    end

    assign {sig_rf_port_A_address,
            sig_rf_port_B_address,
            sig_rf_write_address,
            sig_rf_write_enable,
            sig_alu_op,
            sig_data_write_enable,
            sig_data_to_rf,
            sig_branch,
            sig_jump} = control_signals;    // this latch system is not clock dependent
    assign condition_branch_jump = sig_jump | (sig_branch & flag_zero);    // external gates

endmodule


////~~~~
/*
    standard conslidation of subordinate modules
    data path has 2 main sections
*/
module m_data_path (
                        input wire clock,
                        input wire reset,
                        input wire sig_rf_port_A_address,    // control 1
                        input wire sig_rf_port_B_address,    // control 2
                        input wire sig_rf_write_address,     // control 3
                        input wire sig_rf_write_enable,      // control 4
                        input wire [2:0] sig_alu_op,         // control 5, 6, 7
                        input wire sig_data_to_rf,           // control 9
                        input wire condition_branch_jump,    // handeled by control 10, 11
                        input wire [7:0] data_fetched,
                        input wire [7:0] instruction_fetched,
                        output wire flag_zero,
                        output wire [3:0] pc_executing,
                        output wire [7:0] data_to_write,
                        output wire [7:0] pass_back_AC        // for FPGA
                    );
    
    wire [3:0] pc_next;
    wire [3:0] pc_plus_1;
    wire [7:0] rf_port_A;
    wire [7:0] rf_port_B;
    wire [7:0] alu_result;
    wire [7:0] rf_write_value;

    // program counter logic
    m_program_counter PC (
                            .clock (clock), 
                            .reset (reset),
                            .pc_next (pc_next),
                            .pc_executing (pc_executing)
                        );
    m_incramenter add1 (
                            .pc_executing (pc_executing), 
                            .pc_plus_1 (pc_plus_1)
                        );
    m_mux_2_to_1 #(4) mux_branching_jumping (
                                                .select_0 (pc_plus_1), 
                                                .select_1 (instruction_fetched[3:0]), 
                                                .selector (condition_branch_jump),
                                                .mux_out (pc_next)
                                            );
    
    // register and ALU operations
    m_register_file RF (
                            .clock (clock),
                            .reset (reset),
                            .sig_rf_port_A_address (sig_rf_port_A_address), 
                            .sig_rf_port_B_address (sig_rf_port_B_address), 
                            .sig_rf_write_address (sig_rf_write_address),
                            .sig_rf_write_enable (sig_rf_write_enable), 
                            .rf_write_value (rf_write_value),
                            .rf_port_A (rf_port_A),
                            .rf_port_B (rf_port_B),
                            .pass_back_AC (pass_back_AC)   
                        );
    m_alu ALU (
                .alu_mode (instruction_fetched[7]),
                .sig_alu_op (sig_alu_op),
                .rf_port_A (rf_port_A),
                .rf_port_B (rf_port_B),
                .alu_result (alu_result),
                .flag_zero (flag_zero)
            );
    m_mux_2_to_1 #(8) mux_data (
                                    .select_0 (alu_result), 
                                    .select_1 (data_fetched), 
                                    .selector (sig_data_to_rf),
                                    .mux_out (rf_write_value)
                                );
    assign data_to_write = rf_port_B;

endmodule


////~~~~
/*
    data memory as a 16x8 RAM
    "dynamic memory"
    initialize with macros
    reads in combination
    writes on posedge of the clock
*/
module m_data_memory (
                        input wire clock,
                        input wire reset,
                        input wire sig_data_write_enable, // control 8
                        input wire [3:0] data_address,
                        input wire [7:0] data_to_write,
                        output wire [7:0] data_fetched
                    );

    reg [7:0] RAM[15:0];
    integer idx;

    initial begin
        for (idx = 0; idx < 16; idx = idx + 1) begin
            RAM[idx] = 8'b0000_0000;
        end
        `ifdef TEST_CASE_1
            RAM[0] = 8'h37; // 55 decimal
            RAM[1] = 8'h1D; // 29 decimal
        `endif
        `ifdef DEBUG_INIT_dmem
            $write("\n {m_data_memory}\n");
            `ifdef TEST_CASE_1
                $write("    using test case #1\n");
            `endif
            `ifdef TEST_CASE_2
                $write("    using test case #2\n");
            `endif
            for (idx = 0; idx < 16; idx = idx + 1) begin
                $write("\t\t\t\t%2d)  %2h\n", idx, RAM[idx]);
            end
        `endif
    end

    assign data_fetched = RAM[data_address];

    always @ (posedge clock) begin
        if (reset) begin
            for (idx = 0; idx < 16; idx = idx + 1) begin
                RAM[idx] = 8'b0000_0000;
            end
            `ifdef TEST_CASE_1
                RAM[0] = 8'h37; // 55 decimal
                RAM[1] = 8'h1D; // 29 decimal
            `endif
        end
        else begin
            if (sig_data_write_enable) begin
                RAM[data_address] = data_to_write;
            end
        end
    end

endmodule


////~~~~
/*
    instruction memory as a 16x8 ROM
    initialize with macros
    always reads to bus
*/
module m_instruction_memory (
                                input wire [3:0] pc_executing,
                                output wire [7:0] instruction_fetched
                            );
    
    reg [7:0] ROM[15:0];
    integer idx;

    initial begin
        for (idx = 0; idx < 16; idx = idx + 1) begin
            ROM[idx] = 8'h00;
        end
        `ifdef TEST_CASE_1
            ROM[0] = 8'h10;
            ROM[1] = 8'hA0;
            ROM[2] = 8'h74;
            ROM[3] = 8'h50;
            ROM[4] = 8'hA0;
            ROM[5] = 8'h30;
            ROM[6] = 8'h80;
            ROM[7] = 8'h22;
        `endif
        `ifdef TEST_CASE_2
            ROM[0] = 8'hB0;
            ROM[1] = 8'hA0;
            ROM[2] = 8'h30;
            ROM[3] = 8'hF0;
            ROM[4] = 8'hE0;
            ROM[5] = 8'h6A;
            ROM[6] = 8'h24;
        `endif
        `ifdef DEBUG_INIT_imem
            $write("\n{m_instruction_memory}\n");
            `ifdef TEST_CASE_1
                $write("    using test case #1\n");
            `endif
            `ifdef TEST_CASE_2
                $write("    using test case #2\n");
            `endif
            for (idx = 0; idx < 16; idx = idx + 1) begin
                $write("\t\t\t\t%2d)  %2h\n", idx, ROM[idx]);
            end
        `endif
    end

    assign instruction_fetched = ROM[pc_executing];

endmodule


////~~~~
/*
    2x8 register file
    rf[0] = AC
    rf[1] = R
    reads out 2 ports in combination
    writes on posedge clock
*/
module m_register_file (
                            input wire clock,
                            input wire reset,
                            input wire sig_rf_port_A_address,    // control 1
                            input wire sig_rf_port_B_address,    // control 2
                            input wire sig_rf_write_address,     // control 3
                            input wire sig_rf_write_enable,      // control 4
                            input wire [7:0] rf_write_value,
                            output wire [7:0] rf_port_A,
                            output wire [7:0] rf_port_B,
                            output wire [7:0] pass_back_AC       // FPGA demonstration
                        );
    
    reg [7:0] internal_rf[1:0];

    initial begin
        internal_rf[0] = 8'b0000_0000;
        internal_rf[1] = 8'b0000_0000;
    end

    assign pass_back_AC = internal_rf[0];
    assign rf_port_A = internal_rf[sig_rf_port_A_address];
    assign rf_port_B = internal_rf[sig_rf_port_B_address];

    always @ (posedge clock) begin
        if (reset) begin
            internal_rf[0] = 8'b0000_0000;
            internal_rf[1] = 8'b0000_0000;
        end
        else begin
            if (sig_rf_write_enable) begin
                internal_rf[sig_rf_write_address] = rf_write_value;
            end
        end
    end

endmodule


////~~~~
/*
    ALU fits to any operation in the instruction set
    mode is completley specified by instr[7]
    performs unary operations on portA only
    portA is first operand for binary operations
*/
module m_alu (
                input wire alu_mode,
                input wire [2:0] sig_alu_op,  // contol 5, 6, 7
                input wire [7:0] rf_port_A,
                input wire [7:0] rf_port_B,
                output reg [7:0] alu_result,
                output reg flag_zero
            );
    
    initial begin
        flag_zero = 1'b0;
        alu_result = 8'b0000_0000;
    end

    always @ (*) begin
        if (alu_mode == 1'b0) begin    // instructions 0 to 7
            if (sig_alu_op == 3'b001) begin    // JPNZ
                alu_result = rf_port_A; 
                flag_zero = (alu_result != 8'b0000_0000) ? 1'b1 : 1'b0; 
            end
            else begin    // pass, NOP, LDAC, STAC, MVAC, MOVR, JUMP, JMPZ
                alu_result = rf_port_A;
                flag_zero = (alu_result == 8'b0000_0000) ? 1'b1 : 1'b0; 
            end
        end
        else begin    // instructions 8 to 15
            case (sig_alu_op)
                3'b000 : alu_result = rf_port_A + rf_port_B;    // ADD
                3'b001 : alu_result = rf_port_A - rf_port_B;    // SUB
                3'b010 : alu_result = rf_port_A + 1'b1;         // INAC
                3'b011 : alu_result = 8'b0000_0000;             // CLAC
                3'b100 : alu_result = rf_port_A & rf_port_B;    // AND
                3'b101 : alu_result = rf_port_A | rf_port_B;    // OR
                3'b110 : alu_result = rf_port_A ^ rf_port_B;    // XOR
                3'b111 : alu_result = ~rf_port_A;               // NOT
            endcase
            flag_zero = (alu_result == 8'b0000_0000) ? 1'b1 : 1'b0; 
        end
    end

endmodule


////~~~~
/*
    ordinary 2:1 MUX with parameterized sizing
*/ 
module m_mux_2_to_1 # (parameter WIDTH = 4) (
                                                input wire [WIDTH-1:0] select_0, 
                                                input wire [WIDTH-1:0] select_1, 
                                                input wire selector,
                                                output wire [WIDTH-1:0] mux_out
                                            );

    assign mux_out = (selector) ? select_1 : select_0;

endmodule


////~~~~
/*
    D flip-flops {4x} to represent the program counter
    initializes and resets to 4'b0000
*/
module m_program_counter (
                            input wire clock, 
                            input wire reset,
                            input wire [3:0] pc_next,
                            output reg [3:0] pc_executing
                        );

    initial begin
        pc_executing <= 4'b0000;
    end

    always @ (posedge clock) begin
        if (reset) begin
            pc_executing<= 4'b0000;
        end
        else begin
            pc_executing <= pc_next;
        end
    end

endmodule


////~~~~
/*
    there is not much going on here
    be careful for overflow
    for fast combinational "base + constant"
*/
module m_incramenter (
                        input wire [3:0] pc_executing, 
                        output wire [3:0] pc_plus_1
                    );

    assign pc_plus_1 = pc_executing + 1'b1;

endmodule


////////~~~~~~~~END>  smp8_combined.v
