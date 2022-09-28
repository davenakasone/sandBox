/*
    the improved ALU
*/

`timescale 1ns/100ps
`define STEP 10

`define TEST000 0  // pass
`define TEST001 1  // AND
`define TEST010 2  // OR
`define TEST011 3  // NOT
`define TEST100 4  // add
`define TEST101 5  // subtract
`define TEST110 6  // increment
`define TEST111 7  // decrement

module tb();
    wire [3:0] outY;
    wire SO;
    wire UO;
    reg [3:0] inA;
    reg [3:0] inB;
    reg [2:0] selt;

    integer idxA;
    integer idxB;
    reg [4:0] temp;

    imp_alu DUT (
                    .out_y(outY),
                    .s_o(SO),
                    .u_o(UO),
                    .in_a(inA),
                    .in_b(inB),
                    .sel(selt)
                );

    initial begin
        temp = 5'b0000_0;

        `ifdef TEST000
        selt = 3'b000;
        $write("\ntest bypass  ,  select =  %b  ,  SO = 0  ,  UO = 0  ,  a[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                if (inA == outY) begin
                    $write("    CORRECT, a-> {pass}-> Y\n");
                end
                else begin
                    $write("    WRONG\n");
                end
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST001
        selt = 3'b001;
        $write("\ntest AND  ,  select =  %b  ,  SO = 0  ,  UO = 0  ,  a[3:0] & b[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                temp = inA & inB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                if (temp == outY) begin
                    $write("    CORRECT, a & b -> Y\n");
                end
                else begin
                    $write("    WRONG\n");
                end
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST010
        selt = 3'b010;
        $write("\ntest OR  ,  select =  %b  ,  SO = 0  ,  UO = 0  ,  a[3:0] | b[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                temp = inA | inB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                if (temp == outY) begin
                    $write("    CORRECT, a | b -> Y\n");
                end
                else begin
                    $write("    WRONG\n");
                end
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST011
        selt = 3'b011;
        $write("\ntest NOT  ,  select =  %b  ,  SO = 0  ,  UO = 0  ,  ~a[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                temp[3:0] = ~inA;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                if (temp[3:0] == outY) begin
                    $write("    CORRECT, ~a -> Y\n");
                end
                else begin
                    $write("    WRONG\n");
                end
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST100
        selt = 3'b100;
        $write("\ntest add  ,  select =  %b  ,  a[3:0] + b[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                disp_vals(inA, inB, outY, SO, UO, selt);
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST101
        selt = 3'b101;
        $write("\ntest subtract  ,  select =  %b  ,  a[3:0] - b[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                disp_vals(inA, inB, outY, SO, UO, selt);
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST110
        selt = 3'b110;
        $write("\ntest increment  ,  select =  %b  ,  a[3:0] + 1 --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                disp_vals(inA, inB, outY, SO, UO, selt);
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST111
        selt = 3'b111;
        $write("\ntest decrement  ,  select =  %b  ,  a[3:0] - 1 --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idxA = 0; idxA < 16; idxA = idxA + 1) begin
            inA = idxA;
            for (idxB = 0; idxB < 16; idxB = idxB + 1) begin
                inB = idxB;
                #`STEP
                $write(" %b   | %b    | %b    %b    %b",
                    inA, inB, outY, SO, UO);
                disp_vals(inA, inB, outY, SO, UO, selt);
            end
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end


    task automatic disp_vals;
        input [3:0] regA;
        input [3:0] regB;
        input [3:0] regY;
        input so;
        input uo;
        input [2:0] selector;

        integer intA_u;
        integer intB_u;
        integer intY_u;
        integer intA_s;
        integer intB_s;
        integer intY_s;

        begin

            case(regA)
                4'b0000 : begin intA_u = 0;  intA_s = 0;  end
                4'b0001 : begin intA_u = 1;  intA_s = 1;  end
                4'b0010 : begin intA_u = 2;  intA_s = 2;  end
                4'b0011 : begin intA_u = 3;  intA_s = 3;  end
                4'b0100 : begin intA_u = 4;  intA_s = 4;  end
                4'b0101 : begin intA_u = 5;  intA_s = 5;  end
                4'b0110 : begin intA_u = 6;  intA_s = 6;  end
                4'b0111 : begin intA_u = 7;  intA_s = 7;  end
                4'b1000 : begin intA_u = 8;  intA_s = -8; end
                4'b1001 : begin intA_u = 9;  intA_s = -7; end
                4'b1010 : begin intA_u = 10; intA_s = -6; end
                4'b1011 : begin intA_u = 11; intA_s = -5; end
                4'b1100 : begin intA_u = 12; intA_s = -4; end
                4'b1101 : begin intA_u = 13; intA_s = -3; end
                4'b1110 : begin intA_u = 14; intA_s = -2; end
                4'b1111 : begin intA_u = 15; intA_s = -1; end
            endcase  

            case(regB)
                4'b0000 : begin intB_u = 0;  intB_s = 0; end
                4'b0001 : begin intB_u = 1;  intB_s = 1; end
                4'b0010 : begin intB_u = 2;  intB_s = 2; end
                4'b0011 : begin intB_u = 3;  intB_s = 3; end
                4'b0100 : begin intB_u = 4;  intB_s = 4; end
                4'b0101 : begin intB_u = 5;  intB_s = 5; end
                4'b0110 : begin intB_u = 6;  intB_s = 6; end
                4'b0111 : begin intB_u = 7;  intB_s = 7; end
                4'b1000 : begin intB_u = 8;  intB_s = -8; end
                4'b1001 : begin intB_u = 9;  intB_s = -7; end
                4'b1010 : begin intB_u = 10; intB_s = -6; end
                4'b1011 : begin intB_u = 11; intB_s = -5; end
                4'b1100 : begin intB_u = 12; intB_s = -4; end
                4'b1101 : begin intB_u = 13; intB_s = -3; end
                4'b1110 : begin intB_u = 14; intB_s = -2; end
                4'b1111 : begin intB_u = 15; intB_s = -1; end
            endcase 

            if (selector == 3'b100) begin
                intY_u = intA_u + intB_u;
                intY_s = intA_s + intB_s;
                $write("  ~~~~  %3d + %3d = %3d   <*>   %3d + %3d = %3d\n",
                    intA_s, intB_s, intY_s, intA_u, intB_u, intY_u);
            end
            if (selector == 3'b101) begin
                intY_u = intA_u - intB_u;
                intY_s = intA_s - intB_s;
                $write("  ~~~~  %3d - %3d = %3d   <*>   %3d - %3d = %3d\n",
                    intA_s, intB_s, intY_s, intA_u, intB_u, intY_u);
            end
            if (selector == 3'b110) begin
                intY_u = intA_u + 1;
                intY_s = intA_s + 1;
                $write("  ~~~~  %3d + 1 = %3d   <*>   %3d + 1 = %3d\n",
                    intA_s, intY_s, intA_u, intY_u);
            end
            if (selector == 3'b111) begin
                intY_u = intA_u - 1;
                intY_s = intA_s - 1;
                $write("  ~~~~  %3d - 1 = %3d   <*>   %3d - 1 = %3d\n",
                    intA_s, intY_s, intA_u, intY_u);
            end
            
        end

    endtask
               
endmodule


////~~~~ ALU


module imp_alu (
                    output [3:0] out_y,
                    output s_o,
                    output u_o,
                    input [3:0] in_a,
                    input [3:0] in_b,
                    input [2:0] sel
               );
    wire [3:0] w_ae;
    wire [3:0] w_le;
    wire w_ce;
    wire [2:0] out_c;
    wire w_so;

    CE ce0 (w_ce, sel);
    AE ae0 (w_ae[0], in_b[0], sel);
    LE le0 (w_le[0], in_a[0], in_b[0], sel);
    fullAdder fa0 (w_ae[0], w_le[0], w_ce, out_c[0], out_y[0]);
   
    AE ae1 (w_ae[1], in_b[1], sel);
    LE le1 (w_le[1], in_a[1], in_b[1], sel);
    fullAdder fa1 (w_ae[1], w_le[1], out_c[0], out_c[1], out_y[1]);
    
    AE ae2 (w_ae[2], in_b[2], sel);
    LE le2 (w_le[2], in_a[2], in_b[2], sel);
    fullAdder fa2 (w_ae[2], w_le[2], out_c[1], out_c[2], out_y[2]);
   
    AE ae3 (w_ae[3], in_b[3], sel);
    LE le3 (w_le[3], in_a[3], in_b[3], sel);
    fullAdder fa3 (w_ae[3], w_le[3], out_c[2], u_o, out_y[2]);
    
    xor out_xor (s_o, u_o, out_c[2]);

endmodule


////~~~~ arithmetic extension


module AE (
            output out_yi,
            input in_bi,
            input [2:0] sel
          );
    wire w_not1_or2_g1;
    wire w_not2_and4_g2;
    wire w_not3_and4_g2;
    wire w_or2_g1;
    wire w_and3_g1;
    wire w_and4_g2;
    
    not not1_or2_g1 (w_not1_or2_g1, in_bi);
    not not2_and4_g2 (w_not2_and4_g2, sel[0]);
    not not3_and4_g2 (w_not3_and4_g2, sel[1]);
  
    or or2_g1 (w_or2_g1, sel[1], w_not1_or2_g1);
    and and3_g1 (w_and3_g1, sel[0], sel[2], w_or2_g1);
    and and4_g2 (w_and4_g2, sel[2], in_bi, w_not2_and4_g2, w_not3_and4_g2);
    or or2_g2 (out_yi, w_and3_g1, w_and4_g2);
endmodule

////~~~~ CE


module CE (
            output c_in,
            input [2:0] sel
          );
    wire w_xor;
    xor xor_g (w_xor, sel[0], sel[1]);
    and and_out (c_in, w_xor, sel[2]);
endmodule


////~~~~ logic extension


module LE (
            output out_xi,
            input in_ai,
            input in_bi,
            input [2:0] sel
          );
    wire w_not1_and4_g4;
    wire w_not2_and2_g2;
    wire w_not3_and3_g3;
    wire w_not4_and4_g4;
    wire w_and2_g1;
    wire w_and2_g2;
    wire w_and3_g3;
    wire w_and4_g4;
    wire w_or2_g1;

    not not1_and4_g4 (w_not1_and4_g4, sel[2]);
    not not2_and2_g2 (w_not2_and2_g2, sel[0]);
    not not3_and3_g3 (w_not3_and3_g3, sel[1]);
    not not4_and4_g4 (w_not4_and4_g4, in_ai);

    and and2_g1 (w_and2_g1, in_ai);
    and and2_g2 (w_and2_g2, w_not2_and2_g2, in_ai);
    and and3_g3 (w_and3_g3, w_not3_and3_g3, in_ai, in_bi);
    or or2_g1 (w_or2_g1, in_bi, sel[0]);
    and and4_g4 (w_and4_g4, w_not1_and4_g4, w_not4_and4_g4, w_or2_g1, sel[1]);
endmodule


////~~~~ Full Adder {1-bit}


module fullAdder (
                    input in_x, 
                    input in_y, 
                    input in_c, 
                    output out_c,
                    output out_sum);
    assign out_sum = in_x ^ in_y ^ in_c;
    assign out_c = (in_x & in_y) | (in_x & in_c) | (in_y & in_c); 
endmodule


////////~~~~~~~~END>  que2.v












/*
////~~~~ Full Adder {4-bit}


module adder4 (
                input [3:0] in_a,
                input [3:0] in_b,
                input in_c,
                output out_c,
                output [3:0] out_sum
              );
    wire   [3:1] C;

    fullAdder FA0 (in_a[0], in_b[0], in_c, C[1], out_sum[0]);
    fullAdder FA1 (in_a[1], in_b[1], C[1], C[2], out_sum[1]);
    fullAdder FA2 (in_a[2], in_b[2], C[2],C[3], out_sum[2]);
    fullAdder FA3 (in_a[3], in_b[3], C[3], out_c, out_sum[3]);
endmodule
*/