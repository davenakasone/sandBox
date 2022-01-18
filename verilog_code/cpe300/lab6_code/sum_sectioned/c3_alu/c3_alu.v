/*
    the alu
*/

`include "../heads.v"


module c3_alu (
                output reg [7:0] from_alu,
                input wire [7:0] A_bus,
                input wire [7:0] B_bus,
                input wire [2:0] ALU
            );

    parameter pass_A = 3'b000;     // bus A passes through
    parameter A_and_B = 3'b001;    // bitwise AND
    parameter A_or_B = 3'b010;     // bitwise OR
    parameter not_A = 3'b011;      // negate bus A
    parameter A_add_B = 3'b100;    // addition
    parameter A_sub_B = 3'b101;    // subtraction
    parameter inc_A = 3'b110;      // increment bus A
    parameter dec_A = 3'b111;      // decrement bus A

    always @ (*) begin 
        case(ALU) 
            pass_A  : from_alu = A_bus;                  
            A_and_B : from_alu = A_bus & B_bus;                  
            A_or_B  : from_alu = A_bus | B_bus; 
            not_A   : from_alu = ~A_bus;
            A_add_B : from_alu = A_bus + B_bus;
            A_sub_B : from_alu = A_bus - B_bus;
            inc_A   : from_alu = A_bus + 1'b1;
            dec_A   : from_alu = A_bus - 1'b1;                
        endcase

        `ifdef DEBUG_ALU
            $write("\n ************************************\n");
            $write(" {c3_alu}\n");
            $write("              ALU:  %3b\n", ALU);
            $write("           port_A:  %4b_%4b\n", A_bus[7:4], A_bus[3:0]);
            $write("           port_B:  %4b_%4b\n", B_bus[7:4], B_bus[3:0]);
            $write("              ---------------------\n");
            $write("       to_shifter:  %4b_%4b\n", 
                from_alu[7:4], from_alu[3:0]);
            $write(" ************************************\n");
        `endif
    end
endmodule


////////~~~~~~~~END>  c3_alu.v
