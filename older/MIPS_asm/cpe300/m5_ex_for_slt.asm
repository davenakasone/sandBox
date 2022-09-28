#m5  powers of 2 from 1 to 100

# for(i = 1; i < 101; i = i*2) sum = sum + i          2^0 + 2^1 + 2^2 + ... + 2^6  = 

addi $s1, $0, 0            # $s1 = 0
addi $s0, $0, 1            # $s0 = 1
addi $t0, $0, 101          # $t0 = 101

loop:
	slt $t1, $s0, $t0            # $t1 = ($s0 < $t0) ? true : false       a slick loop control method
	beq $t1, $0, done            # if ($t1 == 0) goto done
	add $s1, $s1, $s0            # $s1 = $s1 + $s0
	sll $s0, $s0, 1              # $s0 = $s0 << 1
	j loop                       # goto loop

done:
	# return EXIT_SUCCESS