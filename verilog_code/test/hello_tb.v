`timescale 1ns/1ns
`include "hello.v"

module hello_tb;
    
    reg a; // inputs
    wire b; // outputs

    hello dut(a,b);  // instantiate instance

    initial begin
        $dumpfile("hello_tb.vcd");
        $dumpvars(0, hello_tb);
        a = 0;
        #20
        a = 1;
        #20
        a = 0;
        #20
        $display("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
    end

endmodule

////////~~~~~~~~END>  hello_tb.v
