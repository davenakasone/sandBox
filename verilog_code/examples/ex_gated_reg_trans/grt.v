/*
    4 registers, 4-bits each
    control signals determine how register transfer goes
    can't do all combos on same cycle

    mux21 is good to put at C,D --> AB because reduces control signals needed
    it is the path between the registers

    see mod2

    can even put combinational logic, operate on regs, then output and select
    with a big MUX
*/

`timescale 1ps/1ps
`define HALF 5


module tb();
endmodule


////~~~~


module grt(
                output reg [3:0] a_reg,
                output reg [3:0] b_reg,
                input wire clk,
                input wire [3:0] c_reg,
                input wire [3:0] d_reg,
                input wire g_a,
                input wire g_b,
                input wire g_c,
                input wire g_d
        );
    wire and_c2or;
    wire and_d2or;
    wire 
endmodule


////~~~~


module reg4 (
                output reg [3:0] Q,
                input wire clk,
                input wire [3:0] D
        );
    always @ (posedge clk) Q = D;   // block
endmodule

////////~~~~~~~~END>  grt.v
