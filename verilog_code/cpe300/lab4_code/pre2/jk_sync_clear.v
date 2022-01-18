/*
    JK ff w/ synchronous clear
*/

`timescale 1ns/1ns
`define HALF 5
`define SEED 22


module tb();
    wire out_q;
    wire out_qn;
    reg clear_n;
    reg in_j;
    reg in_k;
    reg clk;

    integer idx;
    integer cyc;
    integer seed;

    ff_JK DUT (
                .outQ(out_q),
                .outQn(out_qn),
                .clearN(clear_n),
                .inJ(in_j),
                .inK(in_k),
                .clock(clk)
            );

    always begin
        #`HALF;
        clk = ~clk;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\n test the JK ff w/ synchronous clearN\n");
        $write(" @posedge JK:\n");
        $write(" 00: no change\n");
        $write(" 01: 0\n");
        $write(" 10: 1\n");
        $write(" 11: toggle\n\n");
        $write(" clk  clrN  J  K  |  Q ~Q      time\n");
        $write(" -------------------------\n");
        seed = `SEED;
        clk = 1'b0;
        clear_n = 1'b0;
        in_j <= 1'b0;
        in_k <= 1'b0;
        #1;
        clear_n = 1'b1;

        for (idx = 0; idx < 32; idx = idx + 1) begin
            in_j <= $random(seed) % 2;
            in_k <= $random(seed) % 2;
            #`HALF;
        end
        $write(" -------------------------\n");

        clear_n = 1'b0;
        for (idx = 0; idx < 8; idx = idx + 1) begin
            in_j <= $random(seed) % 2;
            in_k <= $random(seed) % 2;
            #`HALF;
        end
        $write(" -------------------------\n");
        
        //#`HALF;
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    always @ (posedge clk) begin
        #1;
        disp(clk, clear_n, in_j, in_k, out_q, out_qn);
    end

    task disp;
        input clk;
        input clear_n;
        input in_j;
        input in_k;
        input out_q;
        input out_qn;

        begin
            $write("   %1b    %1b   %1b  %1b  |  %1b  %1b      %3t",
                clk, clear_n, in_j, in_k, out_q, out_qn, $time);
            if (clear_n == 1'b0) begin
                $write("  Q -> 0 clear\n");
            end
            else begin
               case ({in_j, in_k})
                2'b01   : $write("  Q -> 0\n");
                2'b10   : $write("  Q -> 1\n");
                2'b11   : $write("  Q -> ~Q\n");
                default : $write("  Q -> Q\n");
            endcase 
            end
        end
    endtask

endmodule


////~~~~


module ff_JK (
                output reg outQ,
                output wire outQn,
                input wire clearN,
                input wire inJ,
                input wire inK,
                input wire clock);
    
    always @ (posedge clock or negedge clearN) begin
        if (~clearN) begin
            outQ = 1'b0;
        end
        else begin
            case ({inJ, inK})
                2'b01   : outQ <= 1'b0;
                2'b10   : outQ <= 1'b1;
                2'b11   : outQ <= ~outQ;
                default : outQ <= outQ;
            endcase
        end
    end

    assign outQn = ~outQ;
endmodule


////////~~~~~~~~END>  jk_sync_clear.v



