/*
    the exclusive OR, inverted
    "XNOR"

    a  b  y
    -------
    0  0  1
    0  1  0
    1  0  0
    1  1  0

    2 inputs, 1 output
*/

module xnor_2 (
                output wire y,
                input wire a,
                input wire b
              );

    assign y = ~(a ^ b);
    
endmodule

////////~~~~~~~~END>  xnor_2.v
