/*
    the algorithm to convert BCD to decimal
    usually for the 7-segment display

    takes an 5-bit binary number and gives you the BCD 

    1) if an col ( 10, 1) is <= 5, add 3
    2) shift all numbers to left one position
    3) if 5 shifts performed, it is done, evaluate each col for BCD value
    4) go to step 1 if 5 shifts not performed
*/

`timescale 1ns/1ns
`define STEP 10

module tb();
    wire [3:0] tenz;
    wire [3:0] onez;
    reg [4:0] binz;

    integer idx;
    integer temp;
    integer int10;
    integer int1;

    my_bcd DUT ( 
                    .tens(tenz),
                    .ones(onez),
                    .bin_in(binz)
            );
    
    initial begin
        $write("\n test bin --> BCD, using 5-bit input\n\n");
        $write("  i  :   bin   |   10s    1s  |  bin->dec\n");
        $write(" ----------------------------------------\n");

        for (idx = 0; idx < 32; idx = idx + 1) begin
            temp = 0;
            binz = idx;
            #`STEP;

            int10 = tenz;
            int1 = onez;
            temp = (10 * int10) + int1;
            
            $write(" %2d  :  %5b  |  %4b  %4b  |  %3d    ,  ",
                idx, binz, tenz, onez, temp);
            if (idx == temp) $write("good\n");
        end

        #`STEP;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


module my_bcd ( 
                    output reg [3:0] tens,
                    output reg [3:0] ones,
                    input wire [4:0] bin_in
            );
    integer idx;

    always @ (bin_in) begin
        tens = 4'b0000;
        ones = 4'b0000;
        
        for (idx = 4; idx >= 0; idx = idx - 1) begin
            if (tens >= 3'b101) tens = tens + 2'b11;
            if (ones >= 3'b101) ones = ones + 2'b11;
            
            tens = tens << 1;
            tens[0] = ones[3];
            ones = ones << 1;
            ones[0] = bin_in[idx];
        end
    end
endmodule


////////~~~~~~~~END>  bcd2dec.v
