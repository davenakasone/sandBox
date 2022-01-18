/*
    register 8
        see diagram
*/

`timescale 1ns/1ns


module register8 (
                    output reg [7:0] outD,
                    input wire [7:0] inD,
                    input wire enable,
                    input wire resetLow,
                    input wire clock
            );
    always @ (posedge clock or resetLow) begin
        if (resetLow == 1'b0) begin
            outD = 8'b0000_0000;
        end
        else if (enable == 1'b1) begin
            outD = inD;
        end
        else begin
            outD = outD;
        end
        $write("  %1b    %1b    %1b    %4b_%4b  |  %4b_%4b    %3t\n",
                clock, resetLow, enable, inD[7:4], inD[3:0], outD[7:4], outD[3:0], $time);
    end
endmodule


////////~~~~~~~~END> register8.v


