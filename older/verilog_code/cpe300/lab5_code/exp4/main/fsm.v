/*
    a custom FSM that collects input in 8 cycles
*/

`timescale 1ns/1ns
`define HALF 5
`define REPS 11

module tb();
    wire shift_en;
    wire data_rdy;
    wire cntr_rstN;
    reg serial;
    reg rstN;
    reg clock;

    integer idx;

    total DUT (
                .shift_en(shift_en),
                .data_rdy(data_rdy),
                .cntr_rstN(cntr_rstN),
                .serial(serial),
                .rstN(rstN),
                .clock(clock)
            );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the FSM, reset{00}, waite{01}, load{10}, ready{11}\n\n");
        $write(" clk  rstN  serl  count  |  st  nst  |  sh_en  cntrRn  data\n");
        $write(" ----------------------------------------------------------\n");
        serial = 1'b0;
        rstN = 1'b1;
        clock = 1'b0;
        
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        $write(" ----------------------------------------------------------\n");
        
        serial = 1'b1;
        for (idx = 0; idx < (`REPS/4); idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        $write(" ----------------------------------------------------------\n");
        
        serial = 1'b0;
        rstN = 1'b0;
        for (idx = 0; idx < (`REPS/4); idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        $write(" ----------------------------------------------------------\n");

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~ the top entity
module total (
                output wire shift_en,
                output wire data_rdy,
                output wire cntr_rstN,
                input wire serial,
                input wire rstN,
                input wire clock
            );

    wire [2:0] count_trans;

    fsm inst_fsm (
                    .shift_en(shift_en),
                    .data_rdy(data_rdy),
                    .cntr_rstN(cntr_rstN),
                    .downCount(count_trans),
                    .serial(serial),
                    .rstN(rstN),
                    .clock(clock)
                );
    
    counter inst_counter (
                            .count(count_trans),
                            .rstN(cntr_rstN),
                            .clock(clock)
                    );
endmodule


////~~~~ the finite state machine
module fsm (
                output reg shift_en,
                output reg data_rdy,
                output reg cntr_rstN,
                input wire [2:0] downCount,
                input wire serial,
                input wire rstN,
                input wire clock
            );
    
    parameter reset = 2'b00;
    parameter waite = 2'b01;
    parameter load = 2'b10;
    parameter ready = 2'b11;

    reg [1:0] state;
    reg [1:0] n_state;

    initial begin
        state = reset;
        n_state = reset;
        shift_en = 1'b0;
        data_rdy = 1'b0;
        cntr_rstN = 1'b0;
    end

    always @ (posedge clock) begin
        if (rstN == 1'b0) begin
            state = reset;
            n_state = reset;
            shift_en = 1'b0;
            data_rdy = 1'b0;
            cntr_rstN = 1'b0;
            #1;
            $write("  %1b     %1b     %1b    %3b   |  %2b   %2b  |     %1b     %1b       %1b\n",
                clock, rstN, serial, downCount, state, n_state, shift_en, cntr_rstN, data_rdy);
        end
        else begin
            case(state)
                reset : 
                    begin
                        shift_en = 1'b0;
                        cntr_rstN = 1'b0;
                        data_rdy = 1'b0;
                        n_state = (rstN == 1'b0) ? reset : waite;
                    end
                waite :
                    begin
                        shift_en = 1'b0;
                        cntr_rstN = 1'b0;
                        data_rdy = 1'b0;
                        n_state = (serial == 1'b0) ? load : waite;
                    end
                load :
                    begin
                        shift_en = 1'b1;
                        cntr_rstN = 1'b1;
                        data_rdy = 1'b0;
                        n_state = (downCount == 3'b000) ? ready : load;
                    end 
                ready : 
                    begin
                        shift_en = 1'b0;
                        cntr_rstN = 1'b0;
                        data_rdy = 1'b1;
                        n_state = waite;
                    end
            endcase
            #1;
            $write("  %1b     %1b     %1b    %3b   |  %2b   %2b  |     %1b     %1b       %1b\n",
                clock, rstN, serial, downCount, state, n_state, shift_en, cntr_rstN, data_rdy);
            state = n_state;
        end
    end
endmodule


////~~~~ the down counter
module counter (
                    output reg [2:0] count,
                    input wire rstN,
                    input wire clock
                );

    parameter clear = 3'b111;

    initial begin
        count = clear;
    end

    always @ (posedge clock) begin
        if (rstN == 1'b0) begin
            count = clear;
        end
        else begin
            if (count != 3'b000) begin
                count = count - 1'b1;
            end
        end
    end
endmodule


////////~~~~~~~~END>  fsm.v