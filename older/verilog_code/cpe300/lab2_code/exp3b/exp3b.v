/*
    exp3_B, make a 2:1 mux, conditional operator
    use  assign Y = (s) ? a : b
*/

`timescale 1ns/1ns
`define STEP 10

module tb ();
    wire outY;
    reg sel;
    reg inA;
    reg inB;

    integer idx;
    reg [2:0] trans;

    mux21 DUT (
                .out_y(outY),
                .in_a(inA),
                .in_b(inB),
                .select(sel)
              );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n2:1 MUX, 1-bit, assign Y = (~s) ? a : b\n\n");
        $write(" s  a  b  |  Y\n");
        $write("---------------\n");

        for (idx = 0; idx < 8; idx = idx + 1) begin
            trans = idx;
            sel = trans[2];
            inA = trans[1];
            inB = trans[0];
            # `STEP
            $write(" %b  %b  %b  |  %b\n",
                sel, inA, inB, outY);
        end

        # `STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


module mux21 (
                output wire out_y,
                input wire select,
                input wire in_a,
                input wire in_b
             );
    assign out_y = (~select) ? in_a : in_b;
endmodule


////////~~~~~~~~END>  exp3b.v
