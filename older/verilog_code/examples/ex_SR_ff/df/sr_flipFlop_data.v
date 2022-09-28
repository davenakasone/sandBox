/*
    dataflow model of SR flip-flop
*/

module sr_flipFlop (
                    output Q,
                    input clk,
                    input rst,
                    input set
                );
// synthesis keep
    wire R_g;
    wire S_g;
    wire Qa;
    wire Qb;

// implement with continous-blocking assigment
    assign R_g = rst & clk;
    assign S_g = set & clk;
    assign Qa = ~(R_g | Qb);
    assign Qb = ~(S_g | Qa);
    assign Q = Qa;

endmodule

////////~~~~~~~~END>  sr_flipFlop_data.v
