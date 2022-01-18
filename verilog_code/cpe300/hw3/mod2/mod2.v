module mod2 (input [7:0] A,B,C,D,input clk,output reg [10:0]reg_sum);
reg [7:0] reg_A, reg_B, reg_C, reg_D;
reg [10:0] w1,w2,w3;
always @ (posedge clk)
begin
reg_A <= A; 
reg_B <= B;
reg_C <= C;
reg_D <= D;
w1 = reg_A + reg_B;
w2 = reg_C + w1;
w3 = w2 + reg_D;
reg_sum <= w3;
end
endmodule









