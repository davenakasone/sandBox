top: 
	addi $t0, $zero, 4    # $8 = 0 + 4 = 4
	addi $sp, $sp -8      # $29, 7FFF_EFFC -> 7FFF_EFF4
	sw $t0, 4($sp)        # M[7FFF_EFF8] = $8 = 4
	addi $t1, $t0, 4      # $9 = $8 + 4 = 8
	lw $t0, 4($sp)        # $8 = M[7FFF_EFF8] = 4
	lw $t1, 0($sp)        # $9 = M[7FFF_EFF4] = 0 ?
	beq $t1, $t0, skip    # not taken, $9 != $8, 4 != 0
	sll $t0, $t0, 2       # $8 = 00100 <-- 2 = 10000 = 16
	addi $t1, $t0, -4     # $9 = $8 - 4 = 16 - 4 = 12
	sw $zero, 28($t0)     # M[28($8)] = 0

skip:
	addi $sp, $sp, 8      # $29, 7FFF_EFF4 -> 7FFF_EFFC (restored to original value)
	sltu $t3, $t1, $t0    # $11 = ($9 < $8) ? 1 : 0,     $11 = 0  because 16 !< 12
	beq $t3, $zero, done  # taken, $11 == 0
	addi $t0, $t0, 4      # $8 = $8 + 4 = 16 + 4 = 20  ,  but branched over
	j top                 # PC = 0040_000, but branched over
	sw $t2, 28($t0)       # M[28($t0)] = $10 = 0 ?  , but brached over
	addi $t2, $t2, 4      # $10 = $10 + 4 = 0 + 4 = 4 , but branched over

done:
	j done                # kept to get address
	
	
	
	
