/*
    the algorithm to convert BCD to decimal
    usually for the 7-segment display

    takes an 8-bit binary number and gives you the BCD 

    1) if an col (100, 10, 1) is <= 5, add 3
    2) shift all numbers to left one position
    3) if 8 shifts performed, it is done, evaluate each col for BCD value
    4) go to step 1 if 8 shifts not performed
*/

`timescale 1ns/1ns
`define STEP 10

module tb();
    wire [3:0] hudz;
    wire [3:0] tenz;
    wire [3:0] onez;
    reg [7:0] binz;

    integer idx;
    integer temp;
    integer int100;
    integer int10;
    integer int1;

    my_bcd DUT ( 
                    .hundreds(hudz),
                    .tens(tenz),
                    .ones(onez),
                    .bin_in(binz)
            );
    
    initial begin
        $write("\n test bin --> BCD, using 8-bit input\n\n");
        $write(" i  :  bin         |  100    10    1    |  bin->dec\n");
        $write(" -------------------------------------------------\n");

        for (idx = 0; idx < 128; idx = idx + 1) begin
            temp = 0;
            binz = idx;
            #`STEP;

            int100 = hudz;
            int10 = tenz;
            int1 = onez;
            temp = (100 * int100) + (10 * int10) + int1;
            
            $write(" %3d  :  %8b  |  %4b  %4b  %4b  |  %3d    ,  ",
                idx, binz, hudz, tenz, onez, temp);
            if (idx == temp) $write("good\n");
        end

        #`STEP;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


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


////////~~~~~~~~END>  bcd_2_dec.v
