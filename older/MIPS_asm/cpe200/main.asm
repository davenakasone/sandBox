;
; AssemblerApplication1.asm
; Assignmetn 1A - inplementing 16 bit * 8bit multiplication without mul
; Created: 9/16/2019 4:38:37 PM
; Author : alira
;

; Replace with your application code

; **********NOTEWORTHY VARIABLES********************
; r25:r24 holds 16-bit multiplicand
; r23:r22 holds 16bit multiplier
; r20:r19:r18:r17 hold result

start:
	;Zero Register;
	clr r0
	inc r1
	
	;**Multiplicand**;
    ldi r24,LOW(522)    
    ldi r25,HIGH(522) 
	 
	;**Multiplier**;
	ldi r23, HIGH(520)
	ldi r22, LOW(520)

	;**Result**;
	clr r20
	clr r19
	clr r18
	clr r17
	inc r23
	
	
	;add low, then add c to high, then addc with 0 to the next high, then add c the highest
top: 
	add r17, r24
	adc r18, r25
	adc r19, r0
	adc r20, r0
	cp r22, r0
	breq moveReg
	dec r22 
	brne top
	
	


moveReg:
	cp r23, r0
	breq STOP
	dec r23
	ldi r22, 255
	brne top

STOP:
	rjmp STOP

	
