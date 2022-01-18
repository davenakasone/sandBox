/*
    simple 4x8 register file
        4 registers, 8-bits each
        connect to bus {A,B} with tri-state buffer
        gated control for read and write + 4:2 decoder
*/

`include "../heads.v"


module register_file (
                        output wire [7:0] port_A,
                        output wire [7:0] port_B,
                        input wire clock,
                        input wire write_enable,
                        input wire [1:0] write_address,
                        input wire read_A_enable,
                        input wire [1:0] read_A_address,
                        input wire read_B_enable,
                        input wire [1:0] read_B_address,
                        input wire [7:0] from_mux
                    );
    reg [7:0] internal_register [0:3];

    always @ (posedge clock) begin
        if (write_enable == 1'b1) begin
            internal_register[write_address] <= from_mux;
        end
    end 

    assign port_A = (read_A_enable == 1'b1) ? internal_register[read_A_address] : 8'b0000_0000;
    assign port_B = (read_B_enable == 1'b1) ? internal_register[read_B_address] : 8'b0000_0000;

    `ifdef DEBUG_register_file
        always @ (negedge clock) begin
            $write("\n *****************************************************\n");
            $write(" {register_file}                               %3t ns\n", $time);
            $write("            from_mux:  %4b_%4b\n", from_mux[7:4], from_mux[3:0]);
            $write("        write_enable:  %1b  ,   write_address:  %2b\n", write_enable, write_address);
            $write("       read_A_enable:  %1b  ,  read_A_address:  %2b\n", read_A_enable, read_A_address);
            $write("       read_B_enable:  %1b  ,  read_B_address:  %2b\n", read_B_enable, read_B_address);
            $write("       -----------------------------------------------\n");
            $write("               portA:  %4b_%4b\n", port_A[7:4], port_A[3:0]);
            $write("               portB:  %4b_%4b\n", port_B[7:4], port_B[3:0]);
            $write("\n reg[00]:  %4b_%4b\n", internal_register[2'b00][7:4], internal_register[2'b00][3:0]);
            $write(" reg[01]:  %4b_%4b\n",   internal_register[2'b01][7:4], internal_register[2'b01][3:0]);
            $write(" reg[10]:  %4b_%4b\n",   internal_register[2'b10][7:4], internal_register[2'b10][3:0]);
            $write(" reg[11]:  %4b_%4b\n",   internal_register[2'b11][7:4], internal_register[2'b11][3:0]);
            $write(" *****************************************************\n");
        end
    `endif

endmodule


////////~~~~~~~END>  register_file.v
