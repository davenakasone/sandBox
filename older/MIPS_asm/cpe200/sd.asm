.org 2000h
       
start : mvi a,0c0h
        sim
        call delay
        mvi a,40h
        sim
        call delay
        jmp start

.org 2050h
delay :
 
         push h
         push psw
         lxi h,0ffffh
         

delay1 : dcx h
         mov a,l
         ora h
         jnz delay1
         pop psw
         pop h
         ret
.end

