/*
    example of a 4-bit register
        each bit needs a FF
        clk is shared
        parallel input bus --> parallel output bus
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    wire [3:0] QQ;
    reg clock;
    reg [3:0] DD;

    reg4 DUT (
                .Q(QQ),
                .clk(clock),
                .D(DD)
        );
    
    always begin
        #`STEP 
        clock = ~clock;
    end

    initial begin
        $write("\n test the the register...\n\n");
        $write(" time  D      Q\n");
        $write(" ------------------\n");
        clock = 1'b0;
        
        DD = 4'b1111;
        #(3*`STEP);
        DD = 4'b1110;
        #(3*`STEP);
        DD = 4'b0000;
        #(3*`STEP);

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    always @ (DD or QQ) begin
        $write(" %2t    %4b   %4b\n", $time, DD, QQ);
        #`STEP;
    end
    
endmodule


////~~~~


module reg4 (
                output reg [3:0] Q,
                input wire clk,
                input wire [3:0] D
        );
    always @ (posedge clk) Q = D;   // block
endmodule


////////~~~~~~~~END>  reg_behave.v
