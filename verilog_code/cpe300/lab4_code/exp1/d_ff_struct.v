/*
    structural D flip flop
        complementary output ~Q
        clk posedge: inD -> outQ
*/

`timescale 1ns/1ns
`define HALF 5
`define REPS 4
`define SEED 888


module tb();
    wire Q;
    wire Qn;
    reg D;
    reg clrN;
    reg clk;

    integer idx;
    integer seed;

    dFF_struct DUT(
                    .outQ(Q),
                    .outQn(Qn),
                    .inD(D),
                    .clearN(clrN),
                    .clock(clk)
            );
    
    always begin
        #`HALF;
        clk = ~clk;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\ntest the structural Dff\n\n");
        clrN = 1'b1;
        clk = 1'b0;
        D = 1'b0;
        seed = `SEED;
        $write(" clrN  D  |  Q  Qn\n");
        $write(" ------------------\n\n");

        for (idx = 0; idx < `REPS; idx = idx +1) begin
            D = $random(seed) % 2;
            #(`HALF - 1);
            $write("  %1b    %1b  |  %1b   %1b     %3t ns  before edge\n",
                clrN, D, Q, Qn, $time);
            #2;
            $write("  %1b    %1b  |  %1b   %1b     %3t ns  after edge\n\n",
                clrN, D, Q, Qn, $time);
            #(`HALF - 1);
        end

        clrN = 1'b0;
        $write(" ------------------\n\n");
        for (idx = 0; idx < `REPS; idx = idx +1) begin
            D = $random(seed) % 2;
            #(`HALF - 1);
            $write("  %1b    %1b  |  %1b   %1b     %3t ns  before edge\n",
                clrN, D, Q, Qn, $time);
            #2;
            $write("  %1b    %1b  |  %1b   %1b     %3t ns  after edge\n\n",
                clrN, D, Q, Qn, $time);
            #(`HALF - 1);
        end
        
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module dFF_struct(
                    output wire outQ,
                    output wire outQn,
                    input wire inD,
                    input wire clearN,
                    input wire clock
                );
    wire w_not;
    wire w_and1;
    wire w_and2;
    wire w_nor1;
    wire w_nor2;

    not(w_not, inD);
    and(w_and1, w_not, clock);
    and(w_and2, inD, clock);
    nor(w_nor1, w_and1, w_nor2);
    nor(w_nor2, w_and2, w_nor1);
    
    assign outQ = w_nor1 & clearN;
    assign outQn = ~outQ;
    //nor(outQ, w_and1, outQn, ~clearN);
    //nor(outQn, w_and2, outQ);
    
endmodule


////////~~~~~~~~END>  d_ff_struct.v
