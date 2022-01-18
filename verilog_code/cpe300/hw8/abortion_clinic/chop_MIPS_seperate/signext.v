//copies the 16th bit of the constant field to upper 16 bits //from 17th  to 31st bit
module signext (input [15:0] a,
output [31:0] y);
assign y = {{16{a[15]}}, a};
endmodule