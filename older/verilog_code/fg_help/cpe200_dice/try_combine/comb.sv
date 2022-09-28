/*
    combined
        rolld4.sv
        rolld6.sv

*/


`timescale 1ns/1ns
`define SEED 676
`define REPS 10
`define HALF 5
`define MODULO 111


module tb();
    reg clock;
    reg reset;
    reg [4:0] sides;
    wire [4:0] roll_result;

    m_dice_roll DUT (
						.clock (clock),
                        .reset (reset),
						.sides (sides),
						.roll_result (roll_result)
					);
    
    integer seed;
    integer idx;
    integer delay;

    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        clock = 1'b0;
        reset = 1'b0;
        seed = `SEED;
        sides = 1'b0;
        $write("\ntesting the dice\n");

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            $write("\n\t--> rep{ %3d}\n\n", idx);

            sides = 1'b0;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice_unknown :   %2d\n", roll_result);

            sides = 4;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice4 :   %2d\n", roll_result);

            sides = 6;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice6 :   %2d\n", roll_result);


            sides = 8;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice8 :   %2d\n", roll_result);

            sides = 10;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice10 :  %2d\n", roll_result);

            sides = 12;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice12 :  %2d\n", roll_result);

            sides = 20;
            delay = $urandom(seed) % `MODULO;
            # delay;
            $write("dice20 :  %2d\n", roll_result);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %4t ns\n\n", $time);
        $finish;
    end
    
endmodule


////~~~~
module m_dice_roll (
						input wire clock,
						input wire reset,
                        input wire [4:0] sides,
						output reg [4:0] roll_result
					);
    
	initial begin
        roll_result = 5'b00001;
	end

	always @ (posedge clock) begin
		if(reset) begin
			roll_result = 5'b00001;
		end
		else begin
            roll_result = (roll_result > 5'b10100) ? 5'b00001 : roll_result + 1'b1;
            case (sides)
                4  : roll_result = (roll_result % 4) + 1;
                6  : roll_result = (roll_result % 6) + 1;
                8  : roll_result = (roll_result % 8) + 1;
                10 : roll_result = (roll_result % 10) + 1;
                12 : roll_result = (roll_result % 12) + 1;
                20 : roll_result = (roll_result % 20) + 1;
                default : roll_result = 5'b00001;
            endcase
		end
	end

endmodule


/////////~~~~~~~~END>  comb.sv