
main:
	addi $4, $0, 2        # $a0 = 0 + 2 = 2
	addi $5, $0, 3        # $a1 = 0 + 3 = 3
	jal  sub_routine      # $ra = pc + 4 + j sub_routine
	j done                # finish the program

sub_routine:
	add $8, $4, $5   # $t0 = $a0 + $a1 = 2 + 3 = 5
	addi $9, $0, 1   # shifting by 1 is multiplying by 2, prepare the "1"
	sllv $2, $8, $9  # $v0 = $8 << 1'b1 = 2 * (a + b) = 2 * (2 + 3) = 10 == 0xA
	jr $31           # return by $ra 
	
done:
	sw $2, 80($0)    # store resut, M[0x50] = 0xA
	
	
	
	
	
	
	
	
	
