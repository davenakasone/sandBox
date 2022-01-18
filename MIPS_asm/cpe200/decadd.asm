cpu 8085
.org 2000h
mvi a,45h
mvi b,49h
add b
daa
sta 2030h
rst 5
end

