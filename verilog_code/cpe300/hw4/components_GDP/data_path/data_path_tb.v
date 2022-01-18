/*
    test data path
*/

`include "data_path.v"
//`define cycle1
//`define cycle2
`define cycle3
//`define cycle4


module data_path_tb();
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

    integer seed;
    integer fullCycle;

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
            $dumpvars(0, data_path_tb);
        `endif
        clk = 1'b0;
        seed = `SEED;
        fullCycle = 2 * `HALF_CYCLE;
        $write("\n test the data path\n\n");
        clk = 1'b0;
        n_begin = 8'b0000_0011;    // n = 3

        `ifdef cycle1
            // initialize, sum = 0 --> rf[00]
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b00;
            rae = 1'b1;
            raa = 2'b00;
            rbe = 1'b1;
            rba = 2'b00;
            aluSelect = 3'b101;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #`HALF_CYCLE;    // 5
        `endif

        `ifdef cycle2
            // initialize, sum = 0 --> rf[00]
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b00;
            rae = 1'b1;
            raa = 2'b00;
            rbe = 1'b1;
            rba = 2'b00;
            aluSelect = 3'b101;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #`HALF_CYCLE;    // 5
        
            // rf[00] = 0, n --> rf[01]
            #(2 * `T_ERROR);    // 7
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
            #(fullCycle-(2 * `T_ERROR));    // 15
        `endif

        `ifdef cycle3
            // initialize, sum = 0 --> rf[00]
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b00;
            rae = 1'b1;
            raa = 2'b00;
            rbe = 1'b1;
            rba = 2'b00;
            aluSelect = 3'b101;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #`HALF_CYCLE;    // 5
        
            // rf[00] = 0, n --> rf[01]
            #`T_ERROR;    // 6
            #`T_ERROR;    // 7
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
            #(fullCycle-(2 * `T_ERROR));    // 7 + 8 = 15

            // rf[00] = 0, rf[01] = n, rf[00] <-- rf[00] + rf[01]
            #`T_ERROR;    // 16
            #`T_ERROR;    // 17
            muxSelect = 1'b0;
            we = 1'b0;
            wa = 2'b00;
            rae = 1'b1;
            raa = 2'b00;
            rbe = 1'b1;
            rba = 2'b01;
            aluSelect = 3'b100;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #(fullCycle-(2 * `T_ERROR));    // 17 + 8 = 25
        `endif

        `ifdef cycle4
            // initialize, sum = 0 --> rf[00]
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b00;
            rae = 1'b1;
            raa = 2'b00;
            rbe = 1'b1;
            rba = 2'b00;
            aluSelect = 3'b101;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #`HALF_CYCLE;    // 5
        
            // rf[00] = 0, n --> rf[01]
            #`T_ERROR;    // 6
            #`T_ERROR;    // 7
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
            #(fullCycle-(2 * `T_ERROR));    // 7 + 8 = 15

            // rf[00] = 0, rf[01] = n, rf[00] <-- rf[00] + rf[01]
            #`T_ERROR;    // 16
            #`T_ERROR;    // 17
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
            #(fullCycle-(2 * `T_ERROR));    // 17 + 8 = 25

            // rf[00] = n, rf[01] <-- n-1
            #`T_ERROR;    // 26
            #`T_ERROR;    // 27
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b01;
            rae = 1'b1;
            raa = 2'b01;
            rbe = 1'b0;
            rba = 2'b00;
            aluSelect = 3'b111;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #(fullCycle-(2 * `T_ERROR));    // 27 + 8 = 35

            // rf[00] = n+(n-1), rf[01] = n-1, rf[00] <-- rf[00] + rf[01]
            #`T_ERROR;    // 36
            #`T_ERROR;    // 37
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
            #(fullCycle-(2 * `T_ERROR));    // 37 + 8 = 45

            // rf[00] = n+(n-1), rf[01] <-- n-2
            #`T_ERROR;    // 46
            #`T_ERROR;    // 47
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b01;
            rae = 1'b1;
            raa = 2'b01;
            rbe = 1'b0;
            rba = 2'b00;
            aluSelect = 3'b111;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #(fullCycle-(2 * `T_ERROR));    // 47 + 8 = 55

            // rf[00] = n+(n-1)+(n-2), rf[01] = n, rf[00] <-- rf[00] + rf[01]
            #`T_ERROR;    // 56
            #`T_ERROR;    // 57
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
            #(fullCycle-(2 * `T_ERROR));    // 57 + 8 = 65

            // rf[00] = n+(n-1)+(n-2), rf[01] <-- n-3
            #`T_ERROR;    // 66
            #`T_ERROR;    // 67
            muxSelect = 1'b0;
            we = 1'b1;
            wa = 2'b01;
            rae = 1'b1;
            raa = 2'b01;
            rbe = 1'b0;
            rba = 2'b00;
            aluSelect = 3'b111;
            shiftSelect = 2'b00;
            buffEn = 1'b0;
            #(fullCycle-(2 * `T_ERROR));    // 67 + 8 = 75
        `endif
        
        #`HALF_CYCLE;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~ %3t\n\n", $time);
        $finish;
    end

endmodule


////////~~~~~~~~END>  data_path_tb.v
