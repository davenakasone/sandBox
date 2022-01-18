/*
    some array examples
*/

`timescale 1ns/1ns
`define STEP 1000
`define BITZ 8


module arrEx();
    integer ct;
    //parameter BITZ 8;
    //parameter rowz 3;
    //parameter colz 5;
    reg [`BITZ-1:0] rA;  // 1xN vector

    initial begin
    rA = `BITZ'b1111_1111;
    $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
    #`STEP
    $finish;
    end

endmodule

////////~~~~~~~~END>  arrys.v
