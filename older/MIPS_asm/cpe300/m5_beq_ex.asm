# beq example, m5 lecture

addi $s0, $0, 4               # $s0 = 0 + 4 = 4
addi $s1, $0, 1               # $s1 = 0 + 1 = 1
sll $s1, $s1, 2               # $s1 = $s1 << 2 = 4 (001) --> (100)
beq $s0, $s1, target          # if ($s0 == $s1) goto target
addi $s1, $s1, 1              # $s1++
sub $s1, $s1, $s0             # $s1 = $s1 - $s0

target:
	add $s1, $s1, $s0     # $s1 = $s1 + $s0
	j done		      # goto done;

done:
	j done                # return EXIT_SUCCESS 