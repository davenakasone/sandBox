# cpe300, hw12

main: 
	addi $sp, $sp, -4     # $29 = 7FFF_EFFC -> 7FFF_EFF8
	sw $ra, 0($sp)        # M[7FFF_EFF8] = 0
	addi $a0, $zero, 2    # $4 = 2
	lui $s0, 0x1000       # $16 = 1000_0000
	sw $a0, 0($s0)        # M[1000_0000] = 2
	addi $a1, $zero, 3    # $5 = 3
	sw $a1, 4($s0)        # M[1000_0004] = 3
	jal sum               # call "sum", $ra = 0040_0020
	sw $v0, 8($s0)        # M[1000_0008] = 5
	lw $ra, 0($sp)        # $31 = M[7FFF_EFF8] = 0
	addi $sp, $sp 4       # $29 = 7FFF_EFF8 -> 7FFF_EFFC
	jr $ra                # return EXIT_SUCCESS;

sum:
	add $v0, $a0, $a1     # $2 = $4 + $5
	jr $ra                # return

