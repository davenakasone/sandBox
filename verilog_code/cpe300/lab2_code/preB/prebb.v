/*
    prelab B adjusted for wave
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    wire outY;
    reg inA;
    reg inB;
    reg inC;
    reg [2:0] trans;
    integer idx;

    std_exp DUT (
                    .out_y(outY),
                    .in_a(inA),
                    .in_b(inB),
                    .in_c(inC)
                );

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\npre-lab B results:\n\n");
        $write(" a  b  c  |  Y\n");
        $write("-----------------\n");

        for (idx = 0; idx < 8; idx = idx + 1) begin
            trans = idx;
            inA = trans[2];
            inB = trans[1];
            inC = trans[0];
            #`STEP
            $write(" %b  %b  %b  |  %b\n",
                inA, inB, inC, outY);
        end 

        # `STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module std_exp (
                    output wire out_y,
                    input wire in_a,
                    input wire in_b,
                    input wire in_c
                );
    assign out_y = in_a * (in_b + in_c) + (in_b * (~in_c)) + in_a;
endmodule


////////~~~~~~~~END>  prebb.v
