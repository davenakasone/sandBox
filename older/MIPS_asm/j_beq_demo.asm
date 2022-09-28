main :
	addi $t0, $zero, 3
	addi $t1, $zero, 6
	beq $t0, $t1, b_target

b_target :
	sub $t1, $t1, $t0
	beq $t1, $t0, done

j_target :
	j b_target
	

done :
	j done 