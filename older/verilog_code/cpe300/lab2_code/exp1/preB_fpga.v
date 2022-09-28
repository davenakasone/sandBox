
module preB_fpga (
                    output wire out_y,
                    input wire in_a,
                    input wire in_b,
                    input wire in_c
                );
    assign out_y = in_a * (in_b + in_c) + (in_b * (~in_c)) + in_a;
endmodule
