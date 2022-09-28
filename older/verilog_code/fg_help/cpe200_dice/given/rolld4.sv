//Matthew Howard
//CpE200L - 1001
//Final Project - D4

module rolld4( input logic clk, reset, roll,
			   output logic [6:0] seg
			   output logic [3:0] dicenum);
			   
	logic [3:0] temp;
	
	//counter and roll sequence 
	always_ff @(posedge clk) begin
		if(reset)
			temp = 4'b0001;
		else begin
			temp = temp + 1;
			if(temp > 4'b0100)
				temp = 4'b0001;
			if(roll)
				dicenum = temp;
			else
				dicenum = dicenum;
			end
	end
	
	//2 seven seg displays showing the result of the roll
	always_comb
		case (dicenum)
		4'b0001:       seg = 7'h79; // 1
		4'b0010:       seg = 7'h24; // 2
		4'b0011:       seg = 7'h30; // 3
		4'b0100:       seg=  7'h19; // 4
      default:         seg = 7'h79; // default @ 1
    endcase
endmodule