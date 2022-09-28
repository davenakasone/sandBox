/*
    the ALU, base model
        2* handles negative numbers
    unsinged, for 7segment x2 digit
*/

`timescale 1ns/1ns
`define STEP 10
`define SEED 444
`define REP_PER_OP 4


module tb();
    wire [6:0] segSign;
    wire [6:0] seg2;
    wire [6:0] seg1;
    reg [2:0] sel;
    reg [3:0] inA;
    reg [3:0] inB;
    reg inC;

    integer seed;
    integer ii;
    integer jj;
    integer kk;

    topMod DUT (
                    .dispSign(segSign),
                    .disp2(seg2),
                    .disp1(seg1),
                    .operate(sel),
                    .inpA(inA),
                    .inpB(inB),
                    .Cin(inC)
            );
    
    initial begin
        seed = `SEED;
        $write("\n testing the 4-bit unsinged ALU\n\n");
        $write(" a     b     cin  |  result\n");
        $write(" ---------------------------\n");


        for (ii = 0; ii < 8; ii = ii + 1) begin 
            sel = ii;
            for (jj = 0; jj < `REP_PER_OP; jj = jj + 1) begin
                getRand(inA, inB, inC);
                #`STEP;
                showResults(segSign, seg2, seg1, sel, inA, inB, inC);
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
        input [6:0] seg_s;
        input [6:0] seg_2;
        input [6:0] seg_1;
        input [2:0] sell;
        input [3:0] inAA;
        input [3:0] inBB;
        input inCC;

        integer d2;
        integer d1;
        integer tempA;
        integer tempB;
        integer tempC;
        integer tempRes;
        
        begin
            tempA = inAA;
            tempB = inBB;
            tempC = inCC;
            bcd2digs(seg_2, seg_1, d2, d1);
    
            case(sell)
                3'b000 :
                    begin
                        tempRes = tempA + 1;
                        if (seg_s == 7'b1111_110) begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  OVERFLOW  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d + 1 =  %2d  <>  %3b increment\n", 
                                tempA, tempRes, sell);
                        end
                        else begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d + 1 =  %2d  <>  %3b increment\n", 
                                tempA, tempRes, sell);
                        end
                    end
                3'b001 :
                    begin
                        tempRes = tempA - 1;
                        if (seg_s == 7'b0111_111) begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  NEGATIVE  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d - 1 =  %2d  <>  %3b decrement\n", 
                                tempA, tempRes, sell);
                        end
                        else begin
                           $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d - 1 =  %2d  <>  %3b decrement\n", 
                                tempA, tempRes, sell);
                        end
                    end
                3'b010 :
                    begin
                        $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                            inAA, inBB, inCC, d2, d1);
                        $write("<>  %3b rotate right\n", 
                            sell);
                    end
                3'b011 :
                    begin
                        $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                            inAA, inBB, inCC, d2, d1);
                        $write("<>  %3b shift right\n", 
                            sell);
                    end
                3'b100 :
                    begin
                        $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                            inAA, inBB, inCC, d2, d1);
                        $write("<>  %3b AND\n", 
                            sell);
                    end
                3'b101 :
                    begin
                        $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                            inAA, inBB, inCC, d2, d1);
                        $write("<>  %3b OR\n", 
                            sell);
                    end
                3'b110 :
                    begin
                        tempRes = tempA + tempB + tempC;
                        if (seg_s == 7'b1111_110) begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  OVERFLOW  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d + %2d + %1d =  %2d  <>  %3b addition\n", 
                                tempA, tempB, tempC, tempRes, sell); 
                        end
                        else begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d + %2d + %1d =  %2d  <>  %3b addition\n", 
                                tempA, tempB, tempC, tempRes, sell); 
                        end
                    end
                3'b111 :
                    begin
                        tempRes = tempA - tempB - tempC;
                        if (seg_s == 7'b0111_111) begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  NEGATIVE  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d - %2d - %1d =  %2d  <>  %3b subtraction\n", 
                                tempA, tempB, tempC, tempRes, sell); 
                        end
                        else begin
                            $write(" %4b  %4b  %1b    |    %1d%1d  ,  ",
                                inAA, inBB, inCC, d2, d1);
                            $write("%2d - %2d - %1d =  %2d  <>  %3b subtraction\n", 
                                tempA, tempB, tempC, tempRes, sell); 
                        end
                    end
            endcase
        end
    endtask

    task automatic bcd2digs;
        input [6:0] seg22;
        input [6:0] seg11;
        output integer d2;
        output integer d1;

        begin
            case(seg22)
                    7'b1000_000 : d2 = 0;
                    7'b1111_001 : d2 = 1;
                    7'b0100_100 : d2 = 2;
                    7'b0110_000 : d2 = 3;
                    7'b0011_001 : d2 = 4;
                    7'b0010_010 : d2 = 5;
                    7'b0000_010 : d2 = 6;
                    7'b1111_000 : d2 = 7;
                    7'b0000_000 : d2 = 8;
                    7'b0011_000 : d2 = 9;
                    default :     d2 = -999;
            endcase
            case(seg11)
                    7'b1000_000 : d1 = 0;
                    7'b1111_001 : d1 = 1;
                    7'b0100_100 : d1 = 2;
                    7'b0110_000 : d1 = 3;
                    7'b0011_001 : d1 = 4;
                    7'b0010_010 : d1 = 5;
                    7'b0000_010 : d1 = 6;
                    7'b1111_000 : d1 = 7;
                    7'b0000_000 : d1 = 8;
                    7'b0011_000 : d1 = 9;
                    default :     d1 = -999;
            endcase
        end
    endtask
