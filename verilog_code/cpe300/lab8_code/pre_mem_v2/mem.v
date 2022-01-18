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

	memory_unit DUT (
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
        $write("\ntest the memory read\n\n");
		clock = 1'b0;
		#`HALF;
		#`HALF;
		clock = 1'b0;

        WE = 1'b0;
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address <= idx;
            #`HALF; #`HALF;
            $write("address %4b  ,  %h\n", address, bus);    
        end

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~


module memory_unit (
						inout [15:0] bus,            // width of 16
						input wire [3:0] address,    // 4 address bits = 16 locations (depth)
						input wire WE,
						input wire clock
					);

	reg [15:0] data_out;
	reg [15:0] RAM [0:15];    // 16 x 16 ram

	initial begin
		$readmemh("data.txt", RAM);
	end

	assign bus = WE ? 16'hZZZZ : data_out;

	always @ (posedge clock) begin
		if(WE == 1'b1) begin
			RAM[address] <= bus;
		end
		data_out <= RAM[address];
	end

endmodule
