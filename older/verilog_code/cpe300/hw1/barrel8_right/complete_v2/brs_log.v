/*
    combines the x3 "barrel8" right shifters 
    into 3-level shifter
*/

`timescale 1ns/1ns


module barrel8_s1 (
                    output reg [7:0] out_y,
                    input wire selector,
                    input wire [7:0] in_x
                );
    always @ (*) begin
        out_y = in_x;
        if (selector) begin
            out_y = out_y >> 1'b1;
        end
    end
endmodule


////~~~~


module barrel8_s2 (
                    output reg [7:0] out_y,
                    input wire selector,
                    input wire [7:0] in_x
                );
    always @ (*) begin
        out_y = in_x;
        if (selector) begin
            out_y = out_y >> 2'b10;
        end
    end
endmodule


////~~~~


module barrel8_s4 (
                    output reg [7:0] out_y,
                    input wire selector,
                    input wire [7:0] in_x
                );
    always @ (*) begin
        out_y = in_x;
        if (selector) begin
            out_y = out_y >> 3'b100;
        end
    end
endmodule


////~~~~


module brs_log (
                    output reg [7:0] outp_y,
                    input wire [2:0] shift_ct, 
                    input wire [7:0] inp_x
                );
    wire [7:0] w_1_to_2;
    wire [7:0] w_2_to_4;
    wire [7:0] stop;
    reg [7:0] start;
    reg [7:0] r_1_to_2;
    reg [7:0] r_2_to_4;
    
    barrel8_s1 level1 (
                        .out_y(w_1_to_2),
                        .selector(shift_ct[0]),
                        .in_x(start)
                       );

    barrel8_s2 level2 (
                        .out_y(w_2_to_4),
                        .selector(shift_ct[1]),
                        .in_x(r_1_to_2)
                      );

    barrel8_s4 level3 (
                        .out_y(stop),
                        .selector(shift_ct[2]),
                        .in_x(r_2_to_4)
                      );

    always @ (*) begin
        start = inp_x;
        r_1_to_2 = w_1_to_2;
        r_2_to_4 = w_2_to_4;
        outp_y = stop;
    end

endmodule

////////~~~~~~~~END>  brs_log.v
