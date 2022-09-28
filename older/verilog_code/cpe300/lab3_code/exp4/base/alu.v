/*
    the ALU, base model
        2* handles negative numbers
*/

`timescale 1ns/1ns
`define STEP 10
`define SEED 444
`define REP_PER_OP 4


module tb();
    wire [3:0] outY;
    wire outC;
    reg [2:0] sel;
    reg [3:0] inA;
    reg [3:0] inB;
    reg inC;

    integer seed;
    integer ii;
    integer jj;
    integer kk;

    myALU DUT (
                .out_y(outY),
                .out_c(outC),
                .selector(sel),
                .in_a(inA),
                .in_b(inB),
                .in_c(inC)
            );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        seed = `SEED;
        $write("\n testing the 4-bit unsinged ALU\n\n");
        $write(" a     b     cin  |  cout    Y\n");
        $write(" ------------------------------\n");


        for (ii = 0; ii < 8; ii = ii + 1) begin 
            sel = ii;
            for (jj = 0; jj < `REP_PER_OP; jj = jj + 1) begin
                getRand(inA, inB, inC);
                #`STEP;
                showResults(outY, outC, sel, inA, inB, inC);
            end
            $write(" ------------------------------\n");
        end

        #`STEP;
        $write("\n\n ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic getRand;
        output [3:0] out_A;
        output [3:0] out_B;
        output out_C;
        integer idx;
        begin
            out_C = $random(seed) % 2;
            for (idx = 0; idx < 4; idx = idx + 1) begin
                out_A[idx] = $random(seed) % 2;
                out_B[idx] = $random(seed) % 2;
            end
        end
    endtask

    task automatic showResults;
        input [3:0] outYY;
        input outCC;
        input [2:0] sell;
        input [3:0] inAA;
        input [3:0] inBB;
        input inCC;

        reg [4:0] checker;
        integer tempA;
        integer tempB;
        integer tempC;
        integer tempRes;

        begin
            tempA = inAA;
            tempB = inBB;
            tempC = inCC;
            case(sell)
                3'b000 :
                    begin
                        checker = inAA + 1'b1;
                        tempRes = tempA + 1;
                        if (checker[4] == outCC && checker[3:0] == outYY) begin
                            $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                                inAA, inBB, inCC, outCC, outYY);
                            $write("%2d + 1 =  %2d  <>  %3b increment\n", 
                                tempA, tempRes, sell);
                        end
                        else begin
                            $write(" ERROR\n");
                        end
                    end
                3'b001 :
                    begin
                        tempRes = tempA - 1;
                        if (inA == 4'b0000 && outCC != 1'b1) begin
                            $write(" ERROR\n");
                        end
                        else begin
                           $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                                inAA, inBB, inCC, outCC, outYY);
                            $write("%2d - 1 =  %2d  <>  %3b decrement\n", 
                                tempA, tempRes, sell); 
                        end
                    end
                3'b010 :
                    begin
                        $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                            inAA, inBB, inCC, outCC, outYY);
                        $write("<>  %3b rotate right\n", 
                            sell);
                    end
                3'b011 :
                    begin
                        $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                            inAA, inBB, inCC, outCC, outYY);
                        $write("<>  %3b shift right\n", 
                            sell);
                    end
                3'b100 :
                    begin
                        $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                            inAA, inBB, inCC, outCC, outYY);
                        $write("<>  %3b AND\n", 
                            sell);
                    end
                3'b101 :
                    begin
                        $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                            inAA, inBB, inCC, outCC, outYY);
                        $write("<>  %3b OR\n", 
                            sell);
                    end
                3'b110 :
                    begin
                        tempRes = tempA + tempB + tempC;
                        if (tempRes > 15 && outCC != 1'b1) begin
                            $write(" ERROR\n");
                        end
                        else begin
                            $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                                inAA, inBB, inCC, outCC, outYY);
                            $write("%2d + %2d + %1d =  %2d  <>  %3b addition\n", 
                                tempA, tempB, tempC, tempRes, sell); 
                        end
                    end
                3'b111 :
                    begin
                        tempRes = tempA - tempB - tempC;
                        if (tempRes < 0 && outCC != 1'b1) begin
                            $write(" ERROR\n");
                        end
                        else begin
                            $write(" %4b  %4b  %1b    |  %1b    %4b  ,  ",
                                inAA, inBB, inCC, outCC, outYY);
                            $write("%2d - %2d - %1d =  %2d  <>  %3b subtraction\n", 
                                tempA, tempB, tempC, tempRes, sell); 
                        end
                    end
            endcase
        end
    endtask

endmodule


////~~~~


module myALU (
                output reg [3:0] out_y,
                output reg out_c,
                input wire [2:0] selector,
                input wire [3:0] in_a,
                input wire [3:0] in_b,
                input wire in_c
            );

    reg [6:0] catch;

    always @ (*) begin
        out_c = 1'b0;
        case (selector)
            3'b000 : 
                begin    // increment
                    catch = in_a + 1'b1;
                    out_y = catch[3:0];
                    out_c = catch[4];
                end
            3'b001 : 
                begin    // decrement
                    if (in_a == 4'b0000) begin
                        out_c = 1'b1;
                        out_y = 4'b0001;
                    end
                    else begin
                        out_y = in_a - 1'b1;
                    end
                end
            3'b010 :  
                begin    // rotate right
                    out_y = {in_a[2:0], in_a[3]};
                end
            3'b011 :
                begin    // shift right
                    out_y = in_a >> 1;
                end
            3'b100 : 
                begin    // AND
                    out_y = in_a & in_b;
                end
            3'b101 :
                begin    // OR
                    out_y = in_a | in_b;
                end
            3'b110 :
                begin    // Add
                    catch = in_a + in_b + in_c;
                    out_y = catch[3:0];
                    out_c = catch[4];
                end
            3'b111 :
                begin
                    catch = in_a - in_b - in_c;
                    if (catch[6] == 1'b1) begin
                        catch = catch - 1'b1;
                        catch = ~ catch;
                        out_y = catch [3:0];
                        out_c = 1'b1;
                    end
                    else begin
                        out_y = catch[3:0];
                    end
                end
        endcase

    end
endmodule


////////~~~~~~~~END>  alu.v
