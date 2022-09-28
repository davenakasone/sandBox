/*
    counter
*/

`timescale 1ns/1ns
`define HALF 5
`define REPS 10


module tb();
    wire [2:0] count;
    reg up;
    reg clock;

    integer idx;

    counter DUT (
                    .count(count),
                    .up(up),
                    .clock(clock)
                );
    
    always begin 
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        up = 1'b0;
        clock = 1'b0;
        $write("\n test the counter\n\n");
        $write(" clk  up  |  result\n");
        $write(" ------------------\n");

        
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + 1);
            $write("  %1b   %1b   |  %3b           %6t ns\n",
                clock, up, count, $time);
            #(`HALF - 1);
        end
        $write(" ------------------\n");

        up = 1'b1;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(`HALF + 1);
            $write("  %1b   %1b   |  %3b           %6t ns\n",
                clock, up, count, $time);
            #(`HALF - 1);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %6t ns\n\n", $time);
        $finish;
    end
endmodule


////~~~~


module counter (
                    output reg [2:0] count,
                    input wire up,
                    input wire clock
                );
    
  	parameter s1 = 3'b001;
  	parameter s2 = 3'b010;
  	parameter s3 = 3'b011;
  	parameter s4 = 3'b100;
  	parameter s5 = 3'b101;
  	parameter s6 = 3'b110;
  	reg [2:0] state;
  	reg [2:0] n_state;
  
    initial begin
      count = 3'b001;
      state = s1;
      n_state = s1;
      end

    always @ (posedge clock) begin
      case(state)
        s1 : n_state <= (up == 1'b1) ? s2 : s6;
        s2 : n_state <= (up == 1'b1) ? s3 : s1;
        s3 : n_state <= (up == 1'b1) ? s4 : s2;
        s4 : n_state <= (up == 1'b1) ? s5 : s3;
        s5 : n_state <= (up == 1'b1) ? s6 : s4;
        s6 : n_state <= (up == 1'b1) ? s1 : s5;
        default: n_state = s1;
      endcase
      count <= n_state;
      state <= n_state;
    end
endmodule