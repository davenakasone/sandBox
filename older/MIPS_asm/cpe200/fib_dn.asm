# David Nakasone
# 20200403
# use meaningful comments on each line
# debug each step

 fib: addi $a0, $0, 16       # n = 16..."16 into register $a0...the argument of fib(), test on different values
      addi $s0, $0, 0        # jump-start with initializing fib(0) ...boot-strap loop with these
      addi $s1, $0, 1        # jump-start with initializing fib(1)
     
     add $v0, $0, $s0      # fib(0) = 0
     addi $a0, $a0, -1      # decrement n by 1
      
     add $v0, $s0, $s1      # f(1) = 1 + 0 = 1
     addi $a0, $a0, -1      # decrement n by 1
     addi $s0, $s1, 0       # f(n-2) = f(n-1) , pass recurssive value, now f(1) = f(2) = 1 and further iteration is simple
         
 loop:                      
 	beqz $a0, done      # once n reaches 0, all iterations are complete, exit loop
     	add $v0, $s0, $s1   # f(n) = f(n-1) + f(n-2)
     	addi $s0, $s1, 0    # f(n-2) = f (n-1)
     	addi $s1, $v0, 0    # f(n-1) = f(n)
     	addi $a0, $a0, -1   # decrement n by 1
     	j loop              # continue
     	
 
 #after looping number of times specified by value in $a0, your code should leave resulting fib(n) in register $v0
 # and go to to "done"
 
 done: j done # infinite loop, also the point to read fib(16)
 # this ensures that the program terminates in a predictable manner
 # add, sub, subi, and, or, slt, addi, j, beq, beqz should help
