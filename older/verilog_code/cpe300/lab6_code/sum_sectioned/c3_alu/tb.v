/*
    test:  c3_alu
*/

`include "c3_alu.v"


module tb();
    wire [7:0] from_alu;
    reg [7:0] A_bus;
    reg [7:0] B_bus;
    reg [2:0] ALU;

    integer seed;
    integer ii;
    integer jj;

    c3_alu DUT (
                    .from_alu(from_alu),
                    .A_bus(A_bus),
                    .B_bus(B_bus),
                    .ALU(ALU)
                );
    
    initial begin
        `ifdef DEBUG_WAVE
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        seed = `SEED;
        $write("\n test component 3 of 5, the ALU\n\n");

        for (ii = 0; ii < 8; ii = ii + 1) begin
            ALU = ii;
            for (jj = 0; jj < 8; jj = jj + 1) begin
                A_bus[jj] = $random(seed) % 2;
                B_bus[jj] = $random(seed) % 2;
            end
            #`HALF;

            `ifdef DEBUG_TB
                $write(" operation =  %3b  ,  ", ALU);
                case(ALU)
                    3'b000 : $write("pass through\n");
                    3'b001 : $write("AND\n");
                    3'b010 : $write("OR\n");
                    3'b011 : $write("NOT\n");
                    3'b100 : $write("addition\n");
                    3'b101 : $write("subtraction\n");
                    3'b110 : $write("increment\n");
                    3'b111 : $write("decrement\n");
                endcase
                $write("         A =  %4b_%4b   \"%3d\"\n", 
                    A_bus[7:4], A_bus[3:0], A_bus);
                $write("         B =  %4b_%4b   \"%3d\"\n", 
                    B_bus[7:4], B_bus[3:0], B_bus);
                $write("      --------------------------\n");
                $write("  from_alu =  %4b_%4b   \"%3d\"\n\n", 
                    from_alu[7:4], from_alu[3:0], from_alu);
            `endif
        end

        #`HALF
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////////~~~~~~~~END>  tb.v
