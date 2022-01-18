/*
    the 8-bit barrel-right shift/bypass

        BYPASS:  selector == 0
        RIGHT SHIFT:  selector == 1
*/

module barrel8 (out_y, selector, in_x);
    output reg [7:0] out_y;
    input wire selector;
    input wire [7:0] in_x;

    always @ (in_x) begin
        out_y = in_x;
        if (selector) begin
            out_y = out_y >> 1;
        end
    end

endmodule

////////~~~~~~~~END>  barrel8_right.v
