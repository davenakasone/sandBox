.data
	varA: .word 888 # set value of a
	varB: .word 77  # set value of b
	absAB:  # where to store absolute value in memeory
	newLine: .asciiz "\n ....."
	result1: .asciiz "\n Variable [a] is: "
	result2: .asciiz "\n Variable [b] is: "
	result3: .asciiz "\n |a - b| is: "
.text
	j main

main: 
	la $t9, varA # load adress of varA to $t0
	lw $t7, 0($t9) # var [a] is loaded into $a0
	la $t9, varB # load adress of varA to $t0
	lw $t8, 0($t9) # var [b] is loaded into $a1
	sub $t5, $t7, $t8   # 0 if equal, positive if greater, negative if less
	
	beqz $t5, aEQUALb # a = b
	bgez $t5, aGREATb # a >= b, equal already caught
	blez $t5, aLESSb # a <= b, equal already caught
	

aEQUALb:

	add $t4, $0, $0   # abs = 0
	la $t9, absAB     # load address into $t9
	SW $t4, 0($t9)    # store value of $t0 into address @ $t1
	j done

aGREATb:
	
	add $t4, $t5, $0   # abs = a-b
	la $t9, absAB     # load address into $t9
	SW $t4, 0($t9)    # store value of $t4 into address @ $t9
	j done

aLESSb:

	sub $t4, $t8, $t7   # abs = b-a
	la $t9, absAB     # load address into $t9
	SW $t4, 0($t9)    # store value of $t4 into address @ $t9
	j done

done:
	li $v0, 4      # code for print string
	la $a0, newLine    
	syscall        # print it
	      
	
	li $v0, 4      # code for print string
	la $a0, result1    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t7  # move value to be printed into $a0
	syscall        # print sum of integers
	
	li $v0, 4      # code for print string
	la $a0, result2    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t8  # move value to be printed into $a0
	syscall        # print sum of integers
	
	li $v0, 4      # code for print string
	la $a0, result3    
	syscall        # print it
	
	li $v0, 1     # system call code for print integer
	move $a0, $t4  # move value to be printed into $a0
	syscall        # print sum of integers
	
	j exit         # program complete, end it
	
exit: j exit
	
