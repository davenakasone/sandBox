/*
    test:  c2_register_file
*/

`include "c2_register_file.v"


module tb();
    wire [7:0] port_A;
    wire [7:0] port_B;
    reg [7:0] from_mux;
    reg WE;
    reg [1:0] WA;
    reg RAE;
    reg [1:0] RAA;
    reg RBE;
    reg [1:0] RBA;
    reg clock;

    integer seed;
    integer ii;

    c2_register_file DUT (
                            .port_A(port_A),  
                            .port_B(port_B),     
                            .from_mux(from_mux),
                            .WE(WE), 
                            .WA(WA),         
                            .RAE(RAE),             
                            .RAA(RAA),        
                            .RBE(RBE),            
                            .RBA(RBA),  
                            .clock(clock)
                        ); 
    
    always begin
        #`HALF;
        clock = ~clock;
    end

    initial begin
        `ifdef DEBUG_WAVE
            $dumpfile("wave.vcd");
            $dumpvars(0, tb);
        `endif
        seed = `SEED;
        $write("\n test component 2 of 5, the register file\n\n");
        clock = 1'b0;
        WE = 1'b0;
        WA = 2'b00;
        RAE = 1'b0;
        RAA = 2'b0;
        RBE = 1'b0;
        RBA = 2'b0;
        from_mux = 8'b0000_0000;

        $write("\n fill all 4 registers with values, don't read to ports\n\n");
        WE = 1'b1;
        RAE = 1'b0;
        RBE = 1'b0;
        for (ii = 0; ii < 4; ii = ii + 1) begin
            #`T_ERROR
            rand_reg(from_mux);
            WA = ii;
            #(`HALF + `HALF);
        end
       
        $write("\n fill all 4 registers with values, then read address to <port A>\n");
        WE = 1'b1;
        RAE = 1'b1;
        RBE = 1'b0;
        for (ii = 0; ii < 4; ii = ii + 1) begin
            #`T_ERROR
            rand_reg(from_mux);
            RAA = ii;
            WA = ii;
            #(`HALF + `HALF);
        end

        $write("\n fill all 4 registers with values, then read address to <port B>\n");
        WE = 1'b1;
        RAE = 1'b0;
        RBE = 1'b1;
        for (ii = 0; ii < 4; ii = ii + 1) begin
            #`T_ERROR
            rand_reg(from_mux);
            RBA = ii;
            WA = ii;
            #(`HALF + `HALF);
        end

        $write("\n fill all 4 registers with values, then read address to <port B>\n");
        WE = 1'b1;
        RAE = 1'b1;
        RBE = 1'b1;
        for (ii = 0; ii < 4; ii = ii + 1) begin
            #`T_ERROR
            rand_reg(from_mux);
            RBA = ii;
            RAA = ii;
            WA = ii;
            #(`HALF + `HALF);
        end
        
        #`HALF
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


////////~~~~~~~END>  tb.v
