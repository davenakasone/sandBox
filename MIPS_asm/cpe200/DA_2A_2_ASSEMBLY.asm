;
;main.asm
;
; Created: 9/28/2019 9:31:49 PM
; Author : Alira Coffman
;

.org 0x0				
	//DECLARATION OF REGISTERS
	ldi r26,0b100 //2
	ldi r27, 0b00
	ldi r28,0b1000 //3
	//Delcaration of i/0
	out ddrb, r26			//output port b 2
	out portb, r27	
	out ddrc,  r27			//input Port c 3
	out portc, r28		
	
	//start function
start:		
	
    in r16, pinc		;
	sbrs r16, 3			;
	rjmp LED			;
	rjmp start			;

	//led function turn on led, then turn off led
LED:				
	out portb, r26	
	call DELAY		
	rjmp start	
	
//delay everything	
DELAY:				
	ldi r23, 190		  //stick with 190 loops total 
D2: 
	ldi r24, 200
D3:
	ldi r25, 50
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
	

