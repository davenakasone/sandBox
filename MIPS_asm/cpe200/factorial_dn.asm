# 7 * 6 * 5 * 4 * 3 * 2 * 1 = 5040 = 0000 13B0
# mul $t0, $t1, $t2 will multiply $t1 and $t2 and puts it into $t0
# don't let result get over 32 bits...string together (((7 * 6) *5) * ...
# use add, sub, subi, and, or, mul, addi, j, beq, beqz....put in register $v0

fact: addi $a0, $0, 8    # N = n + 1   (use 8 to get factorial of 7
      addi $v0, $0, 1    # initialize factorial to 1.... 0! = 1
      addi $s0, $0, 1    # initialize counter to 1
      
  

loop:
	mult  $v0, $s0       # factiorial * counter
	mflo  $v0            # store product in $v0 as the factorial
	
	addi $s0, $s0, 1      # increment counter by 1
	
	beq $s0, $a0, done   # if i = n, factorial complete
	
	j loop               #continue

done: j done # infinite loop
