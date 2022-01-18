#program to load arr, add 10 to each element and store back to original address
.text 
.global main 
main: 
 

 movia r9, arr # load address of arr into r9
 addi r3,r0,7
 addi r4,r0,0 #loop counter
 loop:
 ldw r10, 0(r9) # load value that is stored at arr[i] into r10
 addi r10, r10, 10 # increment value by 4
 stw r10, 0(r9) # store the value back to arr
 addi r9,r9,4
 addi r4,r4,1 #increase loop counter
 bne r4,r3,loop

done:
jmpi done
.data #begin the data segment
arr: .word 2, 3, 4, 5, 45, 3, 21
