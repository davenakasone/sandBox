# an array of 5 elements

# use $s0 as the base address

lui $s0, 0x1234          #  $s0 reads:  0x1234_0000   
ori $s0, $s0, 0x8000     # $s0 reads:   0x1234_8000        base address stored

lw $t1, 0($s0)           # $t1 = array[0]     $t1 = *($s0)
sll $t1, $t1, 1          # $t1 = $t1 * 2
sw $t1, 0($s0)           # array[0] = $t1

#lw $t1, 4($s0)  

# wtf?

