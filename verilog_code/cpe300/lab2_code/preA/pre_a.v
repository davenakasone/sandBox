/*
    preLab circuit A
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    reg inA;
    reg inB;
    reg inC;
    wire outX;
    wire outY;
    integer idx;
    reg [2:0] trans;

    f1 DUT (
            .out_x(outX),
            .out_y(outY),
            .in_a(inA),
            .in_b(inB),
            .in_c(inC)
           );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\npre-lab A results:\n\n");
        $write(" a  b  c  |  X  Y\n");
        $write("----------------------\n");

        for (idx = 0; idx < 8; idx = idx + 1) begin
            trans = idx;
            inA = trans[2];
            inB = trans[1];
            inC = trans[0];
            #`STEP
            $write(" %b  %b  %b  |  %b  %b\n",
                inA, inB, inC, outX, outY);
        end 
        # `STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


module f1 (
            output wire out_x,
            output wire out_y,
            input wire in_a,
            input wire in_b,
            input wire in_c
          );
    wire t1;
    wire t2;

    xnor g1(t1, in_a, in_b);
    not g2(out_x, t1);
    and g3(t2, out_x, in_c);
    or g4(out_y, t2, in_b);
endmodule

////////~~~~~~~~END>  pre_a.v
