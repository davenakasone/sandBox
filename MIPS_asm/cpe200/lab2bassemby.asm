.org 0x0	
jmp main
.org 0x02 
jmp interupt
main:			
	//DECLARATION OF REGISTERS
	ldi r20, HIGH(RAMEND)
	out SPH, r20
	ldi r20, LOW(RAMEND)
	out SPL, r20 ; stack set
	sts EICRA,r20
	ldi r20, 0x2 ; falling edge
	ldi r26,0b100 //2
	ldi r27, 0b01
	ldi r28,0b1000 //3
	//Delcaration of i/0
	out ddrb, r26			//output port b 2
	out portb, r27	
	out ddrc,  r27			//input Port c 3
	out portc, r28		
	LDI r20, 1<<INT0;
	out EIMSK, r20;
	SEI;
start:		
	
    in r16, pinc		;
	sbrs r16, 3			;
	rjmp interupt		;
	rjmp start			;

	//led function turn on led, then turn off led
LED:				
	
	rjmp start	

interupt:
	out PORTB, r26	
	rjmp DELAY
	out PORTB, r26
	RETI	
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