/*
    test the adder

    consider delay, fan in, fan out, setup time, hold time --> total times
*/

`timescale 1ns/1ns
`include "funEx.v"
`define STEP 5

module adderTB;
    initial begin
    $display("\naladeen\n");
    $finish;
    end
endmodule

////////~~~~~~~~END>  funEx_TB.v
