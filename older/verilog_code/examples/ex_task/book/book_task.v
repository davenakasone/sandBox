/*
    [Cavanagh, Verilog HDL Examples] "VerilogExamples.pdf" {p132}
    verilog task example from book
*/

module task_log_arith;

    reg [7:0] in_1;     // input
    reg [7:0] in_2;     // input
    reg [7:0] in_3;     // input
    reg [7:0] out_1;    // output
    reg [7:0] out_2;    // output
    reg [7:0] out_3;    // output
    reg [7:0] out_4;    // output

    initial begin
        $display("\nthe task can assign value to address...\n\n");
        in_1 = 8'b1111_1111;
        in_2 = 8'b0011_1111;
        in_3 = 8'b0001_1101;
        calc(in_1, in_2, in_3, out_1, out_2, out_3, out_4);
        $write("\n\ta:  %b  ,  b:  %b  ,  c:  %b\n", 
            in_1, in_2, in_3);
        $write("\tw:  %b  ,  x:  %b  ,  y:  %b  ,  z:  %b\n\n",
            out_1, out_2, out_3, out_4);
    end

    task calc;
        input [7:0] arg_1;    // basically redeclaring
        input [7:0] arg_2;
        input [7:0] arg_3;
        output [7:0] ret_1;
        output [7:0] ret_2;
        output [7:0] ret_3;
        output [7:0] ret_4;

        begin
            ret_1 = (arg_2 + arg_3) | (arg_1);
            ret_2 = (arg_1 & arg_3) + (arg_2);
            ret_3 = (~arg_1 + arg_3) & (arg_2);
            ret_4 = (arg_2 | arg_3) & (arg_1);
            
            $write("a:  %b  ,  b:  %b  ,  c:  %b\n", 
                arg_1, arg_2, arg_3);
            $write("w:  %b  ,  x:  %b  ,  y:  %b  ,  z:  %b\n",
                ret_1, ret_2, ret_3, ret_4);
    
        end
    endtask

endmodule

////////~~~~~~~END>  book_task.v
