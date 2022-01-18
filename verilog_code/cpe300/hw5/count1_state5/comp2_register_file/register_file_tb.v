/*
    test:  register_file.v
*/

`include "register_file.v"

//`define WRITE_4 1111
//`define WRITE_4_A 2222
//`define WRITE_4_B 3333
`define WRITE_4_AB 4444



module register_file_tb();
    wire [7:0] outA;
    wire [7:0] outB;
    reg clk;
    reg WE;
    reg [1:0] WA;
    reg RAE;
    reg [1:0] RAA;
    reg RBE;
    reg [1:0] RBA;
    reg [7:0] inP;

    integer seed;
    integer ii;
    integer fullCycle;

    register_file DUT (
                        .port_A(outA),
                        .port_B(outB),
                        .clock(clk),
                        .write_enable(WE),
                        .write_address(WA),
                        .read_A_enable(RAE),
                        .read_A_address(RAA),
                        .read_B_enable(RBE),
                        .read_B_address(RBA),
                        .from_mux(inP)
                    );
    
    always begin
        #`HALF_CYCLE;
        clk = ~clk;
    end

    initial begin
        `ifdef DEBUG_wave
            $dumpfile("wave.vcd");
            $dumpvars(0, register_file_tb);
        `endif
        seed = `SEED;
        fullCycle = 2 * `HALF_CYCLE;
        $write("\n test the Register File\n");
        clk = 1'b0;
        WE = 1'b0;
        WA = 2'b00;
        RAE = 1'b0;
        RAA = 2'b0;
        RBE = 1'b0;
        RBA = 2'b0;
        inP = 8'b0000_0000;

        `ifdef WRITE_4
            $write(" fill all 4 registers with values, don't read to ports\n\n");
            WE = 1'b1;
            RAE = 1'b0;
            RBE = 1'b0;
            for (ii = 0; ii < 4; ii = ii + 1) begin
                #`T_ERROR
                rand_reg(inP);
                WA = ii;
                #fullCycle;
            end
        `endif

        `ifdef WRITE_4_A
            $write(" fill all 4 registers with values, then read address to <port A>\n");
            WE = 1'b1;
            RAE = 1'b1;
            RBE = 1'b0;
            for (ii = 0; ii < 4; ii = ii + 1) begin
                #`T_ERROR
                rand_reg(inP);
                RAA = ii;
                WA = ii;
                #fullCycle;
            end
        `endif
        
        `ifdef WRITE_4_B
            $write(" fill all 4 registers with values, then read address to <port B>\n");
            WE = 1'b1;
            RAE = 1'b0;
            RBE = 1'b1;
            for (ii = 0; ii < 4; ii = ii + 1) begin
                #`T_ERROR
                rand_reg(inP);
                RBA = ii;
                WA = ii;
                #fullCycle;
            end
        `endif

        `ifdef WRITE_4_AB
            $write(" fill all 4 registers with values, then read address to <port B>\n");
            WE = 1'b1;
            RAE = 1'b1;
            RBE = 1'b1;
            for (ii = 0; ii < 4; ii = ii + 1) begin
                #`T_ERROR
                rand_reg(inP);
                RBA = ii;
                RAA = ii;
                WA = ii;
                #fullCycle;
            end
        `endif
        
        #`HALF_CYCLE
        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic rand_reg;
        output reg [7:0] r_r;
        integer idx;
        begin
            for (idx = 0; idx < 8; idx = idx + 1) begin
                r_r[idx] = $random(seed) % 2;
            end
        end
    endtask

endmodule


////////~~~~~~~END>  register_file_tb.v
