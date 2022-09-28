module texp2 (
                    input wire in_a,
                    input wire in_b,
                    output wire out_y
                );
    wire t_1;
    wire t_2;
    wire w_1;
    wire w_2;

    not b_bar (w_1, in_b);
    not a_bar (w_2, in_a);
    and and_g1 (t_1, w_1, in_a);
    and and_g2 (t_2, w_2, in_b);
    or or_g (out_y, t_1, t_2);

endmodule
