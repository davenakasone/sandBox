/*
    applying controls
*/


`timescale 1ns/1ns
`define HALF 5


`define DEBUG_tb 999
`define DEBUG_wave 998
`define DEBUG_PASS 996


module tb();

    reg clock;
    reg reset;
    reg start;
    reg valid_dice;
    reg valid_target;
    reg roll;
    reg [4:0] sides;
    reg [4:0] target;
    wire [4:0] user_dice_roll;
    wire win_result;

    controller DUT (
                        .clock (clock),
                        .reset (reset),
                        .start (start),
                        .valid_dice (valid_dice),
                        .valid_target (valid_target),
                        .roll (roll),
                        .sides (sides),
                        .target (target),
                        .user_dice_roll (user_dice_roll),
                        .win_result (win_result)
                    );
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        clock = 1'b0;
        reset = 1'b1;
        start = 1'b0;
        valid_dice = 1'b0;
        valid_target = 1'b0;
        roll = 1'b0;
        #`HALF; #`HALF;

        `ifdef DEBUG_PASS
            $write("\n testing state transistion:\n\n");
            sides = 4'b1000;
            target = 3'b111;
            reset = 1'b0;
            start = 1'b1;

            #`HALF;#`HALF; #`HALF; // s0 -> s1

            valid_dice = 1'b1;
            #`HALF;#`HALF; #`HALF; // s1 -> s2

            valid_target = 1'b1;
            #`HALF;#`HALF; #`HALF; // s2 -> s3

            roll = 1'b1;
            #`HALF; #`HALF; // s3 -> s4
            #`HALF; #`HALF; // s4 ->    s5 or s6

            reset = 1'b1;
            #`HALF; #`HALF; // --> s0
        `endif
        
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~     %4t\n\n ", $time);
        $finish;
    end
    
endmodule


////~~~~
module controller (
                        input wire clock,
                        input wire reset,
                        input wire start,
                        input wire valid_dice,
                        input wire valid_target,
                        input wire roll,
                        input wire [4:0] sides,
                        input wire [4:0] target,
                        output reg [4:0] user_dice_roll,
                        output reg win_result
                    );

    wire [4:0] roll_result;
    reg [4:0] store_targert;
    wire win;
    
    assign win = (roll_result >= target) ? 1 : 0;

    m_dice_roll ROLL(
						.clock (clock),
						.reset (reset),
                        .sides (sides),
						.roll_result (roll_result)
					);

    reg [2:0] state;
	reg [2:0] n_state;

	parameter s0 = 3'b000;
	parameter s1 = 3'b001;
	parameter s2 = 3'b010;
	parameter s3 = 3'b011;
	parameter s4 = 3'b100;
    parameter s5 = 3'b101;
    parameter s6 = 3'b110;
	
	initial begin
        state <= s0;
        user_dice_roll <= 1'b0;
        store_targert <= 1'b0; 
        win_result <= 1'b0;
    end

    always @ (posedge clock) begin
        if (reset) begin
            state <= s0;
            user_dice_roll <= 1'b0;
            store_targert <= 1'b0; 
        end
        else begin
            state <= n_state;
        end

        // apply next state execution ... no next state logic
        case (state)
            s0 :    
                begin  
                    user_dice_roll <= 1'b0; 
                    store_targert <= 1'b0;       
                end     
            s1 : 
                begin
                end
            s2 : 
                begin
                    store_targert <= target;
                end
            s3 :
                begin
                    user_dice_roll <= roll_result;
                end
            s4 : 
                begin
                    win_result = (roll_result >= target) ? 1 : 0;
                end
            s5 : 
                begin
                    
                end
            s6 : 
                begin
                end
            default :
                begin
                    
                end
        endcase
    end

    // determines next state
    always @ (*) begin
        case(state)
            s0 :    // waiting
                begin          
                    if (reset) n_state = s0;
                    else n_state = (start) ? s1 : s0;
                end     
            s1 : 
                begin
                    if (reset) n_state = s0;
                    else n_state = (valid_dice) ? s2 : s1;
                end
            s2 : 
                begin
                    if (reset) n_state = s0;
                    else n_state = (valid_target) ? s3 : s2;
                end
            s3 :
                begin
                    if (reset) n_state = s0;
                    else n_state = (roll) ? s4 : s3;
                end
            s4 : 
                begin
                    if (reset) n_state = s0;
                    else n_state = (win) ? s5 : s6;
                end
            s5 : n_state = (reset) ? s0 : s5;
            s6 : n_state = (reset) ? s0 : s6;
            default : n_state = s0;               // stop the latch
        endcase
	end

    `ifdef DEBUG_PASS
        always @ (posedge clock) begin
            #1;
            $write("\n*************************************************************\n");
            $write("state:  %2d   -->  n_state:  %2d        %4t ns\n",
                DUT.state, DUT.n_state, $time);
            $write("reset:  %1b\n", reset);
            $write("start:  %1b\n", start);
            $write("valid_dice:  %1b\n", valid_dice);
            $write("valid_target:  %1b\n", valid_target);
            $write("roll  %1b\n", roll);
            $write("sides:  %5b\n", sides);
            $write("target:  %5b\n", target);
            $write("usr_roll:  %5b\n", user_dice_roll);
            $write("win_result  %1b\n", win_result);
            $write("roll_result:  %5b\n", roll_result);
            $write("store_targert:  %5b\n", store_targert);
            $write("win %1b\n", win);
            $write("*************************************************************\n");
        end
    `endif

endmodule


////~~~~~
module m_dice_roll (
						input wire clock,
						input wire reset,
                        input wire [4:0] sides,
						output reg [4:0] roll_result
					);
    
	initial begin
        roll_result = 5'b00001;
	end

	always @ (posedge clock) begin
		if(reset) begin
			roll_result = 5'b00001;
		end
		else begin
            roll_result = (roll_result > 5'b10100) ? 5'b00001 : roll_result + 1'b1;
            case (sides)
                4  : roll_result = (roll_result % 4) + 1;
                6  : roll_result = (roll_result % 6) + 1;
                8  : roll_result = (roll_result % 8) + 1;
                10 : roll_result = (roll_result % 10) + 1;
                12 : roll_result = (roll_result % 12) + 1;
                20 : roll_result = (roll_result % 20) + 1;
                default : roll_result = 5'b00001;
            endcase
		end
	end

endmodule


/////////~~~~~~~~END>  prototype.sv
