# array of strings and integers

# data takes some of that static memory
.data

# 3 contigious blocks of memory, 4-bytes each
int_array: .word 10, 11, 12

# each of these strings is null-terminated, each label is a "pointer"
one: .asciiz "one\n"
two: .asciiz "two\n"
three: .asciiz "three\n"

# make each value of this string array a label   ...now it is an array of strings
str_array: .word one, two, three

.text
# this is where you put the instructions after initializing memory
main:# you should have a label "main" , it is where execution starts

la $s0, int_array     # this is the address of the first element in the array loaded to $s0
lw $t0, 0($s0)        # load first element of array,   $t0 = *($s0)
lw $t1, 4($s0)        # load second element of array,  $t1 = *($s0+4)
lw $t2, 8($s0)        # load third element of array,   $t2 = *($s0+8)

li $v0, 4             # system call to print string
la $s1, str_array     # $s1 = &str_array   $s1 takes address of first element in string array
lw $a0, 0($s1)        # print first element
syscall
lw $a0, 4($s1)        # print second element
syscall
lw $a0, 8($s1)        # print third element
syscall

la $t0, str_array    # load the address of the first element
li $v0, 4            # prepare system to print string
li $t1, 0            # initialize array offset
li $t2 8             # last element
loop:
# an address mode label(register)

lw $a0, str_array($t1)       #  you are loading $t1, offset by str_array
syscall
addi $t1, $t1, 4             # increment to next element
ble $t1, $t2, loop

li $v0, 10
syscall # EXIT_SUCCESS

