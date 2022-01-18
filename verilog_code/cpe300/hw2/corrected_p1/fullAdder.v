/*
    corrected files:
        - test bench
        - modified adder (quick version)
*/

`timescale 1ns/1ns
`define STEP 100
`define WIDTH 4

module TestAdder(); //no ports

    parameter  N = 11; //11 tests are applied
    parameter BITZ = 4; 

    reg [`WIDTH-1:0] addend;
    reg [`WIDTH-1:0] augend;
    reg cin;
    wire [`WIDTH-1:0] sum;
    wire cout; 

    reg  [`WIDTH-1:0] addend_array [N-1:0];
    reg [N-1:0] cin_array;
    reg [`WIDTH-1:0] augend_array [N-1:0];
    reg [`WIDTH-1:0] sum_array [N-1:0];
    reg [N-1:0] cout_array;
    
    reg [`WIDTH:0] verify;
    integer idx;
    integer wrong;

    add4quick DUT(
                    .inp_a(addend),
                    .inp_b(augend),
                    .inp_carry(cin),
                    .sum(sum),
                    .outp_carry(cout)
                );

    initial begin
        //initialization of addend_array  ... index starts at 0
        addend_array [0] = 4'b0111;   // 7
        addend_array [1] = 4'b1101;   // 13
        addend_array [2] = 4'b0101;   // 5
        addend_array [3] = 4'b1101;   // 13
        addend_array [4] = 4'b0111;   // 7
        addend_array [5] = 4'b1000;   // 8
        addend_array [6] = 4'b0111;   // 7
        addend_array [7] =4'b1000;    // 8
        addend_array [8] =4'b0000;    // 0
        addend_array [9] =4'b1111;    // 15
        addend_array [10] = 4'b0000;  // 0
        //initialization of cin_array  ... index starts at 0
        cin_array[0]=1'b0;
        cin_array[1]=1'b0;
        cin_array[2] =1'b0;
        cin_array[3]=1'b0;
        cin_array[4] =1'b1;
        cin_array[5]=1'b0;
        cin_array[6]=1'b0;
        cin_array[7]=1'b0;
        cin_array[8]=1'b1;
        cin_array[9]=1'b1;
        cin_array[10]=1'b0;
        //initialization of augend_array  ... index starts at 0
        augend_array[0] = 4'b0101;   // 5
        augend_array[1] = 4'b0101;   // 5
        augend_array[2] = 4'b1101;   // 13
        augend_array[3] = 4'b1101;   // 13
        augend_array[4] = 4'b0111;   // 7
        augend_array[5] = 4'b0111;   // 7
        augend_array[6] = 4'b1000;   // 8
        augend_array[7] = 4'b1000;   // 8
        augend_array[8] = 4'b1101;   // 13
        augend_array[9] = 4'b1111;   // 15
        augend_array[10] = 4'b0000;  // 0
        //initialization of sum_array (expected sum outputs)  ... index starts at 0
        sum_array[0] = 4'b1100;   // 7 + 5 = 12
        sum_array[1] = 4'b0010;   // 5 + 13 = 18  OVERFLOW
        sum_array[2] = 4'b0010;   // 5 + 13 = 18  OVERFLOW
        sum_array[3] = 4'b1010;   // 13 + 13 = 26  OVERFLOW
        sum_array[4] = 4'b1111;   // 7 + 7 = 14
        sum_array[5] = 4'b1111;   // 8 + 7 = 15
        sum_array[6] = 4'b1111;   // 7 + 8 = 15
        sum_array[7] = 4'b0000;   // 8 + 8 = 16   OVERFLOW
        sum_array[8] = 4'b1110;   // 0 + 13 = 13
        sum_array[9] = 4'b1111;   // 15 + 15 = 30  OVERFLOW
        sum_array[10] = 4'b0000;  // 0 + 0 = 0
        //initialization of cout_array (expected carry output)  ... index starts at 0
        cout_array[0] = 1'b0;
        cout_array[1] = 1'b1;
        cout_array[2] = 1'b1;
        cout_array[3] = 1'b1;
        cout_array[4] = 1'b0;
        cout_array[5] = 1'b0;
        cout_array[6] = 1'b0;//
        cout_array[7] = 1'b1;
        cout_array[8] = 1'b0;
        cout_array[9] = 1'b1;
        cout_array[10] = 1'b0;
        
        wrong = 0;
        $display("\n");
        for(idx = 0 ; idx < N ; idx = idx + 1) begin
            augend = augend_array[idx];
            addend = addend_array[idx];
            cin = cin_array[idx];

            if (cin == 0) begin
                verify = augend + addend;
                $write("Test %2d >>>  cin =  %d  ,  %2d + %2d = %2d\n", 
                    idx, cin, addend_array[idx], augend_array[idx], verify);
                $write("        %b\n", addend);
                $write("     +  %b\n", augend);
                #`STEP
                $write("        %b  ,  cout:  %d  ->  %b    ", sum, cout, verify);
            end
            else begin
                verify = augend + addend + cin;
                $write("Test %2d >>>  cin =  %d  ,  %2d + %2d + 1 = %2d\n", 
                    idx, cin, addend_array[idx], augend_array[idx], verify);
                $write("        %b\n", addend);
                $write("     +  %b\n", augend);
                #`STEP
                $write("        %b  ,  cout:  %d  ->  %b    ", sum, cout, verify);
            end
            
            if(!(sum == sum_array[idx] & cout == cout_array[idx])) begin
                $write ("ERROR: Wrong Answer\n\n");
                wrong = wrong + 1;
            end
            else begin
                $write("Correct!!\n\n");
            end
        end

        $display("\nTEST COMPLETE  ,  wrong answers:  %d\n\n", wrong);
        #`STEP    // wait before releasing control
        $finish;  // $stop; is not good
    end

endmodule


////~~~~


module add4quick(
                    input wire [`WIDTH-1:0] inp_a,
                    input wire [`WIDTH-1:0] inp_b,
                    input wire inp_carry,
                    output wire [`WIDTH-1:0] sum,
                    output wire outp_carry
                );
    assign {outp_carry, sum} = inp_a + inp_b + inp_carry;
endmodule

////////~~~~~~~~END>  fullAdder.v
