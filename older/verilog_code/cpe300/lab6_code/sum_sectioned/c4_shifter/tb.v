/*
    test:  c4_shifter
*/

`include "c4_shifter.v"


module tb();

    wire [7:0] from_shifter;
    reg [7:0] from_alu;
    reg [1:0] SH;

    integer idx;
    integer seed;
    reg [7:0] temp;

    c4_shifter DUT (
                    .from_shifter(from_shifter),
                    .from_alu(from_alu),
                    .SH(SH)
            );
    
    initial begin
        `ifdef DEBUG_WAVE
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        seed = `SEED;
        $write("\n test component 4 of 5, the shifter\n\n");

        for (idx = 0; idx < 8; idx = idx + 1) begin
            temp[idx] = $random(seed) % 2; 
        end

        for (idx = 0; idx < 4; idx = idx + 1) begin
            SH = idx;
            from_alu = temp;
            #`HALF;

            `ifdef DEBUG_TB
                $write(" selector:  %2b ,  ", SH);
                case (SH)
                    2'b00 : $write("pass through\n");
                    2'b01 : $write("left shift\n");
                    2'b10 : $write("right shift\n");
                    2'b11 : $write("rotate right\n");
                endcase
                $write("                   %4b_%4b  before shifter\n", 
                    from_alu[7:4], from_alu[3:0]);
                $write("                   %4b_%4b  after shifter\n\n", 
                    from_shifter[7:4], from_shifter[3:0]);
            `endif
        end

        #`HALF
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %6t ns\n\n", $time);
        $finish;
    end

endmodule


////////~~~~~~~~END>  tb.v
