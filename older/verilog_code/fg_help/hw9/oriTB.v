module oriTB();
	reg clk;
	reg reset;
	wire [31:0] writedata, dataadr;
	wire memwrite;

	// instantiate device to be tested
	ori dut (clk, reset, writedata, dataadr, memwrite);
	
	// initialize test
	initial
		begin
			reset <= 1; # 22; reset <= 0;
		end

	// generate clock to sequence tests
	always
		begin
			clk <= 1;
			# 5; 
			clk <= 0;
			# 5; // clock duration
		end

	// check results
	always @ (negedge clk)
		begin
			if (memwrite) begin
				if (dataadr === 20 & writedata === 1) begin
$display ("asdf:", dataadr);
$display ("fuck:", writedata);
					$display ("Simulation succeeded");
					$stop;
				end else if (dataadr !== 12) begin
$display ("asdf:", dataadr);
$display ("fuck:", writedata);
					$display ("Simulation failed");
					$stop;
				end
			end
		end
endmodule

module ori (input clk, reset,output [31:0] writedata, dataadr,output memwrite);

	wire [31:0] pc, instr, readdata;
	
	// instantiate processor and memories
	mips mips (clk, reset, pc, instr, memwrite, dataadr,
				  writedata, readdata);
	imem imem (pc[7:2], instr);
	dmem dmem (clk, memwrite, dataadr, writedata,readdata);
endmodule

module mips (input clk, reset,
				 output [31:0] pc,
				 input [31:0] instr,
				 output memwrite,
				 output [31:0] aluout, writedata,
				 input [31:0] readdata);
				 
	wire memtoreg, branch, alusrc, regdst, regwrite, jump, ori;				//ori wire added
	wire [2:0] alucontrol;
	
	controller c(instr[31:26], instr[5:0], zero,memtoreg, memwrite, pcsrc,
					 alusrc, regdst, regwrite, jump, ori, alucontrol);		//ori port added to controller
	datapath dp(clk, reset, memtoreg, pcsrc,
					alusrc, regdst, regwrite, jump,	ori,					//ori port added to datapath
					alucontrol,
					zero, pc, instr,
					aluout, writedata, readdata);
endmodule

module imem (input [5:0] a, output [31:0] rd);

	reg [31:0] RAM[63:0]; // limited memory
	
	initial
		begin
			$readmemh ("ori_test.dat",RAM);
		end
	assign rd = RAM[a]; // word aligned
endmodule

module dmem (input clk, we,
				 input [31:0] a, wd,
				 output [31:0] rd);
				 
	reg [31:0] RAM[63:0];
	
	assign rd = RAM[a[31:2]]; // word aligned
	always @ (posedge clk)
		if (we)
			RAM[a[31:2]] <= wd;
endmodule

module controller (input [5:0] op, funct,
						 input zero,
						 output memtoreg, memwrite,
						 output pcsrc, alusrc,
						 output regdst, regwrite,
						 output jump, ori,							//ori output added
						 output [2:0] alucontrol);
						 
	wire [1:0] aluop;
	wire branch;
	
	maindec md(op, memtoreg, memwrite, branch,
				  alusrc, regdst, regwrite, jump, ori,				//ori port added to maindec
				  aluop);								
	aludec ad (funct, aluop, alucontrol);
	assign pcsrc = branch & zero;
endmodule

