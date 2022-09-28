main:
	addi, $4, $0, 0   # ll = 0
	addi, $5, $0, 7   # ul = 7
	addi, $6, $0, 0   # counter = 0

incr:
	addi $6, $6, 1    # counter++
	sw $6, 80($0)     # M[80] <-- $6
	beq $6, $5, decr  # if (counter == 7) goto decr;
	j incr            # repeat loop
	
decr:
	addi $6, $6, -1   # counter--
	sw $6, 80($0)     # M[80] <-- $6
	beq $6, $4, incr  # if (counter == 0) goto incr;
	j decr            # repeat loop

