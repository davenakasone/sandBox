# find n    2^n = 128

addi $s0, $0, 1           # $s0 = 1 
add $s1, $0, $0           # $s0 = 0
addi $t0, $0, 128         # $t0 = 128

while_loop:
	beq $s0, $t0, done           # if($s0 == $t0) goto done
	sll $s0, $s0, 1              # $s0 = $s0 << 1
	addi $s1, $s1, 1             # $s1++
	j while_loop                 # goto while_loop

done:
	j done                       # return EXIT_SUCCESS

