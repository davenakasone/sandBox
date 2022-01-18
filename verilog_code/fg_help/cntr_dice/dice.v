/*
    delete the test bench
    make a .sv if needed
*/

`timescale 1ns/1ns
`define SEED 333
`define HALF 5
`define REPS 20


module tb();
    wire [6:0] seg7;
    reg roll;
    reg reset;
    reg clock;

    integer idx;
    integer seed;
    integer result;
    reg [6:0] pass;
    integer delay;

    topEnt DUT (
                    .seg7(seg7),
                    .roll(roll),
                    .reset(reset), 
                    .clock(clock)
                );
    
    always begin 
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        roll = 1'b0;
        reset = 1'b0;
        clock = 1'b0;
        seed = `SEED;
        $write("\n test the counter and dice roll\n\n");
        $write(" rst  roll  |  result\n");
        $write(" ----------------------------\n");

        roll = 1'b1;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            #(1 + (idx * `HALF));
            pass = seg7;

            case(pass)
                7'b1111_001 : result = 1;
                7'b0100_100 : result = 2;
                7'b0110_000 : result = 3;
                7'b0011_001 : result = 4;
                7'b0010_010 : result = 5;
                7'b0000_010 : result = 6;
                default : result = -1;
            endcase
            
            if (result > 0) begin
              $write("  %1b   %1b     |    %1d           %6t ns\n",
                    reset, roll, result, $time);
            end
            else begin
              $write("  %1b   %1b     |    %1d           %6t ns  no roll\n",
                    reset, roll, result, $time);
            end
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %6t ns\n\n", $time);
        $finish;
    end
endmodule


////~~~~


module topEnt (
                    output reg [6:0] seg7,
                    input wire roll,
                    input wire reset, // put on switch, stops fast clock
                    input wire clock
                );

    wire [2:0] dice_num;
    reg [2:0] catch;
    parameter ON = 1'b0;
    parameter OFF = 1'b1;
    parameter CLEAR = {7{OFF}};
    parameter one_1 = 7'b1111_001;
    parameter two_2 = 7'b0100_100;
    parameter three_3 = 7'b0110_000;
    parameter four_4 = 7'b0011_001;
    parameter five_5 = 7'b0010_010;
    parameter six_6 = 7'b0000_010;

    counter cnt_inst (
                        .count(dice_num),
      					.up(~reset),
                        .clock(clock)
                    );

    initial begin
        seg7 = CLEAR;
        catch = 3'b001;
    end

  always @ (posedge clock) begin

        if (reset == 1'b1) begin
            seg7 <= CLEAR;
        end
        else if (reset == 1'b0 && roll == 1'b1) begin
            catch <= dice_num;
            case (catch)
                3'b001 : seg7 <= one_1;
                3'b010 : seg7 <= two_2;
                3'b011 : seg7 <= three_3;
                3'b100 : seg7 <= four_4;
                3'b101 : seg7 <= five_5;
                3'b110 : seg7 <= six_6;
                default : seg7 <= CLEAR;
            endcase 
        end
        else begin
            seg7 <= one_1;
        end
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


/////////~~~~~~~~END>  dice.v
