/*
    test "xnor_2" module
*/

`timescale 1ns/1ns
`define STEP 5
`include "xnor_2.v"

module xnor_2_TB ();
    wire OUTP;
    reg INP_A;
    reg INP_B;

    xnor_2 DUT (
                    .y(OUTP),
                    .a(INP_A),
                    .b(INP_B)
                );
    
    initial begin
        $dumpfile("xnor_2_TB.vcd");
		$dumpvars(0, xnor_2_TB);
        $display("\n\ttesting 2-input, 1-output XNOR gate:");
        $display("\n\ta     b     Y");
        $display("\t---------------");

        INP_A = 1'b0;
        INP_B = 1'b0;
        # `STEP
        $display("\t%d  |  %d  |  %d", INP_A, INP_B, OUTP);

        INP_A = 1'b0;
        INP_B = 1'b1;
        # `STEP
        $display("\t%d  |  %d  |  %d", INP_A, INP_B, OUTP);

        INP_A = 1'b1;
        INP_B = 1'b0;
        # `STEP
        $display("\t%d  |  %d  |  %d", INP_A, INP_B, OUTP);

        INP_A = 1'b1;
        INP_B = 1'b1;
        # `STEP
        $display("\t%d  |  %d  |  %d", INP_A, INP_B, OUTP);

		$display("\n\n\t\t~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
		$finish;
    end

endmodule

////////~~~~~~~~END>  xnor_2_TB.v
