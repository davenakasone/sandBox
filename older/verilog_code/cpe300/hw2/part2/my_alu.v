/*
    the improved ALU
*/

`timescale 1ns/100ps
`define STEP 10

//`define TEST000 0  // pass
//`define TEST001 1  // AND
//`define TEST010 2  // OR
//`define TEST011 3  // NOT
`define TEST100 4  // add
//`define TEST101 5  // subtract
//`define TEST110 6  // increment
//`define TEST111 7  // decrement

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
    //integer intA;
    //integer intB;
    //integer intY;

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
                check_add(inA, inB, outY, SO, UO);
            end
            $write("-----------------------------------\n");
        end
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
                check_sub(inA, inB, outY, SO, UO);
            end
            $write("-----------------------------------\n");
        end
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
                check_inc(inA,outY,SO,UO);
            end
            $write("-----------------------------------\n");
        end
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
                check_dec(inA,outY,SO,UO);
            end
            $write("-----------------------------------\n");
        end
        `endif

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end


    task automatic check_add;
        input [3:0] regA;
        input [3:0] regB;
        input [3:0] regY;
        input so;
        input uo;

        reg [4:0] temp_u;
        reg [4:0] temp_s;
        reg [4:0] help;
        integer intA_u;
        integer intB_u;
        integer intY_u;
        integer intA_s;
        integer intB_s;
        integer intY_s;

        begin
            temp_u = regA + regB;
            temp_s = temp_u;
            intA_u = regA;
            intB_u = regB;
            intY_u = intA_u + intB_u;

            if (regY[3] == 1'b1 || so == 1'b1) begin
                help = temp_s;
                help = help - 1'b1;
                help = ~help;
                intY_s = help;
                intY_s = intY_s * (-1);
            end
            else begin
                temp_s = regY;
                intY_s = temp_s;
            end
            if (regA[3] == 1'b1) begin
                regA = regA - 1'b1;
                regA = ~regA;
                intA_s = regA;
                intA_s = intA_s * (-1);
            end
            else begin
                intA_s = regA;
            end
            if (regB[3] == 1'b1) begin
                regB = regB - 1'b1;
                regB = ~regB;
                intB_s = regB;
                intB_s = intB_s * (-1);
            end
            else begin
                intB_s = regB;
            end

            if ( ( intY_s < 0 && (-1 * intY_s == {so, regY}) ) || intY_s > 0) begin
                if (temp_u == {uo, regY}) begin
                    $write("   CORRECT, %3d + %3d = %3d  OR  %3d + %3d = %3d\n",
                        intA_u, intB_u, intY_u, intA_s, intB_s, intY_s);
                end
            end
            else begin
                $write("   WRONG, %3d + %3d != %3d  OR  %3d + %3d != %3d\n",
                        intA_u, intB_u, intY_u, intA_s, intB_s, intY_s);
            end
        end
    endtask


    task automatic check_sub;
        input [3:0] regA;
        input [3:0] regB;
        input [3:0] regY;
        input so;
        input uo;

        reg [4:0] temp;
        integer intA;
        integer intB;
        integer intY;

        begin
            temp = regA - regB;

            if (regA[3] == 1'b1) begin
                regA = regA - 1'b1;
                regA = ~regA;
                intA = regA;
                intA = intA * (-1);
            end
            else begin
                intA = regA;
            end
            if (regB[3] == 1'b1) begin
                regB = regB - 1'b1;
                regB = ~regB;
                intB = regB;
                intB = intB * (-1);
            end
            else begin
                intB = regB;
            end

            intY = intA - intB;

            if (so == 1'b0 && uo == 1'b0 && temp[3:0] == regY) begin
                $write("   CORRECT, %3d - %3d = %3d\n",
                    intA, intB, intY);
            end
            else if (so == 1'b1) begin
                $write("   CORRECT, %3d - %3d = %3d\n",
                    intA, intB, intY);
            end
            else if (uo == 1'b1 && temp == {uo, regY}) begin
                $write("   CORRECT, %3d - %3d = %3d\n",
                    intA, intB, intY);
            end
            else begin
                $write("   WRONG, %3d -%3d != %3d\n",
                    intA, intB, intY);
            end
        end
    endtask


    task automatic check_inc;
        input [3:0] regA;
        input [3:0] regY;
        input so;
        input uo;

        reg [4:0] temp;
        integer intA;
        integer intY;

        begin
            temp = regA + 1'b1;

            if (regA[3] == 1'b1) begin
                regA = regA - 1'b1;
                regA = ~regA;
                intA = regA;
                intA = intA * (-1);
            end
            else begin
                intA = regA;
            end

            intY = intA + 1;

            if (so == 1'b0 && uo == 1'b0 && temp[3:0] == regY) begin
                $write("   CORRECT, %3d + 1 = %3d\n",
                    intA, intY);
            end
            else if (so == 1'b1) begin
                $write("   CORRECT, %3d + 1 = %3d\n",
                    intA, intY);
            end
            else if (uo == 1'b1 && temp == {uo, regY}) begin
                $write("   CORRECT, %3d + 1 = %3d\n",
                    intA, intY);
            end
            else begin
                $write("   WRONG, %3d + 1 != %3d\n",
                    intA, intY);
            end
        end
    endtask

    task automatic check_dec;
        input [3:0] regA;
        input [3:0] regY;
        input so;
        input uo;

        reg [4:0] temp;
        integer intA;
        integer intY;

        begin
            temp = regA - 1'b1;

            if (regA[3] == 1'b1) begin
                regA = regA - 1'b1;
                regA = ~regA;
                intA = regA;
                intA = intA * (-1);
            end
            else begin
                intA = regA;
            end

            intY = intA - 1;

            if (so == 1'b0 && uo == 1'b0 && temp[3:0] == regY) begin
                $write("   CORRECT, %3d - 1 = %3d\n",
                    intA, intY);
            end
            else if (so == 1'b1) begin
                $write("   CORRECT, %3d - 1 = %3d\n",
                    intA, intY);
            end
            else if (uo == 1'b1 && temp == {uo, regY}) begin
                $write("   CORRECT, %3d - 1 = %3d\n",
                    intA, intY);
            end
            else begin
                $write("   WRONG, %3d - 1 != %3d\n",
                    intA, intY);
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
        case(sel)   // 3 control signals for one of 8 operations to select
            3'b000 : out_y = in_a;              
            3'b001 : out_y = in_a & in_b;              
            3'b010 : out_y = in_a | in_b;                 
            3'b011 : out_y = ~in_a;                
            3'b100 : begin
                        temp = in_a + in_b;
                        out_y = temp[3:0];
                        {out_c3, catch} = in_a[2:0] + in_b[2:0];
                        s_o = out_c3 ^ temp [4];
                        u_o = temp[4];
                     end                
            3'b101 : begin
                        temp = in_a + (~in_b + 1'b1); 
                        out_y = temp[3:0];
                        {out_c3, catch} = in_a[2:0] + (~in_b[2:0] + 1'b1);
                        s_o = out_c3 ^ temp [4];
                        u_o = temp[4];
                     end    
            3'b110 : begin
                        temp = in_a + 1'b1;
                        out_y = temp[3:0];
                        {out_c3, catch} = in_a[2:0] + 1'b1;
                        s_o = out_c3 ^ temp [4];
                        u_o = temp[4];
                     end               
            3'b111 : begin
                        temp = in_a + 4'b1111;  
                        out_y = temp[3:0]; 
                        {out_c3, catch} = in_a[2:0] + 3'b111;
                        
                     end               
        endcase
    end
endmodule


////////~~~~~~~~END>  my_alu.v



/*
    task automatic check_add;
        input [3:0] regA;
        input [3:0] regB;
        input [3:0] regY;
        input so;
        input uo;

        reg [4:0] temp;
        integer intA;
        integer intB;
        integer intY;

        begin
            temp = regA + regB;

            if (regA[3] == 1'b1) begin
                regA = regA - 1'b1;
                regA = ~regA;
                intA = regA;
                intA = intA * (-1);
            end
            else begin
                intA = regA;
            end
            if (regB[3] == 1'b1) begin
                regB = regB - 1'b1;
                regB = ~regB;
                intB = regB;
                intB = intB * (-1);
            end
            else begin
                intB = regB;
            end

            intY = intA + intB;

            if (so == 1'b0 && uo == 1'b0 && temp[3:0] == regY) begin
                $write("   CORRECT, %3d + %3d = %3d\n",
                    intA, intB, intY);
            end
            else if (so == 1'b1) begin
                $write("   CORRECT, %3d + %3d = %3d\n",
                    intA, intB, intY);
            end
            else if (uo == 1'b1 && temp == {uo, regY}) begin
                $write("   CORRECT, %3d + %3d = %3d\n",
                    intA, intB, intY);
            end
            else begin
                $write("   WRONG, %3d +%3d != %3d\n",
                    intA, intB, intY);
            end
        end
    endtask
*/