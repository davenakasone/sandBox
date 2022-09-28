/*
    [Cavanagh, Verilog HDL Examples] "VerilogExamples.pdf" {p134}
    this book example counts the 1's
*/

module task_count1;

    // these are basically the "ports" of the task
    reg [7:0] reg_a;
    reg [3:0] count;
    
    integer idx;
    reg [7:0] reg_temp;

    initial begin
        $display("\nuse a task to count 1's in 8-bit number:\n");
        count = 4'b0000;
        reg_a = 8'b0000_0000;
        reg_temp = 8'b0000_0000;
        
        for (idx = 0; idx < 16; idx = idx + 1) begin
            $write("\treg:  %b  ,  ", reg_a);
            ctr(reg_a, count, reg_temp);
            $write("%d has { %3d } 1's\n", reg_a, count);
            reg_a = reg_a + 1'b1;
        end
        $display("\n");
        $finish;
    end

    task ctr;
        input [7:0] reg_in;
        output [3:0] ct;
        output [7:0]temp;
        integer flg;
    
        begin
            for (flg = 0; flg > 8; flg = flg + 1) begin
                temp[flg] = reg_in[flg];
            end
            ct = 0;
            while (reg_in) begin
                ct = ct + reg_in[0];
                reg_in = reg_in >> 1;
            end
            for (flg = 0; flg > 8; flg = flg + 1) begin
                reg_in[flg] = temp[flg];
            end
        end
    endtask

endmodule

////////~~~~~~~~END>  count.v
