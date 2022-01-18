/*
    using a 5-bit binary input {0:31}

    the 7-segment display to FPGA, 2 digit {0-9}{0-9}

            hex[0]
    hex[5]         hex[1]
            hex[6]
    hex[4]         hex[2]
            hex[3]

    !!!  you make it "low" == 1'b0  to turn the segment on
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    wire [6:0] seg2;
    wire [6:0] seg1;
    reg [4:0] select;

    integer idx;
    
    seg7_dig2 DUT (
                    .disp2(seg2),
                    .disp1(seg1),
                    .cntl(select)
            );
    
    initial begin
        $write("\n test the 2-digit 7-segment displays\n\n");
        for (idx = 0; idx < 32; idx = idx + 1) begin
            select = idx;
            #`STEP

            $write(" selected:  %4b_%1b  { %2d }  ,  digit#2:  %4b_%3b  -->",
                select[4:1], select[0], select, seg2[6:3], seg2[2:0]);
            retDig(seg2, 1'b0);
            $write("                               digit#1:  %4b_%3b  -->",
                seg1[6:3], seg1[2:0]);
            retDig(seg1, 1'b1);
        end
        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic retDig;
        input [6:0] regIn;
        input last;
        begin
            if (last == 1'b1) begin
                case(regIn)
                    7'b1000_000 : $write("  0\n\n");
                    7'b1111_001 : $write("  1\n\n");
                    7'b0100_100 : $write("  2\n\n");
                    7'b0110_000 : $write("  3\n\n");
                    7'b0011_001 : $write("  4\n\n");
                    7'b0010_010 : $write("  5\n\n");
                    7'b0000_010 : $write("  6\n\n");
                    7'b1111_000 : $write("  7\n\n");
                    7'b0000_000 : $write("  8\n\n");
                    7'b0011_000 : $write("  9\n\n");
                    default :     $write("  ERROR\n\n");
                endcase
            end
            else begin
                case(regIn)
                    7'b1000_000 : $write("  0\n");
                    7'b1111_001 : $write("  1\n");
                    7'b0100_100 : $write("  2\n");
                    7'b0110_000 : $write("  3\n");
                    7'b0011_001 : $write("  4\n");
                    7'b0010_010 : $write("  5\n");
                    7'b0000_010 : $write("  6\n");
                    7'b1111_000 : $write("  7\n");
                    7'b0000_000 : $write("  8\n");
                    7'b0011_000 : $write("  9\n");
                    default :     $write("  ERROR\n");
                endcase
            end
            
        end
    endtask

    task disp_out;
        input [6:0] seg_out;
        begin
            $write("\n");
            case(seg_out)
                7'b1000_000 :
                    begin
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                    end
                7'b1111_001 :
                    begin
                        $write("\t  |\n");
                        $write("\t  |\n");
                    end
                7'b0100_100 :
                    begin
                        $write("\t --\n");
                        $write("\t   |\n");
                        $write("\t --\n");
                        $write("\t|\n");
                        $write("\t --\n");
                    end
                7'b0110_000 :
                    begin
                        $write("\t--\n");
                        $write("\t  |\n");
                        $write("\t--\n");
                        $write("\t  |\n");
                        $write("\t--\n");
                    end
                7'b0011_001 :
                    begin
                        $write("\t|  |\n");
                        $write("\t --\n");
                        $write("\t   |\n");
                    end
                7'b0010_010 :
                    begin
                        $write("\t --\n");
                        $write("\t|\n");
                        $write("\t --\n");
                        $write("\t   |\n");
                        $write("\t --\n");
                    end
                7'b0000_010 :
                    begin
                        $write("\t --\n");
                        $write("\t|\n");
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                    end
                7'b1111_000 :
                    begin
                        $write("\t --\n");
                        $write("\t   |\n");
                        $write("\t   |\n");
                    end
                7'b0000_000 :
                    begin
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                    end
                7'b0011_000 :
                    begin
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                        $write("\t   |\n");
                    end
                default : $write("NO OUTPUT");

            endcase
            $write("\n");
        end
    endtask
endmodule


////~~~~ top module, for using x2 7-segment displays


module seg7_dig2 (
                    output wire [6:0] disp2,
                    output wire [6:0] disp1,
                    input wire [4:0] cntl
            );
    
    wire [3:0] onez;
    wire [3:0] tenz;

    my_bcd getDigs (
                        .tens(tenz),
                        .ones(onez),
                        .bin_in(cntl)
                );
    
    seg7_dig dig2 (
                    .cntl_4bit(tenz),
                    .disp_4bit(disp2)
                );
    
    seg7_dig dig1 (
                    .cntl_4bit(onez),
                    .disp_4bit(disp1)
                );

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
            default : disp_4bit = {7{OFF}};
        endcase
    end
endmodule


////~~~~ get the 2 decimal digits of 5-bit binary


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


////////~~~~~~~~END>  seg7_dig2.v
