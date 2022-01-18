/*
    test the control unit  ... just for getting debug aligment
    use the GDP for complete test
*/

`include "cntlU.v"


module cntlU_tb();
    wire ie;
    wire we;
    wire [1:0] wa;
    wire rae;
    wire [1:0] raa;
    wire rbe;
    wire [1:0] rba;
    wire [2:0] alu;
    wire [1:0] shf;
    wire oe;
    reg clk;
    reg start;
    reg restart;
    reg nEqZero;
    
    cntlU DUT (
                .IE(ie),
                .WE(we), 
                .WA(wa),
                .RAE(rae),
                .RAA(raa),
                .RBE(rbe),
                .RBA(rba),
                .ALU(alu),
                .SH(shf),
                .OE(oe),
                .clk(clk), 
                .start(start), 
                .restart(restart), 
                .nEqZero(nEqZero)
            );

    always begin
        #5;
        clk = ~clk;
    end

    initial begin
        clk = 1'b0;
        start = 1'b1;
        restart = 1'b1;
        nEqZero = 1'b1;
        #20;
        $finish;
    end

endmodule


////////~~~~~~~~END>  cntlU_tb.v


