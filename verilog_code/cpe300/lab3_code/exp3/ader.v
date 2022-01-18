/*
    4-bit RCA by 4x inst of FA
        unsinged w/ Cout
*/

`timescale 1ns/1ns
`define STEP 10
//`define TEST_ALL -22  // test everything
`define TEST_LAB 22   // test 3+5, 8+7, 15+1, 11+11


module tb();
    reg [3:0] inA;
    reg [3:0] inB;
    reg inC;
    wire [3:0] outY;
    wire outC;

    integer ii;
    integer jj;

    rca4bit DUT (
                    .out_y(outY),
                    .out_c(outC),
                    .in_a(inA),
                    .in_b(inB),
                    .in_c(inC)
            );
    
    initial begin
        `ifdef TEST_LAB
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
            inC = 1'b0;
            $write("\n test the RCA, Cin = %1b  ,  no carry in\n\n", inC);
            $write(" a     b    cin |  cout   sum\n");
            $write(" ------------------------------\n");

            inA = 4'b0011;
            inB = 4'b0101;
            #`STEP
            disp(inA, inB, inC, outY, outC);

            inA = 4'b1000;
            inB = 4'b0111;
            #`STEP
            disp(inA, inB, inC, outY, outC);

            inA = 4'b1111;
            inB = 4'b0001;
            #`STEP
            disp(inA, inB, inC, outY, outC);

            inA = 4'b1011;
            inB = 4'b1011;
            #`STEP
            disp(inA, inB, inC, outY, outC);
        `endif

        `ifdef TEST_ALL
            inC = 1'b0;
            $write("\n test the RCA, Cin = %1b  ,  no carry in\n\n", inC);
            $write(" a     b    cin |  cout   sum\n");
            $write(" ------------------------------\n");
            for (ii = 0; ii < 16; ii = ii + 1) begin
                inA = ii;
                for (jj = 0; jj < 16; jj = jj + 1) begin
                    inB = jj;
                    #`STEP
                    disp(inA, inB, inC, outY, outC);
                end
                $write(" ------------------------------\n");
            end
        `endif

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task disp;
        input [3:0] regA;
        input [3:0] regB;
        input carIn;
        input [3:0] outp;
        input carOut;

        integer intA;
        integer intB;
        integer intY;
        reg [4:0] throw;
        integer catch;

        begin
            intA = regA;
            intB = regB;
            intY = intA + intB;
            throw = regA + regB + carIn;
            catch = throw;
        
            if (throw[3:0] != outp || 
                throw[4] != carOut || 
                intY != catch       ) begin
                    $write("\n\t!!! ERROR !!!\n");
            end
            else begin
                if (carOut == 1'b0) begin
                    $write(" %4b  %4b  %1b  |   %1b     %4b  ,    %2d + %2d = %2d    no Cout\n",
                        regA, regB, carIn, carOut, outp, intA, intB, intY);
                end
                else begin
                    $write(" %4b  %4b  %1b  |   %1b     %4b  ,    %2d + %2d = %2d    with Cout\n",
                        regA, regB, carIn, carOut, outp, intA, intB, intY);
                end
            end
        end
    endtask

endmodule


////~~~~ ripple carry adder, 4-bit


module rca4bit (
                output [3:0] out_y,
                output out_c,
                input [3:0] in_a,
                input [3:0] in_b,
                input in_c
            );

    wire co_0;
    wire co_1;
    wire co_2;
    
    fa1bit fa_0(out_y[0], co_0   , in_a[0], in_b[0], in_c);
    fa1bit fa_1(out_y[1], co_1   , in_a[1], in_b[1], co_0);
    fa1bit fa_2(out_y[2], co_2   , in_a[2], in_b[2], co_1);
    fa1bit fa_3(out_y[3], out_c  , in_a[3], in_b[3], co_2);
endmodule


////~~~~ full adder, 1-bit


module fa1bit (
                output out_y,
                output out_c,
                input in_a,
                input in_b,
                input in_c
            );

    assign out_y = (in_a ^ in_b) ^ in_c;
    assign out_c = (in_a & in_b) | (in_a & in_c) | (in_b & in_c);
endmodule


////////~~~~~~~~END>  ader.v




