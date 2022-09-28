/*
    test the control unit and data path
    these 2 create the general data path
*/

`include "gdp.v"
`include "../heads.v"


module gdpTB();
    wire [7:0] result;
    wire resultReady;
    reg [7:0] nIn;
    reg start;
    reg restart;
    reg clk;

    integer idx;
    integer check;
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
        $write(" \ntest your control unit on the GDP\n\n");
        $write(" input   |  output  |  expected  |      time       split     STATUS\n");
        $write(" ---------------------------------\n");
        start = 1'b1;
        restart = 1'b1;
        clk = 1'b0;
    end

    always begin

        for (idx = 0; idx < 23; idx = idx + 1) begin // 22 is max to stop overflow (idx < 23)
            nIn <= idx;
            start = 1'b0;
            //#40;
            #(2 * `HALF_CYCLE);
            restart = 1'b1;

            while (resultReady != 1'b1) begin
                #(`HALF_CYCLE + `T_ERROR);
                //#5;
            end

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
            
            check = ((idx + 1) * idx) / 2;
            $write("  %2d     |  %3d    |   %3d   ",
                nIn, result, check);
            if (result == check) begin
                $write("        %5t ns       +%4d    CORRECT   \n", 
                    $time, split);
            end
            else begin
                $write ("        %5t ns       +%4d    !!! WRONG !!!\n", 
                    $time, split);
            end

            restart = 1'b0;
            start = 1'b1;
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////////~~~~~~~~END>  gdpTB.v
