//Matthew Howard
//CpE200L - 1001
//Final Project - D6

module rolld6(input logic clk, reset, roll,
			   output logic [6:0] segments,
			   output logic [3:0] dicenum);
			   
	logic [3:0] temp;
	
	//counter and roll 
	always_ff @(posedge clk) begin
		if(reset)
			temp = 4'b0001;
		else begin
			temp = temp + 1;
			if(temp > 4'b0110)
				temp = 4'b0001;
			if(roll)
				dicenum = temp;
			else
				dicenum = dicenum;
			end
	end
	
	//seven seg display showing the result of the roll
	always_comb
		case (dicenum)
		4'b0001:       segments = 7'h79; // 1
		4'b0010:       segments = 7'h24; // 2
		4'b0011:       segments = 7'h30; // 3
		4'b0100:       segments=  7'h19; // 4
		4'b0101:       segments = 7'h12; // 5
		4'b0110:       segments = 7'h02; // 6
      default:         segments = 7'h79; // default @ 1
    endcase
endmodule