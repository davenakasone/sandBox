/*
    Parity Detector: serial input, serial output 
        odd 1's : output == 1
        even 1's : output == 0
*/

`timescale 1ns/1ns
`define HALF 5
`define WIDTH 64
`define REPS 1 // 30


module tb();
    wire result;
    reg start;
    reg in_bit;
    reg clock;

    reg [`WIDTH-1:0] feed;
    integer idx;
    integer idxx;
    integer onez;
    reg par;


    parity DUT (
                    .result(result),
                    .start(start),
                    .in_bit(in_bit),
                    .clock(clock)
                );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the parity detector  ,  stream size:  %2d   ,   reps:  %2d\n\n",
            `WIDTH, `REPS);
        start = 1'b0;
        in_bit = 1'b0;
        clock = 1'b0;

        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            getStream(feed);
            count1z(feed, onez);
            start = 1'b1;
            
            for (idxx = 0; idxx < `WIDTH; idxx = idxx + 1) begin
                in_bit = feed[idxx];
                #(`HALF + `HALF);
            end

            start = 1'b0;
            #(`HALF + `HALF);
            printStream(feed);
            par = onez % 2;
            $write("\n      ones:  %2d\n", onez);
            $write("    parity:  %1d    {0 = even, 1 = odd}  --> ones %% 2\n", par);
            
            if (par == result) begin
                $write("    result:  %1b    CORRECT", result);
                $write("                                    test %2d of %2d\n", 
                    idx+1,`REPS);
            end
            else begin
                $write("    result:  %1b   WRONG\n", result);
            end
            $write(" -------------------------------------------------------------------------------\n\n");
        end
        
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %5t ns\n\n", $time);
        $finish;
    end

    task automatic getStream;
        output reg [`WIDTH-1:0] regOut;
        integer ii;
        begin
            for (ii = 0; ii < `WIDTH; ii = ii + 1) begin
                regOut[ii] = $random % 2;
            end
        end
    endtask

    task automatic printStream;
        input reg [`WIDTH-1:0] regIn;
        integer ii;
        begin
            $write(" ");
            for (ii = 0; ii < `WIDTH; ii = ii + 1) begin
                $write("%1b", regIn[ii]);
                if ( ((ii + 1) % 4) == 0 && ii != (`WIDTH-1) )
                    $write("_");
            end
        end 
    endtask

    task automatic count1z;
        input [`WIDTH-1:0] regIn;
        output integer onez;
        integer flg;
    
        begin
            onez = 0;
            for (flg = 0; flg < `WIDTH; flg = flg + 1) begin
                onez = onez + regIn[flg];
            end
        end
    endtask

endmodule


////~~~~


module parity (
                 output reg result,
                 input wire start,
                 input wire in_bit,
                 input wire clock
            );
    
    parameter BEGIN = 2'b00;
    parameter ODD = 2'b01;
    parameter EVEN = 2'b10;
    
    reg [1:0] state;
    reg [1:0] n_state;
    reg [`WIDTH-1:0] rider;
    integer id;

    initial begin
        state = BEGIN;
        n_state = BEGIN;
        result = 1'b0;
        id = 0;
    end

    always @ (posedge clock) begin
        if (start == 1'b0) begin
            state = BEGIN;
            n_state = BEGIN;
            //result = 1'b0;
            printStream(rider);
            id = 0;
            rider = 1'b0;
        end
        else begin
            case(state)
                BEGIN : 
                    begin
                        n_state = (in_bit == 1'b1) ? ODD : EVEN;
                        rider[id] = in_bit;
                        id = id + 1;
                    end
                ODD : 
                    begin
                        n_state = (in_bit == 1'b1) ? EVEN : ODD;
                        rider[id] = in_bit;
                        id = id + 1;
                    end
                EVEN : 
                    begin
                        n_state = (in_bit == 1'b1) ? ODD : EVEN;
                        rider[id] = in_bit;
                        id = id + 1;
                    end
                default : n_state = BEGIN;
            endcase
            state = n_state;
            result = (n_state == ODD) ? 1'b1 : 1'b0;
        end
    end

    task automatic printStream;
        input reg [`WIDTH-1:0] regIn;
        integer ii;
        begin
            $write(" ");
            for (ii = 0; ii < `WIDTH; ii = ii + 1) begin
                $write("%1b", regIn[ii]);
                if ( ((ii + 1) % 4) == 0 && ii != (`WIDTH-1) )
                    $write("_");
            end
            $write("\n");
        end 
    endtask

endmodule

////////~~~~~~~~END>  parity.v
