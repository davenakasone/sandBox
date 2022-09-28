/*
    2:1 MUX, 8-bus, any method you want
        focus is using vectors
*/

`timescale 1ns/1ns
`define STEP 10
`define SEED 999
`define REPS 3


module tb ();
    wire [7:0] outY;
    wire [7:0] outYbar;
    reg sel;
    reg [7:0] inA;
    reg [7:0] inB;

    integer idx;
    integer r_gen;

    mux21_bus8 DUT (
                        .out_y(outY),
                        .out_y_bar(outYbar),
                        .select(sel),
                        .in_a(inA),
                        .in_b(inB)
                    );
    
    initial begin
        //$random(`SEED);
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\nthe 2:1 MUX, 8-bit bus   s=0 -> Y = a ,  s=1 -> Y=b\n\n");
        $write(" s  |   a           b      |  Y          ~Y\n");
        $write("--------------------------------------------------\n");

        sel = 1'b0;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            r_gen = $random;
            r_gen =  r_gen % 256;
            inA = r_gen;
            r_gen = $random;
            r_gen =  r_gen % 256;
            inB = r_gen;
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b\n",
                sel, inA, inB, outY, outYbar);
        end
        $write("--------------------------------------------------\n");
        sel = 1'b1;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            r_gen = $random;
            r_gen =  r_gen % 256;
            inA = r_gen;
            r_gen = $random;
            r_gen =  r_gen % 256;
            inB = r_gen;
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b\n",
                sel, inA, inB, outY, outYbar);
        end
        $write("--------------------------------------------------\n");
        # `STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module mux21_bus8 (
                    output wire [7:0] out_y,
                    output wire [7:0] out_y_bar,
                    input wire select,
                    input wire [7:0] in_a,
                    input wire [7:0] in_b
                  );
    assign out_y = (~select) ? in_a : in_b;
    assign out_y_bar = (~select) ? ~in_a : ~in_b;
endmodule


////////~~~~~~~~END>  exp3c.v
