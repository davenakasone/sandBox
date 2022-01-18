/*
    test the control unit and data path
    these 2 create the general data path
*/

`include "gdp.v"
`include "../heads.v"
`define START 0       // begin loop @ this
`define REPS 256      // 255 is max to stop overflow (idx < 256)


module gdpTB();
    wire [7:0] result;
    wire resultReady;
    reg [7:0] nIn;
    reg start;
    reg restart;
    reg clk;

    reg [3:0] check;
    integer idx;
    integer past;
    integer now;
    integer split;

    GDP dut (
                .runSum(result),
                .done(resultReady),
                .n_in(nIn),
                .start(start),
                .restart(restart),
                .clock(clk)
        );

    always begin
        #`HALF_CYCLE;
        //#2;
        clk = ~clk;
    end

    initial begin
        `ifdef DEBUG_tb
            $write(" \ntest your control unit on the GDP\n\n");
            $write("    input    |  output  |  expected  |    time    split     STATUS\n");
            $write(" ------------------------------------------------------------------\n");
        `endif
        start = 1'b0;
        restart = 1'b0;
        clk = 1'b0;
    end

    always begin

        for (idx = `START; idx < `REPS; idx = idx + 1) begin 
            #(2 * `HALF_CYCLE);  // +10, to make 0
            restart = 1'b0;
            nIn <= idx;
            start = 1'b1;

            while (resultReady != 1'b1) begin
                #(`HALF_CYCLE + `T_ERROR);
            end

            `ifdef DEBUG_tb
                if (idx == 0) begin
                    past = 0;
                    now = $time;
                    split = now - past;
                end
                else begin
                    past = now;
                    now = $time;
                    split = now - past;
                end
                
                count_ones(nIn, check);
                $write("  %4b_%4b  |  %3d     |   %3d      | ",
                    nIn[7:4], nIn[3:0], result, check);
                if (result == check) begin
                    $write("%5t ns   +%4d     CORRECT   \n", 
                        $time, split);
                end
                else begin
                    $write ("%5t ns   +%4d     !!! WRONG !!!\n", 
                        $time, split);
                end
                if ( (idx % 8) == 0 && idx != 0) begin
                    $write(" ------------------------------------------------------------------\n");
                end
            `endif 

            restart = 1'b1;
            start = 1'b0;
        end

        #(2 * `HALF_CYCLE); // for lags and stability
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic count_ones;
        input [7:0] reg_in;
        output reg [3:0] cnt;

        integer flg;
    
        begin
            cnt = 4'b0000;
            for (flg = 0; flg < 8; flg = flg + 1) begin
                cnt = cnt + reg_in[flg];
            end
        end
    endtask

endmodule


////////~~~~~~~~END>  gdpTB.v
