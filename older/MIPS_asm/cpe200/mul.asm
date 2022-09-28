.org 2000h
 lhld 2030h
 xchg
 lxi h,0000h
 mvi c,00h
 lda 2032h

START: dad d
       jnc DONE
       inr c

DONE: dcr a
      jnz START
      shld 2033h
      mov a,c
      sta 2035h

.org 2030h
.db 32h,45h,12h
.END


