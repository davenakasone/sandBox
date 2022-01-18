/*
    the data path combines all 5 components
    also, any probing for logic check(s)
        change the logic checks depending on algorithim
*/

`include "../c1_mux/c1_mux.v"
`include "../c2_register_file/c2_register_file.v"
`include "../c3_alu/c3_alu.v"
`include "../c4_shifter/c4_shifter.v"
`include "../c5_triBuff/c5_triBuff.v"


module data_path (
                    output wire n_is_0,
                    output wire [7:0] result,
                    input wire [7:0] n_input,
                    input wire IE,
                    input wire WE,
                    input wire [1:0] WA,
                    input wire RAE,
                    input wire [1:0] RAA,
                    input wire RBE,
                    input wire [1:0] RBA,
                    input wire [2:0] ALU,
                    input wire [1:0] SH,
                    input wire OE,
                    input wire clock
                );

    parameter BLANK = 8'b0000_0000;  
    wire [7:0] from_mux;          
	reg [7:0] to_register_file;
    wire [7:0] rf_port_A;
    wire [7:0] rf_port_B;
    wire [7:0] from_alu;
    wire [7:0] from_shifter;
	
    /*
        This internal register completes the feedback.
        Unlike the other connections, it must be a register.
        It is very important and provides the initialization,
        along with proper transfer sequence.
    */
    initial begin
        to_register_file = BLANK;
    end
    always @ (*) begin
        to_register_file = from_mux;
    end
	
    /*
        This is the probe right under the MUX.
        It won't fail if you move states correctly.
        Don't get too crazy with the logic checks.
    */
	assign n_is_0 = (from_mux == 8'b0000_0000); 

    c1_mux comp1 (
                    .from_mux(from_mux),
                    .new_data(n_input), 
                    .feedback(from_shifter),
                    .IE(IE)
                );

    c2_register_file comp2 (
                            .port_A(rf_port_A),
                            .port_B(rf_port_B),     
                            .from_mux(to_register_file),
                            .WE(WE),                
                            .WA(WA),          
                            .RAE(RAE),    
                            .RAA(RAA),         
                            .RBE(RBE),            
                            .RBA(RBA),      
                            .clock(clock)
                        ); 

    c3_alu comp3 (
                    .from_alu(from_alu),
                    .A_bus(rf_port_A),
                    .B_bus(rf_port_B),
                    .ALU(ALU)
                );

    c4_shifter comp4 (
                        .from_shifter(from_shifter),
                        .from_alu(from_alu),
                        .SH(SH)
                    );


    c5_triBuff comp5 (
                        .result(result), 
                        .from_shifter(from_shifter), 
                        .OE(OE)
                    );
    
    `ifdef DEBUG_DP
        always @ (negedge clock) begin
            #1;
            $write("\n ************************************************\n");
            $write(" {data_path}                               %7t ns\n", $time);
            $write("               n_is_0:  %1b\n", n_is_0);
            $write(" -------------------------\n");
            $write("                   IE:  %1b\n", IE);
            $write("  mux[0], shifter_out:  %4b_%4b\n", from_shifter[7:4], from_shifter[3:0]);
            $write("         mux[1], n_in:  %4b_%4b\n", n_input[7:4], n_input[3:0]);
            $write("         mux out, nnn:  %4b_%4b\n", from_mux[7:4], from_mux[3:0]);
            $write(" ---------------------------------\n");
            $write("               rf_inp:  %4b_%4b\n", to_register_file[7:4], to_register_file[3:0]);
            $write(" WE:   %1b  ,  WA:   %2b\n", WE, WA);
            $write(" RAE:  %1b  ,  RAA:  %2b\n", RAE, RAA);
            $write(" RBE:  %1b  ,  RBA:  %2b\n", RBE, RBA);
            $write(" reg[00]:  %4b_%4b\n", comp2.internal[2'b00][7:4], comp2.internal[2'b00][3:0]);
            $write(" reg[01]:  %4b_%4b\n", comp2.internal[2'b01][7:4], comp2.internal[2'b01][3:0]);
            $write(" reg[10]:  %4b_%4b\n", comp2.internal[2'b10][7:4], comp2.internal[2'b10][3:0]);
            $write(" reg[11]:  %4b_%4b\n", comp2.internal[2'b11][7:4], comp2.internal[2'b11][3:0]);
            $write("               port A:  %4b_%4b\n", rf_port_A[7:4], rf_port_A[3:0]);
            $write("               port B:  %4b_%4b\n", rf_port_B[7:4], rf_port_B[3:0]);
            $write(" --------------------------------------\n");
            $write("        alu operation:  %3b\n", ALU);
            $write("           alu output:  %4b_%4b\n", from_alu[7:4], from_alu[3:0]);
            $write(" ---------------------------------\n");
            $write("    shifter operation:  %3b\n", SH);
            $write("       shifter output:  %4b_%4b\n", from_shifter[7:4], from_shifter[3:0]);
            $write(" ---------------------------------\n");
            $write("                   OE:  %1b\n", OE);
            $write("               result:  %4b_%4b", result[7:4], result[3:0]);
            if (OE == 1'b1) $write("   !!!SUCCESS!!!\n");
            else $write("      ...working\n");
            $write(" ************************************************\n");
        end
    `endif
endmodule


////////~~~~~~~~END>  data_path.v
