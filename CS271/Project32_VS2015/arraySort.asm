sortList PROC

push ebp
mov ebp, esp
mov eax, 0				;k in outer loop
mov edx, [ebp + 12]
dec edx					;count - 1 in outer loop
sub esp,  8				;[ebp - 4] now points to "i"
mov esi, [ebp + 8]		;esi = array[0]


jmp sortLoop

sortLoop:

mov DWORD PTR [ebp - 4], eax		;"i = k"

inc edx					;edx now equals count, needed for inner loop
mov edi, 0				;for accessing array
makeSwapLoop:

mov DWORD PTR [edp - 8], eax
inc [edp - 8]			;"j" in inner loop (j = k + 1). From second loop onwards, "j++"

push eax
push edx
mov eax, [esi + edi]			;eax = array[i]
add edi, TYPE DWORD				;on each pass, edi = index of next element
mov edx, [esi + 4]				;edx = array[j]
cmp edx, eax					;if array[j] > array[i]
jg swapIndices					;i = j

endLoop:

pop eax
pop edx

cmp [edp - 8], edx		;while j < count
jl makeSwapLoop			



dec edx					;sets edx back to count - 1
call exchange (switch array[k] and array[i]

add esi, TYPE DWORD			;in next call to inner loop, edi = array[i + 1]
inc eax						;"k++"
cmp eax, edx				;"while k < count - 1"
jl sortLoop


jmp endProcedure

swapIndices:



jmp endLoop


endProcedure:


mov esp, ebp
pop ebp
sortList ENDP


;push ecx
;mov ecx, [edx]
;mov [eax], ecx
;pop ecx