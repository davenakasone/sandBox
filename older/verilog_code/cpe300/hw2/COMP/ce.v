
module CE (
            output c_in,
            input [2:0] sel
          );
    wire w_xor;
    xor xor_g (w_xor, sel[0], sel[1]);
    and and_out (c_in, w_xor, sel[2]);
endmodule