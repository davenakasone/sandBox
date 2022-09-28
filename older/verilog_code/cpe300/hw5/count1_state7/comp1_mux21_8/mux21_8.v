/*
    8-bit MUX 2:1
        selects input, outputs to register file
        0 : feed output from shifter
        1 : feed input_data
*/

`include "../heads.v"


module mux21_8 (
                    output reg [7:0] to_register_file,
					input wire [7:0] from_shifter,
					input wire [7:0] input_data,
					input wire mux_selector
            );
	always @ (*) begin
		to_register_file = (mux_selector == 1'b0) ?
								from_shifter : 
								input_data;

		`ifdef DEBUG_mux21_8
			$write("\n **********************************************\n");
            $write(" mux21_8:  mux_selector = %1b\n",
				mux_selector);
            $write("            from_shifter =  %4b_%4b\n", 
				from_shifter[7:4], from_shifter[3:0]);
			$write("              input_data =  %4b_%4b\n", 
				input_data[7:4], input_data[3:0]);

            $write("      to_register_file   =  %4b_%4b\n", 
				to_register_file[7:4], to_register_file[3:0]);
            $write(" **********************************************\n");
		`endif
	end
endmodule


////////~~~~~~~~END>  mux21_8.v
