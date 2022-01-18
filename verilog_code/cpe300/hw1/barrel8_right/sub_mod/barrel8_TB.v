/*
	test "barrel8"
*/

`timescale 1ns/1ns

`include "barrel8.v"

`define BITZ 8
`define STEP 5


module barrel8_TB ();
	wire [`BITZ-1:0] outY;
	reg SEL;
	reg [`BITZ-1:0] inpX;
	integer idx;

	barrel8 DUT (
					.out_y(outY),
					.selector(SEL),
					.in_x(inpX)
				);
	
	initial begin
		$dumpfile("barrel8_TB.vcd");
		$dumpvars(0, barrel8_TB);
		SEL = 1'b0;
		inpX = 8'b11111111;
		$display("\nTIME  selector    input         output     ACTION\n");

		for (idx = 0; idx < `BITZ; idx++) begin
			# `STEP
			$display("%3t       %b      %b      %b    BYPASS", 
				$time, SEL, inpX, outY);
			inpX = inpX >> 1;
		end

		$display("");
		inpX = 8'b11111111;
		SEL = 1'b1;
		for (idx = 0; idx < `BITZ; idx++) begin
			# `STEP
			$display("%3t       %b      %b      %b    RIGHT SHIFT", 
				$time, SEL, inpX, outY);
			inpX = inpX >> 1;
		end
		
		# `STEP
		$display("\n\n\t~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
		$finish;
	end

endmodule

////////~~~~~~~~END>  barrel8_TB.v
