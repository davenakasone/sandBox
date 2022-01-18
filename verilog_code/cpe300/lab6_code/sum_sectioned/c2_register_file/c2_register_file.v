/*
    the register file
*/

`include "../heads.v"


module c2_register_file(
                            output wire [7:0] port_A,     // value assigned to port A
                            output wire [7:0] port_B,     // value assigned to port B
                            input wire [7:0] from_mux,    // bus after MUX selection
                            input wire WE,                // write enable
                            input wire [1:0] WA,          // write address
                            input wire RAE,               // port A read enable
                            input wire [1:0] RAA,         // port A Read address 
                            input wire RBE,               // port B read enable
                            input wire [1:0] RBA,         // port B read address
                            input wire clock
                        ); 
	
    parameter BLANK = 8'b0000_0000;

    // x4 8-bit registers "4x8"
	reg [7:0] internal [3:0]; 

    // only write if WE is active
	always @ (posedge clock) begin
        if (WE == 1'b1) internal[WA] <= from_mux;
    end
     
    // reading to ports is done in combination, if enabled
    assign port_A = (RAE == 1'b1) ? internal[RAA] : BLANK; 
    assign port_B = (RBE == 1'b1) ? internal[RBA] : BLANK;

    `ifdef DEBUG_RF
        always @ (negedge clock) begin
            $write("\n *****************************************************\n");
            $write(" {c2_register_file}                               %3t ns\n", $time);
            $write("                       from_mux:  %4b_%4b\n", from_mux[7:4], from_mux[3:0]);
            $write("        WE:  %1b  ,   WA:  %2b\n", WE, WA);
            $write("       RAE:  %1b  ,  RAA:  %2b\n", RAE, RAA);
            $write("       RBE:  %1b  ,  RBA:  %2b\n", RBE, RBA);
            $write("       -----------------------------------------------\n");
            $write("               portA:  %4b_%4b\n", port_A[7:4], port_A[3:0]);
            $write("               portB:  %4b_%4b\n", port_B[7:4], port_B[3:0]);
            $write("\n reg[00]:  %4b_%4b\n", internal[2'b00][7:4], internal[2'b00][3:0]);
            $write(" reg[01]:  %4b_%4b\n",   internal[2'b01][7:4], internal[2'b01][3:0]);
            $write(" reg[10]:  %4b_%4b\n",   internal[2'b10][7:4], internal[2'b10][3:0]);
            $write(" reg[11]:  %4b_%4b\n",   internal[2'b11][7:4], internal[2'b11][3:0]);
            $write(" *****************************************************\n");
        end
    `endif
endmodule


////////~~~~~~~~END>  c2_register_file.v
