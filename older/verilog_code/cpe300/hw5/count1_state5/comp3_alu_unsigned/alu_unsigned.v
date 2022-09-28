/*
    the 2-input, 8-bit, unsigned ALU
    8 operations
*/

`include "../heads.v"


module alu_unsigned (
                        output reg [7:0] to_shifter,
                        input wire [7:0] rf_A,
                        input wire [7:0] rf_B,
                        input wire [2:0] alu_operation
                );

    always @ (*) begin
        case(alu_operation)
            3'b000 : to_shifter = rf_A;
            3'b001 : to_shifter = rf_A & rf_B;
            3'b010 : to_shifter = rf_A | rf_B;
            3'b011 : to_shifter = ~rf_A;
            3'b100 : to_shifter = rf_A + rf_B;
            3'b101 : to_shifter = rf_A - rf_B;
            3'b110 : to_shifter = rf_A + 1'b1;
            3'b111 : to_shifter = rf_A - 1'b1;
        endcase 

        `ifdef DEBUG_alu_unsigned
            $write("\n ************************************\n");
            $write(" {alu_unsigned}\n");
            $write("    alu_operation:  %3b\n", alu_operation);
            $write("             rf_A:  %4b_%4b\n", rf_A[7:4], rf_A[3:0]);
            $write("             rf_B:  %4b_%4b\n", rf_B[7:4], rf_B[3:0]);
            $write("              ---------------------\n");
            $write("       to_shifter:  %4b_%4b\n", 
                to_shifter[7:4], to_shifter[3:0]);
            $write(" ************************************\n");
        `endif
    end 
endmodule


////////~~~~~~~~END>  alu_unsinged.v
