/*
	not sure what this guy wants me to do
	no test bench
	no explination
	no printouts
	...not in the business of doing other people's work for free
*/

module smp8trial2 (input clk, reset,output [7:0] writedata, dataadr,output memwrite);

	wire [7:0] pc, instr, readdata;
	
	// instantiate processor and memories
	mips mips (clk, reset, pc, instr, memwrite, dataadr,
				  writedata, readdata);
	imem imem (pc, instr);
	dmem dmem (clk, memwrite, dataadr, writedata,readdata);
endmodule

module mips (input clk, reset,
			 output [7:0] pc,
			 input [7:0] instr,
			 output memwrite,
			 output [7:0] aluout, writedata,
			 input [7:0] readdata);
			
	wire memtoreg, branch, alusrc, regdst, regwrite, jump, zero, pcsrc;
	wire [3:0] alucontrol;

	controller c(instr[7:4],memtoreg, memwrite, pcsrc,
				 alusrc, regdst, regwrite, jump, zero,alucontrol);
	datapath dp(clk, reset, memtoreg, pcsrc,
				alusrc, regdst, regwrite, jump,
				alucontrol,
				zero, pc, instr,
				aluout, writedata, readdata);
endmodule

module imem (input [7:0] a, output [7:0] rd);

	reg [7:0] RAM[255:0]; // limited memory
	
	initial
		begin
			$readmemh ("memfile.dat",RAM);
		end
	assign rd = RAM[a]; // word aligned
endmodule

module dmem (input clk, we,
			 input [7:0] a, wd,
             output [7:0] rd);
				 
	reg [7:0] RAM[255:0];
	
	assign rd = RAM[a]; // word aligned
	always @ (posedge clk)
		if (we)
			begin
				RAM[0] <= 55;
				RAM[1] <= 29;
			end
endmodule

module controller (input [3:0] op,
						 output memtoreg, memwrite,
						 output pcsrc, alusrc,
						 output regdst, regwrite,
						 output jump, zero,
                   output [3:0] alucontrol);
						 
  wire [2:0] aluop;
	wire branch;
	
	maindec md(op, memtoreg, memwrite, branch,
				  alusrc, regdst, regwrite, jump, zero,
				  aluop);								
	aludec ad (op, aluop, alucontrol);
	assign pcsrc = branch & zero;
endmodule

module datapath (input clk, reset,
				 input memtoreg, pcsrc,
				 input alusrc, regdst,
				 input regwrite, jump,
                 input [3:0] alucontrol,
				 output zero,
				 output [7:0] pc,
				 input [7:0] instr,
				 output [7:0] aluout, writedata,
				 input [7:0] readdata);

	wire [3:0] writereg;
	wire [7:0] pcnext, pcnextbr, pcplus1, pcbranch;
	wire [7:0] srca, srcb;
	wire [7:0] result;

	// next PC logic
	flopr #(8) pcreg(clk, reset, pcnext, pc);
	adder pcadd1 (pc, 8'b00000001, pcplus1);
	adder pcadd2(pcplus1, instr, pcbranch);
	mux2 #(8) pcbrmux(pcplus1, pcbranch, pcsrc, pcnextbr);
	mux2 #(8) pcmux(pcnextbr, instr ,jump, pcnext);

	// register file logic
	regfile rf(clk, regwrite, instr[3:0],
	instr[3:0], writereg, result, srca, writedata);
  mux2 #(4) wrmux(instr[3:0], instr[3:0],regdst, writereg);
	mux2 #(8) resmux(aluout, readdata, memtoreg, result);

	// ALU logic
	mux2 #(8) srcbmux(writedata, instr, alusrc, srcb);
	alu alu(srca, srcb, alucontrol, aluout, zero);
endmodule

module maindec (input [3:0] op, output memtoreg, memwrite, output branch, alusrc,
				output regdst, regwrite, output jump, zero, output [2:0] aluop);
	
	reg [10:0] controls;
	assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, zero, aluop}  = controls;

	always @ (* )
		case(op)
			4'b0000 :  controls <= 11'b00000000000; 		//NOP
			4'b0001 :  controls <= 11'b10100100000; 		//LDAC
			4'b0010 :  controls <= 11'b00101000000; 		//STAC
			4'b0101 :  controls <= 11'b00000010000; 		//JUMP
			4'b0110 :  controls <= 11'b00010001001; 		//JUMPZ
			4'b0111 :  controls <= 11'b00010000001; 		//JPNZ
			4'b1xxx :  controls <= 11'b1100000x010; 		//Rtyp
			default:  controls <= 11'bXXXXXXXXXX; 		//???
	endcase
