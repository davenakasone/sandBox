/*
    the 8-bit shifter
*/

`include "../heads.v"


module c4_shifter (
                    output reg [7:0] from_shifter,
                    input wire [7:0] from_alu,
                    input wire [1:0] SH
                );

    parameter PASS = 2'b00;      // pass through
    parameter LEFT = 2'b01;      // left shift and fill with 0's
    parameter RIGHT = 2'b10;     // right shift and fill with 0's
    parameter ROTATE = 2'b11;    // rotate right

    always @ (*) begin 
        case(SH) 
            PASS   : from_shifter = from_alu;                  
            LEFT   : from_shifter = from_alu << 1;                 
            RIGHT  : from_shifter = from_alu >> 1;
            ROTATE : from_shifter = {from_alu[6:0], from_alu[7]};                    
        endcase

        `ifdef DEBUG_SH
            $write("\n *********************************\n");
            $write(" {c4_shifter}\n");
            $write("              SH = %2b\n", SH);
            $write("        from_alu =  %4b_%4b\n", from_alu[7:4], from_alu[3:0]);
            $write("    from_shifter =  %4b_%4b\n", from_shifter[7:4], from_shifter[3:0]);
            $write(" *********************************\n");
        `endif
    end
endmodule


////////~~~~~~~~END>  c4_shifter.v
