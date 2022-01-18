/*
    IEEE 754 number addition for rounding
        for single precision (32 total bits)

        sign bit gets 1, {0 == positive, 1==negative} ...signed mag, not 2 comp
        exponent is 8 bits, must align smaller exp with larger by shifting right
        floating is 23 bits  

    the process is:
        shift lower exp to higher, changing the hidden big and GRS 
        add the floats once aligned
        shift the resulting exp if there is 2 bins to hidden
*/

module tb();
    reg sign_A;
    reg [7:0] exp_A;
    reg hid_A;            // the hidden bit   h.fffffff
    reg [22:0] flt_A;
    reg [2:0] grs_A;
    real num_A;           // A's float representation

    reg sign_B;
    reg [7:0] exp_B;
    reg hid_B;            // the hidden bit   h.fffffff
    reg [22:0] flt_B;
    reg [2:0] grs_B;
    real num_B;           // B's float representation

    real check1;
    real check2;

    initial begin
        sign_A = 1'b1;
        exp_A = 8'b1000_0000;
        hid_A = 1'b1;
        flt_A = 23'b110_0000_0000_0000_0001_1111;
        grs_A = 3'b000;
        getReal(sign_A, exp_A, hid_A, flt_A, grs_A, num_A);
        $write("\n%f\n", num_A);
        
        sign_B = 1'b1;
        exp_B = 8'b1000_0010;
        hid_B = 1'b1;
        flt_B = 23'b111_0000_0000_0000_0001_1001;
        grs_B = 3'b000;
        
        
/*
        $write("\n\tgiven:\n");
        $write("\n sign    exp                float              | g  r  s\n");
        $write(" -------------------------------------------------------\n");
        $write("  %1b   %4b_%4b  %3b_%4b_%4b_%4b_%4b_%4b  | %1b  %1b  %1b",
            signBit, expBits[7:4], expBits[3:0], fBits[22:20], 
            fBits[19:16], fBits[15:12], fBits[11:8], fBits[7:4], fBits[3:0],
            grs[2], grs[1], grs[0]); 
        
        
        

        dispNum(sign_A, exp_A, float_A, grs_A);
        $write("    number A\n");
        dispNum(sign_B, exp_B, float_B, grs_B);
        $write("    number B\n");
        
        $write("\n\tSince number A has smaller exponent, shift right x2 to match number B\n");
        dispHead();
        dispNum(sign_A, exp_A, float_A, grs_A);
        $write("    number A before shift\n");

        catch_A = float_A[0]; // to grs
        float_A = float_A >> 1; 
        exp_A = exp_A + 1'b1; // reflects a shift
        grs_A[2] = catch_A;
        dispNum(sign_A, exp_A, float_A, grs_A);
        $write("    number A after first shift\n");

        catch_A = float_A[0]; // to grs
        float_A = float_A >> 1; 
        exp_A = exp_A + 1'b1; // reflects a shift
        grs_A[1] = grs_A[2];
        grs_A[2] = catch_A;
        dispNum(sign_A, exp_A, float_A, grs_A);
        $write("    number A after second shift\n");
*/

        $write("\n\n\t\t ~ ~ ~ TEST COMPLETE ~ ~ ~\n\n");
        $finish;
    end

    task automatic getReal;
        input reg sign;
        input reg [7:0] exp;
        input reg hid;
        input reg [22:0] flt;
        input reg [2:0] grs;
        output real num;

        real expMap;
        real signMap;
        real floatMap;
        real temp_exp;
        integer idx;

        begin
            expMap = 0;
            signMap = 0;
            floatMap = 0;

            signMap = (sign == 1'b0) ? 1 : -1; // 0 pos, 1 neg

            expMap = exp - 127; // 0 to 127 is neg exp, 128 to 254 is pos

            for (idx = 0; idx < 23; idx = idx + 1) begin
                temp_exp = 0; // reset
                if (flt[idx] == 1'b1) begin
                    case(idx)
                        0  : temp_exp = 2**23;
                        1  : temp_exp = 2**22;
                        2  : temp_exp = 2**21;
                        3  : temp_exp = 2**20;
                        4  : temp_exp = 2**19;
                        5  : temp_exp = 2**18;
                        6  : temp_exp = 2**17;
                        7  : temp_exp = 2**16;
                        8  : temp_exp = 2**15;
                        9  : temp_exp = 2**14;
                        10 : temp_exp = 2**13;
                        11 : temp_exp = 2**12;
                        12 : temp_exp = 2**11;
                        13 : temp_exp = 2**10;
                        14 : temp_exp = 2**9;
                        15 : temp_exp = 2**8;
                        16 : temp_exp = 2**7;
                        17 : temp_exp = 2**6;
                        18 : temp_exp = 2**5;
                        19 : temp_exp = 2**4;
                        20 : temp_exp = 2**3;
                        21 : temp_exp = 2**2;
                        21 : temp_exp = 2**1;
                    endcase
                    floatMap = floatMap + (1 / temp_exp);
                    $write("\n%0.11f\n", floatMap);
                end
            end
            
            if (hid == 1'b1) begin
                floatMap = 1 + floatMap;
            end

            num = signMap * (2**expMap) * floatMap;
            $write("\n%0.11f\n", num);
        end
    endtask
    
endmodule


////////~~~~~~~~END>  float_add.v
