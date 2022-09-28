;
; main.asm
;
; Created: 9/30/2019 9:49:20 PM
; Author : alira
;

.org 0x00
	//DECLARATION OF REGISTERS
	ldi r26,0b100 //2
	ldi r27, 0b00
	out ddrb, r26			//output port b 2
	out portb, r27	

on:
	out portb, r26	
	call DELAY		
	call Off
Off:
	out portb, r27
	call DELAYOFF
	rjmp on
DELAY:				
	ldi r23, 150		  //stick with 190 loops total 
D2: 
	ldi r24, 100
D3:
	ldi r25, 100
D0:		
	nop
	nop
	nop
	nop
	nop
	dec r24
	brne D0
	dec r25
	brne D0
	dec r23		
	brne D2
	out portb, r27		//turn off light
	ret

DELAYOFF:				
	ldi r23, 150		  //stick with 190 loops total 
D2O: 
	ldi r24, 100
D3O:
	ldi r25, 100
D0O:		
	nop
	nop
	nop
	nop
	nop
	dec r24
	brne D0O
	dec r25
	brne D0O
	dec r23		
	brne D2O
	out portb, r27		//turn off light
	ret