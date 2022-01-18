        cpu 8085
        org 2000h
        mvi a,25h
        mvi b,29h
        add b
        daa
        sta 8220h
        rst 5
        end



