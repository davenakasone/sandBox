
module preA_fpga (
            output wire out_x,
            output wire out_y,
            input wire in_a,
            input wire in_b,
            input wire in_c
          );
    wire t1;
    wire t2;

    xnor g1(t1, in_a, in_b);
    not g2(out_x, t1);
    and g3(t2, out_x, in_c);
    or g4(out_y, t2, in_b);
endmodule
