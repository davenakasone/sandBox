
`include "and_gate.v"

module and_gateTB();
    reg A;
    reg B;
    wire outP;

    and_gate DUT (
                    .a(A),
                    .b(B),
                    .out(outP)
                 );
    
    initial begin
        $display("\n\ttime\ta,\tb,\tout");
        $monitor("\t%2d,\t%b,\t%b,\t%b", $time, A, B, outP);
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, and_gateTB);
        A = 1'b0; B = 1'b0;
        #10
        A = 1'b0; B = 1'b1;
        #10
        A = 1'b1; B = 1'b0;
        #10
        A = 1'b1; B = 1'b1;
        #10
        A = 1'b0; B = 1'b0;
        #10
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule