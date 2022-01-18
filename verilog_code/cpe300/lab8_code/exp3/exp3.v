/*
    using memory
*/

`timescale 1ns/1ns
`define HALF 5
`define SEED 556

module tb();

    wire [7:0] bus;
    reg [7:0] data_in;
    reg [3:0] address;
    reg WE;
    reg clock;

    integer idx;
    integer seed;
    reg [7:0] catch;

    memory_unit DUT (
						.bus(bus), 
                        .data_in(data_in),
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
        $write("\ntest the memory unit\n\n");
        seed = `SEED;
		clock = 1'b0;
		#`HALF;
		#`HALF;

        $write(" the initialized values:\n");
        WE = 1'b0;
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address = idx;
            #`HALF; #`HALF;
            $write("\taddress %4b  ,  %4b_%4b\n", address, bus[7:4], bus[3:0]);    
        end

        $write("\nread half new data, keep half old data:\n\n");
        $write(" address  |  data_in    |  RAM[address] |  bus \"output\"\n");
        $write("-----------------------------------------------------------------\n");
        WE = 1'b1;
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address = idx;
            data_in = $random(seed) % 256;
            #`HALF; #`HALF;
            catch = DUT.ram_memory[address];
            if (idx > 7) WE = 1'b0;
            $write("   %4b   |  %4b_%4b  |  %4b_%4b    |  %4b_%4b\n", 
                address, data_in[7:4], data_in[3:0], 
                catch[7:4], catch[3:0],
                bus[7:4], bus[3:0]);
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module memory_unit (
						output wire [7:0] bus,       // always reads data from address here
                        input wire [7:0] data_in,    // read to memory if WE 
						input wire [3:0] address,    // 4 address bits = 16 locations (depth)
						input wire WE,               // won't read unless enabled
						input wire clock
					);

	reg [7:0] ram_memory [15:0];    // 16 x 8 RAM
    integer idx;
    parameter ram_init = 8'b1111_1111;

	initial begin
		//$readmemb("data.txt", ram_memory);
        //
        for (idx = 0; idx < 16; idx = idx + 1) begin
            ram_memory[idx] = ram_init;
        end
        //
	end

	assign bus = ram_memory[address];

	always @ (posedge clock) begin
		if(WE == 1'b1) begin
			ram_memory[address] <= data_in; 
		end
	end
endmodule


////////~~~~~~~~END>  exp3.v


module my_ROM (
                output wire [7:0] rom_out, 
                input wire [2:0] address,
                input wire read
            );

reg [7:0] rom_memory [7:0];   //  8 address of 8-bit-words

    // any values you need, or use file
    parameter rom_000 = 0000_0000; 
    parameter rom_001 = 0000_0001;
    parameter rom_010 = 0000_0010;
    parameter rom_011 = 0000_0011;
    parameter rom_100 = 0000_0100;
    parameter rom_101 = 0000_0101;
    parameter rom_110 = 0000_0110;
    parameter rom_111 = 0000_0111;

always @(read) begin
        rom_memory[3'b000] = rom_000;
        rom_memory[3'b001] = rom_001;
        rom_memory[3'b010] = rom_010;
        rom_memory[3'b011] = rom_011;
        rom_memory[3'b100] = rom_100;
        rom_memory[3'b101] = rom_101;
        rom_memory[3'b110] = rom_110;
        rom_memory[3'b111] = rom_111;
        rom_out=ROM[address];
    end
endmodule