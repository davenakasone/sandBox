/*
    2:1 MUX, 8-bus, any method you want
        focus is using vectors
    
    with DEMUX attached
*/

`timescale 1ns/1ns
`define STEP 10
`define REPS 3


module tb ();
    wire [7:0] outY;
    wire [7:0] outYbar;
    wire [7:0] outZ;
    reg sel;
    reg [2:0] sell;
    reg [7:0] inA;
    reg [7:0] inB;

    integer idx;
    integer r_gen;

    mux21_bus8 DUT1 (
                        .out_y(outY),
                        .out_y_bar(outYbar),
                        .select(sel),
                        .in_a(inA),
                        .in_b(inB)
                    );
    
    demux21_bus8 DUT2 (
                        .out_z(outZ),
                        .select(sell),
                        .in_y(outY)
                    );
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $write("\nthe 2:1 MUX, 8-bit bus   s=0 -> Y = a ,  s=1 -> Y=b  with DEMUX\n\n");
        $write(" s  |   a           b      |  Y          ~Y        | sel    demux_Z\n");
        $write("---------------------------------------------------------------------\n");
        inA = 8'b1111_1111;
        r_gen = $random;
        r_gen =  r_gen % 256;
        inB = r_gen;
        sel = 1'b0;

        sell = 3'b000;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b001;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b010;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b011;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b100;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b101;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b110;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

        sell = 3'b111;
        for (idx = 0; idx < `REPS; idx = idx + 1) begin
            # `STEP
            $write(" %1b  |  %8b  %8b  |  %8b  %8b   |  %3b    %8b\n",
                sel, inA, inB, outY, outYbar, sell, outZ);
        end
        $write("---------------------------------------------------------------------\n");

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


////~~~~


module demux21_bus8 (
                        output reg [7:0] out_z,
                        input wire [2:0] select,
                        input wire [7:0] in_y
                    );
    always @ (*) begin
        out_z = 8'b0000_0000;
        case(select)
            3'b000 : out_z[0] = in_y[0];
            3'b001 : out_z[1] = in_y[1];
            3'b010 : out_z[2] = in_y[2];
            3'b011 : out_z[3] = in_y[3];
            3'b100 : out_z[4] = in_y[4];
            3'b101 : out_z[5] = in_y[5];
            3'b110 : out_z[6] = in_y[6];
            3'b111 : out_z[7] = in_y[7];
        endcase
    end

endmodule


////////~~~~~~~~END>  exp3d.v
