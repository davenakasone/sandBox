/*
    use funcitons to make an adder
*/

module fullAdder (
                    output wire sum,
                    output wire c_out,
                    input wire a,
                    input wire b,
                    input wire c_in
                );

    function wire f_sum (
                            input wire arg_x,
                            input wire arg_y,
                            input wire arg_z
                        );
        begin
            f_sum = arg_x ^ arg_y ^ arg_z;
        end
    endfunction
    
    function wire f_carry(
                            wire arg_x,
                            wire arg_y,
                            wire arg_z
                         );
        begin
            f_carry = (arg_x & arg_y) |
                    (arg_x | arg_z) |
                    (arg_y & arg_z);
        end
    endfunction

    assign sum = f_sum(a, b, c_in);
    assign c_out = f_carry(a, b, c_in);

    

endmodule






////////~~~~~~~~END>  funEx.v
