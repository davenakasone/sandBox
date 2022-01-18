/*
    combine the original design files
    for the single-cycle, limited 32-bit MIPS proccessor
        - added wire "zero" in module "mips"
        - added wire "prsrc" in module "mips"
        - memory reading enhancement (use macro)
        - cleaned up indepents, spacing, port lists
        - $stop -> $finish
*/

`timescale 1ns/1ns

//`define FILE_OG 100
`define DIRECT_OG 101


////~~~~
// source:  testbench.v  [ 1 of 16 ]
module testbench();
    reg clk;
    reg reset;
    wire [31:0] writedata, dataadr;
    wire memwrite;

    top dut (clk, reset, writedata, dataadr, memwrite);
    
    initial begin
        reset <= 1; 
        # 22; 
        reset <= 0;
    end
    
    always begin
        clk <= 1;
        # 5; 
        clk <= 0;
        # 5; 
    end
    
    always @ (negedge clk) begin
        if (memwrite) begin
            if (dataadr === 84 & writedata === 7) begin
                $display ("Simulation succeeded");
                $finish;
            end 
            //else if (dataadr !== 80) begin
            else begin
                $display ("Simulation failed");
                $finish;
            end
        end
    end
endmodule


////~~~~
// source:  top.v  [ 2 of 16 ]
module top (
                input wire clk, 
                input wire reset,
                output wire [31:0] writedata, 
                output wire [31:0] dataadr,
                output wire memwrite
            );

    wire [31:0] pc;
    wire [31:0] instr; 
    wire [31:0] readdata;

    // instantiate processor and memories
    mips mips (clk, reset, pc, instr, memwrite, dataadr, writedata, readdata);
    imem imem (pc[7:2], instr);
    dmem dmem (clk, memwrite, dataadr, writedata,readdata);

endmodule


////~~~~
// source:  mips.v  [ 3 of 16 ]
module mips (
                input wire clk, 
                input wire reset,
                output wire [31:0] pc,
                input wire [31:0] instr,
                output wire memwrite,
                output wire [31:0] aluout, 
                output wire [31:0] writedata,
                input wire [31:0] readdata
            );

    wire memtoreg;
    wire branch;
    wire alusrc;
    wire regdst;
    wire regwrite;
    wire jump;
    wire [2:0] alucontrol;
    wire zero;//
    wire pcsrc;//

    controller c(instr[31:26], instr[5:0], zero,memtoreg, memwrite, pcsrc,
        alusrc, regdst, regwrite, jump, alucontrol);
    datapath dp(clk, reset, memtoreg, pcsrc, alusrc, regdst, regwrite, jump,
        alucontrol, zero, pc, instr, aluout, writedata, readdata);

endmodule


////~~~~
// source:  imem.v  [ 4 of 16 ]
module imem (
                input wire [5:0] a, 
                output wire [31:0] rd
            );

    reg [31:0] RAM [63:0]; // limited memory

    initial begin
        `ifdef FILE_OG
            $readmemh ("memfile.dat",RAM);
        `endif
        `ifdef DIRECT_OG
            RAM[0] = 32'h2002_0005;
            RAM[1] = 32'h2003_000c;
            RAM[2] = 32'h2067_fff7;
            RAM[3] = 32'h00e2_2025;
            RAM[4] = 32'h0064_2824;
            RAM[5] = 32'h00a4_2820;
            RAM[6] = 32'h10a7_000a;
            RAM[7] = 32'h0064_202a;
            RAM[8] = 32'h1080_0001;
            RAM[9] = 32'h2005_0000;
            RAM[10] = 32'h00e2_202a;
            RAM[11] = 32'h0085_3820;
            RAM[12] = 32'h00e2_3822;
            RAM[13] = 32'hac67_0044;
            RAM[14] = 32'h8c02_0050;
            RAM[15] = 32'h0800_0011;
            RAM[16] = 32'h2002_0001;
            RAM[17] = 32'hac02_0054;
        `endif
    end

    assign rd = RAM[a]; // word aligned

endmodule


////~~~~
// source:  dmem.v  [ 5 of 16 ]
module dmem (
                input wire clk, 
                input wire we,
                input wire [31:0] a, 
                input wire [31:0] wd,
                output wire [31:0] rd
            );

    reg [31:0] RAM [63:0];

    assign rd = RAM[a[31:2]]; // word aligned

    always @ (posedge clk) begin
        if (we) RAM[a[31:2]] <= wd;
    end

endmodule


////~~~~
// source:  controller.v  [ 6 of 16 ]
module controller (
                    input wire [5:0] op, 
                    input wire [5:0] funct,
                    input wire zero,
                    output wire memtoreg, 
                    output wire memwrite,
                    output wire pcsrc, 
                    output wire alusrc,
                    output wire regdst, 
                    output wire regwrite,
                    output wire jump,
                    output wire [2:0] alucontrol
                );

    wire [1:0] aluop;
    wire branch;

    maindec md(op, memtoreg, memwrite, branch, alusrc, regdst, regwrite, jump, aluop);
    aludec ad (funct, aluop, alucontrol);

    assign pcsrc = branch & zero;

endmodule


////~~~~
// source:  datapath.v  [ 7 of 16 ]
module datapath (
                    input wire clk, 
                    input wire reset,
                    input wire memtoreg, 
                    input wire pcsrc,
                    input wire alusrc, 
                    input wire regdst,
                    input wire regwrite, 
                    input wire jump,
                    input wire [2:0] alucontrol,
                    output wire zero,
                    output wire [31:0] pc,
                    input wire [31:0] instr,
                    output wire [31:0] aluout, 
                    output wire [31:0] writedata,
                    input wire [31:0] readdata
                );

    wire [4:0] writereg;
    wire [31:0] pcnext, pcnextbr, pcplus4, pcbranch;
    wire [31:0] signimm, signimmsh;
    wire [31:0] srca, srcb;
    wire [31:0] result;

    // next PC logic
    flopr #(32) pcreg(clk, reset, pcnext, pc);
    adder pcadd1 (pc, 32'b100, pcplus4);
    sl2 immsh(signimm, signimmsh); 
    adder pcadd2(pcplus4, signimmsh, pcbranch);
    mux2 #(32) pcbrmux(pcplus4, pcbranch, pcsrc, pcnextbr);
    mux2 #(32) pcmux(pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);

    // register file logic
    regfile rf(clk, regwrite, instr[25:21], instr[20:16], writereg, result, srca, writedata);
    mux2 #(5) wrmux(instr[20:16], instr[15:11],regdst, writereg);
    mux2 #(32) resmux(aluout, readdata, memtoreg, result);
    signext se(instr[15:0], signimm);

    // ALU logic
    mux2 #(32) srcbmux(writedata, signimm, alusrc, srcb);
    alu alu(srca, srcb, alucontrol, aluout, zero);

endmodule


////~~~~
// source:  maindec.v  [ 8 of 16 ]
module maindec (
                    input wire [5:0] op, 
                    output wire memtoreg, 
                    output wire memwrite, 
                    output wire branch, 
                    output wire alusrc,
                    output wire regdst, 
                    output wire regwrite, 
                    output wire jump, 
                    output wire [1:0] aluop
                );

    reg [8:0] controls;

    assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, aluop}  = controls;

    always @ (*) begin
        case(op)
            6'b000000 :  controls <= 9'b110000010; 		//Rtyp
            6'b100011 :  controls <= 9'b101001000; 		//LW
            6'b101011 :  controls <= 9'b001010000; 		//SW
            6'b000100 :  controls <= 9'b000100001; 		//BEQ
            6'b001000 :  controls <= 9'b101000000; 		//ADDI
            6'b000010 :  controls <= 9'b000000100; 		//J
            default   :  controls <= 9'bXXXXXXXXX; 		//???
        endcase
    end

endmodule


////~~~~
// source:  aludec.v  [ 9 of 16 ]
module aludec (
                input wire [5:0] funct,
                input wire [1:0] aluop,
                output reg [2:0] alucontrol
            );

    always @ (*) begin
        if (aluop == 2'b00) begin
            alucontrol <= 3'b010; // add
        end
        else if (aluop == 2'b01) begin
            alucontrol <= 3'b110; // sub
        end
        else begin
            case(funct) // RTYPE
                6'b100000 : alucontrol <= 3'b010; // ADD
                6'b100010 : alucontrol <= 3'b110; // SUB
                6'b100100 : alucontrol <= 3'b000; // AND
                6'b100101 : alucontrol <= 3'b001; // OR
                6'b101010 : alucontrol <= 3'b111; // SLT
                default   : alucontrol <= 3'bxxx; // ???
            endcase
        end
    end

endmodule


////~~~~
// source:  flopr.v  [ 10 of 16 ]
module flopr # (parameter WIDTH = 8) (
                                        input wire clk, 
                                        input wire reset,
                                        input wire [WIDTH-1:0] d,
                                        output reg [WIDTH-1:0] q
                                    );

    always @ (posedge clk, posedge reset) begin
        if (reset) q <= 0;
        else q <= d;
    end

endmodule


////~~~~
// source:  adder.v  [ 11 of 16 ]
module adder (
                input wire [31:0] a, 
                input wire [31:0] b, 
                output wire [31:0] y
            );

    assign y = a + b;

endmodule


////~~~~
// source:  sl2.v  [ 12 of 16 ]
module sl2 (
                input wire [31:0] a, 
                output wire [31:0] y
            );

    assign y = {a[25:0], 2'b00};  // shift left by 2

endmodule


////~~~~
// source:  mux2.v  [ 13 of 16 ]
module mux2 # (parameter WIDTH = 8) (
                                        input wire [WIDTH-1:0] d0, 
                                        input wire [WIDTH-1:0] d1,
                                        input wire s,
                                        output wire [WIDTH-1:0] y
                                    );
    assign y = (s) ? d1 : d0;

endmodule


////~~~~
// source:  sigext.v  [ 14 of 16 ]
module signext (
                    input wire [15:0] a,
                    output wire [31:0] y
                );

    assign y = {{16{a[15]}}, a};

endmodule


////~~~~
// source:  alu.v  [ 15 of 16 ]
module alu (
                input wire [31:0] a,
                input wire [31:0] b,
                input wire [2:0] sel, 
                output reg [31:0] out, 
                output reg zero
            );
  
    initial begin
        out = 0;
        zero =1'b0;
    end

    always @ (*) begin 
        case(sel) 
            3'b000: 
	            begin
		            out = a & b; 
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end                   
            3'b001:
	            begin 
                    out = a | b; 
		            if (out == 0) zero = 1;  
		            else zero = 0; 
                end		
            3'b110: 
	            begin
		            out = a - b;  
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end              
            3'b010: 
	            begin
		            out = a + b;  
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end         
            3'b111: 
                begin
		            if ( a < b) out = 1;  
		            else out = 0;
                end 
        endcase
    end

endmodule


////~~~~
// source:  regfile.v  [ 16 of 16 ]
module regfile (
                    input wire clk, 
                    input wire we3,
                    input wire [4:0] ra1, 
                    input wire [4:0] ra2, 
                    input wire [4:0] wa3,
                    input wire [31:0] wd3,
                    output wire [31:0] rd1, 
                    output wire [31:0] rd2
                );

    reg [31:0] rf [31:0];

    /*
        three ported register file
        read two ports combinationally
        write third port on rising edge of clock
        register 0 hardwired to 0
    */
    
    always @ (posedge clk) begin
        if (we3) rf[wa3] <= wd3;
    end

    assign rd1 = (ra1 != 0) ? rf[ra1] : 0;
    assign rd2 = (ra2 != 0) ? rf[ra2] : 0;

endmodule


////////~~~~~~~~END>  clean.v
