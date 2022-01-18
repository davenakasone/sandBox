/*
    5-bit, mod25 counter, 7-seg + 1 Hz clock
*/

`timescale 1ns/1ns

`define TEST_10 66    //~~~~{on|off}  comment out to test "15"

`define HALF 24999999
`define T15 15   //  15{->25->0}  
`define T10 10   //  10{->0->25}
`define SEED 987
//`define DEBUG -111
`define REP10 36
`define REP15 36


module tb();
    wire [6:0] seg2;
    wire [6:0] seg1;
    reg [4:0] n_in;
    reg start;
    reg restart;
    reg upc;
    reg clock;

    integer idx;
    integer ic;
    integer dig2;
    integer dig1;

    total DUT (
                .digit_2(seg2),
                .digit_1(seg1),
                .n_in(n_in),
                .start(start),
                .restart(restart),
                .up(upc),
                .clk(clock)
            );

    always begin
        for (ic = 0; ic < `HALF; ic = ic + 1) begin
           #1;
            clock = ~clock; 
        end
    end

    initial begin
        //$dumpfile("wave.vcd");
        //$dumpvars(0, tb);
        $write("\n test the counter %% 25\n\n");
        //$write(" st  Nst  Up  strt  rstrt  n=0  n=25  |  count\n");
        //$write(" ----------------------------------------------\n");
        clock = 1'b0;

        `ifdef TEST_10
            n_in = `T10;
            start = 1'b1;
            restart = 1'b0;
            upc = 1'b0;
            for (idx = 0; idx < `REP10; idx = idx + 1) begin
                #(2 * `HALF);
                bcd2digs(seg2, seg1, dig2, dig1);
                $write("%1d%1d\n", dig2, dig1);
            end
        `else
            n_in = `T15;
            start = 1'b1;
            restart = 1'b0;
            upc = 1'b1;
            for (idx = 0; idx < `REP15; idx = idx + 1) begin
                #(2 * `HALF);
            end
        `endif 

        restart = 1'b1;
        #`HALF;
        #2;
        $write("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %4t  ns\n\n", $time);
        $finish;
    end 

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


////~~~~  combines all
module total (
                output wire [6:0] digit_2,
                output wire [6:0] digit_1,
                input wire [4:0] n_in,
                input wire start,
                input wire restart,
                input wire up,
                input wire clk
            );
    
    wire clk_trans;
    wire [4:0] temp;
    wire [3:0] onez;
    wire [3:0] tenz;

    clk_50MHz_to_1Hz CLK ( 
                            .clk_1hz(clk_trans),
                            .clk_50mhz(clk)
                        );

    control_unit CU (
                        .count(temp),
                        .n_in(n_in),
                        .start(start),
                        .restart(restart),
                        .up_count(up),
                        .clock(clk_trans)
                    );

    seg7_dig dig2 (
                    .cntl_4bit(tenz),
                    .disp_4bit(digit_2)
                );
    
    seg7_dig dig1 (
                    .cntl_4bit(onez),
                    .disp_4bit(digit_1)
                );

    my_bcd getDigs (
                        .tens(tenz),
                        .ones(onez),
                        .bin_in(temp)
                );
endmodule


////~~~~  main circuit
module control_unit (
                        output reg [4:0] count,
                        input wire [4:0] n_in,
                        input wire start,
                        input wire restart,
                        input wire up_count,
                        input wire clock
                );
    
    wire n_is_0;
    wire n_is_25;
    assign n_is_0 = (count == 5'b0000_0);
    assign n_is_25 = (count == 5'b1100_1);

    reg [1:0] state;
    reg [1:0] next_state;
    parameter s0 = 2'b00;
    parameter s1 = 2'b01;
    parameter s2 = 2'b10;
    parameter s3 = 2'b11;

    initial begin
        state = s0;
        next_state = s0;
        count = 5'b0000_0;
    end

    always @ (posedge clock or restart) begin
        if (restart == 1'b1) begin
            state = s0;
            next_state = s0;
            count = 5'b0000_0;
        end
        else begin
            case (next_state)
                s0 : 
                    begin
                        state = next_state;
                        next_state = (start == 1'b1) ? s1 : s0;
                    end
                s1 :
                    begin
                        state = next_state;
                        count = n_in;
                        if (up_count == 1'b1) begin
                            next_state = (n_is_25 == 1'b1) ? s3 : s2;
                        end
                        else begin
                            next_state = (n_is_0 == 1'b1) ? s2 : s3;
                        end
                    end
                s2 : 
                    begin
                        state = next_state;
                        count = count + 1'b1;
                        next_state = (n_is_25 == 1'b1) ? s3 : s2;
                    end
                s3 : 
                    begin
                        state = next_state;
                        count = count - 1'b1;
                        next_state = (n_is_0 == 1'b1) ? s2 : s3;
                    end
                default : next_state = s0;
            endcase 
        end
    end

    always @ (posedge clock) begin
        `ifdef DEBUG
            #1;
            $write(" %2b  %2b    %1b    %1b      %1b    %1b    %1b    |  %5b     \"%3d \"   {%4t  ns}\n", 
                state, next_state, up_count, start, restart, n_is_0, n_is_25, count, count, $time);
        `endif
    end
endmodule


////~~~~  slow the FPGA clock to 1 Hz
module clk_50MHz_to_1Hz ( 
                            output reg clk_1hz,
                            input wire clk_50mhz
                        );

    reg [24:0] count;    

    initial begin
        count <= 1'b0;
        clk_1hz <= 1'b0;
    end

    always @ (posedge clk_50mhz) begin
        if(count == 25'b1011111010111100000111111) begin
            count <= 0;
            clk_1hz <= ~clk_1hz;
        end
        else begin
            count <= count + 1;
        end
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


////////~~~~~~~~END>  total.v
