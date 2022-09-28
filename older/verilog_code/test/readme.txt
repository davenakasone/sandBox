make your "modules"

make a test bench (pay attention to the house-keeping procedures)
    note that modelsim, icarus, and others may be different

when all the code is good, "compile" the TB:
(base) Davids-MacBook-Pro-2:test davidnakasone$ iverilog -o hello_tb.vvp hello_tb.v

if there are no errors, run the object file:
(base) Davids-MacBook-Pro-2:test davidnakasone$ vvp hello_tb.vvp
VCD info: dumpfile hello_tb.vcd opened for output.


		 ~ ~ ~ TEST COMPLETE ~ ~ ~



double click the *.vcd file to view the wave
