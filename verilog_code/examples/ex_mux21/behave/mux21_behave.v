/*
    model the 2:1 MUX with behavioral
*/

module mux21_behave (outp, inp0, inp1, sel);

    output reg outp;
    input wire inp0;
    input wire inp1;
    input wire sel;
    
    always @ (inp0 or inp1 or sel)
        begin
            if (sel)
                outp = inp1;
            else
                outp = inp0; 
        end

endmodule

////////~~~~~~~~END>  mux21_behave.v
