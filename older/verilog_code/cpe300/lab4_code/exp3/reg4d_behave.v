/*
    4-bit reg from Dff, behavioral model
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

    reg4d_behave DUT (
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
        $write("\ntest behavioral version of the 4-bit reg\n\n");
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


module reg4d_behave (
                        output reg [3:0] q_bus,
                        input wire [3:0] d_bus,
                        input wire clrN,
                        input wire clk
                    );
    always @ (posedge clk or negedge clrN) begin
        if (clrN == 1'b0) begin
            q_bus <= 4'b0000;
        end
        else begin
            q_bus = d_bus;
        end
    end
endmodule


////////~~~~~~~~END>  reg4d_behave.v
