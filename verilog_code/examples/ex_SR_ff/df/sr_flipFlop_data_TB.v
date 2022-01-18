/*
    test "sr_flipFlop"
*/

`timescale 1ns/1ns
`include "sr_flipFlop_data.v"


module sr_flipFlop_TB();
    
    // inputs
    reg CLK;
    reg R;
    reg S;

    // outputs
    wire OUTP;

    // make instance
    sr_flipFlop DUT (
                    .Q(OUTP),
                    .clk(CLK),
                    .rst(R),
                    .set(S)
                );

    

    initial begin
        $dumpfile("sr_flipFlop_data_TB.vcd");
        $dumpvars(0, sr_flipFlop_TB);
        CLK = 1'b0;
        R = 1'b0;
        S = 1'b0;
        $display("\nTIME  S |  R  |  CLK  >>>  Q\n");
        $monitor("%2t     %d      %d       %d         %d", 
            $time, S, R, CLK, OUTP);
        #100 
            $display("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
            $finish;
    end

    always #1 CLK = ~CLK;  // 2ns period
    always #9 S = ~S;
    always #21 R = ~R;

endmodule

////////~~~~~~~~END>  sr_flipFlop_data_TB.v
