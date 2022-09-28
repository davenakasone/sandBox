/*
    5-bit, mod25 counter
*/

`timescale 1ns/1ns

`define TEST_10 66    //~~~~{on|off}  comment out to test "15"

`define HALF 5
`define T15 15   //  15{->25->0}  
`define T10 10   //  10{->0->25}
`define SEED 987
`define DEBUG -111
`define REP10 36
`define REP15 36

module tb();
    wire [4:0] count;
    reg [4:0] n_in;
    reg start;
    reg restart;
    reg up_count;
    reg clock;

    integer idx;

    control_unit CU(
                        .count(count),
                        .n_in(n_in),
                        .start(start),
                        .restart(restart),
                        .up_count(up_count),
                        .clock(clock)
                );

    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the counter %% 25\n\n");
        $write(" st  Nst  Up  strt  rstrt  n=0  n=25  |  count\n");
        $write(" ----------------------------------------------\n");
        clock = 1'b0;

        `ifdef TEST_10
            n_in = `T10;
            start = 1'b1;
            restart = 1'b0;
            up_count = 1'b0;
            for (idx = 0; idx < `REP10; idx = idx + 1) begin
                #(2 * `HALF);
            end
        `else
            n_in = `T15;
            start = 1'b1;
            restart = 1'b0;
            up_count = 1'b1;
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

endmodule


////~~~~


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


////////~~~~~~~~END>  base.v
