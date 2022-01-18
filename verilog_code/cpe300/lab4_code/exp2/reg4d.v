/*
    4-bit reg from Dff, structual model
*/

`timescale 1ns/1ns
`define HALF 5
`define REPS 4
`define SEED 888


module tb();
    wire [3:0] Q;
    reg [3:0] D;
    reg clrN;
    reg clk;

    integer ii;
    integer jj;
    integer seed;

    reg4d DUT (
                .q_bus(Q),
                .d_bus(D),
                .clrN(clrN),
                .clk(clk)
        );
    
    always begin
        #`HALF;
        clk = ~clk;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\ntest the structural Dff, in 4-bit reg\n\n");
        clrN = 1'b1;
        clk = 1'b0;
        D = 4'b0000;
        seed = `SEED;
        $write(" clrN    D   |   Q \n");
        $write(" --------------------\n\n");

        for (ii = 0; ii < `REPS; ii = ii + 1) begin
            for (jj = 0; jj < 4; jj = jj + 1) begin
                D[jj] = $random(seed) % 2;
            end
            #(`HALF - 1);
            $write("  %1b    %4b  |  %4b      %3t ns  before edge\n",
                clrN, D, Q, $time);
            #2;
            $write("  %1b    %1b  |  %4b      %3t ns  after edge\n\n",
                clrN, D, Q, $time);
            #(`HALF - 1);
        end

        clrN = 1'b0;
        $write(" --------------------\n\n");
        for (ii = 0; ii < `REPS; ii = ii + 1) begin
            for (jj = 0; jj < 4; jj = jj + 1) begin
                D[jj] = $random(seed) % 2;
            end
            #(`HALF - 1);
            $write("  %1b    %4b  |  %4b      %3t ns  before edge\n",
                clrN, D, Q, $time);
            #2;
            $write("  %1b    %1b  |  %4b      %3t ns  after edge\n\n",
                clrN, D, Q, $time);
            #(`HALF - 1);
        end
        
        
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


module reg4d (
                output wire [3:0] q_bus,
                input wire [3:0] d_bus,
                input wire clrN,
                input wire clk
        );
    
    dFF_struct dff_0 (
                        .outQ(q_bus[0]),
                        .inD(d_bus[0]),
                        .clearN(clrN),
                        .clock(clk)
                );
    
    dFF_struct dff_1 (
                        .outQ(q_bus[1]),
                        .inD(d_bus[1]),
                        .clearN(clrN),
                        .clock(clk)
                );
    
    dFF_struct dff_2 (
                        .outQ(q_bus[2]),
                        .inD(d_bus[2]),
                        .clearN(clrN),
                        .clock(clk)
                );
    
    dFF_struct dff_3 (
                        .outQ(q_bus[3]),
                        .inD(d_bus[3]),
                        .clearN(clrN),
                        .clock(clk)
                );
    
endmodule


////~~~~


module dFF_struct(
                    output wire outQ,
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
endmodule


////////~~~~~~~~END>  reg4d.v
