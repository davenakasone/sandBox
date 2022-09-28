/*
    tri-state buffer, 8-bit bus, on output
*/

`include "../heads.v"


module output_buffer (
                        output reg [7:0] result,
                        input wire [7:0] from_shifter,
                        input wire enable
                );
    always @ (*) begin
        result = (enable == 1'b1) ?
                                    from_shifter : 8'bzzzz_zzzz;
        `ifdef DEBUG_output_buffer
            $write("\n *****************************\n");
            $write(" {output_buffer}\n");
            $write("          enable:  %1b\n", enable);
            $write("    from_shifter:  %4b_%4b\n", 
                from_shifter[7:4], from_shifter[3:0]);
            $write("          result:  %4b_%4b\n", 
                result[7:4], result[3:0]);
            $write(" *****************************\n");
        `endif
    end 
endmodule


////////~~~~~~~~END>  output_buffer.v
