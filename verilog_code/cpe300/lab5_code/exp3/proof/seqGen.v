/*
    proof of concept
    exp3
*/

`timescale 1ns/1ns
`define HALF 5

module tb();
    wire [3:0] wxyz;
    reg a_in;
    reg reset;
    reg clock;

    integer idx;

    seqGen DUT (
                    .wxyz(wxyz),
                    .a_in(a_in),
                    .reset(reset),
                    .clock(clock)
                );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the sequence generator\n\n");
        $write(" st  nst   A | WXYZ\n");
        $write(" ------------------\n");
        a_in = 1'b0;
        reset = 1'b0;
        clock = 1'b0;

        for (idx = 0; idx < 9; idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        $write(" ------------------\n");
        for (idx = 0; idx < 9; idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        reset = 1'b1;
        #(`HALF + `HALF);
        reset = 1'b0;
        a_in = 1'b1;
        $write(" ------------------\n");
        $write(" ------------------\n");
        for (idx = 0; idx < 9; idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        $write(" ------------------\n");
        for (idx = 0; idx < 9; idx = idx + 1) begin
            #(`HALF + `HALF);
        end
        $write(" ------------------\n");

        $write("\t\t\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


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

            if (state != s0) begin
                $write(" s%1d   s%1d   %1b |  %1d\n",
                    state, n_state, a_in, wxyz);
            end
            state = n_state;
        end
    end

endmodule


////////~~~~~~~~END>  seqGen.v
