/*
    combined version, some clean up
    - missing wires {added some}
    - mismatched parameters {re-wrote arguments}
    - still have some incomplete case statements

    The single-cycle MIPS processor (select instructions only)
    32-bit
*/

`timescale 1ns/1ns

//`define ORIGINAL_INSTRUCTIONS 123
//`define CHANGE_INSTRUCTIONS 1234  // fails if on
//`define READ_FILE_ORIGINAL 12345
`define READ_FILE_V1 123456

`define DEBUG_top 1111
`define DEBUG_imem 2222
`define DEBUG_dmem 3333


module tb();
    reg clk;
    reg reset;
    wire [31:0] writedata, dataadr;
    wire memwrite;

    // instantiates the  device to be tested (device under test-DUT)
    top dut (clk, reset, writedata, dataadr, memwrite);

    // generate clock to sequence tests
    always begin
        clk <= 1;
        # 5; 
        clk <= 0;
        # 5; // clock duration
    end

    // initialize test
    initial begin
        reset <= 1; 
        # 22; 
        reset <= 0;
        $write(" \n\n test the MIPS_32 circuit\n");
    end

    // check the contents of memory location 84. It must be 7
    always @ (negedge clk) begin
        if (memwrite) begin
            if (dataadr === 84 & writedata === 7) begin // notice 4-state logic test
                $write ("\n\t Simulation succeeded");
                $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~  %8t  ns\n\n", $time);
                $finish;
            end 
            else if (dataadr !== 80) begin
                $write ("\n\t Simulation failed");
                $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~  %8t  ns\n\n", $time);
                $finish;
            end
        end
    end
endmodule


////~~~~
// gets everything together by instantiating processor and memory
module top (
                input wire clk, 
                input wire reset,
                output wire [31:0] writedata, 
                output wire [31:0] dataadr,
                output wire memwrite
            );

    wire [31:0] pc, instr, readdata;

    // instantiate processor and memories
    mips mips (clk, reset, pc, instr, 
        memwrite, dataadr, writedata, readdata);
    imem imem (pc[7:2], instr); //6-bit address
    dmem dmem (clk, memwrite, dataadr, writedata,readdata);

    `ifdef DEBUG_top
        always @ (negedge clk) begin
            $write("{top}\n");
            $write(" clk:  %1b  ,  reset:  %1b  ,  memwrite:  %1b\n",
                clk, reset, memwrite);
            $write(" writedata:  %4h_%4h  ,  dataadr:  %4h_%4h\n\n",
                writedata[31:16], writedata[15:0], dataadr[31:16], dataadr[15:0]);
        end
    `endif

endmodule


////~~~~
// instatiates modules in MIPS Processor
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

    wire memtoreg, branch, alusrc, regdst, regwrite, jump, zero, pcsrc;
    wire [2:0] alucontrol;

    controller c(instr[31:26], instr[5:0], zero,memtoreg, 
        memwrite, pcsrc, alusrc, regdst, regwrite, jump, alucontrol);

    datapath dp(clk, reset, memtoreg, pcsrc,
        alusrc, regdst, regwrite, jump,
        alucontrol,zero, pc, instr,
        aluout, writedata, readdata);

endmodule

