/*
    4-bit RCA by 4x inst of FA
        unsinged w/ Cout
    
    made for output to x2 7-seg displays

    test 3+5, 8+7, 15+1, 11+11
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    wire [6:0] seg2;
    wire [6:0] seg1;
    reg [3:0] inA;
    reg [3:0] inB;
    reg inC;

    topMod DUT (
                    .disp2(seg2),
                    .disp1(seg1),
                    .inpA(inA),
                    .inpB(inB),
                    .Cin(inC)
            );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        inC = 1'b0;
        $write("\n test the RCA, Cin = %1b  ,  no carry in\n\n", inC);

        inA = 4'b0011;
        inB = 4'b0101;
        #`STEP
        disp(seg2, seg1, inA, inB, inC);

        inA = 4'b1000;
        inB = 4'b0111;
        #`STEP
        disp(seg2, seg1, inA, inB, inC);

        inA = 4'b1111;
        inB = 4'b0001;
        #`STEP
        disp(seg2, seg1, inA, inB, inC);

        inA = 4'b1011;
        inB = 4'b1011;
        #`STEP
        disp(seg2, seg1, inA, inB, inC);

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic disp;
        input [6:0] seg22;
        input [6:0] seg11;
        input [3:0] inAA;
        input [3:0] inBB;
        input inCC;

        reg outC;
        reg [3:0] outY;
        integer intA;
        integer intB;
        integer outp;

        begin
            {outC, outY} = inAA + inBB + inCC;
            intA = inAA;
            intB = inBB;
            outp = inAA + inBB;
            
            $write("    %1b       c_in\n", inCC);
            $write("    %4b    A\n", inAA);
            $write(" +  %4b    B\n", inBB);
            $write("--------------\n");
            $write("  %1b_%4b    Cout, Y\n", outC, outY);
            $write("                    ----> %2d + %2d =  ", intA, intB);

            case(seg22)
                    7'b1000_000 : $write("0");
                    7'b1111_001 : $write("1");
                    7'b0100_100 : $write("2");
                    7'b0110_000 : $write("3");
                    7'b0011_001 : $write("4");
                    7'b0010_010 : $write("5");
                    7'b0000_010 : $write("6");
                    7'b1111_000 : $write("7");
                    7'b0000_000 : $write("8");
                    7'b0011_000 : $write("9");
                    default :     $write("ERROR");
            endcase
            case(seg11)
                    7'b1000_000 : $write("0\n\n");
                    7'b1111_001 : $write("1\n\n");
                    7'b0100_100 : $write("2\n\n");
                    7'b0110_000 : $write("3\n\n");
                    7'b0011_001 : $write("4\n\n");
                    7'b0010_010 : $write("5\n\n");
                    7'b0000_010 : $write("6\n\n");
                    7'b1111_000 : $write("7\n\n");
                    7'b0000_000 : $write("8\n\n");
                    7'b0011_000 : $write("9\n\n");
                    default :     $write("ERROR\n\n");
            endcase
        end
    endtask   
endmodule


////~~~~ top module, for using x2 7-segment displays


module topMod (
                    output wire [6:0] disp2,
                    output wire [6:0] disp1,
                    input wire [3:0] inpA,
                    input wire [3:0] inpB,
                    input wire Cin
            );
    wire [4:0] temp;
    wire [3:0] onez;
    wire [3:0] tenz;

    rca4bit adder (
                    .out_y(temp[3:0]),
                    .out_c(temp[4]),
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


////~~~~ single digit 7-segment display


module seg7_dig(
                input wire [3:0] cntl_4bit,
                output reg [6:0] disp_4bit
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


////////~~~~~~~~END>  ader7.v
