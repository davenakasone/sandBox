/*
    a [2:0], 7 to 0 down counter
*/

`timescale 1ns/1ns
`define HALF 5
`define REPS 10


module tb();
    wire [2:0] count;
    reg rstN;
    reg clock;

    integer idx;

    counter DUT (
                    .count(count),
                    .rstN(rstN),
                    .clock(clock)
                );
    
    always begin
        #`HALF;
        clock = ~clock;
    end
    
    initial begin
        $write("\n test the down-counter\n\n");
        $write(" clk  rstN  |  count\n");
        $write(" -------------------\n");
        rstN = 1'b1;
        clock = 1'b0;

        $write("  %1b    %1b    |  %3b    %4t ns\n", 
            clock, rstN, count, $time);
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + 1);
            $write("  %1b    %1b    |  %3b    %4t ns\n", 
                clock, rstN, count, $time);
            #(`HALF - 1);
        end

        $write(" -------------------\n");
        rstN = 1'b0;
        #(`HALF + 1);
        $write("  %1b    %1b    |  %3b    %4t ns\n", 
            clock, rstN, count, $time);
        #(`HALF - 1);
        $write(" -------------------\n");
        rstN = 1'b1;
        
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + 1);
            $write("  %1b    %1b    |  %3b    %4t ns\n", 
                clock, rstN, count, $time);
            #(`HALF - 1);
        end
        
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module counter (
                    output reg [2:0] count,
                    input wire rstN,
                    input wire clock
                );

    parameter clear = 3'b111;

    initial begin
        count = clear;
    end

    always @ (posedge clock) begin
        if (rstN == 1'b0) begin
            count = clear;
        end
        else begin
            if (count != 3'b000) begin
                count = count - 1'b1;
            end
        end
    end
endmodule


////////~~~~~~~~END>  counter.v
