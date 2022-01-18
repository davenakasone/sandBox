/*
    tri-state buffer
        8-bit bus, on output
            must be enabled to output 
            else, high impedence
*/

`include "../heads.v"


module c5_triBuff (
                    output reg [7:0] result, 
                    input wire [7:0] from_shifter, 
                    input wire OE
                );

	always @ (*) begin
        result = (OE == 1'b1) ? from_shifter : 8'bzzzz_zzzz;
        `ifdef DEBUG_BUF
            $write("\n *****************************\n");
            $write(" {c5_triBuff}\n");
            $write("          OE:  %1b\n", OE);
            $write("    from_shifter:  %4b_%4b\n", 
                from_shifter[7:4], from_shifter[3:0]);
            $write("          result:  %4b_%4b\n", 
                result[7:4], result[3:0]);
            $write(" *****************************\n");
        `endif
    end		
endmodule


////////~~~~~~~~END>  c5_triBuff.v
