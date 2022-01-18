/*
    test:  shifter8
*/


`include "shifter8.v"


module shifter8_tb();

    wire [7:0] outP;
    reg [7:0] inP;
    reg [1:0] select;

    integer idx;
    integer seed;
    reg [7:0] temp;

    shifter8 DUT (
                    .to_bus(outP),
                    .from_alu(inP),
                    .shift_operation(select)
            );
    
    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, shifter8_tb);
        `endif
        seed = `SEED;
        $write("\n test the 8-bit shifter\n\n");

        for (idx = 0; idx < 8; idx = idx + 1) begin
            temp[idx] = $random(seed) % 2;    // {0,1}
        end

        for (idx = 0; idx < 4; idx = idx + 1) begin
            select = idx;
            inP = temp;
            #`STEP;

            `ifdef DEBUG_tb
                $write(" selector:  %2b ,  ", select);
                case (select)
                    2'b00 : $write("pass\n");
                    2'b01 : $write("left shift\n");
                    2'b10 : $write("right shift\n");
                    2'b11 : $write("rotate right\n");
                endcase
                $write("                   %4b_%4b  before shifter\n", 
                    inP[7:4], inP[3:0]);
                $write("                   %4b_%4b  after shifter\n\n", 
                    outP[7:4], outP[3:0]);
            `endif
        end

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////////~~~~~~~~END>  shifter8_tb.v
