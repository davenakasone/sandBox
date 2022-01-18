/*
    applied to FPGA
    exp3
*/

`timescale 1ps/1ps
`define HALF 20
`define HALFFF 24999999
`define DEBUG -99


module tb();
    wire [6:0] seg2;
    wire [6:0] seg1;
    reg a_in;
    reg reset;
    reg clock;

    integer idx;
    integer idxc;

    topGen DUT (
                    .seg2(seg2),
                    .seg1(seg1),
                    .a_in(a_in),
                    .reset(reset),
                    .clock(clock)
                );
    
    always begin
        #1;
        clock = ~clock; 
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the sequence generator\n\n");
        $write("  A  | WXYZ\n");
        $write(" ----------\n");
        a_in = 1'b0;
        reset = 1'b0;
        clock = 1'b0;

        for (idx = 0; idx < 9; idx = idx + 1) begin
            #(`HALFFF + `HALF);
            dispR(seg1, seg2, a_in);
            #(`HALFFF - `HALF);
        end
        $write(" ----------\n");

        reset = 1'b1;
        #(`HALFFF + `HALFFF);
        reset = 1'b0;
        a_in = 1'b1;
        for (idx = 0; idx < 9; idx = idx + 1) begin
            #(`HALFFF + `HALF);
            dispR(seg1, seg2, a_in);
            #(`HALFFF - `HALF);
        end
          
        $write("\t\t\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task dispR;
        input [6:0] seg11;
        input [6:0] seg22;
        input regA;

        begin
            $write("  %1b  |  ", regA);
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
                    7'b1000_000 : $write("0\n");
                    7'b1111_001 : $write("1\n");
                    7'b0100_100 : $write("2\n");
                    7'b0110_000 : $write("3\n");
                    7'b0011_001 : $write("4\n");
                    7'b0010_010 : $write("5\n");
                    7'b0000_010 : $write("6\n");
                    7'b1111_000 : $write("7\n");
                    7'b0000_000 : $write("8\n");
                    7'b0011_000 : $write("9\n");
                    default :     $write("ERROR\n");
            endcase
        end
    endtask

endmodule


////~~~~ highest entity
module topGen (
                    output wire [6:0] seg2,
                    output wire [6:0] seg1,
                    input wire a_in,
                    input wire reset,
                    input wire clock
                );

    wire clk_trans;
    wire [3:0] temp;
    wire [3:0] onez;
    wire [3:0] tenz;

    clk_50MHz_to_1Hz CLK ( 
                            .clk_1hz(clk_trans),
                            .clk_50mhz(clock)
                        );
    
    seqGen SG (
                .wxyz(temp),
                .a_in(a_in),
                .reset(reset),
                .clock(clk_trans)
            );

    seg7_dig dig2 (
                    .cntl_4bit(tenz),
                    .disp_4bit(seg2)
                );
    
    seg7_dig dig1 (
                    .cntl_4bit(onez),
                    .disp_4bit(seg1)
                );

    my_bcd getDigs (
                        .tens(tenz),
                        .ones(onez),
                        .bin_in(temp)
                );
endmodule


////~~~~ module of focus
module seqGen (
                output reg [3:0] wxyz,
                input wire a_in,
                input wire reset,
                input wire clock
            );
    
    parameter s0 = 4'b0000;
    parameter s1 = 4'b0001;
    parameter s2 = 4'b0010;
    parameter s3 = 4'b0011;
    parameter s4 = 4'b0100;
    parameter s5 = 4'b0101;
    parameter s6 = 4'b0110;
    parameter s7 = 4'b0111;
    parameter s8 = 4'b1000;

    parameter clear = 4'b0000;
    parameter one = 4'b0001;
    parameter two = 4'b0010;
    parameter three = 4'b0011;
    parameter four = 4'b0100;
    parameter six = 4'b0110;
    parameter eight = 4'b1000;
    parameter nine = 4'b1001;
    parameter twelve = 4'b1100;

    reg [3:0] state;
    reg [3:0] n_state;

    initial begin
        state = s0;
        n_state = s0;
        wxyz = clear;
    end

    always @ (posedge clock) begin
        if (reset == 1'b1) begin
            state = s0;
            n_state = s0;
            wxyz = clear;
        end
        else begin
            case(state)
                s0 :
                    begin
                        wxyz = clear;
                        n_state = s1;
                    end
                s1 :
                    begin
                        wxyz = (a_in == 1'b0) ? eight : nine;
                        n_state = s2;
                    end
                s2 :
                    begin
                        wxyz = (a_in == 1'b0) ? twelve : one;
                        n_state = s3;
                    end
                s3 :
                    begin
                        wxyz = (a_in == 1'b0) ? four : three;
                        n_state = s4;
                    end
                s4 :
                    begin
                        wxyz = (a_in == 1'b0) ? six : two;
                        n_state = s5;
                    end
                s5 :
                    begin
                        wxyz = (a_in == 1'b0) ? two : six;
                        n_state = s6;
                    end
                s6 :
                    begin
                        wxyz = (a_in == 1'b0) ? three : four;
                        n_state = s7;
                    end
                s7 :
                    begin
                        wxyz = (a_in == 1'b0) ? one : twelve;
                        n_state = s8;
                    end
                s8 :
                    begin
                        wxyz = (a_in == 1'b0) ? nine : eight;
                        n_state = s1;
                    end
            endcase
            state = n_state;
        end
    end

endmodule


////~~~~ get the 2 decimal digits of 4-bit binary
module my_bcd ( 
                    output reg [3:0] tens,
                    output reg [3:0] ones,
                    input wire [3:0] bin_in
            );

    integer idx;

    always @ (bin_in) begin
        case(bin_in)
            4'b0000 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0000;
                end
            4'b0001 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0001;
                end
            4'b0010 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0010;
                end
            4'b0011 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0011;
                end
            4'b0100 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0100;
                end
            4'b0101 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0101;
                end
            4'b0110 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0110;
                end
            4'b0111 :
                begin
                    tens = 4'b0000;
                    ones = 4'b0111;
                end
            4'b1000 :
                begin
                    tens = 4'b0000;
                    ones = 4'b1000;
                end
            4'b1001 :
                begin
                    tens = 4'b0000;
                    ones = 4'b1001;
                end
            4'b1010 :
                begin
                    tens = 4'b0001;
                    ones = 4'b0000;
                end
            4'b1011 :
                begin
                    tens = 4'b0001;
                    ones = 4'b0001;
                end
            4'b1100 :
                begin
                    tens = 4'b0001;
                    ones = 4'b0010;
                end
            4'b1101 :
                begin
                    tens = 4'b0001;
                    ones = 4'b0011;
                end
            4'b1110 :
                begin
                    tens = 4'b0001;
                    ones = 4'b0100;
                end
            4'b1111 :
                begin
                    tens = 4'b0001;
                    ones = 4'b0101;
                end
        endcase
    end
endmodule


////~~~~  output to 7-segment display
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


////~~~~  slow the FPGA clock to 1 Hz
module clk_50MHz_to_1Hz ( 
                            output reg clk_1hz,
                            input wire clk_50mhz
                        );

    //reg [24:0] count;    
    integer count;

    initial begin
        //count <= 1'b0;
        count = 0;
        clk_1hz <= 1'b0;
    end

    // 24999999
    // 25'b1_0111_1101_0111_1000_0011_1111
    always @ (posedge clk_50mhz) begin
        if(count == 24999999) begin    
            count <= 0;
            clk_1hz <= ~clk_1hz;
        end
        else begin
            count <= count + 1;
        end
    end
endmodule


////////~~~~~~~~END>  seqGen.v
