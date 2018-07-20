 insertion_sort PROC
 pusha ; save registers
 mov BP,SP
 mov BX,[BP+18] ; copy array pointer
 mov CX,[BP+20] ; copy array size
 mov SI,2 ; array left of SI is sorted

for_loop:
 ; variables of the algorithm are mapped as follws:
 ; DX = temp, SI = i, and DI = j
 mov DX,SORT_ARRAY[SI] ; temp := array[i]
 mov DI,SI ; j := i-1
 sub DI,2
 while_loop:
 cmp DX,SORT_ARRAY[DI] ; temp < array[j]
 jge exit_while_loop
 ; array[j+1] := array[j]
 mov AX,SORT_ARRAY[DI]
 mov SORT_ARRAY[DI+2],AX
 sub DI,2 ; j := j-1
 cmp DI,0 ; j >= 0
 jge while_loop
 exit_while_loop:
 ; array[j+1] := temp
 mov SORT_ARRAY[DI+2],DX
 add SI,2 ; i := i+1
 dec CX
 cmp CX,1 ; if CX = 1, we are done
 jne for_loop
 sort_done:
 popa ; restore registers
 ret 4
 insertion_sort ENDP