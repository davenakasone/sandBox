/*
    prelab3, 1c
        by case, NO "default"
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    reg [0:2] inp;
    wire [3:0] outp;

    pre1c DUT (
                .abc(inp),
                .y1234(outp)
              );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\ntesting function using case NO default\n\n");
        $write(" a   b   c   |  Y1  Y2  Y3  Y4\n");
        $write("-------------------------------\n");

        inp = 3'b000;
        #`STEP
        $write(" %b   %b   %b   |  %b    %b   %b   %b\n",
            inp[0], inp[1], inp[2], outp[0], outp[1], outp[2], outp[3]);
        
        inp = 3'b011;
        #`STEP
        $write(" %b   %b   %b   |  %b    %b   %b   %b\n",
            inp[0], inp[1], inp[2], outp[0], outp[1], outp[2], outp[3]);
        
        inp = 3'b101;
        #`STEP
        $write(" %b   %b   %b   |  %b    %b   %b   %b\n",
            inp[0], inp[1], inp[2], outp[0], outp[1], outp[2], outp[3]);
        
        inp = 3'b111;
        #`STEP
        $write(" %b   %b   %b   |  %b    %b   %b   %b\n",
            inp[0], inp[1], inp[2], outp[0], outp[1], outp[2], outp[3]);

        
        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~ 


module pre1c (
                input wire [0:2] abc,
                output reg [3:0] y1234
            );
    always @ (*) begin
        y1234 = 4'b0000;
        case (abc)
            3'b000 : y1234[0] = 1'b1; 
            3'b011 : y1234[1] = 1'b1;
            3'b101 : y1234[2] = 1'b1;
            3'b111 : begin
                        y1234[0] = 1'b1;
                        y1234[1] = 1'b1;
                    end
            //default : y1234 = 4'b0000;
        endcase
    end
endmodule

////////~~~~~~~~END>  pre1c.v