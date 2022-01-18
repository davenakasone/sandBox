/*
    model the 2:1 MUX with gates
*/

module mux21_gate (outp, inp0, inp1, sel);

    output outp;
    input inp0;
    input inp1;
    input sel;
    wire w0;
    wire w1;
    wire sel_BAR;

    and (w0, inp0, sel_bar);
    and (w1, inp1, sel);
    not (sel, sel_BAR);
    or (outp, w0, w1);

endmodule

////////~~~~~~~~END>  mux21_gate.v

