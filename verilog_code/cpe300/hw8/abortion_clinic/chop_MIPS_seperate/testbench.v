module testbench();
reg clk;
reg reset;
wire [31:0] writedata, dataadr;
wire memwrite;

// instantiates the  device to be tested (device under test-DUT)
top dut (clk, reset, writedata, dataadr, memwrite);

// initialize test
initial
begin
reset <= 1; # 22; reset <= 0;
end

// generate clock to sequence tests

always
begin
clk <= 1;
 # 5; 
 clk <= 0;
 # 5; // clock duration
end

// check the contents of memory location 84. It must be 7

always @ (negedge clk)
begin
if (memwrite) begin
if (dataadr === 84 & writedata === 7) begin
$display ("Simulation succeeded");
$stop;
end 
else if (dataadr !== 80) begin
$display ("Simulation failed");
$stop;
end
end
end
endmodule
