/*
    the 7-segment display to FPGA

            hex[0]
    hex[5]         hex[1]
            hex[6]
    hex[4]         hex[2]
            hex[3]
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    reg [3:0] select;
    wire [6:0] seg;
    integer idx;

    seg7 DUT (
                .cntl(select),
                .disp(seg)
            );
    
    initial begin
        $write("\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            select = idx;
            #`STEP
            $write("selected:  %4b  ,  disp:  %4b_%3b  -->  %2d\n",
                select, seg[6:3], seg[2:0], idx);
            disp_out(seg);
        end
        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task disp_out;
        input [6:0] seg_out;
        begin
            $write("\n");
            case(seg_out)
                7'b0111_111 :
                    begin
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                    end
                7'b0000_110 :
                    begin
                        $write("\t  |\n");
                        $write("\t  |\n");
                    end
                7'b1011_011 :
                    begin
                        $write("\t --\n");
                        $write("\t   |\n");
                        $write("\t --\n");
                        $write("\t|\n");
                        $write("\t --\n");
                    end
                7'b1001_111 :
                    begin
                        $write("\t--\n");
                        $write("\t  |\n");
                        $write("\t--\n");
                        $write("\t  |\n");
                        $write("\t--\n");
                    end
                7'b1100_110 :
                    begin
                        $write("\t|  |\n");
                        $write("\t --\n");
                        $write("\t   |\n");
                    end
                7'b1101_101 :
                    begin
                        $write("\t --\n");
                        $write("\t|\n");
                        $write("\t --\n");
                        $write("\t   |\n");
                        $write("\t --\n");
                    end
                7'b1111_101 :
                    begin
                        $write("\t --\n");
                        $write("\t|\n");
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                    end
                7'b0000_111 :
                    begin
                        $write("\t --\n");
                        $write("\t   |\n");
                        $write("\t   |\n");
                    end
                7'b1111_111 :
                    begin
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                        $write("\t|  |\n");
                        $write("\t --\n");
                    end
                7'b1100_111 :
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


////~~~~


module seg7(
                input [3:0] cntl,
                output reg [6:0] disp
            );

    parameter ON = 1'b1;
    parameter OFF = 1'b0;

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
        endcase
    end
endmodule

////////~~~~~~~~END>  seg7.v
