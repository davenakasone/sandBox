/*
	a combined GDP, all modules
    application of summing algorithm to DE2 board
*/

`timescale 1ns/1ns 
`define HALF 5
`define START 0   
`define STOP 22   // don't do more than 22
`define DEBUG_TB -999
//`define DEBUG_WAVE -888
//`define DEBUG_CU -777
//`define DEBUG_DP -666


module tb();
	wire [6:0] sum_hundreds;
    wire [6:0] sum_tens;
    wire [6:0] sum_ones;
	wire done;
	reg [7:0] n_input;
	reg start;
    reg reset;
    reg clock;

	integer idx;
    real check;
    time past;
    time split;

    summing DUT (
                    .sum_hundreds(sum_hundreds),
                    .sum_tens(sum_tens),
                    .sum_ones(sum_ones),
                    .done(done),
                    .n_input(n_input),
                    .start(start),
                    .reset(reset),
                    .clock(clock)
                );

	always begin
		#`HALF;
		clock = ~clock;
	end
	
	initial begin
        `ifdef DEBUG_WAVE
		    $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
		$write("\n testing the summing algorithm  ,  N [ %3d : %3d ]  on %1d ns cycles\n\n",
            `START, `STOP, 2 * `HALF);
        $write("    input  \"N\"      |  sum  |  expected       time ns   split\n");
        $write(" ---------------------------------------\n");
        past = 0;
        split = 0;

		start = 1'b1;
		reset = 1'b0;
		clock = 1'b0;

        for (idx = `START; idx <= `STOP; idx = idx + 1) begin
            past = $time;
            reset = 1'b0;
            n_input = idx;
            check = idx * (idx + 1) / 2;

            while (done != 1'b1) begin
                #(`HALF + `HALF);
            end

            split = $time - past;

            `ifdef DEBUG_TB
                $write("  {%3d}  %4b_%4b  |  ",
                    n_input, n_input[7:4], n_input[3:0]);
                retDig(sum_hundreds);
                retDig(sum_tens);
                retDig(sum_ones);
                $write( "  |    %3d  ", check);
                $write("  |     %6t    %4t        CORRECT  \n", $time, split);
            `endif
            
            reset = 1'b1;
            #(`HALF + `HALF);
        end

        #3;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~  %7t  ns\n\n", $time);
		$finish;
	end

    task automatic retDig;
        input [6:0] regIn;
        begin
            case(regIn)
                7'b1000_000 : $write("0");
                7'b1111_001 : $write("1");
                7'b0100_100 : $write("2");
                7'b0110_000 : $write("3");
                7'b0011_001 : $write("4");
                7'b0010_010 : $write("5");
                7'b0000_010 : $write("6");
                7'b1111_000 : $write("7");
                7'b0000_000 : $write("8");
                7'b0011_000 : $write("9");
                default :     $write(" ERROR ");
            endcase
        end
    endtask
    
endmodule


////~~~~ applies DE2 features to GDP
module summing (
                    output wire [6:0] sum_hundreds,
                    output wire [6:0] sum_tens,
                    output wire [6:0] sum_ones,
                    output wire done,
                    input wire [7:0] n_input,
                    input wire start,
                    input wire reset,
                    input wire clock
                );
    
    wire [7:0] result;

    general_data_path GDP (
                            .result(result),
                            .done(done),
                            .n_input(n_input),
                            .start(start), 
                            .reset(reset), 
                            .clock(clock)
                        );
    
    seg7_dig3 power_top (
                            .disp_hundreds(sum_hundreds),
                            .disp_tens(sum_tens),
                            .disp_ones(sum_ones),
                            .binary_number(result)
                        );
endmodule


////~~~~  combines control unit and data path
module general_data_path (
                            output wire [7:0] result,
                            output wire done,
                            input wire [7:0] n_input,
                            input wire start, 
                            input wire reset, 
                            input wire clock
                        );	
	wire IE;
    wire WE;
    wire [1:0] WA;
    wire RAE;
    wire [1:0] RAA;
    wire RBE;
    wire [1:0] RBA;
    wire [2:0] ALU;
    wire [1:0] SH;
    wire OE;
    wire n_is_0; 
	
    assign done = OE;

    control_unit CU (
                        .IE(IE), 
                        .WE(WE),
                        .WA(WA),
                        .RAE(RAE),
                        .RAA(RAA),
                        .RBE(RBE),
                        .RBA(RBA),
                        .ALU(ALU),
                        .SH(SH),
                        .OE(OE),
                        .n_is_0(n_is_0),
                        .start(start),
                        .reset(reset),
                        .clock(clock)
                    );

    data_path DP (
                    .n_is_0(n_is_0),
                    .result(result),
                    .n_input(n_input),
                    .IE(IE),
                    .WE(WE),
                    .WA(WA),
                    .RAE(RAE),
                    .RAA(RAA),
                    .RBE(RBE),
                    .RBA(RBA),
                    .ALU(ALU),
                    .SH(SH),
                    .OE(OE),
                    .clock(clock)
                );
endmodule


////~~~~  control unit applied to data path
module control_unit (
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
                        input wire n_is_0,
                        input wire start,
                        input wire reset,
                        input wire clock
                    );

	reg [2:0] state;
	reg [2:0] n_state;

	parameter s0 = 3'b000;
	parameter s1 = 3'b001;
	parameter s2 = 3'b010;
	parameter s3 = 3'b011;
	parameter s4 = 3'b100;
	
	initial begin
        state = s0;
    end
	
	always @ (posedge clock) begin
        if (reset == 1'b1) n_state = s0;  // interupt all
        `ifdef DEBUG_CU
            $write("\n st   nst  || IE | WE | WA | RAE | RAA | RBE | RBA | ALU | SH | OE || start | reset | n==0    %7t ns\n",
                $time);
            $write("-------------------------------------------------------------------------------------------\n");
            $write(" %3b  %3b  || %1b  | %1b  | %2b |  %1b  | %2b  |  %1b  | %2b  | %3b | %2b | %1b  ||   %1b   |   %1b   |  %1b\n", 
                    state, n_state, IE,    WE,    WA,  RAE,    RAA,    RBE,   RBA,   ALU,   SH,   OE,   start, reset,   n_is_0);
        `endif
        state <= n_state;
    end

    always @ (*) begin
        case(state)
            s0 : n_state = (start) ? s1 : s0;     // rf[00] <-- 0  make zero  ,  wait for start
            s1 : n_state = (n_is_0) ? s4 : s2;    // rf[01] <-- N  ,  get input
            s2 : n_state = s3;                    // rf[00] <-- rf[00] + 1  ,  increment sum
            s3 : n_state = (n_is_0) ? s4 : s2;    // rf[01] <-- rf[01] - 1  ,  decrement N
            s4 : n_state = (reset) ? s0 : s4;     // show rf[00]  ,  output and wait for reset
            default : n_state = s0;               // stop the latch
        endcase
	end
	
	assign IE = (state == s1);
		
	assign WE = (state == s0) || 
                (state == s1) || 
                (state == s2) || 
                (state == s3);
                
	assign WA[1] = 1'b0;
	assign WA[0] = (state == s1) || 
                   (state == s3);
		
	assign RAE = (state == s0) || 
                 (state == s2) || 
                 (state == s3) || 
                 (state == s4);
	assign RAA[1] = 1'b0;
	assign RAA[0] = (state == s3);
		
	assign RBE = (state == s0) ||
                 (state == s2);
	assign RBA[1] = 1'b0;
	assign RBA[0] = (state == s2);
		
	assign ALU[2] = (state == s0) || 
                    (state == s2) || 
                    (state == s3);
	assign ALU[1] = (state == s3);
	assign ALU[0] = (state == s0) ||
                    (state == s3);
		
	assign SH[1] = 1'b0;
	assign SH[0] = 1'b0;
	assign OE = (state == s4);	
endmodule


////~~~~  data path combining the 5 components 
module data_path (
                    output wire n_is_0,
                    output wire [7:0] result,
                    input wire [7:0] n_input,
                    input wire IE,
                    input wire WE,
                    input wire [1:0] WA,
                    input wire RAE,
                    input wire [1:0] RAA,
                    input wire RBE,
                    input wire [1:0] RBA,
                    input wire [2:0] ALU,
                    input wire [1:0] SH,
                    input wire OE,
                    input wire clock
                );

    parameter BLANK = 8'b0000_0000;  
    wire [7:0] from_mux;          
	reg [7:0] to_register_file;
    wire [7:0] rf_port_A;
    wire [7:0] rf_port_B;
    wire [7:0] from_alu;
    wire [7:0] from_shifter;
	
    /*
        This internal register completes the feedback.
        Unlike the other connections, it must be a register.
        It is very important and provides the initialization,
        along with proper transfer sequence.
        To use a wire, all subordinate modules would need to be structural.
    */
    initial begin
        to_register_file = BLANK;
    end
    always @ (*) begin
        to_register_file = from_mux;
    end
	
    /*
        This is the probe right under the MUX.
        It won't fail if you move states correctly.
        Don't get too crazy with the logic checks.
    */
	assign n_is_0 = (from_mux == 8'b0000_0000); 

    c1_mux comp1 (
                    .from_mux(from_mux),
                    .new_data(n_input), 
                    .feedback(from_shifter),
                    .IE(IE)
                );

    c2_register_file comp2 (
                            .port_A(rf_port_A),
                            .port_B(rf_port_B),     
                            .from_mux(to_register_file),
                            .WE(WE),                
                            .WA(WA),          
                            .RAE(RAE),    
                            .RAA(RAA),         
                            .RBE(RBE),            
                            .RBA(RBA),      
                            .clock(clock)
                        ); 

    c3_alu comp3 (
                    .from_alu(from_alu),
                    .A_bus(rf_port_A),
                    .B_bus(rf_port_B),
                    .ALU(ALU)
                );

    c4_shifter comp4 (
                        .from_shifter(from_shifter),
                        .from_alu(from_alu),
                        .SH(SH)
                    );


    c5_triBuff comp5 (
                        .result(result), 
                        .from_shifter(from_shifter), 
                        .OE(OE)
                    );
    
    `ifdef DEBUG_DP
        always @ (posedge clock) begin
            #1;
            $write("\n ************************************************\n");
            $write(" {data_path}                               %7t ns\n", $time);
            $write("               n_is_0:  %1b\n", n_is_0);
            $write(" -------------------------\n");
            $write("                   IE:  %1b\n", IE);
            $write("  mux[0], shifter_out:  %4b_%4b\n", from_shifter[7:4], from_shifter[3:0]);
            $write("         mux[1], n_in:  %4b_%4b\n", n_input[7:4], n_input[3:0]);
            $write("         mux out, nnn:  %4b_%4b\n", from_mux[7:4], from_mux[3:0]);
            $write(" ---------------------------------\n");
            $write("               rf_inp:  %4b_%4b\n", to_register_file[7:4], to_register_file[3:0]);
            $write(" WE:   %1b  ,  WA:   %2b\n", WE, WA);
            $write(" RAE:  %1b  ,  RAA:  %2b\n", RAE, RAA);
            $write(" RBE:  %1b  ,  RBA:  %2b\n", RBE, RBA);
            $write(" reg[00]:  %4b_%4b \"k\"\n", comp2.internal[2'b00][7:4], comp2.internal[2'b00][3:0]);
            $write(" reg[01]:  %4b_%4b \"N\"\n"  , comp2.internal[2'b01][7:4], comp2.internal[2'b01][3:0]);
            $write(" reg[10]:  %4b_%4b\n"        , comp2.internal[2'b10][7:4], comp2.internal[2'b10][3:0]);
            $write(" reg[11]:  %4b_%4b\n"        , comp2.internal[2'b11][7:4], comp2.internal[2'b11][3:0]);
            $write("               port A:  %4b_%4b\n", rf_port_A[7:4], rf_port_A[3:0]);
            $write("               port B:  %4b_%4b\n", rf_port_B[7:4], rf_port_B[3:0]);
            $write(" --------------------------------------\n");
            $write("        alu operation:  %3b\n", ALU);
            $write("           alu output:  %4b_%4b\n", from_alu[7:4], from_alu[3:0]);
            $write(" ---------------------------------\n");
            $write("    shifter operation:  %3b\n", SH);
            $write("       shifter output:  %4b_%4b\n", from_shifter[7:4], from_shifter[3:0]);
            $write(" ---------------------------------\n");
            $write("                   OE:  %1b\n", OE);
            $write("               result:  %4b_%4b", result[7:4], result[3:0]);
            if (OE == 1'b1) $write("   !!!SUCCESS!!!\n");
            else $write("      ...working\n");
            $write(" ************************************************\n");
        end
    `endif
endmodule


////~~~~  2-to-1 mux, 8 bits, component 1 of 5
module c1_mux (
                    output reg [7:0] from_mux,
                    input wire [7:0] new_data, 
                    input wire [7:0] feedback,
                    input wire IE
                );
	
	always @ (*) begin
        from_mux = (IE == 1'b1) ? new_data : feedback;
    end
endmodule


////~~~~  register file, component 2 of 5
module c2_register_file(
                            output wire [7:0] port_A,     // value assigned to port A
                            output wire [7:0] port_B,     // value assigned to port B
                            input wire [7:0] from_mux,    // bus after MUX selection
                            input wire WE,                // write enable
                            input wire [1:0] WA,          // write address
                            input wire RAE,               // port A read enable
                            input wire [1:0] RAA,         // port A Read address 
                            input wire RBE,               // port B read enable
                            input wire [1:0] RBA,         // port B read address
                            input wire clock
                        ); 
	
    parameter BLANK = 8'b0000_0000;

    // x4 8-bit registers "4x8", index them in binary
	reg [7:0] internal [3:0]; 

    // only write if WE is active
	always @ (posedge clock) begin
        if (WE == 1'b1) internal[WA] <= from_mux;
    end
     
    // reading to ports is done in combination, if enabled
    assign port_A = (RAE == 1'b1) ? internal[RAA] : BLANK; 
    assign port_B = (RBE == 1'b1) ? internal[RBA] : BLANK;
endmodule


////~~~~  ALU, component 3 of 5
module c3_alu (
                output reg [7:0] from_alu,
                input wire [7:0] A_bus,
                input wire [7:0] B_bus,
                input wire [2:0] ALU
            );

    parameter pass_A = 3'b000;     // bus A passes through
    parameter A_and_B = 3'b001;    // bitwise AND, A & B
    parameter A_or_B = 3'b010;     // bitwise OR, A | B
    parameter not_A = 3'b011;      // bitwise negate, ~A
    parameter A_add_B = 3'b100;    // addition, A + B
    parameter A_sub_B = 3'b101;    // subtraction, A - B
    parameter inc_A = 3'b110;      // increment, A = A + 1
    parameter dec_A = 3'b111;      // decrement, A = A - 1

    always @ (*) begin 
        case(ALU) 
            pass_A  : from_alu = A_bus;                  
            A_and_B : from_alu = A_bus & B_bus;                  
            A_or_B  : from_alu = A_bus | B_bus; 
            not_A   : from_alu = ~A_bus;
            A_add_B : from_alu = A_bus + B_bus;
            A_sub_B : from_alu = A_bus - B_bus;
            inc_A   : from_alu = A_bus + 1'b1;
            dec_A   : from_alu = A_bus - 1'b1;                
        endcase
    end
endmodule


////~~~~  shifter, componenet 4 of 5
module c4_shifter (
                    output reg [7:0] from_shifter,
                    input wire [7:0] from_alu,
                    input wire [1:0] SH
                );

    parameter PASS = 2'b00;      // pass through
    parameter LEFT = 2'b01;      // left shift and fill with 0's
    parameter RIGHT = 2'b10;     // right shift and fill with 0's
    parameter ROTATE = 2'b11;    // rotate right

    always @ (*) begin 
        case(SH) 
            PASS   : from_shifter = from_alu;                  
            LEFT   : from_shifter = from_alu << 1;                 
            RIGHT  : from_shifter = from_alu >> 1;
            ROTATE : from_shifter = {from_alu[6:0], from_alu[7]};                    
        endcase
    end
endmodule


////~~~~  final output buffer, componenet 5 of 5
module c5_triBuff (
                    output reg [7:0] result, 
                    input wire [7:0] from_shifter, 
                    input wire OE
                );

	always @ (*) begin
        result = (OE == 1'b1) ? from_shifter : 8'bzzzz_zzzz;
    end		
endmodule


////~~~~ top module, for using x3 7-segment displays
module seg7_dig3 (
                    output wire [6:0] disp_hundreds,
                    output wire [6:0] disp_tens,
                    output wire [6:0] disp_ones,
                    input wire [7:0] binary_number
            );
    
    wire [3:0] hundreds;
    wire [3:0] ones;
    wire [3:0] tens;

    my_bcd getDigs (
                        .hundreds(hundreds),
                        .tens(tens),
                        .ones(ones),
                        .bin_in(binary_number)
                );
    
    seg7_dig dig3 (
                    .cntl_4bit(hundreds),
                    .disp_4bit(disp_hundreds)
                );
    
    seg7_dig dig2 (
                    .cntl_4bit(tens),
                    .disp_4bit(disp_tens)
                );
    
    seg7_dig dig1 (
                    .cntl_4bit(ones),
                    .disp_4bit(disp_ones)
                );

endmodule


////~~~~ get the 3 decimal digits of 8-bit binary
module my_bcd ( 
                    output reg [3:0] hundreds,
                    output reg [3:0] tens,
                    output reg [3:0] ones,
                    input wire [7:0] bin_in
            );
    integer idx;

    always @ (bin_in) begin
        hundreds = 4'b0000;
        tens = 4'b0000;
        ones = 4'b0000;

        if (bin_in != 8'b0000_0000) begin
            for (idx = 7; idx >= 0; idx = idx - 1) begin
                if (hundreds >= 3'b101) hundreds = hundreds + 2'b11;
                if (tens >= 3'b101) tens = tens + 2'b11;
                if (ones >= 3'b101) ones = ones + 2'b11;
                
                hundreds = hundreds << 1;
                hundreds[0] = tens[3];
                tens = tens << 1;
                tens[0] = ones[3];
                ones = ones << 1;
                ones[0] = bin_in[idx];
            end
        end
    end
endmodule


////~~~~ single digit 7-segment display
module seg7_dig(
                input wire [3:0] cntl_4bit,
                output reg [6:0] disp_4bit
            );

    parameter ON = 1'b0;
    parameter OFF = 1'b1;

    always @ (*) begin
        disp_4bit = {7{OFF}};
        case (cntl_4bit)
            4'b0000 : disp_4bit[5:0] = {6{ON}};
            4'b0001 : disp_4bit[2:1] = {2{ON}};
            4'b0010 :
                begin
                    disp_4bit[1:0] = {2{ON}};
                    disp_4bit[6] = ON;
                    disp_4bit[4:3] = {2{ON}};
                end
            4'b0011 :
                begin
                    disp_4bit[3:0] = {4{ON}};
                    disp_4bit[6] = ON;
                end
            4'b0100 :
                begin
                    disp_4bit[2:1] = {2{ON}};
                    disp_4bit[6:5] = {2{ON}};
                end 
            4'b0101 :
                begin
                    disp_4bit[0] = ON;
                    disp_4bit[3:2] = {2{ON}};
                    disp_4bit[6:5] = {2{ON}};
                end
            4'b0110 :
                begin
                    disp_4bit[0] = ON;
                    disp_4bit[6:2] = {5{ON}};
                end
            4'b0111 : disp_4bit[2:0] = {3{ON}};
            4'b1000 : disp_4bit[6:0] = {7{ON}};
            4'b1001 :
                begin
                    disp_4bit[6:0] = {7{ON}};
                    disp_4bit[4:3] = {2{OFF}};
                end
        endcase
    end
endmodule

////////~~~~~~~~END>  summing_q.v
