/*
    1-bit to 1-bit comparator
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    reg inA;
    reg inB;
    wire [0:2] outY;

    comp11 DUT (
                    .in_a(inA),
                    .in_b(inB),
                    .out_y(outY)
                );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\ntest 1 to 1 comparator\n\n");
        $write(" a  b  |  a<b  a=b  a>b\n");
        $write("------------------------\n");

        inA = 1'b0; inB = 1'b0;
        #`STEP
        $write(" %b  %b  |   %b    %b    %b\n", 
            inA, inB, outY[0], outY[1], outY[2]);
        
        inA = 1'b0; inB = 1'b1;
        #`STEP
        $write(" %b  %b  |   %b    %b    %b\n", 
            inA, inB, outY[0], outY[1], outY[2]);
        
        inA = 1'b1; inB = 1'b0;
        #`STEP
        $write(" %b  %b  |   %b    %b    %b\n", 
            inA, inB, outY[0], outY[1], outY[2]);
        
        inA = 1'b1; inB = 1'b1;
        #`STEP
        $write(" %b  %b  |   %b    %b    %b\n", 
            inA, inB, outY[0], outY[1], outY[2]);

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~ \n\n");
        $finish;
    end
endmodule


////~~~~


module comp11 (
                input wire in_a,
                input wire in_b,
                output reg [0:2] out_y
              );
    always @ (*) begin
        out_y = 3'b000;
        if (in_a < in_b)  out_y[0] = 1'b1;
        if (in_a == in_b) out_y[1] = 1'b1;
        if (in_a > in_b)  out_y[2] = 1'b1;
    end
endmodule


////////~~~~~~~~END>  pre2.v
