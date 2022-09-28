module adder (input [7:0] A,B,C,input clk,output reg [9:0]reg_sum);
reg [7:0] reg_A, reg_B, reg_C;
reg [9:0] w1,w2;
always @ (posedge clk)
begin
reg_A <= A; 
reg_C <= C;
w1 = reg_A + reg_B;
w2 = reg_C + w1;
reg_sum <= w2;
end
endmodule

