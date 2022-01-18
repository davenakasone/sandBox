/*
    the 8-bit shifter
        with 4 functions
*/

`include "../heads.v"


module shifter8 (
                    output reg [7:0] to_bus,
                    input wire [7:0] from_alu,
                    input wire [1:0] shift_operation
            );

    always @ (*) begin 
        case(shift_operation) 
            2'b00 : to_bus = from_alu;  
            2'b01 : to_bus = from_alu << 1;
            2'b10 : to_bus = from_alu >> 1;
            2'b11 : to_bus = {from_alu[6:0], from_alu[7]};                
        endcase

        `ifdef DEBUG_shifter8
            $write("\n *********************************\n");
            $write(" {shifter8}\n");
            $write("     shift_operation = %2b\n", shift_operation);
            $write("            from_alu =  %4b_%4b\n", from_alu[7:4], from_alu[3:0]);
            $write("            to_bus   =  %4b_%4b\n", to_bus[7:4], to_bus[3:0]);
            $write(" *********************************\n");
        `endif
    end
endmodule


////////~~~~~~~~END>  shifter8.v
