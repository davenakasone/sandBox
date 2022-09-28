/*
    model the 2:1 MUX with structural
*/

module and2_gate (and_out, and_in0, and_in1);
    input and_in0;
    input and_in1;
    output and_out;
    assign and_out = and_in0 & and_in1;
endmodule


module not_gate (not_out, not_in);
    input not_in;
    output not_out;
    assign not_out = ~not_in;
endmodule


module or2_gate (or_out, or_in0, or_in1);
    input or_in0;
    input or_in1;
    output or_out;
    assign or_out = or_in0 | or_in1;
endmodule


module mux21_stc (outp, inp0, inp1, sel);

    output outp;
    input inp0;
    input inp1;
    input sel;
    wire w1, w2, w3;

    and2_gate u1 (w1, inp1, sel);
    not_gate u2 (w2, sel);
    and2_gate u3 (w3, inp0, w2);
    or2_gate u4 (outp, w1, w3);

endmodule

////////~~~~~~~~END>  mux21_stc.v