endmodule

module aludec (input [3:0] op,
			   input [2:0] aluop,
			   output reg [3:0] alucontrol);

	always @ (*)
		case (aluop)
			3'b000: alucontrol <= 4'b0000; // add
			3'b001: alucontrol <= 4'b0001; // sub
			default: case(op) // RTYPE
				4'b1000: alucontrol <= 4'b0000; // ADD
				4'b1001: alucontrol <= 4'b0001; // SUB
				4'b1010: alucontrol <= 4'b0010; // INAC
				4'b1011: alucontrol <= 4'b0011; // CLAC
				4'b1100: alucontrol <= 4'b0100; // AND
				4'b1101: alucontrol <= 4'b0101; // OR
				4'b1110: alucontrol <= 4'b0110; // XOR
				4'b1111: alucontrol <= 4'b0111; // NOT
				default: alucontrol <= 4'bxxxx; // ???
			endcase
			3'b010: alucontrol <= 4'b1000;	// MVAC
			3'b011: alucontrol <= 4'b1001;	// MOVR
		endcase
endmodule

module flopr # (parameter WIDTH = 8)
	(input clk, reset,
	 input [WIDTH-1:0] d,
	 output reg [WIDTH-1:0] q);

	 always @ (posedge clk, posedge reset)
		if (reset) q <= 0;
		else q <= d;
endmodule

module adder (input [7:0] a, b, output [7:0] y);
	assign y = a + b;
endmodule

module mux2 # (parameter WIDTH = 8)
	(input [WIDTH-1:0] d0, d1, input s,
	 output [WIDTH-1:0] y);
	
	assign y = s ? d1 : d0;
endmodule

module regfile (input clk, input we3,
					 input [3:0] ra1, ra2, wa3,
					 input [7:0] wd3,
					 output [7:0] rd1, rd2);

	reg [7:0] rf[255:0];
	
	// three ported register file
	// read two ports combinationally
	// write third port on rising edge of clock
	// register 0 hardwired to 0
	always @ (posedge clk)
		if (we3) rf[wa3] <= wd3;
			assign rd1 = (ra1 != 0) ? rf[ra1] : 0;
			assign rd2 = (ra2 != 0) ? rf[ra2] : 0;
endmodule

module alu (a,b,sel, out, zero);				
    input [7:0] a,b;
    input [3:0] sel; 
    output reg [7:0] out;
	output reg zero;
	 
	 initial
		begin
			out = 0;
			zero = 1'b0;
		end
    
	 always @ (*) 
		begin 
        case(sel) 
            4'b0000: 					// ADD
					begin
						out = a + b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end                   
			4'b0001: 					// SUB
					begin
						out = a - b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end 
			4'b0010: 					// INAC
					begin
						out = a + 1; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end 
			4'b0011: 					// CLAC
					begin
						out = 0; 
						zero = 1;
					end 
			4'b0100: 					// AND
					begin
						out = a & b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end 
			4'b0101: 					// OR
					begin
						out = a | b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end 
			4'b0110: 					// XOR
					begin
						out = a ^ b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end 
			4'b0111: 					// NOT
					begin
						out = !a; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end 
			4'b1000: 					// MVAC
					begin
						out = a; 
					end 
			4'b1001: 					// MOVR
					begin
						out = b; 
					end 
        endcase
    end
endmodule
