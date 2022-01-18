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
                input wire nEqZero
            );

	reg [2:0] state;
	reg [2:0] next_state;

	parameter S0 = 3'b000;
	parameter S1 = 3'b001;
	parameter S2 = 3'b010;
	parameter S3 = 3'b011;
	parameter S4 = 3'b100;
	parameter S5 = 3'b101;
	parameter S6 = 3'b110;
	
	initial state = S0;
	
	always @ (posedge clk) state <= next_state;
	
	always @ (*) begin
		case(state)
			S0 : next_state = (start == 1'b1) ? S1 : S0;
			S1 : next_state = (nEqZero == 1'b1) ? S6 : S2;
			S2 : next_state = S3;
			S3 : next_state = S4;
			S4 : next_state = S5;
			S5 : next_state = (nEqZero == 1'b1) ? S6 : S3;
			S6 : next_state = (restart == 1'b1) ? S0 : S6;	
			default : next_state = S0;
		endcase
	end
		
	assign IE = (state == S1);
		
	assign WE = (state != S6);

	assign WA[1] = (state == S2) | (state == S3);
	assign WA[0] = (state == S1) | (state == S3) | (state == S5);
		
	assign RAE = (state != S1);
	assign RAA[1] = (state == S3) | (state == S4);
	assign RAA[0] = (state == S4) | (state == S5);
		
	assign RBE = (state == S0) | (state == S3) | (state == S4);
	assign RBA[1] = 1'b0;
	assign RBA[0] = (state == S3);
		
	assign ALU[2] = (state == S0) | (state == S2) | (state == S4);
	assign ALU[1] = (state == S2);
	assign ALU[0] = (state == S0) | (state == S3);
		
	assign SH[1] = (state == S5);
	assign SH[0] = 1'b0;

	assign OE = (state == S6);

	`ifdef DEBUG_cu
		//always @ (*) begin
		always @ (posedge clk) begin
			#1;
			$write(" \nstate || IE | WE | WA | RAE | RAA | RBE | RBA | ALU | SH | OE || next || st | rst | n==0  %4t\n",
				$time);
			$write("-----------------------------------------------------------------------------------------\n");
			$write(" %3b  || %1b  | %1b  | %2b | %1b   | %2b  | %1b   | %2b  | %3b | %2b | %1b  || %3b  ||  %1b | %1b   |  %1b\n\n", 
					state, IE, WE, WA, RAE, RAA, RBE, RBA, ALU, SH, OE, next_state, start, restart, nEqZero);
		end
	`endif	
endmodule


////////~~~~~~~~END>  cntlU.v
