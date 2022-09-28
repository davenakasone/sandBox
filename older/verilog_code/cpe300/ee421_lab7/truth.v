/*
    truth tables for lab calculations
*/

`timescale 1ns/1ns
`define HALF 5


module tb();
    reg aa;
    reg bb;
    reg yy;
    reg [7:0] a_in;
    reg [7:0] b_in;
    reg [7:0] y_out;
    integer idx;

    initial begin
        a_in = 8'b0101_1010;
        b_in = 8'b1010_1010;

        $write("\n\n*****************************************************************\n");

        // NOT
        $write("\n the NOT gate truth table:\n\n");
        $write("\t\t\t\t a  |  Y\n");
        $write("\t\t\t\t --------\n");
        for (idx = 0; idx < 2; idx = idx + 1) begin
            aa = idx;
            yy = ~aa;
            $write("\t\t\t\t %1b  |  %1b\n", aa, yy);
        end
        $write("\n");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            y_out[idx] = ~a_in[idx];
        end
        $write(" the example inputs:  NOT a  --> Y\n\n");
        $write("\t\t\t\t a:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", a_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n\t\t\t\t-----------------\n");
        $write("\t\t\t\t Y:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", y_out[idx]);
            if (idx == 4) $write("_");
        end

        $write("\n\n*****************************************************************\n");

        // AND
        $write("\n the AND gate truth table:\n\n");//
        $write("\t\t\t\t a  b  |  Y\n");
        $write("\t\t\t\t -----------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {aa, bb} = idx;
            yy = (aa & bb);//
            $write("\t\t\t\t %1b  %1b  |  %1b\n", aa, bb, yy);
        end
        $write("\n");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            y_out[idx] = (a_in[idx] & b_in[idx]);//
        end
        $write(" the example inputs:  a AND b  --> Y\n\n");//
        $write("\t\t\t\t a:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", a_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n");
        $write("\t\t\t\t b:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", b_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n\t\t\t\t-----------------\n");
        $write("\t\t\t\t Y:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", y_out[idx]);
            if (idx == 4) $write("_");
        end

        $write("\n\n*****************************************************************\n");

        // NAND
        $write("\n the NAND gate truth table:\n\n");//
        $write("\t\t\t\t a  b  |  Y\n");
        $write("\t\t\t\t -----------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {aa, bb} = idx;
            yy = ~(aa & bb);//
            $write("\t\t\t\t %1b  %1b  |  %1b\n", aa, bb, yy);
        end
        $write("\n");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            y_out[idx] = ~(a_in[idx] & b_in[idx]);//
        end
        $write(" the example inputs:  a NAND b  --> Y\n\n");//
        $write("\t\t\t\t a:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", a_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n");
        $write("\t\t\t\t b:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", b_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n\t\t\t\t-----------------\n");
        $write("\t\t\t\t Y:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", y_out[idx]);
            if (idx == 4) $write("_");
        end

        $write("\n\n*****************************************************************\n");

        // OR
        $write("\n the OR gate truth table:\n\n");//
        $write("\t\t\t\t a  b  |  Y\n");
        $write("\t\t\t\t -----------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {aa, bb} = idx;
            yy = (aa | bb);//
            $write("\t\t\t\t %1b  %1b  |  %1b\n", aa, bb, yy);
        end
        $write("\n");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            y_out[idx] = (a_in[idx] | b_in[idx]);//
        end
        $write(" the example inputs:  a OR b  --> Y\n\n");//
        $write("\t\t\t\t a:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", a_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n");
        $write("\t\t\t\t b:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", b_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n\t\t\t\t-----------------\n");
        $write("\t\t\t\t Y:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", y_out[idx]);
            if (idx == 4) $write("_");
        end

        $write("\n\n*****************************************************************\n");

        // NOR
        $write("\n the NOR gate truth table:\n\n");//
        $write("\t\t\t\t a  b  |  Y\n");
        $write("\t\t\t\t -----------\n");
        for (idx = 0; idx < 4; idx = idx + 1) begin
            {aa, bb} = idx;
            yy = ~(aa | bb);//
            $write("\t\t\t\t %1b  %1b  |  %1b\n", aa, bb, yy);
        end
        $write("\n");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            y_out[idx] = ~(a_in[idx] | b_in[idx]);//
        end
        $write(" the example inputs:  a NOR b  --> Y\n\n");//
        $write("\t\t\t\t a:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", a_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n");
        $write("\t\t\t\t b:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", b_in[idx]);
            if (idx == 4) $write("_");
        end
        $write("\n\t\t\t\t-----------------\n");
        $write("\t\t\t\t Y:  ");
        for (idx = 7; idx>= 0; idx = idx - 1) begin
            $write("%1b", y_out[idx]);
            if (idx == 4) $write("_");
        end

    $write("\n\n*****************************************************************\n");
    $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
    $finish;
    end

endmodule

////////~~~~~~~~END>  truth.v

