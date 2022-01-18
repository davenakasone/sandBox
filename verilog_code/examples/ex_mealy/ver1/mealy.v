/*
    the Mealy FSM, output needs state and input
        includes asynch reset to s0
        next state passes info, while "state" holds state

    makes a clockwise state rotation if A == 3'b000
    else, counter clockwise
*/

`timescale 1ns/1ns
`define HALF 5
`define SEED 444 // change
`define REPS 12  // change


module tb();
    wire [2:0] z_out;
    reg [2:0] a_in;
    reg reset;
    reg clock;

    integer seed;
    integer idx;

    mealy DUT (
                .z_out(z_out),
                .a_in(a_in),
                .reset(reset),
                .clock(clock)
            );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $write("\n the mealy FSM\n\n");
        $write(" st  nst  rst  inp   |  outp\n");
        $write(" ---------------------------\n");
        seed = `SEED;
        a_in = 3'b000;
        clock = 1'b0;
        reset = 1'b0;
        
        for (idx = 0; idx < 3; idx = idx + 1) begin
            a_in[idx] = $random(seed) % 2;
        end

        //a_in = 3'b000;

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + `HALF);
        end

        reset = 1'b1;    // check reset
        #(3 * `HALF + 1);
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~

module mealy (
                output reg [2:0] z_out,
                input wire [2:0] a_in,
                input wire reset,
                input wire clock
            );
    
    parameter s0 = 2'b00;
    parameter s1 = 2'b01;
    parameter s2 = 2'b10;

    reg [1:0] state;
    reg [1:0] n_state;

    initial begin
        state = s0;
        n_state = s0;
        z_out = 3'b000;
    end

    // sequential logic, don't block in here
    always @ (posedge reset or posedge clock) begin
        $write(" %2b  %2b    %1b    %3b  |  %3b      %4t\n",
            state, n_state, reset, a_in, z_out, $time);
        if (reset == 1'b1) begin
            state <= s0;
            z_out = 3'b000;
        end
        else begin
            state <= n_state;
        end
    end

    // combonational logic, block
    always @ (state or a_in) begin
        case(state)
            s0 :
                begin
                    z_out = (a_in == 3'b000) ? 3'b110 : 3'b111;
                    n_state = (a_in == 3'b000) ? s1 : s2;
                end
            s1 :
                begin
                    z_out = (a_in == 3'b000) ? 3'b111 : 3'b101;
                    n_state = (a_in == 3'b000) ? s2 : s0;
                end
            s2 :
                begin
                    z_out = (a_in == 3'b000) ? 3'b101 : 3'b110;
                    n_state = (a_in == 3'b000) ? s0 : s1;
                end
            default : // need, not call cases can be specified
                begin
                    z_out = 3'b000;
                    n_state = s0;
                end
        endcase
    end

endmodule


////////~~~~~~~~END>  mealy.v
