/*
    model the 2:1 MUX with data flow
*/

module mux21_data (outp, inp0, inp1, sel);

    output outp;
    input inp0;
    input inp1;
    input sel;
    
    assign outp = (sel) ? inp1 : inp0;

endmodule

////////~~~~~~~~END>  mux21_data.v
