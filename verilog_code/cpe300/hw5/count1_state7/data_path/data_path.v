/*
    data path links the 5 components together
*/

`include "../comp1_mux21_8/mux21_8.v"
`include "../comp2_register_file/register_file.v"
`include "../comp3_alu_unsigned/alu_unsigned.v"
`include "../comp4_shifter8/shifter8.v"
`include "../comp5_output_buffer/output_buffer.v"


module data_path (
                    output wire n_is_0,
                    output wire [7:0] run_sum,
                    input wire [7:0] n_in,
                    input wire clock,
                    input wire input_enable_mux,
                    input wire WE,
                    input wire [1:0] WA,
                    input wire RAE,
                    input wire [1:0] RAA,
                    input wire RBE,
                    input wire [1:0] RBA,
                    input wire [2:0] alu_op,
                    input wire [1:0] shift_op,
                    input wire output_enable_buf
            );

    reg [7:0] rf_inp;
    wire [7:0] rf_a;
    wire [7:0] rf_b;
    wire [7:0] alu_out;
    wire [7:0] shifter_out;
    wire [7:0] nnn;
	
	initial rf_inp = 8'b0000_0000;
	
    // n == 0 once input number is completey shifted with 0's
    // only valid on right shift instruction because others could be 0
	always @ (*) rf_inp = nnn;
	
	assign n_is_0 = ( (nnn == 8'b0000_0000) &
                      (shift_op == 2'b10) ) |
                    (n_in == 8'b0000_0000); 

    mux21_8 c1_mux (
                        .to_register_file (nnn),
					    .from_shifter     (shifter_out),
					    .input_data       (n_in),
					    .mux_selector     (input_enable_mux)
                );
    
    register_file c2_rf(
                            .port_A(rf_a),
                            .port_B(rf_b),
                            .clock(clock),
                            .write_enable(WE),
                            .write_address(WA),
                            .read_A_enable(RAE),
                            .read_A_address(RAA),
                            .read_B_enable(RBE),
                            .read_B_address(RBA),
                            .from_mux(rf_inp)
                    );
    
    alu_unsigned c3_alu (
                            .to_shifter(alu_out),
                            .rf_A(rf_a),
                            .rf_B(rf_b),
                            .alu_operation(alu_op)
                    );
    
    shifter8 c4_shift (
                        .to_bus(shifter_out),
                        .from_alu(alu_out),
                        .shift_operation(shift_op)
                    );
    
    output_buffer c5_tri_buff (
                                .result(run_sum),
                                .from_shifter(shifter_out),
                                .enable(output_enable_buf)
                        );
    
    `ifdef DEBUG_data_path
        //always @ (*) begin
        always @ (posedge clock) begin
            //#1;
            $write("\n ************************************************\n");
            $write(" {data_path}                               %4t\n", $time);
            $write("               n_is_0:  %1b\n", n_is_0);
            $write(" -------------------------\n");
            $write("     input_enable_mux:  %1b\n", input_enable_mux);
            $write("  mux[0], shifter_out:  %4b_%4b\n", shifter_out[7:4], shifter_out[3:0]);
            $write("         mux[1], n_in:  %4b_%4b\n", n_in[7:4], n_in[3:0]);
            $write("         mux out, nnn:  %4b_%4b\n", nnn[7:4], nnn[3:0]);
            $write(" ---------------------------------\n");
            $write("               rf_inp:  %4b_%4b\n", rf_inp[7:4], rf_inp[3:0]);
            $write("      write enable WE:  %1b  ,   WA:  %2b\n", WE, WA);
            $write("    read A enable RAE:  %1b  ,  RAA:  %2b\n", RAE, RAA);
            $write("    read B enable RBE:  %1b  ,  RBA:  %2b\n", RBE, RBA);
            $write(" reg[00]:  %4b_%4b \"count\"\n", c2_rf.internal_register[2'b00][7:4], c2_rf.internal_register[2'b00][3:0]);
            $write(" reg[01]:  %4b_%4b \"n\"\n", c2_rf.internal_register[2'b01][7:4], c2_rf.internal_register[2'b01][3:0]);
            $write(" reg[10]:  %4b_%4b \"AND mask\"\n", c2_rf.internal_register[2'b10][7:4], c2_rf.internal_register[2'b10][3:0]);
            $write(" reg[11]:  %4b_%4b \"AND result\"\n", c2_rf.internal_register[2'b11][7:4], c2_rf.internal_register[2'b11][3:0]);
            $write("               port A:  %4b_%4b\n", rf_a[7:4], rf_a[3:0]);
            $write("               port B:  %4b_%4b\n", rf_b[7:4], rf_b[3:0]);
            $write(" --------------------------------------\n");
            $write("        alu operation:  %3b\n", alu_op);
            $write("           alu output:  %4b_%4b\n", alu_out[7:4], alu_out[3:0]);
            $write(" ---------------------------------\n");
            $write("    shifter operation:  %3b\n", shift_op);
            $write("       shifter output:  %4b_%4b\n", shifter_out[7:4], shifter_out[3:0]);
            $write(" ---------------------------------\n");
            $write("  ouput buffer enable:  %1b\n", output_enable_buf);
            $write("          running sum:  %4b_%4b\n", run_sum[7:4], run_sum[3:0]);
            if (n_is_0 == 1'b1 && run_sum != 8'bzzzz_zzzz) begin
                $write("\n^^^ algorithm success: sum =  %2d ^^^\n", run_sum);
            end
            $write(" ************************************************");
        end
    `endif
endmodule


////////~~~~~~~~END>  data_path.v
