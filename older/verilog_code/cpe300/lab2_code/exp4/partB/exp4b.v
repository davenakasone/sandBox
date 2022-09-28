/*
    OR gate w/ 5ns delay
    input state changes every 10ns
*/

`timescale 1ns/1ns
`define G_DELAY 5
`define INP_CHANGE 2


module tb();
    reg inA;
    reg inB;
    wire outY;

    my_OR DUT(
                .in_a(inA),
                .in_b(inB),
                .out_y(outY)
             );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n TIME(ns)  a  b  |  Y\n");
        $write(" ----------------------\n");

        inA = 1'b0; inB = 1'b0;
        #`INP_CHANGE

        inA = 1'b0; inB = 1'b1;
        #`INP_CHANGE

        inA = 1'b1; inB = 1'b0;
        #`INP_CHANGE

        inA = 1'b1; inB = 1'b1;
        #`INP_CHANGE

        #(`G_DELAY*2)
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~ \n\n");
        $finish;
    end

    always @ (inA or inB or outY) begin
        $write(" %2t        %b  %b  |  %b    value changed\n",
            $time, inA, inB, outY);
    end

endmodule

////~~~~ OR gate


module my_OR (
                input wire in_a,
                input wire in_b,
                output wire out_y
                //output reg out_y
             );

    assign #`G_DELAY out_y = in_a | in_b;
    /*       
    always @ (*) begin
       #`G_DELAY 
       out_y = in_a | in_b; 
    end
    */
endmodule



////////~~~~~~~~END>  exp4a.v
