/*
    the general data path
    ensure proper algorithm to control unit
        control unit
        data path (adjust output logic as needed)
    other components follow
*/

`include "../control_unit/cntlU.v"
`include "../data_path/data_path.v"


module GDP (
                output wire [7:0] runSum,
                output wire done,
                input wire [7:0] n_in,
                input wire start,
                input wire restart,
                input wire clock
        );

    wire ie;
    wire condition;
    wire we;
    wire [1:0] wa;
    wire rae;
    wire [1:0] raa;
    wire rbe;
    wire [1:0] rba;
    wire [2:0] alu;
    wire [1:0] shf;
    wire oe;

    assign done = oe;

    cntlU CU (
                .IE(ie),
                .WE(we), 
                .WA(wa),
                .RAE(rae),
                .RAA(raa),
                .RBE(rbe),
                .RBA(rba),
                .ALU(alu),
                .SH(shf),
                .OE(oe),
                .clk(clock), 
                .start(~start), 
                .restart(~restart), 
                .nEqZero(condition)
        );
    
    data_path DP (
                    .n_is_0(condition),
                    .run_sum(runSum),
                    .n_in(n_in),
                    .clock(clock),
                    .input_enable_mux(ie),
                    .WE(we),
                    .WA(wa),
                    .RAE(rae),
                    .RAA(raa),
                    .RBE(rbe),
                    .RBA(rba),
                    .alu_op(alu),
                    .shift_op(shf),
                    .output_enable_buf(oe)
            );
endmodule

////////~~~~~~~~END>  gpd.v
	