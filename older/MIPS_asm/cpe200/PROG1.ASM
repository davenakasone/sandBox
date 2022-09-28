	.org 2000h
	lxi h,0000h
	lxi d,0001h
	mvi b,64h
start:  dad d
	inx d
	dcr b
	jnz start
	shld 2020h
	rst 5
	.end
