/*
    test:  mux21_8
*/

`include "c1_mux.v"
`define REPS 4


module tb();
    wire [7:0] from_mux;
    reg [7:0] new_data;
    reg [7:0] feedback;
    reg IE;

    integer ii;
    integer jj;
    integer seed;

    c1_mux DUT (
                        .from_mux(from_mux),
                        .new_data(new_data),
                        .feedback(feedback),
                        .IE(IE)
            );
    
    initial begin
        `ifdef DEBUG_WAVE
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        seed = `SEED;
        $write("\n test component 1 of 5, the MUX 2-to-1 : 8-bit \n\n");

        for (ii = 0; ii < `REPS; ii = ii + 1) begin
            IE = $random(seed) % 2;
            for (jj = 0; jj < 8; jj = jj + 1) begin
                feedback[jj] = $random(seed) % 2;
                new_data[jj] = $random(seed) % 2;
            end
            #`HALF;

            `ifdef DEBUG_TB
                $write("         IE:  %1b\n", IE);
                $write("     inp[0]:  %4b_%4b\n", 
                    feedback[7:4], feedback[3:0]);
                $write("     inp[1]:  %4b_%4b\n",
                    new_data[7:4], new_data[3:0]);
                $write("       outp:  %4b_%4b\n\n",
                    from_mux[7:4], from_mux[3:0]);
            `endif
        end

        #`HALF;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %6t ns\n\n", $time);
        $finish; 
    end

endmodule 


////////~~~~~~~~END>  tb.v
