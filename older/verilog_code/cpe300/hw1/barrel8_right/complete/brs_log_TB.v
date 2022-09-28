/*
    test the completed shifter
        all 3 barrel8 right sub modules
*/

`define STEP 5
`include "brs_log.v"


module brs_log_TB ();
    wire [7:0] OUT_Y;
    reg [2:0] SC;
    reg [7:0] INP_X;
    integer idx;

    brs_log DUT (
                    .outp_y(OUT_Y),
                    .shift_ct(SC),
                    .inp_x(INP_X)
                );
    
    initial begin
        $dumpfile("brs_log_TB.vcd");
		$dumpvars(0, brs_log_TB);
		SC = 3'b000;
		INP_X = 8'b11111111;
        # `STEP
        INP_X = 8'b00000000;
        # `STEP
        INP_X = 8'b11111111;
        # `STEP
		$display("\nTIME  selector      input         output     ACTION\n");
        
        for (idx = 0; idx <= 8; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    BYPASS", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end
        
        $display("");
		INP_X = 8'b11111111;
		SC = 3'b001;
        for (idx = 0; idx < 8; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 1-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        $display("");
		INP_X = 8'b11111111;
		SC = 3'b010;
        for (idx = 0; idx < 7; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 2-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        $display("");
		INP_X = 8'b11111111;
		SC = 3'b011;
        for (idx = 0; idx < 6; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 3-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        $display("");
		INP_X = 8'b11111111;
		SC = 3'b100;
        for (idx = 0; idx < 5; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 4-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        $display("");
		INP_X = 8'b11111111;
		SC = 3'b101;
        for (idx = 0; idx < 4; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 5-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        $display("");
		INP_X = 8'b11111111;
		SC = 3'b110;
        for (idx = 0; idx < 3; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 6-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        $display("");
		INP_X = 8'b11111111;
		SC = 3'b111;
        for (idx = 0; idx < 2; idx = idx + 1) begin
            # `STEP
            $display("%3t       %b      %b      %b    SHIFT RIGHT 7-bit", 
				$time, SC, INP_X, OUT_Y);
			INP_X = INP_X >> 1;
        end

        # `STEP
		$display("\n\n\t~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
		$finish;
    end

endmodule

////////~~~~~~~~END>  brs_log_TB.v