endmodule


////~~~~


module topMod (
                    output wire [6:0] dispSign,
                    output wire [6:0] disp2,
                    output wire [6:0] disp1,
                    input wire [2:0] operate,
                    input wire [3:0] inpA,
                    input wire [3:0] inpB,
                    input wire Cin
            );
    wire [4:0] temp;
    wire [3:0] onez;
    wire [3:0] tenz;

    myALU alu (
                .out_y(temp),
                .d_sin(dispSign),
                .selector(operate),
                .in_a(inpA),
                .in_b(inpB),
                .in_c(Cin)
            );

    my_bcd getDigs (
                        .tens(tenz),
                        .ones(onez),
                        .bin_in(temp)
                );
    
    seg7_dig dig2 (
                    .cntl_4bit(tenz),
                    .disp_4bit(disp2)
                );
    
    seg7_dig dig1 (
                    .cntl_4bit(onez),
                    .disp_4bit(disp1)
                );
endmodule


////~~~~


module myALU (
                output reg [4:0] out_y,
                output reg [6:0] d_sin,
                input wire [2:0] selector,
                input wire [3:0] in_a,
                input wire [3:0] in_b,
                input wire in_c
            );

    reg [4:0] catch;

    always @ (*) begin
        d_sin = 7'b1111_111;
        case (selector)
            3'b000 : 
                begin    // increment
                    out_y = in_a + 1'b1;
                    if (out_y[4] == 1'b1) begin
                        d_sin = 7'b1111_110;  // overflow
                    end
                end
            3'b001 : 
                begin    // decrement
                    
                    if (in_a == 4'b0000) begin
                        d_sin = 7'b0111_111; // negative
                        out_y = 5'b0000_1;
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
                    out_y  = in_a + in_b + in_c;
                    if (out_y[4] == 1'b1) begin
                        d_sin = 7'b1111_110;  // overflow
                    end
                end
            3'b111 :
                begin
                    catch = in_a - in_b - in_c;
                    if (catch[4] == 1'b1 ) begin
                        catch = catch - 1'b1;
                        catch = ~ catch;
                        out_y = catch;
                        d_sin = 7'b0111_111; // negative
                    end
                    else begin
                        out_y = catch[3:0];
                    end
                end
        endcase

    end
endmodule


////~~~~


module seg7_dig(
                    output reg [6:0] disp_4bit,
                    input wire [3:0] cntl_4bit
                );

    parameter ON = 1'b0;
    parameter OFF = 1'b1;

    always @ (*) begin
        disp_4bit = {7{OFF}};
        case (cntl_4bit)
            4'b0000 : disp_4bit[5:0] = {6{ON}};
            4'b0001 : disp_4bit[2:1] = {2{ON}};
            4'b0010 :
                begin
                    disp_4bit[1:0] = {2{ON}};
                    disp_4bit[6] = ON;
                    disp_4bit[4:3] = {2{ON}};
                end
            4'b0011 :
                begin
                    disp_4bit[3:0] = {4{ON}};
                    disp_4bit[6] = ON;
                end
            4'b0100 :
                begin
                    disp_4bit[2:1] = {2{ON}};
                    disp_4bit[6:5] = {2{ON}};
                end 
            4'b0101 :
                begin
                    disp_4bit[0] = ON;
                    disp_4bit[3:2] = {2{ON}};
                    disp_4bit[6:5] = {2{ON}};
                end
            4'b0110 :
                begin
                    disp_4bit[0] = ON;
                    disp_4bit[6:2] = {5{ON}};
                end
            4'b0111 : disp_4bit[2:0] = {3{ON}};
            4'b1000 : disp_4bit[6:0] = {7{ON}};
            4'b1001 :
                begin
                    disp_4bit[6:0] = {7{ON}};
                    disp_4bit[4:3] = {2{OFF}};
                end
        endcase
    end
endmodule


////~~~~ get the 2 decimal digits of 5-bit binary


module my_bcd ( 
                    output reg [3:0] tens,
                    output reg [3:0] ones,
                    input wire [4:0] bin_in
            );

    integer idx;

    always @ (bin_in) begin
        tens = 4'b0000;
        ones = 4'b0000;
        for (idx = 4; idx >= 0; idx = idx - 1) begin
            if (tens >= 3'b101) tens = tens + 2'b11;
            if (ones >= 3'b101) ones = ones + 2'b11;
            tens = tens << 1;
            tens[0] = ones[3];
            ones = ones << 1;
            ones[0] = bin_in[idx];
        end
    end
endmodule


////////~~~~~~~~END>  alu7.v




