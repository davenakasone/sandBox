/*
    test bench
        top mod: 4-bit adder
        w/ 1-bit adder (in_1, in_2, in_c, out_c, sum)
*/

module TestAdder; //no ports
    parameter  N = 11; //11 tests are applied 
    reg [3:0] addend;
    reg [3:0] augend;
    reg        cin;
    wire [3:0] sum;
    wire       cout; 
    reg [3:0] addend_array [1:N];
    reg [1:N] cin_array;
    reg [3:0] augend_array [1:N];
    reg [3:0] sum_array [1:N];
    reg [1:N] cout_array;

    initial

    begin
    //initialization of addend_array
    addend_array [1] = 4'b0111;
    addend_array [2] = 4'b1101;
    addend_array [3] = 4'b0101;
    addend_array [4] = 4'b1101;
    addend_array [5] = 4'b0111;
    addend_array [6] = 4'b1000;
    addend_array [7] = 4'b0111;
    addend_array [8] =4'b1000;
    addend_array [9] =4'b0000;
    addend_array [10] =4'b1111;
    addend_array [11] = 4'b0000;
    //initialization of cin_array
    cin_array[1]=1'b0;
    cin_array[2]=1'b0;
    cin_array[3] =1'b0;
    cin_array[4]=1'b0;
    cin_array[5] =1'b1;
    cin_array[6]=1'b0;
    cin_array[7]=1'b0;
    cin_array[8]=1'b0;
    cin_array[9]=1'b1;
    cin_array[10]=1'b1;
    cin_array[11]=1'b0;
    //initialization of augend_array
    augend_array[1] = 4'b0101;
    augend_array[2] = 4'b0101;
    augend_array[3] = 4'b1101;
    augend_array[4] = 4'b1101;
    augend_array[5] = 4'b0111;
    augend_array[6] = 4'b0111;
    augend_array[7] = 4'b1000;
    augend_array[8] = 4'b1000;
    augend_array[9] = 4'b1101;
    augend_array[10] = 4'b1111;
    augend_array[11] = 4'b0000;
    //initialization of sum_array (expected sum outputs)
    sum_array[1] = 4'b1100;
    sum_array[2] = 4'b0010;
    sum_array[3] = 4'b0010;
    sum_array[4] = 4'b1010;
    sum_array[5] = 4'b1111;
    sum_array[6] = 4'b1111;
    sum_array[7] = 4'b0111;
    sum_array[8] = 4'b0000;
    sum_array[9] = 4'b1110;
    sum_array[10] = 4'b1111;
    sum_array[11] = 4'b0000;
    //initialization of cout_array (expected carry output)
    cout_array[1] = 1'b0;
    cout_array[2] = 1'b1;
    cout_array[3] = 1'b1;
    cout_array[4] = 1'b1;
    cout_array[5] = 1'b0;
    cout_array[6] = 1'b0;
    cout_array[7] = 1'b1;
    cout_array[8] = 1'b1;
    cout_array[9] = 1'b0;
    cout_array[10] = 1'b1;
    cout_array[11] = 1'b0;
    end
    integer i;  
    always
    begin
    for(i = 1 ; i <= N ; i = i + 1)
    begin
        $display(i);
    //apply an addend test vector
    addend <= addend_array[i];
    //apply an augend test vector

    augend <= augend_array[i];
    //apply a carry in
    cin <= cin_array[i];
    #100;
    if(!(sum == sum_array[i] & cout == cout_array[i]))
        begin
        $write ("ERROR: ");
        $display ("Wrong Answer ");
        end
        else begin
        $display("Correct!!");
        end
    end
    $display("Test Finished");
    $stop;
    end
    //module under test instantiated
    Adder4 add1(addend,augend,cin,cout,sum); 
endmodule


////~~~~ Full Adder {4-bit}


module Adder4(A,B,Ci,Co,S);
    output [3:0] S;
    output Co;
    input  [3:0] A, B;
    input  Ci;
    wire   [3:1] C;  // C is an internal signal

    FullAdder FA0 (A[0],B[0],Ci,C[1],S[0]);
    FullAdder FA1 (A[1],B[1],C[1],C[2],S[1]);
    FullAdder FA2 (A[2],B[2],C[2],C[3],S[2]);
    FullAdder FA3 (A[3],B[3],C[3],Co,S[3]);
endmodule


////////~~~~~~~~ Full Adder {1-bit}


module FullAdder (X,Y,Cin,Cout,Sum);
    output Cout, Sum;
    input  X, Y, Cin;
    assign #10 Sum  = X ^ Y ^ Cin;
    assign #10 Cout = (X && Y) || (X && Cin) || (Y && Cin);
endmodule


////////~~~~~~~~END>  TestAdder.v
