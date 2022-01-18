
////~~~~  combines all
module total (
                output wire [6:0] digit_2,
                output wire [6:0] digit_1,
                input wire [4:0] n_in,
                input wire start,
                input wire restart,
                input wire up,
                input wire clk
            );
    
    wire clk_trans;
    wire [4:0] temp;
    wire [3:0] onez;
    wire [3:0] tenz;

    clk_50MHz_to_1Hz CLK ( 
                            .clk_1hz(clk_trans),
                            .clk_50mhz(clk)
                        );

    conUnit CoU (
                        .countt(temp),
                        .n_in(n_in),
                        .start(start),
                        .restart(restart),
                        .up_count(up),
                        .clock(clk_trans)
                    );

    seg7_dig dig2 (
                    .cntl_4bit(tenz),
                    .disp_4bit(digit_2)
                );
    
    seg7_dig dig1 (
                    .cntl_4bit(onez),
                    .disp_4bit(digit_1)
                );

    my_bcd getDigs (
                        .tens(tenz),
                        .ones(onez),
                        .bin_in(temp)
                );
endmodule


////~~~~  main circuit
module conUnit (
                        output wire [4:0] countt,
                        input wire [4:0] n_in,
                        input wire start,
                        input wire restart,
                        input wire up_count,
                        input wire clock
                );
    
    wire n_is_0;
    wire n_is_25;
    reg [4:0] count;
    assign countt = count;
    assign n_is_0 = (count == 5'b0000_0);
    assign n_is_25 = (count == 5'b1100_1);

    reg [1:0] next_state;
    parameter s0 = 2'b00;
    parameter s1 = 2'b01;
    parameter s2 = 2'b10;
    parameter s3 = 2'b11;

    initial begin
        next_state = s0;
        count = 5'b0000_0;
    end

    always @ (posedge clock) begin
        case (next_state)
            s0 : 
                begin
                    if (restart == 1'b1) begin
                        next_state = s0;
                        count = 5'b0000_0;
                    end
                    else begin
                        next_state = (start == 1'b1) ? s1 : s0;
                    end
                end
            s1 :
                begin
                    if (restart == 1'b1) begin
                        next_state = s0;
                        count = 5'b0000_0;
                    end
                    else begin
                       count = n_in;
                        if (up_count == 1'b1) begin
                            next_state = (n_is_25 == 1'b1) ? s3 : s2;
                        end
                        else begin
                            next_state = (n_is_0 == 1'b1) ? s2 : s3;
                        end 
                    end
                end
            s2 : 
                begin
                    if (restart == 1'b1) begin
                        next_state = s0;
                        count = 5'b0000_0;
                    end
                    else begin
                        count = count + 1'b1;
                        next_state = (n_is_25 == 1'b1) ? s3 : s2; 
                    end
                end
            s3 : 
                begin
                    if (restart == 1'b1) begin
                        next_state = s0;
                        count = 5'b0000_0;
                    end
                    else begin 
                        count = count - 1'b1;
                        next_state = (n_is_0 == 1'b1) ? s2 : s3;
                    end
                end
        endcase 
    end
endmodule


////~~~~  slow the FPGA clock to 1 Hz
module clk_50MHz_to_1Hz ( 
                            output reg clk_1hz,
                            input wire clk_50mhz
                        );

    reg [24:0] count;    

    initial begin
        count <= 1'b0;
        clk_1hz <= 1'b0;
    end

    always @ (posedge clk_50mhz) begin
        if(count == 25'b1011111010111100000111111) begin
            count <= 0;
            clk_1hz <= ~clk_1hz;
        end
        else begin
            count <= count + 1;
        end
    end
endmodule


////~~~~  output to 7-segment display
module seg7_dig(
                    output reg [6:0] disp_4bit,
                    input wire [3:0] cntl_4bit
                );

    parameter ON = 1'b0;
    parameter OFF = 1'b1;

    always @ (*) begin
        disp_4bit = {7{OFF}};
        case (cntl_4bit)
            4'b0000 : disp_4bit[5:0] = {6{ON}};
            4'b0001 : disp_4bit[2:1] = {2{ON}};
            4'b0010 :
                begin
                    disp_4bit[1:0] = {2{ON}};
                    disp_4bit[6] = ON;
                    disp_4bit[4:3] = {2{ON}};
                end
            4'b0011 :
                begin
                    disp_4bit[3:0] = {4{ON}};
                    disp_4bit[6] = ON;
                end
            4'b0100 :
                begin
                    disp_4bit[2:1] = {2{ON}};
                    disp_4bit[6:5] = {2{ON}};
                end 
            4'b0101 :
                begin
                    disp_4bit[0] = ON;
                    disp_4bit[3:2] = {2{ON}};
                    disp_4bit[6:5] = {2{ON}};
                end
            4'b0110 :
                begin
                    disp_4bit[0] = ON;
                    disp_4bit[6:2] = {5{ON}};
                end
            4'b0111 : disp_4bit[2:0] = {3{ON}};
            4'b1000 : disp_4bit[6:0] = {7{ON}};
            4'b1001 :
                begin
                    disp_4bit[6:0] = {7{ON}};
                    disp_4bit[4:3] = {2{OFF}};
                end
        endcase
    end
endmodule


////~~~~ get the 2 decimal digits of 5-bit binary
module my_bcd ( 
                    output reg [3:0] tens,
                    output reg [3:0] ones,
                    input wire [4:0] bin_in
            );

    integer idx;

    always @ (bin_in) begin
        tens = 4'b0000;
        ones = 4'b0000;
        for (idx = 4; idx >= 0; idx = idx - 1) begin
            if (tens >= 3'b101) tens = tens + 2'b11;
            if (ones >= 3'b101) ones = ones + 2'b11;
            tens = tens << 1;
            tens[0] = ones[3];
            ones = ones << 1;
            ones[0] = bin_in[idx];
        end
    end
endmodule


////////~~~~~~~~END>  total.v