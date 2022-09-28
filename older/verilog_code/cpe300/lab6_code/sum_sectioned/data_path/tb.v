/*
    test data_path
*/

`include "../heads.v"
`include "data_path.v"

module tb();
    wire n_is_0;
    wire [7:0] result;
    reg [7:0] n_input;
    reg IE;
    reg WE;
    reg [1:0] WA;
    reg RAE;
    reg [1:0] RAA;
    reg RBE;
    reg [1:0] RBA;
    reg [2:0] ALU;
    reg [1:0] SH;
    reg OE;
    reg clock;

    reg [7:0] test_vals [3:0];
    integer idx;

    data_path DUT (
                    .n_is_0(n_is_0),
                    .result(result),
                    .n_input(n_input),
                    .IE(IE),
                    .WE(WE),
                    .WA(WA),
                    .RAE(RAE),
                    .RAA(RAA),
                    .RBE(RBE),
                    .RBA(RBA),
                    .ALU(ALU),
                    .SH(SH),
                    .OE(OE),
                    .clock(clock)
                );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        `ifdef DEBUG_WAVE
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        $write("\n test the data path, 4 inputs, add, and output\n\n");
        clock = 1'b0;
        test_vals[2'b00] = 8'b0000_0001;    // rf[00] <-- 1
        test_vals[2'b01] = 8'b0000_0011;    // rf[01] <-- 3
        test_vals[2'b10] = 8'b0000_0111;    // rf[10] <-- 7
        test_vals[2'b11] = 8'b0000_1111;    // rf[11] <-- 15

        // load the register file with 4 inputs
        for (idx = 0; idx < 4; idx = idx + 1) begin
            n_input = test_vals[idx];
            IE = 1'b1;
            WE = 1'b1;
            WA = idx;
            RAE = 1'b0;
            RAA = 2'b00;
            RBE = 1'b0;
            RBA = 2'b00;
            ALU = 3'b000;
            SH = 2'b00;
            OE = 1'b0;
            #(`HALF + `HALF);
        end

        // now add rf[00] + rf[11] --> rf[00] 
        IE = 1'b0;
        WE = 1'b1;
        WA = 2'b00;
        RAE = 1'b1;
        RAA = 2'b00;
        RBE = 1'b1;
        RBA = 2'b11;
        ALU = 3'b100;
        SH = 2'b00;
        OE = 1'b0;
        #(`HALF + `HALF);

        // and output rf[00], look for  { 1 + 15 => 16 }
        IE = 1'b0;
        WE = 1'b0;
        WA = 2'b00;
        RAE = 1'b1;
        RAA = 2'b00;
        RBE = 1'b0;
        RBA = 2'b00;
        ALU = 3'b000;
        SH = 2'b00;
        OE = 1'b1;

        #`HALF;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~    %6t ns\n\n", $time);
        $finish;
    end
endmodule


////////~~~~~~~~END>  tb.v
