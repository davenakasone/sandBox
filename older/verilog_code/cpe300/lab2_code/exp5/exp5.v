/*
    8-bit addition, unsigned only
    A + B = Y
*/

`timescale 1ns/1ns
`define REPZ 6
`define STEP 5


module tb();
    reg [7:0] inA;
    reg [7:0] inB;
    wire [8:0] outY;

    integer decA;
    integer decB;
    integer idx;
    integer idxx;

    add8 DUT (
                .in_a(inA),
                .in_b(inB),
                .out_y(outY)
            );

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n8-bit unsigned addition  ,  %d tests\n\n", `REPZ);
        //$write(" A          B         |    Y    \n");
        //$write(" -----------------------------------\n");

        for (idx = 0; idx < `REPZ; idx = idx + 1) begin
            for (idxx = 0; idxx < 8; idxx = idxx + 1) begin
                inA[idxx] = $random % 2;
                inB[idxx] = $random % 2;
            end
            decA = inA;
            decB = inB;
            #`STEP

            $write(" A:    %4b_%4b\n", inA[7:4], inA[3:0]);
            $write(" B:    %4b_%4b\n", inB[7:4], inB[3:0]);
            $write(" ----------------\n");
            $write(" Y:  %1b_%4b_%4b", outY[8], outY[7:4], outY[3:0]);
            $write("     %3d + %3d = %3d\n\n", decA, decB, decA+decB);
        end

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
    end
endmodule


////~~~~ adder


module add8 (
                input wire [7:0] in_a,
                input wire [7:0] in_b,
                output reg [8:0] out_y
            );
    always @ (*) begin
        out_y = in_a + in_b;
    end
endmodule


////////~~~~~~~~END>  exp5.v
