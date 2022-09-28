
.org 2000H

 xra A
 lda 2020h
 mov b,a
 mvi c,08h

START: dcr c
       jz ENDCONV
       rar
       xra b
       jmp START

ENDCONV: sta 2021h
         rst 5

.org 2020h
.db 64h
.end
