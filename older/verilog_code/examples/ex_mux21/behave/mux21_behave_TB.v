/*
    test "mux21_behave"
*/

`timescale 1ns/1ns
`include "mux21_behave.v"


module mux21_behave_TB();
    
    // inputs
    reg D0;
    reg D1;
    reg SEL;

    // outputs
    wire OUTP;

    // instanciate
    mux21_behave DUT (
                    .outp(OUTP), 
                    .inp0(D0), 
                    .inp1(D1), 
                    .sel(SEL)
                    );

    initial begin
        $dumpfile("mux21_behave_TB.vcd");
        $dumpvars(0, mux21_behave_TB);
        D0 = 1'b0;
        D1 = 1'b0;
        SEL = 1'b0;
        $display("\nTIME  D0  |  D1  |  Sel  >>> Output\n");
        $monitor("%2t     %d      %d       %d         %d", 
            $time, D0, D1, SEL, OUTP);
        #100 
            $display("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
            $finish;
    end

    always #39 D0 = ~D0;
    always #21 D1 = ~D1;
    always #10 SEL = ~SEL;

endmodule

////////~~~~~~~~END>  mux21_behave_TB.v
