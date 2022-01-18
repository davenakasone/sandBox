/*
    input 4-bit binary
    get correct 7-segment [0:9,A:F]

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
    reg [3:0] select;
    wire [6:0] seg;

    integer idx;
    reg [3:0] transfer;

    m_seg7hex DUT (
                    .cntl(select),
                    .disp(seg)
                );
    
    initial begin
        $write("\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            select = idx;
            #`STEP
            $write("selected:  %4b  ,  disp:  %4b_%3b  -->  %1h  ,  7seg:  ",
                select, seg[6:3], seg[2:0], idx);
            disp_out(seg, transfer);
            $write("%1h\n", transfer);
        end
        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic disp_out;
        input [6:0] seg_out;
        output [3:0] to_hex;
        begin
            case(seg_out)
                7'b1000_000 : to_hex = 4'h0;
                7'b1111_001 : to_hex = 4'h1;
                7'b0100_100 : to_hex = 4'h2;
                7'b0110_000 : to_hex = 4'h3;
                7'b0011_001 : to_hex = 4'h4;
                7'b0010_010 : to_hex = 4'h5;
                7'b0000_010 : to_hex = 4'h6;
                7'b1111_000 : to_hex = 4'h7;
                7'b0000_000 : to_hex = 4'h8;
                7'b0011_000 : to_hex = 4'h9;
                7'b0001_000 : to_hex = 4'hA;
                7'b0000_011 : to_hex = 4'hB;
                7'b1000_110 : to_hex = 4'hC;
                7'b0100_001 : to_hex = 4'hD;
                7'b0000_110 : to_hex = 4'hE;
                7'b0001_110 : to_hex = 4'hF;
                default : to_hex = 4'bXXXX;
            endcase
        end
    endtask
    
endmodule


////~~~~


module m_seg7hex (
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
            4'b1010 :
                begin
                    disp[6:0] = {7{ON}};
                    disp[3] = OFF;
                end
            4'b1011 :
                begin
                    disp[6:0] = {7{ON}};
                    disp[1:0] = {2{OFF}};
                end
            4'b1100 :
                begin
                    disp[5:3] = {3{ON}};
                    disp[0] = ON;
                end
            4'b1101 :
                begin
                    disp[4:1] = {4{ON}};
                    disp[6] = ON;
                end
            4'b1110 :
                begin
                    disp[6:3] = {4{ON}};
                    disp[0] = ON;
                end
            4'b1111 :
                begin
                    disp[6:4] = {3{ON}};
                    disp[0] = ON;
                end
        endcase
    end

endmodule

////////~~~~~~~~END>  seg7hex.v
