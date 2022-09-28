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

    integer idx;
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
        inA = 4'b0000;
        inB = 4'b0000;

        `ifdef TEST000
        selt = 3'b000;
        $write("\ntest bypass  ,  select =  %b  ,  SO = 0  ,  UO = 0  ,  a[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O\n");
        $write("-----------------------------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
            #`STEP
            $write(" %b   | %b    | %b    %b    %b",
                inA, inB, outY, SO, UO);
            if (inA == outY) begin
                $write("    CORRECT, a-> {pass}-> Y\n");
            end
            else begin
                $write("    WRONG\n");
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
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
            #`STEP
            temp = inA & inB;
            $write(" %b   | %b    | %b    %b    %b",
                inA, inB, outY, SO, UO);
            if (temp == outY) begin
                $write("    CORRECT, a & b -> Y\n");
            end
            else begin
                $write("    WRONG\n");
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
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
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
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
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
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST100
        selt = 3'b100;
        $write("\ntest add  ,  select =  %b  ,  a[3:0] + b[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O             signed              unsigned\n");
        $write("------------------------------------------------------------------------------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
            #`STEP
            $write(" %b   | %b    | %b    %b    %b",
                inA, inB, outY, SO, UO);
            disp_vals(inA, inB, outY, SO, UO, selt);
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST101
        selt = 3'b101;
        $write("\ntest subtract  ,  select =  %b  ,  a[3:0] - b[3:0] --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O             signed              unsigned\n");
        $write("------------------------------------------------------------------------------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
            #`STEP
            $write(" %b   | %b    | %b    %b    %b",
                inA, inB, outY, SO, UO);
            disp_vals(inA, inB, outY, SO, UO, selt);
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST110
        selt = 3'b110;
        $write("\ntest increment  ,  select =  %b  ,  a[3:0] + 1 --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O             signed              unsigned\n");
        $write("------------------------------------------------------------------------------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
            #`STEP
            $write(" %b   | %b    | %b    %b    %b",
                inA, inB, outY, SO, UO);
            disp_vals(inA, inB, outY, SO, UO, selt);
            $write("-----------------------------------\n");
        end
        $write("\n\n************************************************************************************\n");
        $write("************************************************************************************\n\n");
        `endif

        `ifdef TEST111
        selt = 3'b111;
        $write("\ntest decrement  ,  select =  %b  ,  a[3:0] - 1 --> Y[3:0]\n\n", selt);
        $write("   a    |   b     |  Y     S_O  U_O             signed              unsigned\n");
        $write("------------------------------------------------------------------------------------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            case(idx)
                0 : begin
                        inA = 4'b0011;    // unsigned 3   ,  singed 3
                        inB = 4'b0111;    // unsigned 7   ,  singed 7
                    end
                1 : begin
                        inA = 4'b0001;    // unsigned 1   ,  singed 1
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
                2 : begin
                        inA = 4'b1001;    // unsigned 9   ,  singed -7
                        inB = 4'b0001;    // unsigned 1   ,  singed 1
                    end
                3 : begin
                        inA = 4'b0000;    // unsigned 0   ,  singed 0
                        inB = 4'b1111;    // unsigned 15  ,  singed -1
                    end
            endcase
            #`STEP
            $write(" %b   | %b    | %b    %b    %b",
                inA, inB, outY, SO, UO);
            disp_vals(inA, inB, outY, SO, UO, selt);
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


////~~~~~


module imp_alu (
                    output reg [3:0] out_y,
                    output reg s_o,
                    output reg u_o,
                    input wire [3:0] in_a,
                    input wire [3:0] in_b,
                    input wire [2:0] sel
                );
    reg out_c3;
    reg [2:0] catch;
    reg [4:0] temp;

    always @ (*) begin 
        s_o = 1'b0;
        u_o = 1'b0;
        case(sel) 
            3'b000 : out_y = in_a;              
            3'b001 : out_y = in_a & in_b;              
            3'b010 : out_y = in_a | in_b;                 
            3'b011 : out_y = ~in_a;                
            3'b100 : begin
                        temp = in_a + in_b;
                        out_y = temp[3:0];
                        {out_c3, catch} = in_a[2:0] + in_b[2:0];
                        s_o = out_c3 ^ temp[4];
                        u_o = temp[4];
                        //s_o = (~in_a[3] & ~in_b[3] & out_c3) | (in_a[3] & in_b[3] & ~out_c3);
                     end                
            3'b101 : begin
                        temp = in_a + (~in_b + 1'b1); 
                        out_y = temp[3:0];
                        {out_c3, catch} = in_a[2:0] + (~in_b[2:0] + 1'b1);
                        s_o = out_c3 ^ temp[4];
                        u_o = temp[4];
                        //s_o = (~in_a[3] & ~in_b[3] & out_c3) | (in_a[3] & in_b[3] & ~out_c3);
                     end    
            3'b110 : begin
                        temp = in_a + 1'b1;
                        out_y = temp[3:0];
                        {out_c3, catch} = in_a[2:0] + 1'b1;
                        s_o = out_c3 ^ temp[4];
                        u_o = temp[4];
                        //s_o = (~in_a[3] & 1'b1 & out_c3) | (in_a[3] & 1'b0 & ~out_c3);
                     end               
            3'b111 : begin
                        temp = in_a + 4'b1111;  
                        out_y = temp[3:0]; 
                        {out_c3, catch} = in_a[2:0] + 3'b111;
                        u_o = (in_a == 4'b0000) ? 1'b1 : 1'b0;
                        s_o = out_c3 ^ temp[4];
                        //s_o = (~in_a[3] & 1'b0 & out_c3) | (in_a[3] & 1'b1 & ~out_c3);
                     end               
        endcase
    end
endmodule


////////~~~~~~~~END>  my_alu.v
