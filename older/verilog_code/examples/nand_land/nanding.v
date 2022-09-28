/*
    use the NAND gate for a basis because it has an advantage
        1 ) NAND
*/

`timescale 1ns/1ns
`define HALF 5
`define DEBUG_wave -999


module tb();
    wire y_nand;
    wire y_not;
    wire y_and;
    wire y_or;
    wire y_nor;
    wire y_xor;
    wire y_nxor;
    reg a_in;
    reg b_in;

    integer idx;

    nand_gate DUT_nand (
                            .y_nand(y_nand),
                            .a_in(a_in),
                            .b_in(b_in)
                        );

    not_ng DUT_not (
                        .y_not(y_not),
                        .a_in(a_in)
                    );
    
    and_ng DUT_and (
                            .y_and(y_and),
                            .a_in(a_in),
                            .b_in(b_in)
                        );
    
    or_ng DUT_or (
                    .y_or(y_or),
                    .a_in(a_in),
                    .b_in(b_in)
                );
        
    nor_ng DUT_nor (
                        .y_nor(y_nor),
                        .a_in(a_in),
                        .b_in(b_in)
                    );
    
    xor_ng DUT_xor (
                        .y_xor(y_xor),
                        .a_in(a_in),
                        .b_in(b_in)
                    );
    
    nxor_ng DUT_nxor (
                        .y_nxor(y_nxor),
                        .a_in(a_in),
                        .b_in(b_in)
                    );
    
    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        $write("\ntest the other gates that NAND gates can make { 2 input only }\n");

        // NOT
        $write("\n\ntest the NOT gate:\n\n");
        $write("\t\t\t a  |  Y\n");
        $write("\t\t\t---------\n");
        for (idx = 0; idx < 2; idx = idx + 1) begin
            a_in = idx;
            #`HALF;
            $write("\t\t\t %1b  |  %1b\n", a_in, y_not);
        end

        // AND
        $write("\n\ntest the AND gate:\n\n");
        $write("\t\t\t a  b  |  Y\n");
        $write("\t\t\t------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {a_in, b_in} = idx;
            #`HALF;
            $write("\t\t\t %1b  %1b  |  %1b\n", a_in, b_in, y_and);
        end

        // NAND
        $write("\n\ntest the NAND gate:\n\n");
        $write("\t\t\t a  b  |  Y\n");
        $write("\t\t\t------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {a_in, b_in} = idx;
            #`HALF;
            $write("\t\t\t %1b  %1b  |  %1b\n", a_in, b_in, y_nand);
        end

        // OR
        $write("\n\ntest the OR gate:\n\n");
        $write("\t\t\t a  b  |  Y\n");
        $write("\t\t\t------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {a_in, b_in} = idx;
            #`HALF;
            $write("\t\t\t %1b  %1b  |  %1b\n", a_in, b_in, y_or);
        end

        // NOR
        $write("\n\ntest the NOR gate:\n\n");
        $write("\t\t\t a  b  |  Y\n");
        $write("\t\t\t------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {a_in, b_in} = idx;
            #`HALF;
            $write("\t\t\t %1b  %1b  |  %1b\n", a_in, b_in, y_nor);
        end

        // XOR
        $write("\n\ntest the XOR gate:\n\n");
        $write("\t\t\t a  b  |  Y\n");
        $write("\t\t\t------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {a_in, b_in} = idx;
            #`HALF;
            $write("\t\t\t %1b  %1b  |  %1b\n", a_in, b_in, y_xor);
        end

        // NXOR
        $write("\n\ntest the NXOR gate:\n\n");
        $write("\t\t\t a  b  |  Y\n");
        $write("\t\t\t------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {a_in, b_in} = idx;
            #`HALF;
            $write("\t\t\t %1b  %1b  |  %1b\n", a_in, b_in, y_nxor);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %4t  ns\n\n", $time);
        $finish;
    end
endmodule


////~~~~ the basis, NAND gate
module nand_gate (
                    output wire y_nand,
                    input wire a_in,
                    input wire b_in
                );
    nand(y_nand, a_in, b_in);
endmodule


////~~~~ NOT, by NAND gate
module not_ng (
                    output wire y_not,
                    input wire a_in
                );
    nand_gate to_NOT (
                        .y_nand(y_not),
                        .a_in(a_in),
                        .b_in(a_in)
                    );
endmodule


////~~~~ AND, by 2 NAND gates
module and_ng (
                output wire y_and,
                input wire a_in,
                input wire b_in
            );
    wire ng_out;

    nand_gate to_AND_1 (
                            .y_nand(ng_out),
                            .a_in(a_in),
                            .b_in(b_in)
                        );
    
    nand_gate to_AND_2 (
                            .y_nand(y_and),
                            .a_in(ng_out),
                            .b_in(ng_out)
                        );
endmodule


////~~~~ OR, by 3 NAND gates
module or_ng (
                output wire y_or,
                input wire a_in,
                input wire b_in
            );
    wire ng_out_1;
    wire ng_out_2;

    nand_gate to_OR_1 (
                            .y_nand(ng_out_1),
                            .a_in(a_in),
                            .b_in(a_in)
                        );
    
    nand_gate to_OR_2 (
                            .y_nand(ng_out_2),
                            .a_in(b_in),
                            .b_in(b_in)
                        );
    
    nand_gate to_OR_3 (
                            .y_nand(y_or),
                            .a_in(ng_out_1),
                            .b_in(ng_out_2)
                        );
endmodule


////~~~~ NOR, by 4 NAND gates
module nor_ng (
                output wire y_nor,
                input wire a_in,
                input wire b_in
            );
    wire ng_out_1;
    wire ng_out_2;
    wire ng_out_3;

    nand_gate to_NOR_1 (
                            .y_nand(ng_out_1),
                            .a_in(a_in),
                            .b_in(a_in)
                        );
    
    nand_gate to_NOR_2 (
                            .y_nand(ng_out_2),
                            .a_in(b_in),
                            .b_in(b_in)
                        );
    
    nand_gate to_NOR_3 (
                            .y_nand(ng_out_3),
                            .a_in(ng_out_1),
                            .b_in(ng_out_2)
                        );
    
    nand_gate to_NOR_4 (
                            .y_nand(y_nor),
                            .a_in(ng_out_3),
                            .b_in(ng_out_3)
                        );
endmodule


////~~~~ XOR, by 4 NAND gates
module xor_ng (
                output wire y_xor,
                input wire a_in,
                input wire b_in
            );
    wire ng_out_1;
    wire ng_out_2;
    wire ng_out_3;

    nand_gate to_NOR_1 (
                            .y_nand(ng_out_1),
                            .a_in(a_in),
                            .b_in(b_in)
                        );
    
    nand_gate to_NOR_2 (
                            .y_nand(ng_out_2),
                            .a_in(a_in),
                            .b_in(ng_out_1)
                        );
    
    nand_gate to_NOR_3 (
                            .y_nand(ng_out_3),
                            .a_in(ng_out_1),
                            .b_in(b_in)
                        );
    
    nand_gate to_NOR_4 (
                            .y_nand(y_xor),
                            .a_in(ng_out_2),
                            .b_in(ng_out_3)
                        );
endmodule


////~~~~ NXOR, by 5 NAND gates
module nxor_ng (
                output wire y_nxor,
                input wire a_in,
                input wire b_in
            );
    wire ng_out_1;
    wire ng_out_2;
    wire ng_out_3;
    wire ng_out_4;

    nand_gate to_NXOR_1 (
                            .y_nand(ng_out_1),
                            .a_in(a_in),
                            .b_in(b_in)
                        );
    
    nand_gate to_NXOR_2 (
                            .y_nand(ng_out_2),
                            .a_in(a_in),
                            .b_in(a_in)
                        );
    
    nand_gate to_NXOR_3 (
                            .y_nand(ng_out_3),
                            .a_in(b_in),
                            .b_in(b_in)
                        );
    
    nand_gate to_NXOR_4 (
                            .y_nand(ng_out_4),
                            .a_in(ng_out_2),
                            .b_in(ng_out_3)
                        );
    
    nand_gate to_NXOR_5 (
                            .y_nand(y_nxor),
                            .a_in(ng_out_1),
                            .b_in(ng_out_4)
                        );
endmodule


////////~~~~~~~~END>  nanading.v