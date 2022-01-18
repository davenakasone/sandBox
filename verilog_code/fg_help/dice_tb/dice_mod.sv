/*
    test the "dice_roller" module
*/

`timescale 1ns/1ns

`define TEST_SEQ 700
`define TEST_RAN 701

// only use one at a time
//`define TEST_SIDES_4 111
//`define TEST_SIDES_6 112
//`define TEST_SIDES_8 113
//`define TEST_SIDES_10 114
//`define TEST_SIDES_12 115
`define TEST_SIDES_20 116

`define REPS 12
`define HALF 5
`define TIME_SPAN 20
`define SEED 777


module tb();

    reg clock;
    reg reset;
    reg roll;
    reg [2:0] die;
    wire [4:0] roll_result;

    integer seed;
    integer idx;
    integer delay;
    integer die_code;

    dice_roller DUT(
                            .clock (clock), 
                            .reset (reset),
                            .roll (roll), 
                            .die (die),
                            .roll_result (roll_result)
                        );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        clock = 1'b0;
        reset = 1'b0;
        roll = 1'b0;
        seed = `SEED;

        `ifdef TEST_SIDES_4
            die = 3'b001;
            die_code = 4;
        `endif
        `ifdef TEST_SIDES_6
            die = 3'b010;
            die_code = 6;
        `endif
        `ifdef TEST_SIDES_8
            die = 3'b011;
            die_code = 8;
        `endif
        `ifdef TEST_SIDES_10
            die = 3'b100;
            die_code = 10;
        `endif
        `ifdef TEST_SIDES_12
            die = 3'b101;
            die_code = 12;
        `endif
        `ifdef TEST_SIDES_20
            die = 3'b110;
            die_code = 20;
        `endif

        $write("\ntesting the die, sides:  %2d\n\n", die_code);

        for (idx = 0; idx < `REPS; idx = idx + 1) begin

            `ifdef TEST_RAN
                delay = $urandom(seed) % `TIME_SPAN;
                #delay;
            `endif
            `ifdef TEST_SEQ
                #`HALF; #`HALF;
            `endif
            $write("%3d)  rolled:  %2d    %9t ns\n", idx, roll_result, $time);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~   %9t ns\n\n", $time);
        $finish;
    end
endmodule


////~~~~


module dice_roller(
                   input wire clock, reset,
                   input logic roll, 
                   input wire [2:0] die,
                   output wire [4:0] roll_result
                   );

    logic [4:0] temp; //temp values so that I can assign rolled number roll_result
    parameter CLEAR =  5'b00001;
    parameter MAX_4 =  5'b00100;
    parameter MAX_6 =  5'b00110;
    parameter MAX_8 =  5'b01000;
    parameter MAX_10 = 5'b01010;
    parameter MAX_12 = 5'b01100;
    parameter MAX_20 = 5'b10100;

    //give roll_result and temp starting values of 1
    initial begin
        temp = CLEAR;
    end

    assign roll_result = temp;

    //start the rolling process 
    //always_ff(posedge clock) begin
    always @ (posedge clock) begin
        if(reset) begin
            temp = CLEAR;
        end
        else begin
            temp = (temp > MAX_20) ? CLEAR : temp + 1'b1;
        end
        case(die)
            3'b001 : //if d4 
                begin
                    if (roll) temp = (temp > MAX_4) ? CLEAR : temp;
                end
            3'b010 : //if d6 
                begin
                    if (roll) temp = (temp > MAX_6) ? CLEAR : temp;
                end
            3'b011 : //if d8    
                begin
                    temp = (temp > MAX_8) ? CLEAR : temp;
                end
            
            3'b100 : //if d10
                begin
                    temp = (temp > MAX_10) ? CLEAR : temp;
                end
            
            3'b101 : //if d12    
                begin
                    temp = (temp > MAX_12) ? CLEAR : temp;
                end
            //if d20
            3'b110: 
                begin
                    temp = (temp > MAX_20) ? CLEAR : temp;
                end   
            //set default values of temp and roll_result to 0 so I know if anything is wrong
            default:     
                begin
                    temp = CLEAR;
                end
        endcase
    end
endmodule


////////~~~~~~~~END>  dice_mod.sv