////~~~~
// 64 word memory is defined here
// .dat file has a hexadecimal code of instructions (if indexed correctly)
module imem (
                input wire [5:0] a, 
                output wire [31:0] rd
            );

    reg [31:0] RAM[63:0]; // limited memory
    //reg [31:0] RAM[0:63]; // IEEE left hand starts index...
    initial begin
        `ifdef READ_FILE_ORIGINAL
            $readmemh ("memfile.dat",RAM);//lines of test code in hex 
        `endif 

        `ifdef READ_FILE_V1
            $readmemh ("memfile_NEW.dat",RAM);
        `endif
        
        `ifdef ORIGINAL_INSTRUCTIONS
            RAM[0] = 32'h2002_0005;
            RAM[1] = 32'h2003_000c; // conflict
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

        `ifdef CHANGE_INSTRUCTIONS
            RAM[0] = 32'h2002_0005;
            RAM[1] = 32'h2003_300c; // conflict
            RAM[2] = 32'h2067_fff7;
            RAM[3] = 32'h00e2_2025;
            RAM[4] = 32'h0064_2824;
            RAM[5] = 32'h00a4_2820;
            RAM[6] = 32'h10a7_000a;
            RAM[7] = 32'h0064_202a;
            RAM[8] = 32'h1080_0001;
            RAM[9] = 32'h2005_0000;
            RAM[10] = 32'h00e2_202a;
            RAM[11] = 32'hac67_0044;
            RAM[12] = 32'h8c02_0050;
            RAM[13] = 32'h0800_0011;
            RAM[14] = 32'h2002_0001;
            RAM[15] = 32'hac02_0054;
        `endif
        
    end

    assign rd = RAM[a]; // word aligned

    `ifdef DEBUG_imem
        always @ (rd) begin
            $write("{imem}\n");
            $write(" address:  %5b  ,  instr:  %4h_%4h\n\n", a, rd[31:16], rd[15:0]);
        end
    `endif

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
        `ifdef DEBUG_dmem
            $write("{dmem}\n");
            $write("we: %1b  ,  rd:  %4h_%4h\n",
                we, rd[31:16], rd[15:0]);
            $write(" a:  %4h_%4h  ,  wd:  %4h_%4h\n\n",
                a[31:16], a[15:0], wd[31:16], wd[15:0]);
        `endif
    end

endmodule


////~~~~
// instantiates both maind ecoder and ALU decoder
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

    maindec md(op, memtoreg, memwrite, branch,
        alusrc, regdst, regwrite, jump, aluop);
    aludec ad (funct, aluop, alucontrol);
    assign pcsrc = branch & zero; //does it here because the logic is outside of main decoder and ALU decoder
endmodule


////~~~~
// got all control signals
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

    //defines all internal wires
    wire [4:0] writereg;
    wire [31:0] pcnext, pcnextbr, pcplus4, pcbranch;
    wire [31:0] signimm, signimmsh;
    wire [31:0] srca, srcb;
    wire [31:0] result;

    // next PC logic. Instantiates PC and adders
    flopr #(32) pcreg(clk, reset, pcnext, pc);
    adder pcadd1 (pc, 32'b100, pcplus4);
    sl2 immsh(signimm, signimmsh); 

    adder pcadd2(pcplus4, signimmsh, pcbranch);
    mux2 #(32) pcbrmux(pcplus4, pcbranch, pcsrc, pcnextbr);
    mux2 #(32) pcmux(pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);

    // register file logic; instatiates RF
    regfile rf(clk, regwrite, instr[25:21],
    instr[20:16], writereg, result, srca, writedata);

    //instatiates the number of multiplexers
    mux2 #(5) wrmux(instr[20:16], instr[15:11],regdst, writereg);
    mux2 #(32) resmux(aluout, readdata, memtoreg, result);
    signext se(instr[15:0], signimm);

    // ALU logic: defines inputs and instatiates Alu
    mux2 #(32) srcbmux(writedata, signimm, alusrc, srcb);
    alu alu(srca, srcb, alucontrol, aluout, zero);
endmodule


////~~~~
// takes opcode and produces control signals except branch 
// this is done by controller module as an outside logic)
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

    // checks the opcode and produces 9 control signals as in the //control word table

    always @ (*) begin
        case(op)
            6'b000000 :  controls <= 9'b110000010; 		//Rtyp
            6'b100011 :  controls <= 9'b101001000; 		//LW
            6'b101011 :  controls <= 9'b001010000; 		//SW
            6'b000100 :  controls <= 9'b000100001; 		//BEQ
            6'b001000 :  controls <= 9'b101000000; 		//ADDI
            6'b000010 :  controls <= 9'b000000100; 		//J
            default:  controls <= 9'bXXXXXXXXX; 		// any
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
                6'b100000: alucontrol <= 3'b010; // ADD
                6'b100010: alucontrol <= 3'b110; // SUB
                6'b100100: alucontrol <= 3'b000; // AND
                6'b100101: alucontrol <= 3'b001; // OR
                6'b101010: alucontrol <= 3'b111; // SLT
                default: alucontrol <= 3'bxxx; // ???
            endcase
        end
    end
endmodule


////~~~~
// D flip-flop is designed in this module
module flopr # (parameter WIDTH = 8)(
                                        input wire clk, 
                                        input wire reset,
                                        input wire [WIDTH-1:0] d,
                                        output reg [WIDTH-1:0] q
                                    );

    always @ (posedge clk, posedge reset) begin
        q <= (reset) ? 0 : d;
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
// appends two zeros from the right of LSB of 26-bit immediate field
module sl2 (
                input wire [31:0] a, 
                output wire [31:0] y
            );

    // shift left by 2; does not shift , but appends
    assign y = {a[25:0], 2'b00};

endmodule


////~~~~
/*
    Defines 2-to-1 MUX with the parameter as the width of data inputs. 
    Please note, it is limited to 8 as both addresses for instruction 
        and data memory are limited to 6, and data in the test code are in 
            the range 0-255.
    For the real design the width is 8.
*/ 
module mux2 # (parameter WIDTH = 8) (
                                        input wire [WIDTH-1:0] d0, 
                                        input wire [WIDTH-1:0]d1, 
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
                    output wire [31:0] rd1, rd2
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


////~~~~
// copies the 16th bit of the constant field to upper 16 bits from 17th  to 31st bit
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
        zero = 1'b0;
    end

    always @ (*) begin 
        case(sel) 
            3'b000 : 
	            begin
		            out = a & b; 
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end                   
            3'b001 :
	            begin
		            out = a | b; 
		            if (out == 0) zero = 1;  
	                else zero = 0; 
                end		
            3'b110 : 
	            begin
		            out= a - b;  
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end              
            3'b010 : 
	            begin
		            out = a + b;  
		            if (out == 0) zero = 1;  
		            else zero = 0;
                end         
            3'b111 : 
                begin
		            if ( a < b) out = 1;  
                    else out = 0;
                end 
            // default ???
        endcase
    end
endmodule


////////~~~~~~~~END>  mips_single.v
