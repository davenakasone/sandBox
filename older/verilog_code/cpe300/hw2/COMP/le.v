/*
    "logic extension circuit"
*/

module LE (
            output out_xi,
            input in_ai,
            input in_bi,
            input [2:0] sel
          );
    wire w_not1_and4_g4;
    wire w_not2_and2_g2;
    wire w_not3_and3_g3;
    wire w_not4_and4_g4;
    wire w_and2_g1;
    wire w_and2_g2;
    wire w_and3_g3;
    wire w_and4_g4;
    wire w_or2_g1;

    not not1_and4_g4 (w_not1_and4_g4, sel[2]);
    not not2_and2_g2 (w_not2_and2_g2, sel[0]);
    not not3_and3_g3 (w_not3_and3_g3, sel[1]);
    not not4_and4_g4 (w_not4_and4_g4, in_ai);

    and and2_g1 (w_and2_g1, in_ai);
    and and2_g2 (w_and2_g2, w_not2_and2_g2, in_ai);
    and and3_g3 (w_and3_g3, w_not3_and3_g3, in_ai, in_bi);
    or or2_g1 (w_or2_g1, in_bi, sel[0]);
    and and4_g4 (w_and4_g4, w_not1_and4_g4, w_not4_and4_g4, w_or2_g1, sel[1]);
endmodule
