/*
    use the primitive to make 4inp AND gate
*/

`timescale 1ns/100ps
`define STEP 10

module tb();
    reg [3:0] inp_vec;
    wire out_val;
    integer idx;

    and4p DUT (
                .out_y(out_val),
                .in_a(inp_vec[0]),
                .in_b(inp_vec[1]),
                .in_c(inp_vec[2]),
                .in_d(inp_vec[3])
              );
    
    initial begin
        $write("\nresults of 4-input AND gate:\n\n");
        $write(" a  b  c  d    Y\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            inp_vec = idx;
            #`STEP
            $write(" %b  %b  %b  %b    %b\n",
                inp_vec[0], inp_vec[1], inp_vec[2], inp_vec[3], out_val);
        end
        #`STEP
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
    end 
endmodule

////~~~~

module and4p (
                output wire out_y,
                input wire in_a,
                input wire in_b,
                input wire in_c,
                input wire in_d
            );
    and (out_y, in_a, in_b, in_c, in_d);
endmodule


////////~~~~~~~~END>  and4p.v
