# a difference of sums, function call

# int main() { int y;  y = diff_of_sums(2,3,4,5); // 4 args     return EXIT_SUCCESS;
# int diff_of_sums(inft f, int g, int h, int i) { int result; result = (f+g)-(h+i); return result;}


addi $s7, $0, 0            # $s9 = 0
addi $a0, $0, 2             # arg[0] = 2
addi $a1, $0, 3             # arg[1] = 3
addi $a2, $0, 4             # arg[2] = 4
addi $a3, $0, 5             # arg[3] = 5
jalr diff_of_sums, $ra      # a function call

diff_of_sums:
	addi $sp, $sp, -12            # make space on stack to store 3 regs, frame of size 12
	
	sw $s0, 8($sp)                # saves $s0 into address $sp + 8
	sw $t0, 4($sp)                # saves $t0 into address $sp + 4
	sw $t1, 0($sp)                # saves $t1 into address $sp + 0
	
	add $t0, $a0, $a1             # $t0 = f + g
	add $t1, $a2, $a3             # $t1 = h + i
	sub $s0, $t0, $t1             # $s0 = result = (f+g) - (h+i)
	
	add $v0, $s0, $0              # puts return value into $v0
	
	lw $t1, 0($sp)                # restore $t1 from stack
	lw $t0, 4($sp)                # restore $t0 from stack
	lw $s0, 8($sp)                # restore $s0 from stack
	
	addi $sp, $sp 12              # deallocate stack space
	jr $ra                        # return to caller

	
	