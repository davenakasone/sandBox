/*
    converts 50 MHz FPGA clock to 1Hz clock
    good for making a clock to observe operations
    change clock period and duty cycle at will

    split the slower clock at half the period of faster frequency

    for 50 MHz, the period is 1/50E6 = 20 ns (10ns half cycle)
    PIN_M9 (signal CLOCK_50) of DE2 should take input "clk_50mhz"
    use output "clk_1hz" to feed rest of circuit
*/

`timescale 1ns/1ns
`define HALF 10
`define REPS 6
`define DEBUG -999    ////~~~~{on|off}


module tb();
    wire out_1hz;
    reg in_50mhz;

    integer idx;
    reg tog;

    clk_50MHz_to_1Hz DUT (
                            .clk_1hz(out_1hz),
                            .clk_50mhz(in_50mhz)
                        );

    always @ (posedge out_1hz) begin
        tog = 1'b1;
    end

    always @ (negedge out_1hz) begin
        tog = 1'b0;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the clock converter\n");
        $write(" @50 MHz, period = %2d ns  ,  changes every %2d ns\n\n",
            (2 * `HALF), `HALF);
        $write(" 50 MHz  |  1 Hz  |         $time(ns)\n");
        $write(" ------------------\n");
        in_50mhz = 1'b0;
        tog = 1'b0;

        `ifdef DEBUG
            for (idx = 0; idx < 100; idx = idx + 1) begin
                #`HALF;
                in_50mhz = ~in_50mhz;
                $write("    %1b    |    %1b   |   %4t\n", 
                    in_50mhz, out_1hz, $time);
            end
        `else
            idx = 0;
            while (idx < `REPS) begin
                if (out_1hz == 1'b1 && tog == 1'b1) begin
                    idx = idx + 1;
                    $write("    %1b    |    %1b   |   %4t\n", 
                        in_50mhz, out_1hz, $time);
                    tog = 1'b0;
                end
                #`HALF;
                in_50mhz = ~in_50mhz;
            end

        `endif

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~ 


module clk_50MHz_to_1Hz (
                            output reg clk_1hz,
                            input wire clk_50mhz
                        );

    // must store 24,999,999, adjust as needed
    // most reg sizes max out at 32 bits, check hardware
    // 25'b1011111010111100000111111 == 24,999,999
    reg [24:0] count;    

    initial begin
        count <= 1'b0;
        clk_1hz <= 1'b0;
    end

    always @ (posedge clk_50mhz) begin
        `ifdef DEBUG
            if(count == 4'b1010) begin
                count <= 0;
                clk_1hz <= ~clk_1hz;
            end
            else begin
                count <= count + 1;
            end
        `else
            if(count == 8'b0000_1111) begin
                count <= 0;
                clk_1hz <= ~clk_1hz;
            end
            else begin
                count <= count + 1;
            end
        `endif
    end
endmodule


////////~~~~~~~~END>  clk_50MHz_to_1Hz.v


/*  use this >>>

module clk_50MHz_to_1Hz ( 
                            output reg clk_1hz,
                            input wire clk_50mhz
                        );

    reg [24:0] count;    

    initial begin
        count <= 1'b0;
        clk_1hz <= 1'b0;
    end

    always @ (posedge clk_50mhz) begin
        if(count == 25'b1011111010111100000111111) begin
            count <= 0;
            clk_1hz <= ~clk_1hz;
        end
        else begin
            count <= count + 1;
        end
    end
endmodule

*/


/* ORIGINAL  ORIGINAL  ORIGINAL  ORIGINAL
module onehertz(clk_50mhz, clk_1hz);
input clk_50mhz;
output clk_1hz;
reg clk_1hz;
reg [24:0] count;
always @ (posedge clk_50mhz)
begin
if(count == 24999999) begin
count <= 0;
$dumpfile("f.vcd");
clk_1hz <= ~clk_1hz;
end
else begin
count <= count + 1;
end
end
endmodule
  ORIGINAL  ORIGINAL  ORIGINAL  ORIGINAL */
