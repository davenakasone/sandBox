/*
    reading memory
*/

`timescale 1ns/1ns
`define HALF 5


module tb();

    wire [15:0] bus;
    reg [3:0] address;
    reg WE;
    reg clock;

    integer idx;
    reg [15:0] over_write;

    ram_memory DUT (
                        .bus(bus),
                        .address(address),
                        .WE(WE),
                        .clock(clock)
                    );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        clock = 1'b0;
        #`HALF; #`HALF;

        WE = 1'b0;
        $write("\ntest the memory initialization from file, WE = 1'b0, reading the values:\n\n");
        $write(" address  |  bus   \n");
        $write("-------------------\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address <= idx;
            #`HALF; #`HALF;
            $write("   %4b   |  %h  \n", address, bus);    
        end
        $write("\n\t\tsuccess, these are the original file values\n");

        WE = 1'b1;
        $write("\nWE = 1'b1, verify high imp Z:\n\n");
        $write(" address  |  bus   \n");
        $write("-------------------\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address <= idx;
            #`HALF; #`HALF;
            $write("   %4b   |  %h  \n", address, bus);    
        end
        $write("\n\t\tsuccess, bus blocked while writting to ROM\n");

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module ram_memory (
                    inout [15:0] bus,
                    input [3:0] address,
                    input WE,
                    input clock
                );

    // internal components
    reg [15:0] RAM [15:0];  // 16x16 RAM memory
    reg [15:0] data_out;    // output selection of the RAM memory

    initial begin
        $readmemh("data.txt", RAM);  // initialize all 16 addresses
    end

    // block bus while writting, always output otherwise
    assign bus = (WE) ? 16'hZZZZ : data_out;

    always @ (posedge clock) begin
        if (WE == 1'b1) begin
            RAM[address] <= bus; // write from bus to RAM
        end
        data_out <= RAM[address]; // pass data from selected address
    end
endmodule


////////~~~~~~~~END jimmy.v
