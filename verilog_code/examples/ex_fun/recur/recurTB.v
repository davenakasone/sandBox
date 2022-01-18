/*
    a function that calls itself....use "automatic"
*/

module auto_fun();

    integer reps;
    integer idx;

    initial begin
        reps = 6;    // change here
        $display("\ncomputing the factorial with recursion:\n");
        for (idx = 0; idx < reps; idx = idx + 1) begin
            $write("Factorial of %d =  %d\n",
                idx, factorial(idx));
        end
        $display("\n");
        $finish;
    end

    function automatic [7:0] factorial;
        input [7:0] to_fact;  // input 1 of 1
        begin
            case(to_fact)
                1'b0 : factorial = 1;
                1'b1 : factorial = 1;
                default : factorial = to_fact * factorial(to_fact - 1);
            endcase
        end
    endfunction
    
endmodule



////////~~~~~~~~END>  recurTB.v

/*

    function automatic [7:0] factorial;
        input [7:0] to_fact;  // input 1 of 1
        begin
            if (to_fact == 1'b0 or to_fact == 1'b1) 
                factorial = 1;
            else
                factorial = to_fact * factorial(to_fact - 1);
        end
    endfunction






    integer toFact = 4;    // change here
    integer result;

    initial begin
        result = fact(toFact);
        $display("\nfactorial of %d =  %d\n", result);
    end

    function automatic integer fact(integer i);
        integer result = i;

        //this gets called inside the body with a different argument
        if (i) begin
            result = i * fact(i-1);
            $display("%d)  %d", i, result);
        else
            result = 1;
        end
        return result;
    endfunction
*/