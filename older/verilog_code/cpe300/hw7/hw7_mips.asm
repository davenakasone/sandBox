# $s0 = amount
# $s1 = fee
# assume code is loaded from address 0x0040_0000

.data
    initial_amount: .word 100    # the amount is initially set to this number

.text

    j main
    
main:
    la $t9, initial_amount     # $t9 = &(initial_amount); // address stored
    lw $s0, 0($t9)             # $s0 = *($t9);            // defrence address and store data 

case20:
    addi $t0, $0, 20            # $t0 = 20;
    bne $s0, $t0, case50        # if(amount != 20) goto case50;
    addi $s1, $0, 2             # if(amount == 20) fee = 2;
    j done                      # goto done;

case50:
    addi $t0, $0, 50            # $t0 = 50;
    bne $s0, $t0, case100       # if(amount != 50) goto case100;
    addi $s1, $0, 3             # if(amount == 50) fee = 3;
    j done                      # goto done;

case100:
    addi $t0, $0, 100           # $t0 = 100
    bne $s0, $t0, default       # if(amount != 100) goto default;
    addi $s1, $0, 5             # if(amount == 100) fee = 5;
    j done                      # goto done;

default:
    add $s1, $0, $0             # fee = 0

done:                           # return EXIT_SUCCESS;
