//Matthew Howard
//CpE200L - 1001
//Final Project - D20

module rolld20( input logic clk, reset, roll,
			   output logic [6:0] seg1, seg2
			   output logic [4:0] dicenum);
			   
	logic [3:0] temp;
	
	//counter and roll sequence 
	always_ff @(posedge clk) begin
		if(reset)
			temp = 5'b00001;
		else begin
			temp = temp + 1;
			if(temp > 5'b10100)
				temp = 5'b00001;
			if(roll)
				dicenum = temp;
			else
				dicenum = dicenum;
			end
	end
	
	//2 seven seg displays showing the result of the roll
	always_comb
		case (dicenum)
		5'b00001:       seg1 = 7'h40; // 01
						seg2 = 7'h79;
		5'b00010:       seg1 = 7'h40; // 02
						seg2 = 7'h24;
		5'b00011:       seg1 = 7'h40; // 03
						seg2 = 7'h30;
		5'b00100:       seg1 = 7'h40; // 04
						seg2=  7'h19;
		5'b00101:       seg1 = 7'h40; // 05
						seg2 = 7'h12;
		5'b00110:       seg1 = 7'h40; // 06
						seg2 = 7'h02;
		5'b00111:		seg1 = 7'h40; // 07
						seg2 = 7'h78;
		5'b01000:		seg1 = 7'h40; // 08
						seg2 = 7'h00;
		5'b01001:		seg1 = 7'h40; // 09
						seg2 = 7'h18; 
		5'b01010:		seg1 = 7'h79; // 10
						seg2 = 7'h40; 
		5'b01011:		seg1 = 7'h79; // 11
						seg2 = 7'h79;
		5'b01100:		seg1 = 7'h79; // 12
						seg2 = 7'h24;
		5'b01101:		seg1 = 7'h79; // 13
						seg2 = 7'h30;
		5'b01110:		seg1 = 7'h79; // 14
						seg2 = 7'h40;
		5'b01111:		seg1 = 7'h79; // 15
						seg2 = 7'h12;
		5'b10000:		seg1 = 7'h79; // 16
						seg2 = 7'h02;
		5'b10001:		seg1 = 7'h79; // 17
						seg2 = 7'h78; 
		5'b10010:		seg1 = 7'h79; // 18
						seg2 = 7'h00; 
		5'b10011:		seg1 = 7'h79; // 19
						seg2 = 7'h18;
		5'b10100:		seg1 = 7'h24; // 20
						seg2 = 7'h40;
      default:          segments = 7'h79; // default @ 1
    endcase
endmodule