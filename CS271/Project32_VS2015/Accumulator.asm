; Name: Connor Shields
; Email: shielcon@oregonstate.edu
; CS 271-400
; Programming Project #2
; Due: 1/28/2018

INCLUDE Irvine32.inc

.data

array DWORD 100, 400, 23, 5, 1, 6, 8, 22, 143, 11
count DWORD 10
swapMade dWORD 0

.code
main proc


mov ecx, count													;;;;
dec ecx					;ecx begins at count - 1
mov edx, 0				;edx = i (i = k)
mov esi, OFFSET array	;esi = array[0]							;;;;


sortLoop:

mov eax, ecx
push ecx				;push ecx to be used in inner loop
mov ecx, eax			;inner loop will iterate from count-1 to 0
mov ebx, edx			;ebx(j) = i
add ebx, TYPE DWORD		;ebx(j) = i + 1	

switchIndexLoop:		;inner loop


mov eax, [esi + edx]	;eax = array[i]
mov edi, [esi + ebx]	;edi = array[j]

cmp edi, eax
jg indexSwap

endSwitch:

;end of inner loop

add ebx, TYPE DWORD		;j++
loop switchIndexLoop


;end of outer looop
mov eax, [esi + edx]	;eax = @array[i]
lea ecx, [esi + edx]	;ecx = array[i]
mov ebx, swapMade		;restore edx for indexing in outer loop, and for swap				;;;;;
cmp ebx, 1				;if swap was made
je restoreEdx

continue:

mov ebx, [esi + edx]	;ebx = @array[k]
lea edi, [esi + edx]	;edi = array[k]

mov ebx, ecx		;@array[k] = array[i]
mov eax, edi		;@array[i] = array[k]
					
add edx, TYPE DWORD		;i++ (because k++, and i = k)
pop ecx
loop sortLoop

jmp functionEnd			;avoids indexSwap when outer loop is finished

indexSwap:

mov eax, swapMade																;;;;;;
cmp eax, 0				;check if swap has been made
je 	incEdx				;if a swap is made, edx needs to be saved for outer loop
continue2:				;so that it can be incremented from its original index
mov edx, ebx			;i = j
jmp endSwitch

restoreEdx:				;then restore edx

pop edx
jmp continue

incEdx:

push ebx
mov ebx, 1
mov swapMade, ebx 
pop ebx
push edx
jmp continue2

functionEnd:

push OFFSET array
push count
call displayList

exit
main ENDP






exchange PROC

;ecx is currently array[i]
;edi is currently array[k]
;eax is currently @array[i]
;ebx is currently @array[k]

mov ebx, ecx		;@array[k] = array[i]
mov eax, edi		;@array[i] = array[k]

ret

exchange ENDP



displayList PROC

push ebp
mov ebp, esp
mov ecx, [ebp + 8]
mov esi, [ebp + 12]

printLoop:

mov eax, [esi]
call writeDec
call crlf
add esi, TYPE DWORD
loop printLoop

pop ebp
ret 8

displayList ENDP

END main