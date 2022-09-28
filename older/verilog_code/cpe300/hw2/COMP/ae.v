/*
    arithmetic extension
*/

module AE (
            output out_yi,
            input in_bi,
            input [2:0] sel
          );
    wire w_not1_or2_g1;
    wire w_not2_and4_g2;
    wire w_not3_and4_g2;
    wire w_or2_g1;
    wire w_and3_g1;
    wire w_and4_g2;

    not not1_or2_g1 (w_not1_or2_g1, in_bi);
    not not2_and4_g2 (w_not2_and4_g2, sel[0]);
    not not3_and4_g2 (w_not3_and4_g2, sel[1]);

    or or2_g1 (w_or2_g1, sel[1], w_not1_or2_g1);
    and and3_g1 (w_and3_g1, sel[0], sel[2], w_or2_g1);
    and and4_g2 (w_and4_g2, sel[2], in_bi, w_not2_and4_g2, w_not3_and4_g2);
    or or2_g2 (out_yi, w_and3_g1, w_and4_g2);
endmodule
