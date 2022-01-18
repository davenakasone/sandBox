;
; DA_1A.asm
;
; Created: 2/14/2020 4:10:35 PM
; Author : mcarn
;


.equ MULTIPLICAND = 0x8FC	;Multiplicand is set to the value 8FC in hex (2300 in decimal)
.equ MULTIPLIER = 0x07		;Multiplier is set to 07 in order to speed up the simulation time

; .DEF statements used to help make the code easier to follow with what is going on instead of having to keep track of each register

.DEF MULTIPLICAND_BYTE_0 = R16
.DEF MULTIPLICAND_BYTE_1 = R17
.DEF MULTIPLICAND_BYTE_2 = R18
.DEF MULTIPLICAND_BYTE_3 = R19
.DEF MULTIPLIER_BYTE_0 = R20
.DEF MULTIPLIER_BYTE_1 = R21
.DEF MULTIPLIER_BYTE_2 = R22
.DEF MULTIPLIER_BYTE_3 = R23
.DEF PRODUCT_BYTE_0 = R24
.DEF PRODUCT_BYTE_1 = R25
.DEF PRODUCT_BYTE_2 = R26
.DEF PRODUCT_BYTE_3 = R27
.DEF PRODUCT_BYTE_4 = R28
.DEF PRODUCT_BYTE_5 = R29
.DEF PRODUCT_BYTE_6 = R30
.DEF PRODUCT_BYTE_7 = R31

;The registers that were defined above are now being loaded with their respective .equ values

	LDI MULTIPLICAND_BYTE_0,BYTE1(MULTIPLICAND)
	LDI MULTIPLICAND_BYTE_1,BYTE2(MULTIPLICAND)
	LDI MULTIPLICAND_BYTE_2,BYTE3(MULTIPLICAND)
	LDI MULTIPLICAND_BYTE_3,BYTE4(MULTIPLICAND)

	LDI MULTIPLIER_BYTE_0,BYTE1(MULTIPLIER)
	LDI MULTIPLIER_BYTE_1,BYTE2(MULTIPLIER)
	LDI MULTIPLIER_BYTE_2,BYTE3(MULTIPLIER)
	LDI MULTIPLIER_BYTE_3,BYTE4(MULTIPLIER)

;iitializing the Product registers with zeroes by clearing any data that may be stored in each register

	CLR PRODUCT_BYTE_0
	CLR PRODUCT_BYTE_1
	CLR PRODUCT_BYTE_2
	CLR PRODUCT_BYTE_3
	CLR PRODUCT_BYTE_4
	CLR PRODUCT_BYTE_5
	CLR PRODUCT_BYTE_6
	CLR PRODUCT_BYTE_7

;The code below handles the repeated addition of the multiplicand and repeated subtraction of the multiplier

BEGIN:
	cp MULTIPLIER_BYTE_0,R0							;Compares byte zero of the multiplier with zero, it is zero then jump to BORROW_FROM_BYTE_1 label
	breq BORROW_FROM_BYTE_1 
	BYTE_0_DNE_ZERO:
		dec MULTIPLIER_BYTE_0						;Decrement the first byte of the multiplier
		ADD PRODUCT_BYTE_0,MULTIPLICAND_BYTE_0		;Add registers and store the value inside PRODUCT_BYTE_0

		ADC PRODUCT_BYTE_1,MULTIPLICAND_BYTE_1		;Every ADC instruction adds the respective register with the carry from the previous instruction
		ADC PRODUCT_BYTE_2,MULTIPLICAND_BYTE_2
		ADC PRODUCT_BYTE_3,MULTIPLICAND_BYTE_3

		ADC PRODUCT_BYTE_4,R0						;Last four ADC instructions do not include a multiplicand since it is only 32 bits and will be added with zero
		ADC PRODUCT_BYTE_5,R0
		ADC PRODUCT_BYTE_6,R0
		ADC PRODUCT_BYTE_7,R0

		jmp BEGIN									;Go back to the beginning of this loop to start the process again

BORROW_FROM_BYTE_1:									;Compares byte one of the multiplier with zero, if it is zero then jump to BORROW_FROM_BYTE_2
	cp MULTIPLIER_BYTE_1,R0
	breq BORROW_FROM_BYTE_2
	BYTE_1_DNE_ZERO:
		dec MULTIPLIER_BYTE_1						;Decremnt byte one of the multiplier
		jmp BYTE_0_DNE_ZERO							;Jump to BYTE_0_DNE_0 since we just borrowed from byte 1

BORROW_FROM_BYTE_2:									;Utilizing the same reasoning from BORROW_FROM_BYTE_1 and implementing with byte 2 of multiplier
	cp MULTIPLIER_BYTE_2,R0
	breq BORROW_FROM_BYTE_3
	BYTE_2_DNE_0:
		dec MULTIPLIER_BYTE_2
		jmp BYTE_1_DNE_ZERO

BORROW_FROM_BYTE_3:										;Utilizing the same reasoning from BORROW_FROM_BYTE_1 and implementing with byte 3 of multiplier
	cp MULTIPLIER_BYTE_3,R0
	breq DONE										;If MULTIPLIER_BYTE_3 register is zero, then the addition is complete and jump to infinite done loop
	dec MULTIPLIER_BYTE_3
	jmp BYTE_2_DNE_0

DONE:jmp DONE										;Program has completed the reapeated addition!
