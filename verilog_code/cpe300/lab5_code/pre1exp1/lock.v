/*
    FSM for lock
    no overlaps, must enter 110_110 in serial
    does everything on the clock
*/

`timescale 1ns/1ns
`define HALF 5
`define DEBUG -99


module tb();
    wire [6:0] seg_disp;
    reg reset;
    reg enter;
    reg in_0;
    reg in_1;
    reg clock;

    lock DUT (
                .seg_disp(seg_disp),
                .reset(reset),
                .enter(enter),
                .in_0(in_0),
                .in_1(in_1),
                .clock(clock)
            );
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $write("\n test the serial lock\n\n");
        $write(" st   nst  rst  ent  in1  in0  |   code\n");
        $write("------------------------------------\n");
        clock = 1'b0;
        reset = 1'b1;
        enter = 1'b0;    
        in_1 = 1'b0;
        in_0 = 1'b0;
        // combo:  xxx_xxx
        
        // s0 -> s1 
        #(`HALF - 3);    // 2
        reset = 1'b0;
        enter = 1'b1;    
        in_1 = 1'b1;
        in_0 = 1'b0;
        #(`HALF + 3);    // 10
        // combo:  1xx_xxx

        //s1 -> s2
        #(`HALF - 3);    // 12
        enter = 1'b0;    
        in_1 = 1'b1;
        in_0 = 1'b0;
        #(`HALF + 3);    // 20
        // combo:  11x_xxx

        //s2 -> s3
        #(`HALF - 3);    // 22
        enter = 1'b1;    
        in_1 = 1'b0;
        in_0 = 1'b1;
        #(`HALF + 3);    // 30
        // combo:  110_xxx

        //s3 -> s4
        #(`HALF - 3);    // 32
        enter = 1'b0;    
        in_1 = 1'b1;
        in_0 = 1'b0;
        #(`HALF + 3);    // 40
        // combo:  110_1xx

        //s4 -> s5
        #(`HALF - 3);    // 42
        enter = 1'b1;    
        in_1 = 1'b1;
        in_0 = 1'b0;
        #(`HALF + 3);    // 50
        // combo:  110_11x

        //s5 -> s6
        #(`HALF - 3);    // 52
        enter = 1'b0;    
        in_1 = 1'b0;
        in_0 = 1'b1;
        #(`HALF + 3);    // 60
        // combo:  110_110

        #(`HALF + `HALF);
        reset = 1'b1;
        #(`HALF + `HALF);
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~  %5t ns\n\n", $time);
        $finish;
    end

endmodule


////~~~~


module lock (
                output reg [6:0] seg_disp,
                input wire reset,
                input wire enter,
                input wire in_0,
                input wire in_1,
                input wire clock
            );
    
    parameter locked = 7'b1000_111;
    parameter unlocked = 7'b1000_001;
    parameter s0 = 3'b000;
    parameter s1 = 3'b001;
    parameter s2 = 3'b010;
    parameter s3 = 3'b011;
    parameter s4 = 3'b100;
    parameter s5 = 3'b101;
    parameter s6 = 3'b110;
    parameter combo = 6'b110_110;
    parameter clear = 6'bzzz_zzz;

    reg [2:0] state;
    reg [2:0] n_state;
    reg [5:0] tracker;

    initial begin
        seg_disp = locked;
        tracker = clear;
        state = s0;
        n_state = s0;
    end

    always @ (posedge clock) begin
        if (reset == 1'b1) begin
            seg_disp <= locked;
            tracker <= clear;
            state <= s0;
            n_state <= s0;
            `ifdef DEBUG
                #1;
                $write(" %3b  %3b   %1b    %1b    %1b    %1b   |  %3b_%3b    ",
                    state, n_state, reset, enter, in_1, in_0, tracker[5:3], tracker[2:0]);
                $write("locked...    %4t ns\n", $time);
            `endif
        end
        else begin
            case(state)
                s0 :
                    begin
                        if (enter == 1'b1 && in_1 == 1'b1  && in_0 == 1'b0) begin
                            n_state <= s1;
                            tracker[5] <= in_1;
                            seg_disp <= locked;
                        end
                        else begin
                            n_state <= s0;
                            tracker[5] <= 1'bz;
                            seg_disp <= locked;
                        end
                    end 
                s1 :
                    begin
                        if (enter == 1'b0 && in_1 == 1'b1  && in_0 == 1'b0) begin
                            n_state <= s2;
                            tracker[4] <= in_1;
                            seg_disp <= locked;
                        end
                        else begin
                            n_state = s1;
                            tracker[4] <= 1'bz;
                            seg_disp <= locked;
                        end
                    end 
                s2 :
                    begin
                        if (enter == 1'b1 && in_1 == 1'b0  && in_0 == 1'b1) begin
                            n_state <= s3;
                            tracker[3] <= ~in_0;
                            seg_disp <= locked;
                        end
                        else begin
                            n_state <= s2;
                            tracker[3] <= 1'bz;
                            seg_disp <= locked;
                        end
                    end 
                s3 :
                    begin
                        if (enter == 1'b0 && in_1 == 1'b1  && in_0 == 1'b0) begin
                            n_state <= s4;
                            tracker[2] <= in_1;
                            seg_disp <= locked;
                        end
                        else begin
                            n_state <= s3;
                            tracker[2] <= 1'bz;
                            seg_disp <= locked;
                        end
                    end 
                s4 :
                    begin
                        if (enter == 1'b1 && in_1 == 1'b1  && in_0 == 1'b0) begin
                            n_state <= s5;
                            tracker[1] <= in_1;
                            seg_disp <= locked;
                        end
                        else begin
                            n_state <= s4;
                            tracker[1] <= 1'bz;
                            seg_disp <= locked;
                        end
                    end 
                s5 :
                    begin
                        if (enter == 1'b0 && in_1 == 1'b0  && in_0 == 1'b1) begin
                            n_state <= s6;
                            tracker[0] <= ~in_0;
                            seg_disp <= unlocked;
                        end
                        else begin
                            n_state <= s5;
                            tracker[0] <= 1'bz;
                            seg_disp <= locked;
                        end
                    end 
                s6 : n_state = (reset == 1'b1) ? s0 : s6;
                default :
                    begin
                        state <= s0;
                        n_state <= s0;
                        seg_disp <= locked;
                        tracker <= clear;
                    end
            endcase
            `ifdef DEBUG
                #1;
                $write(" %3b  %3b   %1b    %1b    %1b    %1b   |  %3b_%3b    ",
                    state, n_state, reset, enter, in_1, in_0, tracker[5:3], tracker[2:0]);
                if (tracker == combo) $write("UNLOCKED     %4t ns\n", $time);
                else $write("locked...    %4t ns\n", $time);
            `endif
            state <= n_state;
        end
    end

endmodule


////////~~~~~~~~END>  lock.v
