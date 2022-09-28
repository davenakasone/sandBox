/*
    basic RAM
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
    reg [15:0] validator [15:0];

    mem DUT (
                        .BUS(bus),
                        .ADDR(address),
                        .WE(WE),
                        .CLK(clock)
                    );
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);
        $readmemh("data.txt", validator);
        clock = 1'b0;
        #`HALF; #`HALF;

        WE = 1'b0;
        $write("\ntest the memory initialization from file, WE = 1'b0, reading the values to bus:\n\n");
        $write(" address  |  bus   \n");
        $write("-------------------\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address <= idx;
            #`HALF; #`HALF;
            if (bus == validator[address]) begin
                $write("   %4b   |  %h  \n", address, bus);  
            end
            else begin
                $write("ERROR\n");
            end
        end
        $write("\n\t\tsuccess, these are the original file values, properly read to the bus\n");
      
      $write("\nlook inside the RAM...\n\n");
        $write(" address  |  [15:0]RAM[address]\n");
        $write("--------------------------------\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address <= idx;
            #`HALF; #`HALF;
            if (validator[address] == DUT.RAM[address]) begin
                $write("   %4b   |  %h  \n", address, DUT.RAM[address]);  
            end
            else begin
                $write("ERROR\n");
            end 
        end
        $write("\n\t\tsuccess, the internal RAM has collected file data\n");

        WE = 1'b1;
        $write("\nWE = 1'b1, verify high imp Z:\n\n");
        $write(" address  |  bus   \n");
        $write("-------------------\n");
        for (idx = 0; idx < 16; idx = idx + 1) begin
            address <= idx;
            #`HALF; #`HALF;
            $write("   %4b   |  %h  \n", address, bus);    
        end
        $write("\n\t\tsuccess, bus blocked while writting to RAM\n");

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end
endmodule


////~~~~

module mem(WE, CLK, ADDR, BUS);
input WE, CLK;
input [3:0] ADDR; //4 address bits = 16 locations (depth)
inout [15:0] BUS; //width of 16
reg [15:0] data_out;
//16x16 ram
reg [15:0] RAM [0:15];

initial begin
	$readmemh("data.txt", RAM);
end

assign BUS = WE ? 16'hZZZZ : data_out;

always@(posedge CLK) begin
	if(WE == 1'b1)
		RAM[ADDR] <= BUS;
	data_out <= RAM[ADDR];
end
endmodule

////////~~~~~~~~END> basic.v
