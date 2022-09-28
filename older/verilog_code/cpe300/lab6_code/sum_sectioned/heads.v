/*
    resources for components and modules
        general data path (5 components)
        control unit (top-level)
*/

`ifndef H_heads
`define H_heads

`timescale 1ns/1ns      // change as needed
`define HALF 5          // half a clock period
`define T_ERROR 1       // wrap up skew, prop, fan in, or delay for debugging
`define SEED 999        // gauruntee $random sequence

// testing displays:
// "    ---> Valid"
// "    ---> !!!~~~*** FAIL ***~~~!!!"

// comment OFF, uncomment ON
`define DEBUG_TB -999          // allow test bench to print
`define DEBUG_WAVE -888        // testbench generates wave file

//`define DEBUG_CU -777          // control unit module prints
`define DEBUG_DP -666          // data path module prints

//`define DEBUG_MUX -111         // mux module prints, component 1 of 5
//`define DEBUG_RF -222          // register file module prints, component 2 of 5
//`define DEBUG_ALU -333         // alu module prints, component 3 of 5
//`define DEBUG_SH -444          // shifter module prints, component 4 of 5
//`define DEBUG_BUF -555         // buffer module prints, component 5 of 5


`endif 


////////~~~~~~~~END>  heads.v
