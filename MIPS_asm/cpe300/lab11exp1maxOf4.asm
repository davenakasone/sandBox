#David Nakasone

.data
	size: .word 4 # 4 intgers
	array: .word 99, 88, 77, 66 # change to use different integers
	spacer: .asciiz "\n......"
	resultA: .asciiz "\n Variable [a] is: "    
	resultB: .asciiz "\n Variable [b] is: " 
	resultC: .asciiz "\n Variable [c] is: " 
	resultD: .asciiz "\n Variable [d] is: " 
	result: .asciiz "\n The maximum value is: "
.text
	j main
main:
	# load integers a, b, c, and d from array, just for easy output
	la $t9, array # load adress of varA to $t9
	lw $t0, 0($t9) # make a copy for output
	lw $a0, 0($t9) # to pass
	
	la $t9, array # load adress of varB to $t9
	lw $t1, 4($t9) # make a copy for output
	lw $a1, 4($t9) # to pass
	
	la $t9, array # load adress of varC to $t9
	lw $t2, 8($t9) # make a copy for output
	lw $a2, 8($t9) # to pass
	
	la $t9, array # load adress of varB to $t9
	lw $t3, 12($t9) # make a copy for output
	lw $a3, 12($t9) # to pass
	
	jal findMax    #  get the max of these 4 integers
	add $t4, $0, $v1  # take value returned and put into $t4
	j done
	
		findMax:
			la $t9, size   # get array length to set LCV
			lw $s0, 0($t9) # takes integer from addres, $s0 is now LCV
			la $t9, array    # $t9 holds address of first element
			j loop
		
		loop:
			lw $s1, 0($t9) # $s1 holds value $t9 points to
			bge $s1, $v1, newMax
			
			addi $t9, $t9, 4 # increment $t9 by 4 to get to next address
			addi $s0, $s0, -1 # decrement counter by 1
			beqz $s0, returnMax  # 4, 3, 2, 1, all elements scanned
			j loop
		
		newMax:
			add $v1, $0, $s1 # set new max
			addi $t9, $t9, 4 # increment $t9 by 4 to get to next address
			addi $s0, $s0, -1 # decrement counter by 1
			beqz $s0, returnMax  # 4, 3, 2, 1, all elements scanned
			j loop
			
		returnMax: jr $ra # go back to main, max was found

done:
	li $v0, 4      # code for print string
	la $a0, spacer    
	syscall        # print it
	
	li $v0, 4      # code for print string
	la $a0, resultA    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t0  # move value to be printed into $a0
	syscall        # print sum of integers
	
	li $v0, 4      # code for print string
	la $a0, resultB    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t1  # move value to be printed into $a0
	syscall        # print sum of integers
	
	li $v0, 4      # code for print string
	la $a0, resultC    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t2  # move value to be printed into $a0
	syscall        # print sum of integers
	
	li $v0, 4      # code for print string
	la $a0, resultD    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t3  # move value to be printed into $a0
	syscall        # print sum of integers
	
	li $v0, 4      # code for print string
	la $a0, result    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t4  # move value to be printed into $a0
	syscall        # print sum of integers
	
	j exit         # program complete, end it
	
exit: j exit