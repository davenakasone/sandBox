
module mod1 (input [7:0] A,B,input clk,output reg [8:0]reg_sum);
reg [7:0] reg_A, reg_B;
reg [8:0] w1;
always @ (posedge clk)
begin
reg_A <= A; 
reg_B <= B;
w1 = reg_A + reg_B;
reg_sum <= w1;
end
endmodule


