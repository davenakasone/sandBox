/*
    normal verilog module
    ANSI style
    ...your style is different
*/

`timescale 1ns/100ps
`define STEP 10
`define COMBOZ 8

module tb();
    reg[2:0] tv_n;
    reg[2:0] tv_a;
    wire outp_n;
    wire outp_a;
    integer idx;

    normal_exp DUT_norm(outp_n, tv_n[0], tv_n[1], tv_n[2]);
    ansi_exp DUT_an(outp_a, tv_a[0], tv_a[1], tv_a[2]);

    initial begin
        #`STEP
        $write("\nNormal module:\n\n");
        $write(" a    b    c    Y\n");
        for (idx = 0; idx < `COMBOZ; idx = idx + 1) begin
            tv_n[2:0] = idx;
            #`STEP
            $write(" %b    %b    %b    %b\n",
                tv_n[0], tv_n[1], tv_n[2], outp_n);
        end
        $write("\nANSI module:\n\n");
        $write(" a    b    c    Y\n");
        for (idx = 0; idx < `COMBOZ; idx = idx + 1) begin
            tv_a[2:0] = idx;
            #`STEP
            $write(" %b    %b    %b    %b\n",
                tv_a[0], tv_a[1], tv_a[2], outp_a);
        end

        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

endmodule


////~~~~


module normal_exp(out_y, in_a, in_b, in_c);
    output out_y;
    input in_a, in_b, in_c;
    assign out_y = in_a * (in_b + in_c) + (in_b * (~in_c)) + in_a;
endmodule


////~~~~


module ansi_exp(output out_y, input in_a, in_b, in_c);
    assign out_y = in_a * (in_b + in_c) + (in_b * (~in_c)) + in_a;
endmodule


////////~~~~~~~~END>  preb.v
