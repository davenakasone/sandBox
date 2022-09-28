module adder4 (
                input [3:0] in_a,
                input [3:0] in_b,
                input in_c,
                output out_c,
                output [3:0] out_sum
              );
    wire   [3:1] C;  // C is an internal signal

    fullAdder FA0 (in_a[0], in_b[0], in_c, C[1], out_sum[0]);
    fullAdder FA1 (in_a[1], in_b[1], C[1], C[2], out_sum[1]);
    fullAdder FA2 (in_a[2], in_b[2], C[2],C[3], out_sum[2]);
    fullAdder FA3 (in_a[3], in_b[3], C[3], out_c, out_sum[3]);
endmodule


////////~~~~~~~~ Full Adder {1-bit}


module fullAdder (
                    input in_x, 
                    input in_y, 
                    input in_c, 
                    output out_c,
                    output out_sum
                 );
    assign out_sum = in_x ^ in_y ^ in_c;
    assign out_c = (in_x & in_y) | (in_x & in_c) | (in_y & in_c); 
endmodule
