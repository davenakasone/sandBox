# m5, a for loop    add 0 to 9

addi $s1, $0, 0          # $s0 = 0    "sum"
add $s0, $0, $0          # $s0 = 0    "i"
addi $t0, $0, 10         # $t0 = 10   "loop control"

for_loop:
	beq $s0, $t0, done           # if($s0 == $t0) goto done
	add $s1, $s1, $s0            # $s1 = $s0 + $s0
	addi $s0, $s0, 1             # $s0++
	j for_loop                   # goto for_loop

 done:
 	#j done                       # return EXIT_SUCCESS
 	 