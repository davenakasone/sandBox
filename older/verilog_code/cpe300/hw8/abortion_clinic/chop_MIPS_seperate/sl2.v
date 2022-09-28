//appends two zeros from the right of LSB of 26-bit immediate //field
module sl2 (input [31:0] a, output [31:0] y);
// shift left by 2; does not shift , but appends
assign y = {a[25:0], 2'b00};
endmodule