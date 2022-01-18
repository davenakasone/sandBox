	.org 2000h
	lda 2030h
	mov b,a
	rar
	xra b
	sta 2031h
	rst 5
	.org 2030h
	.db 64h
	.end
