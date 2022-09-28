/*
    tri-state buffer:
        input from wire
        if enable, input passes to output
        else output is Z (high imp)
*/

`timescale 1ps/1ps
`define STEP 10


module tb();
    wire outp;
    reg en;
    reg inp;
    
    tri_buff DUT (
                    .sig_out(outp),
                    .enable(en),
                    .sig_in(inp)
            );
    
    initial begin
        $write("\n test tri-state buffer...\n\n");
        $write(" en  inp  |  outp\n");
        $write(" ------------------\n");

        en = 1'b0; inp = 1'b0;
        #`STEP;
        $write("  %1b    %1b  |    %1b\n", en, inp, outp);

        en = 1'b0; inp = 1'b1;
        #`STEP;
        $write("  %1b    %1b  |    %1b\n", en, inp, outp);

        en = 1'b1; inp = 1'b0;
        #`STEP;
        $write("  %1b    %1b  |    %1b\n", en, inp, outp);

        en = 1'b1; inp = 1'b1;
        #`STEP;
        $write("  %1b    %1b  |    %1b\n", en, inp, outp);

        #`STEP;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module tri_buff (
                    output wire sig_out,
                    input wire enable,
                    input wire sig_in
            );
    assign sig_out = (enable == 1'b1) ? sig_in : 1'bZ;
endmodule


////////~~~~~~~~END>  tri_buff.v
