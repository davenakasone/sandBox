        .org 2000h
        mvi a,8bh
        out 0fh
        lxi h,2040h
        mvi b,1eh
        mvi a,00h
start:  inr a
        out 0ch
        mov m,a
        inx h
        dcr b
        jnz start
        rst 5
        .end
