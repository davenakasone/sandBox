        CPU 8085
        ORG 2000h

        MVI A,80H
        OUT 03H
        MVI D,20H
LP:     MVI A,00H
        OUT 02H
        MVI A,0FFH
        OUT 01H
        MVI A,01H
        OUT 02H
        DCR D
        JNZ LP
        LXI H,2100H
        MVI C,04H
COUNT:  MVI B,08H
        MOV D,M
LP1:    MVI A,00H
        OUT 02H
        MOV A,D
        RLC
        MOV D,A
        RAL
        OUT 01
        MVI A,01H
        OUT 02H
        DCR B
        JNZ LP1
        LXI D,0000H
        CALL 03BCH
        INX H
        DCR C
        JNZ COUNT
        RST 5

        ORG 2100H
        DFB 82H,0C0H,0C0H,0A1H
                
        END

