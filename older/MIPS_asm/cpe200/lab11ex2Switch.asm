.data
	case0: .asciiz "\n It is zero"      # what to print if case 0 comes
	case3: .asciiz "\n It is three"     # what to print if case 3 comes
	caseD: .asciiz "\n Invalid Entry"   # what to print if default case comes
	intA: .word 5    # change this as needed
	intB: .word 8    # change this as needed
	value: .word 10   # initialize to 0, but change as needed
	result: .word 0  # initizalize to 0, but change as needed
.text
	j main
main:
	la $t9, intA  # load the address of "intA" into $t9
	lw $s4, 0($t9) # $s4 represents "intA"
	la $t9, intB	# load the address of "intB" into $t9
	lw $s5, 0($t9) #  $s5 represents "intB"
	la $t9, value # load the address of "value"  into $t9
	lw $s6, 0($t9) # $s6 represents "value" now
	la $t9, result # load the address of "result" into $t9
	lw $s7, 0($t9) # $s7 represents "result"
	
	# set cases for switch
	addi $s1, $0, 1   # $s1 = 1 and represents case 1
	addi $s2, $0, 2   # $s2 = 2 and represents case 2
	addi $s3, $0, 3   # $s3 = 3 and represents case 3
	
	#enter SWITCH
	beqz $s6, switch0     # if value = 0, go to case 0
	beq $s6, $s1, switch1    # if value = 1, go to case 1
	beq $s6, $s2, switch2    # if value = 2, go to case 2
	beq $s6, $s3, switch3   # if value = 3, got to case 3
	j default               # vlaues is not 0, 1, 2, or 3, go to the default

switch0: 
	li $v0, 4      # code for print string
	la $a0, case0    
	syscall        # print it
	add $s7, $s4, $s5  # result = a + b
	j done      # break;
switch1:
	# hand over values to argument variables
	add $a0, $s4, $0  # $a0 takes $s4 to represent "intA"
	add $a1, $s5, $0  # $a1 takes $s5 to represent "intB"
	add $a2, $s6, $0  # $a2 takes $s6 to represent "value"
	jal fun_do  # call function, arguments are set
	add $s7, $v1, $0    # set result to what was returned " result = fun_do(a, b, value)
	j done # break;

switch2:
	addi $s6, $s6, 1  # value = value + 1
	j switch3    # no break, continue down the switch structure
switch3:
	li $v0, 4      # code for print string
	la $a0, case3    
	syscall        # print it
	addi $s6, $s6, 100  # value = value + 100
	j done  # break;
default:
	li $v0, 4      # code for print string
	la $a0, caseD    
	syscall        # print it
	j done  # break;
	
	
	
	fun_do: 
		bgt $a0, $a1, aGREATb   # if ( a > b)
		blt $a0, $a1, aLESSb    # else if (a < b)
		j else			# end of the line
		
		aGREATb:
		add $t8, $a0, $a1  # a + b
		add $t8, $t8, $t8  # (a+b) + (a+b) = 2* (a+b)   to $t8
		add $v1, $0, $0    # clear incase it is not 0
		add $v1, $t8, $0  # set $v1 = 2* (a+b)
		jr $ra   # return to main with value in $v1
		
		aLESSb:
		sub $t7, $a1, $a0   # $t7 is now  ( b - a )
		add $t7, $t7, $t7   # using (b - a) + ( b-a) = 2* (b-a)
		add $v1, $0, $0     # clear v1
		add $v1, $t7, $0    # v1 has result and is ready to return to caller
		jr $ra     # returns to main with value in $v1
		
		else:
		add $v1, $0, $0   # clear v1
		addi $v1, $a0, 1   # a = a + 1
		jr $ra    # returns to main with v1
		
			

done: j done  # hold


	