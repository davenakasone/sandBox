/*
    prelab3, 1a 
        by assignment
*/

`timescale 1ns/1ns
`define STEP 10


module tb();
    reg [0:2] inp;
    wire [3:0] outp;

    pre1a DUT (
                .abc(inp),
                .y1234(outp)
              );
    
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\ntesting function using assigment\n\n");
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


module pre1a (
                input wire [0:2] abc,
                output wire [3:0] y1234
            );
    assign y1234[0] = (~abc[0] & ~abc[1] & ~abc[2]) |
                      (abc[0] & abc[1] & abc[2]);
    
    assign y1234[1] = (~abc[0] & abc[1] & abc[2])   |
                      (abc[0] & abc[1] & abc[2]);
    
    assign y1234[2] = (abc[0] & ~abc[1] & abc[2]);
    
    assign y1234[3] = 1'b0;

endmodule

////////~~~~~~~~END>  pre1a.v
