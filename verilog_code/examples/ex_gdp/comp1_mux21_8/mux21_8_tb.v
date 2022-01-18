/*
    test:  mux21_8
*/

`include "mux21_8.v"
`define REPS 3


module mux21_8_tb();
    wire [7:0] outRF;
    reg [7:0] inShifter;
    reg [7:0] inData;
    reg select;
    integer ii;
    integer jj;
    integer seed;

    mux21_8 DUT (
                    .to_register_file(outRF),
                    .from_shifter(inShifter),
                    .input_data(inData),
                    .mux_selector(select)
            );
    
    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, mux21_8_tb);
        `endif
        seed = `SEED;
        $write("\ntest 2-to-1 MUX, 8-bit bus\n\n");

        for (ii = 0; ii < `REPS; ii = ii + 1) begin
            select = $random(seed) % 2;
            for (jj = 0; jj < 8; jj = jj + 1) begin
                inShifter[jj] = $random(seed) % 2;
                inData[jj] = $random(seed) % 2;
            end
            #`STEP;

            `ifdef DEBUG_tb
                $write(" selector:  %1b\n", select);
                $write("     inp[0]:  %4b_%4b\n", 
                    inShifter[7:4], inShifter[3:0]);
                $write("     inp[1]:  %4b_%4b\n",
                    inData[7:4], inData[3:0]);
                $write("       outp:  %4b_%4b\n\n",
                    outRF[7:4], outRF[3:0]);
            `endif
        end

        #`STEP;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish; 
    end

endmodule 


////////~~~~~~~~END>  mux21_8_tb.v
