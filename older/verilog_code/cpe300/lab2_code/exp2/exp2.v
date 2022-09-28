/*
    use primitives for circuit #2
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    reg inA;
    reg inB;
    wire outY;
    reg [1:0] trans;
    integer idx;

    circuit2 DUT (
                    .in_a(inA),
                    .in_b(inB),
                    .out_y(outY)
                );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\ncircuit #2 results:\n\n");
        $write(" a  b  |  Y\n");
        $write("-------------\n");

        for (idx = 0; idx < 4; idx = idx + 1) begin
            trans = idx;
            inA = trans[1];
            inB = trans[0];
            #`STEP
            $write(" %b  %b  |  %b\n",
                inA, inB, outY);
        end 

        # `STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module circuit2 (
                    input wire in_a,
                    input wire in_b,
                    output wire out_y
                );
    wire t_1;
    wire t_2;
    wire w_1;
    wire w_2;

    not b_bar (w_1, in_b);
    not a_bar (w_2, in_a);
    and and_g1 (t_1, w_1, in_a);
    and and_g2 (t_2, w_2, in_b);
    or or_g (out_y, t_1, t_2);

endmodule


////////~~~~~~~~END>  exp2.v
