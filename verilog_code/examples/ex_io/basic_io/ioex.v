/*
    a basic io example
    make sure .txt files are good

    focus on files
*/

`timescale 1ns/1ns
`define BITZ 3
`define IN_FILE `"input.txt`"
`define OUT_FILE `"output.txt`"
`define EOFF 0

module io_example();
    reg [3:0] holder;
    integer read_fd;
    integer write_fd;
    reg status;

    initial begin

        read_fd = $fopenr(`IN_FILE);
        status = read_fd;
        if (~status) begin
            $write("error opening read file %s  ,  returned:  %d\n", 
                `IN_FILE, status);
        end

        write_fd = $fopenw(`OUT_FILE);
        status = write_fd;
        if (~status) begin
            $write("error opening write file %s  ,  returned:  %d\n", 
                `OUT_FILE, status);
        end

        status = $fgets(holder, read_fd);
        while (status == `EOFF) begin
            status = $fputc(write_fd, holder[0]);
            status = $fgets(holder, read_fd);
        end

        $fclose(read_fd);
        $fclose(write_fd);
        #100000
        $finish;
    end
endmodule

////////~~~~~~~~END>  ioex.v