module datapath (input clk, reset,
					  input memtoreg, pcsrc,
					  input alusrc, regdst,
					  input regwrite, jump, ori,					//ori input added
					  input [2:0] alucontrol,
					  output zero,
					  output [31:0] pc,
					  input [31:0] instr,
					  output [31:0] aluout, writedata,
					  input [31:0] readdata);

	wire [4:0] writereg;
	wire [31:0] pcnext, pcnextbr, pcplus4, pcbranch;
	wire [31:0] signimm, signimmsh, zeroimm;						// 32-bit zeroimm wire added
	wire [31:0] srca, srcb;
	wire [31:0] result, zeout;										// 32-bit zeout wire added
	
	// next PC logic
	flopr #(32) pcreg(clk, reset, pcnext, pc);
	adder pcadd1 (pc, 32'b100, pcplus4);
	sl2 immsh(signimm, signimmsh); 
	adder pcadd2(pcplus4, signimmsh, pcbranch);
	mux2 #(32) pcbrmux(pcplus4, pcbranch, pcsrc, pcnextbr); 								 
	mux2 #(32) pcmux(pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);
	
	// register file logic
	regfile rf(clk, regwrite, instr[25:21],
	instr[20:16], writereg, result, srca, writedata);
	mux2 #(5) wrmux(instr[20:16], instr[15:11],regdst, writereg);
	mux2 #(32) resmux(aluout, readdata, memtoreg, result);
	signext se(instr[15:0], signimm);
	zeroext ze(instr[15:0], zeroimm); // zero-extend circuit added to datapath
	
	// ALU logic
	mux2 #(32) zemux(signimm,zeroimm,ori,zeout);	//zero-extend mux added
	mux2 #(32) srcbmux(writedata, zeout, alusrc, srcb);	//changed signimm input to zemux output
	alu alu(srca, srcb, alucontrol, aluout, zero);
endmodule

module maindec (input [5:0] op, output memtoreg, memwrite, output branch, alusrc,
					 output regdst, regwrite, output jump, ori, output [1:0] aluop);		//ori output added
					 
	reg [9:0] controls;				//controls register becomes 10-bit wide b/c of ori instruction											
	assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, ori, aluop}  = controls; //ori output assigned to controls register
	always @ (* )
		case(op)											  
			6'b000000 :  controls <= 10'b110_000_001_0; 		//Rtyp		//change to 10 bits				
			6'b100011 :  controls <= 10'b1010010000; 		//LW		//change to 10 bits				
			6'b101011 :  controls <= 10'b0010100000; 		//SW		//change to 10 bits				
			6'b000100 :  controls <= 10'b0001000001; 		//BEQ		//change to 10 bits				
			6'b001000 :  controls <= 10'b1010000000; 		//ADDI		//change to 10 bits				
			6'b000010 :  controls <= 10'b0000001000; 		//J			//change to 10 bits
			6'b001101 :  controls <= 10'b1010000111;		//ORI		//ori control signal added
			default:  controls <= 10'bXXXXXXXXXX; 			//???						
		endcase
endmodule

module aludec (input [5:0] funct,
					input [1:0] aluop,
					output reg [2:0] alucontrol);
					
	always @ (*)
		case (aluop)
			2'b00: alucontrol <= 3'b010; // add
			2'b01: alucontrol <= 3'b110; // sub	
			default: case(funct) 		  // RTYPE
				6'b100000: alucontrol <= 3'b010; // ADD
				6'b100010: alucontrol <= 3'b110; // SUB
				6'b100100: alucontrol <= 3'b000; // AND
				6'b100101: alucontrol <= 3'b001; // OR
				6'b101010: alucontrol <= 3'b111; // SLT
				default: alucontrol <= 3'bxxx; 	// ???
			endcase
			2'b11: alucontrol <= 3'b001;	//OR		//accepts aluop for OR
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

module adder (input [31:0] a, b, output [31:0] y);

	assign y = a + b;
endmodule

module sl2 (input [31:0] a, output [31:0] y);

	// shift left by 2
	assign y = {a[25:0], 2'b00};
endmodule

module mux2 # (parameter WIDTH = 8)
	(input [WIDTH-1:0] d0, d1, input s,
	 output [WIDTH-1:0] y);
	
	assign y = s ? d1 : d0;
endmodule

module regfile (input clk, input we3,
					 input [4:0] ra1, ra2, wa3,
					 input [31:0] wd3,
					 output [31:0] rd1, rd2);

	reg [31:0] rf[31:0];
	
	// three ported register file
	// read two ports combinationally
	// write third port on rising edge of clock
	// register 0 hardwired to 0
	always @ (posedge clk)
		if (we3) rf[wa3] <= wd3;
			assign rd1 = (ra1 != 0) ? rf[ra1] : 0;
			assign rd2 = (ra2 != 0) ? rf[ra2] : 0;
endmodule

module signext (input [15:0] a,
				output [31:0] y);
	
	assign y = {{16{a[15]}}, a};
endmodule

// zero extend circuit created
module zeroext (input [15:0] a,
				output [31:0] y);
	
	assign y = {16'b0000000000000000, a};
endmodule

module alu (a,b,sel, out, zero);				
    input [31:0] a,b;
    input [2:0] sel; 
    output reg [31:0] out;
	 output reg zero;
	 
	 initial
		begin
			out = 0;
			zero =1'b0;
		end
    
	 always @ (*) 
		begin 
        case(sel) 
            3'b000: 
					begin
						out=a & b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end                   
            3'b001:
					begin
						out= a | b; 
						if (out == 0)
							zero = 1;  
						else
							zero = 0; 
				end		
            3'b110: 
					begin
						out=a-b;  
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end              
            3'b010: 
					begin
						out=a+b;  
						if (out == 0)
							zero = 1;  
						else
							zero = 0;
					end         
            3'b111: 
				   begin
						if ( a < b)
							out = 1;  
						else
							out=0;
					end 
        endcase
    end
endmodule

