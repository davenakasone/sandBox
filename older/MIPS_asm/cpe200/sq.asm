.org 2000h
 mvi a,80h
 out 0fh
start: mvi a,0ff h
       out 0ch 
       out 0dh
       out 0eh
       call delay
       mvi a,00h
       out 0ch
       out 0dh
       out 0eh
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
