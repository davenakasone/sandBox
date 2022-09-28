/*
    Moore FSM, output only depends on state
    seperate clearly to show outputs only depend on state...
*/

`timescale 1ns/1ns
`define DEBUG -22 //~~~~{on|off}
`define HALF 5
`define REPS 12  // actual reps is half
`define SEED 373 // change here


module tb();
    wire [2:0] z_out;
    reg [2:0] a_in;
    reg clock;

    integer idx;
    integer ii;
    integer seed;

    moore DUT (
                .z_out(z_out),
                .a_in(a_in),
                .clock(clock)
            );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $write(" the Moore FSM\n\n");
        $write(" st  nst  inp  |  outp\n");
        $write(" ----------------------\n");
        clock = 1'b0;
        a_in = 1'b0;
        seed = `SEED;

        for (ii = 0; ii < 3; ii = ii + 1) begin
            a_in[ii] = $random(seed) % 2;
        end

        a_in = 3'b001;

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + 1);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module moore (
                output reg [2:0] z_out,
                input wire [2:0] a_in,
                input wire clock
            );

    reg [1:0] state;
    reg [1:0] n_state;

    parameter s0 = 2'b00;
    parameter s1 = 2'b01;
    parameter s2 = 2'b10;
    parameter s3 = 2'b11;

    initial begin
        state = s0;
        n_state = s0;
        z_out = 3'b000;
    end

    always @ (posedge clock) begin
        case(n_state)
            s0 :
                begin
                    state <= n_state;
                    n_state <= (a_in == 3'b000) ? s0 : s2;
                end
            s1 :
                begin
                    state <= n_state;
                    n_state <= (a_in == 3'b000) ? s0 : s2;
                end
            s2 :
                begin
                    state <= n_state;
                    n_state <= (a_in == 3'b000) ? s2 : s3;
                end
            s3 :
                begin
                    state <= n_state;
                    n_state <= (a_in == 3'b000) ? s1 : s3;
                end
        endcase
    end

    always @ (n_state) begin // notice the blocking vs non-blocking
        case (n_state)
            s0 : z_out = 3'b111;
            s1 : z_out = 3'b101;
            s2 : z_out = 3'b110;
            s3 : z_out = 3'b111;
        endcase 
    end

    `ifdef DEBUG
        always @ (posedge clock) begin
            #1;
            $write(" %2b   %2b  %3b  |  %3b         %4tns\n",
                state, n_state, a_in, z_out, $time);
        end
    `endif
endmodule


////////~~~~~~~~END>  moore.v
