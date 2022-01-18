/*
    test:  c5_triBuff
*/

`include "c5_triBuff.v"
`define REPS 7

module tb();
    wire [7:0] result;
    reg [7:0] from_shifter;
    reg OE;

    integer seed;
    integer ii;
    integer jj;

    c5_triBuff DUT (
                        .result(result),
                        .from_shifter(from_shifter),
                        .OE(OE)
                );

    initial begin
        `ifdef DEBUG_WAVE
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        seed = `SEED;
        $write("\ntest component 5 of 5, the tri-state buffer  ,  iterations:  %2d\n\n", `REPS);

        for (ii = 0; ii < `REPS; ii = ii + 1) begin
            OE = $random(seed) % 2;
            for (jj = 0; jj < 8; jj = jj + 1) begin
                from_shifter[jj] = $random(seed) % 2;
            end
            #`HALF;

            `ifdef DEBUG_TB
                $write(" enable =  %1b\n", OE);
                $write(" input  =  %4b_%4b\n", from_shifter[7:4], from_shifter[7:4]);  
                $write(" output =  %4b_%4b", result[7:4], result[3:0]);
                if (OE == 1'b0) begin
                    $write("    ---> Valid\n\n");
                end
                else if (OE == 1'b1 && result == from_shifter) begin
                    $write("    ---> Valid\n\n");
                end
                else begin
                    $write("    ---> !!!~~~*** FAIL ***~~~!!!\n\n");
                end
            `endif
        end

        #`HALF
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %6t ns\n\n", $time);
        $finish;
    end

endmodule


////////~~~~~~~~END>  tb.v
