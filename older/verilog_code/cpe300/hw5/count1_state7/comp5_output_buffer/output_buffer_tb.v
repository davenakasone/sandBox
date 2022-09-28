/*
    test:  output_buffer
*/

`include "output_buffer.v"
`define REPS 5

module output_buffer_tb();
    wire [7:0] outP;
    reg [7:0] inP;
    reg enb;

    integer seed;
    integer ii;
    integer jj;

    output_buffer DUT (
                        .result(outP),
                        .from_shifter(inP),
                        .enable(enb)
                );

    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, output_buffer_tb);
        `endif
        seed = `SEED;
        $write("\ntest the final output buffer\n\n");

        for (ii = 0; ii < `REPS; ii = ii + 1) begin
            enb = $random(seed) % 2;
            for (jj = 0; jj < 8; jj = jj + 1) begin
                inP[jj] = $random(seed) % 2;
            end
            #`STEP;

            `ifdef DEBUG_tb
                $write(" enable =  %1b\n", enb);
                $write(" input  =  %4b_%4b\n", inP[7:4], inP[7:4]);  
                $write(" output =  %4b_%4b\n\n", outP[7:4], outP[3:0]);
            `endif
        end

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////////~~~~~~~~END>  output_buffer_tb.v
