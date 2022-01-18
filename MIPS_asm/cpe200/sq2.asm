.org 2000h
 mvi a,80h
 out 07h
start: mvi a,01 h
       out 04h
       call delay
       mvi a,00h
       out 04h
       call delay
       jmp start
.org 2050h
delay: lxi h,0ffffh
delay1: dcx h
        mov a,l
        ora h
        jnz delay1
        ret
.end
