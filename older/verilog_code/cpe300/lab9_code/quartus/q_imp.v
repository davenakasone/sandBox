/*
    read for the FPGA, just checking LSB
*/

`timescale 1ns/1ns
`define HALF 5         // half cycle, time between posedge and negedge
`define SAFETY 40      // kill after this many of instructions


////~~~~
module tb();
    reg clk;
    reg reset;
    wire [6:0] lsb_reg; 
    wire memwrite;
    wire ready;
   
    power_top DUT (
                    .clk(clk),
                    .reset(reset),
                    .lsb_reg(lsb_reg),
                    .memwrite(memwrite),
                    .ready(ready)
                );

    integer idx;

    always begin
        clk <= 1;
        # `HALF; 
        clk <= 0;
        # `HALF; 
    end

    initial begin
        reset <= 1; 
        # 22; 
        reset <= 0;

        for (idx = 0; idx < `SAFETY; idx = idx + 1) begin
            #`HALF;
            if (ready == 1'b1) begin
                $write("\nready: %1b  ,  lsb:  ", ready);
                retDig(lsb_reg);
                $write("\n\n\tSimulation SUCCESS\n");
                $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %9t ns\n\n", $time);
                $finish;
            end
        end

        $write("\n\n\tSimulation FAIL\n");
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %9t ns\n\n", $time);
                $finish;

    end

    task automatic retDig;
        input [6:0] regIn;
        begin
            case(regIn)
                7'b1000_000 : $write("0\n\n");
                7'b1111_001 : $write("1\n\n");
                7'b0100_100 : $write("2\n\n");
                7'b0110_000 : $write("3\n\n");
                7'b0011_001 : $write("4\n\n");
                7'b0010_010 : $write("5\n\n");
                7'b0000_010 : $write("6\n\n");
                7'b1111_000 : $write("7\n\n");
                7'b0000_000 : $write("8\n\n");
                7'b0011_000 : $write("9\n\n");
                default :     $write(" ERROR\n\n");
            endcase
        end
    endtask

endmodule


////~~~~
module power_top (
                    input wire clk,
                    input wire reset,
                    output reg [6:0] lsb_reg,
                    output wire memwrite,
                    output reg ready
                );

    wire [31:0] writedata;
    wire [31:0] dataadr;
    wire [6:0] catch;

    top inst_top (
                    .clk(clk),
                    .reset(reset),
                    .writedata(writedata),
                    .dataadr(dataadr),
                    .memwrite(memwrite)
                );
    
    seg7_dig1 get_dig (
                        .cntl(writedata[3:0]),
                        .disp(catch)
                    );
    
    always @ (*) begin
        if (memwrite == 1'b1) begin
            if (dataadr === 84 & writedata === 7) begin
                ready <= 1'b1;
                lsb_reg <= catch;
            end 
        end
        
    end
    
endmodule


////~~~~
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
    imem imem (pc[7:2], instr); //6-bit address
    dmem dmem (clk, memwrite, dataadr, writedata,readdata);

endmodule


////~~~~
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
    wire zero;
    wire pcsrc; 

    controller CU (instr[31:26], instr[5:0], zero, memtoreg, memwrite, pcsrc, 
        alusrc, regdst, regwrite, jump, alucontrol);
    datapath DP (clk, reset, memtoreg, pcsrc, alusrc, regdst, regwrite, jump,
        alucontrol, zero, pc, instr, aluout, writedata, readdata);

    `ifdef DEBUG_mips

    `endif
endmodule


////~~~~
module imem (
                input wire [5:0] a, 
                output wire [31:0] rd
            );

    reg [31:0] RAM[63:0];  // limited memory

    `ifdef DEBUG_INITIAL
        reg [31:0] temp;
        integer ii;
    `endif
    
    initial begin
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
    end

    assign rd = RAM[a]; // word aligned, always reads to output

endmodule


////~~~~
module dmem (
                input wire clk, 
                input wire we,
                input wire [31:0] a, 
                input wire [31:0] wd,
                output [31:0] rd
            );

    reg [31:0] RAM[63:0];

    assign rd = RAM[a[31:2]]; // word aligned

    always @ (posedge clk) begin
        if (we) RAM[a[31:2]] <= wd;
    end

endmodule


////~~~~
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

    maindec MD (op, memtoreg, memwrite, branch, alusrc, regdst, regwrite, jump, aluop);
    aludec AD (funct, aluop, alucontrol);

    assign pcsrc = branch & zero; 

endmodule


////~~~~
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

    assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, aluop} = controls;

    always @ (*) begin
        case(op)
            6'b000000 :  controls <= 9'b110000010; 		//Rtyp
            6'b100011 :  controls <= 9'b101001000; 		//LW
            6'b101011 :  controls <= 9'b001010000; 		//SW
            6'b000100 :  controls <= 9'b000100001; 		//BEQ
            6'b001000 :  controls <= 9'b101000000; 		//ADDI
            6'b000010 :  controls <= 9'b000000100; 		//J
            default   :  controls <= 9'bXXXXXXXXX; 		// any
        endcase
    end

endmodule


////~~~~
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
    flopr #(32) pcreg (clk, reset, pcnext, pc);
    adder pcadd1 (pc, 32'b100, pcplus4);
    sl2 immsh (signimm, signimmsh); 
    adder pcadd2 (pcplus4, signimmsh, pcbranch);
    mux2 #(32) pcbrmux (pcplus4, pcbranch, pcsrc, pcnextbr);
    mux2 #(32) pcmux (pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);

    // register file logic
    regfile RF (clk, regwrite, instr[25:21],
        instr[20:16], writereg, result, srca, writedata);
    mux2 #(5) wrmux (instr[20:16], instr[15:11],regdst, writereg);
    mux2 #(32) resmux (aluout, readdata, memtoreg, result);
    signext SE (instr[15:0], signimm);

    // ALU logic
    mux2 #(32) srcbmux (writedata, signimm, alusrc, srcb);
    alu ALU (srca, srcb, alucontrol, aluout, zero);

endmodule


////~~~~
module flopr # (parameter WIDTH = 8) (
                                        input wire clk, 
                                        input wire reset,
                                        input wire [WIDTH-1:0] d,
                                        output reg [WIDTH-1:0] q
                                    );

    always @ (posedge clk, posedge reset) begin
        q <= (reset) ? 0 : d;

        `ifdef DEBUG_flopr
            $write("\n{flpr} PC = %4h_%4h\n", q[31:16], q[15:0]);
        `endif
    end

endmodule


////~~~~
module adder (
                input wire [31:0] a, 
                input wire [31:0] b, 
                output wire [31:0] y
            );

    assign y = a + b;

endmodule


////~~~~
module sl2 (
                input wire [31:0] a, 
                output wire [31:0] y
            );

    assign y = {a[25:0], 2'b00};

endmodule


////~~~~
module mux2 # (parameter WIDTH = 8) (
                                        input wire [WIDTH-1:0] d0, 
                                        input wire [WIDTH-1:0] d1, 
                                        input wire s,
                                        output wire [WIDTH-1:0] y
                                    );

    assign y = (s) ? d1 : d0;

endmodule


////~~~~
module regfile (
                    input wire clk, 
                    input wire we3,
                    input wire [4:0] ra1, 
                    input wire [4:0] ra2, 
                    input wire [4:0] wa3,
                    input wire [31:0] wd3,
                    output wire [31:0] rd1, 
                    output wire [31:0]rd2
                );

    reg [31:0] rf[31:0];
    
    always @ (posedge clk) begin
        if (we3) rf[wa3] <= wd3;
    end

    // notice the effective hard-wire rf[0] = 0
    assign rd1 = (ra1 != 0) ? rf[ra1] : 0; 
    assign rd2 = (ra2 != 0) ? rf[ra2] : 0; 

endmodule


////~~~~
module signext (
                    input wire [15:0] a,
                    output wire [31:0] y
                );

    assign y = {{16{a[15]}}, a};

endmodule


////~~~~
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
		            out= a | b; 
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
module seg7_dig1(
                input [3:0] cntl,
                output reg [6:0] disp
            );

    parameter ON = 1'b0;
    parameter OFF = 1'b1;

    always @ (*) begin
        disp = {7{OFF}};
        case (cntl)
            4'b0000 : disp[5:0] = {6{ON}};
            4'b0001 : disp[2:1] = {2{ON}};
            4'b0010 :
                begin
                    disp[1:0] = {2{ON}};
                    disp[6] = ON;
                    disp[4:3] = {2{ON}};
                end
            4'b0011 :
                begin
                    disp[3:0] = {4{ON}};
                    disp[6] = ON;
                end
            4'b0100 :
                begin
                    disp[2:1] = {2{ON}};
                    disp[6:5] = {2{ON}};
                end 
            4'b0101 :
                begin
                    disp[0] = ON;
                    disp[3:2] = {2{ON}};
                    disp[6:5] = {2{ON}};
                end
            4'b0110 :
                begin
                    disp[0] = ON;
                    disp[6:2] = {5{ON}};
                end
            4'b0111 : disp[2:0] = {3{ON}};
            4'b1000 : disp[6:0] = {7{ON}};
            4'b1001 :
                begin
                    disp[6:0] = {7{ON}};
                    disp[4:3] = {2{OFF}};
                end
            default : disp = {7{OFF}};
        endcase
    end
endmodule


////////~~~~~~~~END>  q_imp.v
