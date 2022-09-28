/*
    FSM given a table
*/

`timescale 1ns/1ns
`define HALF 5

module tb();
    wire z_out;
    reg x_in;
    reg reset;
    reg clock;

    integer idx;

    fsm DUT (
                .z_out(z_out),
                .x_in(x_in),
                .reset(reset),
                .clock(clock)
            );
    
    always begin 
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0,tb);
        $write("\n test the FSM, provided by table, exp2  ... both loops {x=0, x=1}\n\n");
        $write("          n state    output Z\n");
        $write(" state | x=0  x=1 |  x=0  x=1\n");
        $write(" ----------------------------------\n");
        x_in = 1'b0;
        reset = 1'b0;
        clock = 1'b0;

        for (idx = 0; idx < 6; idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        
        reset = 1'b1;
        #(`HALF + `HALF);
        reset = 1'b0;
        x_in = 1'b1;
        $write(" ----------------------------------\n");

        for (idx = 0; idx < 6; idx = idx + 1) begin
            #(`HALF + `HALF);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


module fsm (
                output reg z_out,
                input wire x_in,
                input wire reset,
                input wire clock
        );

    parameter s0 = 3'b000;
    parameter s1 = 3'b001;
    parameter s2 = 3'b010;
    parameter s3 = 3'b011;
    parameter s4 = 3'b100;
    parameter s5 = 3'b101;
    parameter s6 = 3'b110;

    reg [2:0] state;
    reg [2:0] n_state;

    initial begin
        state = s0;
        n_state = s0;
        z_out = 1'b0;
    end

    always @ (posedge clock /*or posedge reset*/) begin
        if (reset == 1'b1) begin
            state <= s0;
            n_state <= s0;
            z_out <= 1'b0;
        end
        else begin
            state <= n_state;
        end
    end

    always @ (x_in or state) begin
        if (reset == 1'b0) begin
        case(state)
            s0 :
                begin
                    z_out = (x_in == 1'b0) ? 1'b1 : 1'b0;
                    n_state = (x_in == 1'b0) ? s1 : s2;
                end
            s1 :
                begin
                    z_out = (x_in == 1'b0) ? 1'b1 : 1'b0;
                    n_state = (x_in == 1'b0) ? s3 : s4;
                end
            s2 :
                begin
                    z_out = (x_in == 1'b0) ? 1'b0 : 1'b1;
                    n_state = s4;
                end
            s3 :
                begin
                    z_out = (x_in == 1'b0) ? 1'b0 : 1'b1;
                    n_state = s5;
                end
            s4 :
                begin
                    z_out = (x_in == 1'b0) ? 1'b1 : 1'b0;
                    n_state = (x_in == 1'b0) ? s5 : s6;
                end
            s5 :
                begin
                    z_out = (x_in == 1'b0) ? 1'b0 : 1'b1;
                    n_state = s0;
                end
            s6 :
                begin
                    z_out = 1'b1;
                    n_state = s0;
                end
            default : 
                begin
                    z_out = 1'b0;
                    n_state = s0;
                end
        endcase

        if (reset != 1'b1) begin
            if (x_in == 1'b0) begin
                $write(" %3b   | %3b      |   %1b\n", 
                    state, n_state, z_out);
            end
            else begin
                $write(" %3b   |      %3b |        %1b\n", 
                    state, n_state, z_out);
            end
        end
    end
    end
endmodule


////////~~~~~~~~END>  exp2.v
