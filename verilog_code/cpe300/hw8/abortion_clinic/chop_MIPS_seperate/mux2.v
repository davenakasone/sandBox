//Defines 2-to-1 MUX with the parameter as the width of data //inputs. Please note, it is limited to 8 as both addresses for //instruction and data memory are limited to 6, and data in the //test code are in the range 0-255.  For the real design the //width is 8 

module mux2 # (parameter WIDTH = 8)
(input [WIDTH-1:0] d0, d1, input s,
output [WIDTH-1:0] y);
assign y = s ? d1 : d0;
endmodule