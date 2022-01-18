/*
    test data path
    see how n = 3 is handled
*/

`include "data_path.v"
`define STR8_EXC 187
`define LOOP_EXC -187


module best_tb();
    wire nIS0;
    wire[7:0] sum;
    reg [7:0] nIn;
    reg clk;
    reg muxSelect;
    reg we;
    reg [1:0] wa;
    reg rae;
    reg [1:0] raa;
    reg rbe;
    reg [1:0] rba;
    reg [2:0] aluSelect;
    reg [1:0] shiftSelect;
    reg buffEn;

    reg [7:0] n_begin;

    data_path DUT (
                    .n_is_0(nIS0),
                    .run_sum(sum),
                    .n_in(nIn),
                    .clock(clk),
                    .input_enable_mux(muxSelect),
                    .WE(we),
                    .WA(wa),
                    .RAE(rae),
                    .RAA(raa),
                    .RBE(rbe),
                    .RBA(rba),
                    .alu_op(aluSelect),
                    .shift_op(shiftSelect),
                    .output_enable_buf(buffEn)
            );
    
    always begin
        #`HALF_CYCLE;
        clk = ~clk;
    end

    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, best_tb);
        `endif
        clk = 1'b0;
        n_begin = 8'b0000_0011;    // n = 3
        $write("\n test the data path  ,  n = %1d\n\n", n_begin);
        
        // initialize, 0 --> rf[00]
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b00;
        rae = 1'b1;
        raa = 2'b00;
        rbe = 1'b1;
        rba = 2'b00;
        aluSelect = 3'b101;   // A - B = 0 
        shiftSelect = 2'b00;
        buffEn = 1'b0;

        #`HALF_CYCLE;    // 5
        #`HALF_CYCLE;    // 10

        // rf[00] = 0
        // n --> rf[01]
        nIn = n_begin;
        muxSelect = 1'b1;
        we = 1'b1;
        wa = 2'b01;
        rae = 1'b0;
        raa = 2'b00;
        rbe = 1'b0;
        rba = 2'b00;
        aluSelect = 3'b000;
        shiftSelect = 2'b00;
        buffEn = 1'b0;

        #`HALF_CYCLE;    // 15
        #`HALF_CYCLE;    // 20

        // rf[00] = 0, rf[00] <-- rf[00] + rf[01] = n
        //rf[01] = n, 
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b00;
        rae = 1'b1;
        raa = 2'b00;
        rbe = 1'b1;
        rba = 2'b01;
        aluSelect = 3'b100;
        shiftSelect = 2'b00;
        buffEn = 1'b0;

        #`HALF_CYCLE;    // 25
        #`HALF_CYCLE;    // 30

        // rf[00] = n
        // rf[01] = n, rf[01] <-- n-1
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b01;
        rae = 1'b1;
        raa = 2'b01;
        rbe = 1'b0;
        rba = 2'b00;
        aluSelect = 3'b111;  // decrement
        shiftSelect = 2'b00; 
        buffEn = 1'b0;    

        #`HALF_CYCLE;    // 35
        #`HALF_CYCLE;    // 40

        // rf[00] = n, rf[00] <-- [ {rf[00] = n} + {rf[01] = n-1} ]
        //rf[01] = n-1, 
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b00;
        rae = 1'b1;
        raa = 2'b00;
        rbe = 1'b1;
        rba = 2'b01;
        aluSelect = 3'b100;
        shiftSelect = 2'b00;
        buffEn = 1'b0;

        #`HALF_CYCLE;    // 45
        #`HALF_CYCLE;    // 50

        // rf[00] = n + (n-1)
        // rf[01] = n-1, rf[01] <-- n-2
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b01;
        rae = 1'b1;
        raa = 2'b01;
        rbe = 1'b0;
        rba = 2'b00;
        aluSelect = 3'b111;  // decrement
        shiftSelect = 2'b00; 
        buffEn = 1'b0;    

        #`HALF_CYCLE;    // 55
        #`HALF_CYCLE;    // 60

        // rf[00] = n + (n-1), rf[00] <-- [ {rf[00] = n + (n-1)} + {rf[01] = n-2} ]
        //rf[01] = n-2, 
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b00;
        rae = 1'b1;
        raa = 2'b00;
        rbe = 1'b1;
        rba = 2'b01;
        aluSelect = 3'b100;
        shiftSelect = 2'b00;
        buffEn = 1'b0;

        #`HALF_CYCLE;    // 65
        #`HALF_CYCLE;    // 70

        // rf[00] = n + (n-1) + (n-2)
        // rf[01] = n-1, rf[01] <-- n-3
        muxSelect = 1'b0;
        we = 1'b1;
        wa = 2'b01;
        rae = 1'b1;
        raa = 2'b01;
        rbe = 1'b0;
        rba = 2'b00;
        aluSelect = 3'b111;  // decrement
        shiftSelect = 2'b00; 
        buffEn = 1'b0;    

        #`HALF_CYCLE;    // 75
        if (nIS0) begin
            muxSelect = 1'b0;
            we = 1'b0;
            wa = 2'b00;
            rae = 1'b1;
            raa = 2'b00;
            rbe = 1'b0;
            rba = 2'b00;
            aluSelect = 3'b000;
            shiftSelect = 2'b00; 
            buffEn = 1'b1;  
            #`HALF_CYCLE;    // 80
            $write("\n\n SUCCESS, n = %2d  ,  sum = %2d\n\n", n_begin, sum);
            $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~ %3t\n\n", $time);
            $finish;
        end
        $finish;
    end

endmodule


////////~~~~~~~~END>  best_tb.v
