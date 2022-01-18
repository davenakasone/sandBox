/*
    resources for components and modules
        general data path (5 components)
        control unit (top-level)
*/

`ifndef H_heads
`define H_heads

`timescale 1ns/1ns      // change as needed
`define STEP 10         // basic delay for combinational
`define HALF_CYCLE 5    // half a clock period
`define T_ERROR 1       // wrap up skew, prop, fan in....
`define SEED 999        // gauruntee $random sequence

// comment OFF, uncomment ON
`define DEBUG_tb -999          // testbench prints
`define DEBUG_wave -888        // testbench generates wave file

//`define DEBUG_cu -66           // "cntlU" module prints
//`define DEBUG_data_path -666    // "data_path" module prints

//`define DEBUG_mux21_8 -111          // "mux21_8" module prints 
//`define DEBUG_register_file -222    // "register_file" module prints
//`define DEBUG_alu_unsigned -333     // "alu_unsinged" module prints
//`define DEBUG_shifter8 -444         // "shifter8" module prints
//`define DEBUG_output_buffer -555    // "output_buffer" module prints


`endif 


////////~~~~~~~~END>  heads.v
