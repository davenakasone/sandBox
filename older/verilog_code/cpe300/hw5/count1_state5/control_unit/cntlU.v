/*
    get the states from your algorithim
*/

`include "../heads.v"


module cntlU (
                output wire IE,
                output wire WE, 
                output wire [1:0] WA,
                output wire RAE,
                output wire [1:0] RAA,
                output wire RBE,
                output wire [1:0] RBA,
                output wire [2:0] ALU,
                output wire [1:0] SH,
                output wire OE,
				input wire clk, 
                input wire start, 
                input wire restart, 
                input wire n_is_0,
				input wire n0_is_1
            );

	reg [2:0] state;
	reg [2:0] next_state;

	parameter S0 = 3'b000;
	parameter S1 = 3'b001;
	parameter S2 = 3'b010;
	parameter S3 = 3'b011;
	parameter S4 = 3'b100;
	
	initial state = S0;
	
	always @ (posedge clk) state <= next_state;
	
	always @ (*) begin
		case(state)
			S0 : next_state = (start == 1'b1) ? S1 : S0;
			S1 : 
				begin
					case ({n_is_0, n0_is_1})
						2'b00 : next_state = S3;
						2'b01 : next_state = S2;
						2'b10 : next_state = S4;
						2'b11 : next_state = S4;
					endcase
				end
			S2 : next_state = S3;
			S3 : 
				begin
					case ({n_is_0, n0_is_1})
						2'b00 : next_state = S3;
						2'b01 : next_state = S2;
						2'b10 : next_state = S4;
						2'b11 : next_state = S4;
					endcase
				end
			S4 : next_state = (restart == 1'b1) ? S0 : S4;
			default : next_state = S0;
		endcase
	end
		
	assign IE = (state == S1);
		
	assign WE = (state == S0) | (state == S1) | (state == S2) | (state == S3);

	assign WA[1] = 1'b0;
	assign WA[0] = (state == S1) | (state == S3);
		
	assign RAE = (state == S0) | (state == S2) | (state == S3) | (state == S4);
	assign RAA[1] = 1'b0;
	assign RAA[0] = (state == S3);
		
	assign RBE = (state == S0);
	assign RBA[1] = 1'b0;
	assign RBA[0] = 1'b0;
		
	assign ALU[2] = (state == S0) | (state == S2);
	assign ALU[1] = (state == S2);
	assign ALU[0] = (state == S0);
		
	assign SH[1] = (state == S3);
	assign SH[0] = 1'b0;

	assign OE = (state == S4);

	`ifdef DEBUG_cu
		//always @ (*) begin
		always @ (posedge clk) begin
			#2;
			$write(" \nstate || IE | WE | WA | RAE | RAA | RBE | RBA | ALU | SH | OE || next || st | rst | n==0  n[0]==1  %4t ns\n",
				$time);
			$write("-------------------------------------------------------------------------------------------------\n");
			$write(" %3b  || %1b  | %1b  | %2b | %1b   | %2b  | %1b   | %2b  | %3b | %2b | %1b  || %3b  ||  %1b | %1b   |  %1b      %1b\n\n", 
					state, IE, WE, WA, RAE, RAA, RBE, RBA, ALU, SH, OE, next_state, start, restart, n_is_0, n0_is_1);
		end
	`endif	
endmodule


////////~~~~~~~~END>  cntlU.v
