/*
    test "register8"
*/

`include "register8.v"
`define HALF 5
`define REPS 8
`define SEED 999

module tb();
    wire [7:0] out_d;
    reg [7:0] in_d;
    reg enb;
    reg rsL;
    reg clk;

    integer idx;
    integer seed;

    register8 DUT (
                    .outD(out_d),
                    .inD(in_d),
                    .enable(enb),
                    .resetLow(rsL),
                    .clock(clk)
            );
    
    always begin
        #`HALF;
        clk = ~clk;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        seed = `SEED;
        clk = 1'b0;
        rsL = 1'b0;
        enb = 1'b1;
        #1;
        rsL = 1'b1;
        $write("\n test the 8-bit register\n\n");
        $write(" clk  rsL  enb      inD     |   outD       time\n");
        $write(" ---------------------------------------\n");

        for (idx = 0; idx < 2*`REPS; idx = idx + 1) begin
            getRand(in_d);
            #(2 * `HALF);
        end
        $write(" ---------------------------------------\n");

        rsL = 1'b0;
        enb = 1'b1;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            getRand(in_d);
            #(2 * `HALF);
        end
        $write(" ---------------------------------------\n");

        rsL = 1'b1;
        enb = 1'b1;
        getRand(in_d);
        #( `HALF);
        enb = 1'b0;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            getRand(in_d);
            #(2 * `HALF);
        end
        $write(" ---------------------------------------\n");

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic getRand;
        output [7:0] regOut;
        integer ii;
        
        begin
            for (ii = 0; ii < 8; ii = ii + 1) begin
                regOut[ii] = $random(seed) % 2;
            end
        end
    endtask
endmodule


////////~~~~~~~~END>  registerTB.v


