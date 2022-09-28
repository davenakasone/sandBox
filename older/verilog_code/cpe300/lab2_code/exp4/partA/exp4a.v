/*
    OR gate w/ 5ns delay
    input state changes every 10ns
*/

`timescale 1ns/1ns
`define G_DELAY 5
`define INP_CHANGE 10


module tb();
    reg inA;
    reg inB;
    wire outY;
    integer remainder;

    my_OR DUT(
                .in_a(inA),
                .in_b(inB),
                .out_y(outY)
             );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        remainder = `INP_CHANGE - `G_DELAY;
        $write("\n TIME(ns)  a  b  |  Y\n");
        $write(" ----------------------\n");

        inA = 1'b0; inB = 1'b0;
        $write(" %2t        %b  %b  |  %b    inputs changed\n",
            $time, inA, inB, outY);
        #`G_DELAY
        $write(" %2t        %b  %b  |  %b    gate delay complete\n", 
            $time, inA, inB, outY);
        #remainder
        $write(" %2t        %b  %b  |  %b    full cycle, inputs chaning...\n", 
            $time, inA, inB, outY);
        $write(" ----------------------\n");

        inA = 1'b0; inB = 1'b1;
        $write(" %2t        %b  %b  |  %b    inputs changed\n",
            $time, inA, inB, outY);
        #`G_DELAY
        $write(" %2t        %b  %b  |  %b    gate delay complete\n", 
            $time, inA, inB, outY);
        #remainder
        $write(" %2t        %b  %b  |  %b    full cycle, inputs chaning...\n", 
            $time, inA, inB, outY);
        $write(" ----------------------\n");
        
        inA = 1'b1; inB = 1'b0;
        $write(" %2t        %b  %b  |  %b    inputs changed\n",
            $time, inA, inB, outY);
        #`G_DELAY
        $write(" %2t        %b  %b  |  %b    gate delay complete\n", 
            $time, inA, inB, outY);
        #remainder
        $write(" %2t        %b  %b  |  %b    full cycle, inputs chaning...\n", 
            $time, inA, inB, outY);
        $write(" ----------------------\n");

        inA = 1'b1; inB = 1'b1;
        $write(" %2t        %b  %b  |  %b    inputs changed\n",
            $time, inA, inB, outY);
        #`G_DELAY
        $write(" %2t        %b  %b  |  %b    gate delay complete\n", 
            $time, inA, inB, outY);
        #remainder
        $write(" %2t        %b  %b  |  %b    full cycle, inputs chaning...\n", 
            $time, inA, inB, outY);
        $write(" ----------------------\n");

        #`INP_CHANGE
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~ \n\n");
        $finish;
    end

endmodule

////~~~~ OR gate


module my_OR (
                input wire in_a,
                input wire in_b,
                output wire out_y
             );
    assign #`G_DELAY out_y = in_a | in_b;
endmodule



////////~~~~~~~~END>  exp4a.v
