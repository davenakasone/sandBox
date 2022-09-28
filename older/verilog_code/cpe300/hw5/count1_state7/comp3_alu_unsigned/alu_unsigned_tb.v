/*
    test:  alu_unsigned
*/

`include "alu_unsigned.v"


module alu_unsigned_tb();
    wire [7:0] outP;
    reg [7:0] inpA;
    reg [7:0] inpB;
    reg [2:0] select;

    integer seed;
    integer ii;
    integer jj;

    alu_unsigned DUT (
                        .to_shifter(outP),
                        .rf_A(inpA),
                        .rf_B(inpB),
                        .alu_operation(select)
                );
    
    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, alu_unsigned_tb);
        `endif
        seed = `SEED;
        $write("\ntest the ALU\n\n");

        for (ii = 0; ii < 8; ii = ii + 1) begin
            select = ii;
            for (jj = 0; jj < 8; jj = jj + 1) begin
                inpA[jj] = $random(seed) % 2;
                inpB[jj] = $random(seed) % 2;
            end
            #`STEP;

            `ifdef DEBUG_tb
                $write(" operation =  %3b  ,  ", select);
                case(select)
                    3'b000 : $write("pass\n");
                    3'b001 : $write("AND\n");
                    3'b010 : $write("OR\n");
                    3'b011 : $write("NOT\n");
                    3'b100 : $write("addition\n");
                    3'b101 : $write("subtraction\n");
                    3'b110 : $write("increment\n");
                    3'b111 : $write("decrement\n");
                endcase
                $write("         A =  %4b_%4b   \"%3d\"\n", 
                    inpA[7:4], inpA[3:0], inpA);
                $write("         B =  %4b_%4b   \"%3d\"\n", 
                    inpB[7:4], inpB[3:0], inpB);
                $write("      --------------------------\n");
                $write("      outP =  %4b_%4b   \"%3d\"\n\n", 
                    outP[7:4], outP[3:0], outP);
            `endif
        end

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////////~~~~~~~~END>  alu_unsinged_tb.v
