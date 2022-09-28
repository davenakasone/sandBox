/*
   the MUX
*/

`include "../heads.v"


module c1_mux (
                    output reg [7:0] from_mux,
                    input wire [7:0] new_data, 
                    input wire [7:0] feedback,
                    input wire IE
                );
	
	always @ (*) begin
        from_mux = (IE == 1'b1) ? new_data : feedback;

        `ifdef DEBUG_MUX
			$write("\n **********************************************\n");
            $write(" {c1_mux}    IE = %1b\n",
				IE);
            $write("                feedback =  %4b_%4b\n", 
				feedback[7:4], feedback[3:0]);
			$write("                   input =  %4b_%4b\n", 
				new_data[7:4], new_data[3:0]);

            $write("      to_register_file   =  %4b_%4b\n", 
				from_mux[7:4], from_mux[3:0]);
            $write(" **********************************************\n");
		`endif
    end
endmodule


////////~~~~~~~~END>  c1_mux21_8.v
