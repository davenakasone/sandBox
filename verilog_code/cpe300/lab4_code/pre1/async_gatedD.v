/*
    aysnchorous    set, clear
    gated D latch
*/

`timescale 1ns/1ns
`define STEP 5
`define REPS 6
`define SEED 77

module tb();
    wire Q;
    reg clk;
    reg D;
    reg set;
    reg clear;

    integer split;
    integer idx;
    integer seed;

    myLatch DUT (
                .outQ(Q),
                .clock(clk),
                .inD(D),
                .inSet(set),
                .inClr(clear)
            );
    
    always begin
        #`STEP;
        clk = ~clk;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        seed = `SEED;
        split = `STEP + 1;
        clear = 1'b0;
        clk = 1'b0;
        #1;
        clear = 1'b1;
        set = 1'b0;
        $write("\ntest the gated-D latch with async set and clear\n\n");
        $write(" clk  Din  set  clear  |  Q   Qnext   time\n");
        $write(" ----------------------------------\n");

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            D = $random(seed) %2;
            set = 1'b1;
            clear = 1'b1;
            #split;
            disp(Q, clk, D, set, clear);
        end
        $write(" ----------------------------------\n");

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            D = $random(seed) %2;
            set = 1'b1;
            clear = 1'b1;
            #split;
            disp(Q, clk, D, set, clear);
        end
        $write(" ----------------------------------\n");

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            D = $random(seed) %2;
            set = 1'b1;
            clear = 1'b0;
            #split;
            disp(Q, clk, D, set, clear);
        end
        $write(" ----------------------------------\n");

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            D = $random(seed) %2;
            set = 1'b0;
            clear = 1'b1;
            #split;
            disp(Q, clk, D, set, clear);
        end
        $write(" ----------------------------------\n");

        #`STEP;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task disp;
        input Q;
        input clk;
        input D;
        input set;
        input clear;
        
        reg qnxt;

        begin
            qnxt = (~clk & Q) | (clk & D);
            $write("   %1b   %1b    %1b     %1b    |  %1b    %1b     %3t\n",
                clk, D, set, clear, Q, qnxt, $time);
        end
    endtask 
endmodule


////~~~~


module myLatch(
                output wire outQ,
                input wire clock,
                input wire inD,
                input wire inSet,
                input wire inClr
);
    wire d_not;
    wire nand1_out;       //     nand1 ->  nand3  -> Q
    wire nand2_out;       //     nand2 ->  nand4  -> ~Q
    wire nand3_out;       
    wire nand4_out;      
    
    nand(nand1_out, inD, clock);
    not(d_not, inD);
    nand(nand2_out, d_not, clock);
    nand(nand3_out, nand1_out, nand4_out, inSet);
    nand(nand4_out, nand2_out, nand3_out, inClr);
    assign outQ = nand3_out;

endmodule

////////~~~~~~~~ END>  async_gatedD.v

