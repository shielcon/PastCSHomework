;Connor Shields
;CS271 Program 4
;3/5/18
;This program

INCLUDE Irvine32.inc

.data

MIN = 10
MAX = 200
LO = 100
HI = 999

myString BYTE "Sorting Random Integers       		      Programmed By Connor Shields", 13, 10,
			  "This program generates random numbers in the range [100 .. 999],", 13, 10,
			  "displays the original list, sorts the list, and calculates the", 13, 10,
			  "median value. Finally, it displays the list sorted in descending order.", 13, 10, 10, 0
count DWORD ?
array DWORD 200 DUP(?)
swapMade WORD 0
countPrompt BYTE "How many numbers should be generated?", 13, 10, 0
errorMessage BYTE "Invalid input", 13, 10, 0



.code
main PROC

call randomize
push OFFSET myString
call printGreeting

push OFFSET count
call getData

push OFFSET array
push count
call fillArray

push OFFSET array
push count
call displayList

push OFFSET swapMade
push count
push OFFSET array
call sortList

push OFFSET array
push count
call displayList

exit

main ENDP

printGreeting PROC

push ebp
mov ebp, esp
mov edx, [ebp + 8]
call writeString
pop ebp
ret 1

printGreeting ENDP

getData PROC

push ebp

mov ebp, esp
mov ebx, [ebp + 8]

jmp getCount
invalidInput:
mov edx, OFFSET errorMessage
call writeString
getCount:
mov edx, OFFSET countPrompt
call writeString
call readDec

cmp eax, 10
jl invalidInput
cmp eax, 200
jg invalidInput

mov [ebx], eax


pop ebp

ret 4

getData ENDP

	;fills the array with random values
fillArray PROC
push ebp
mov ebp, esp
mov ecx, [ebp + 8]
mov esi, [ebp + 12]

fillLoop:

mov eax, HI
sub eax, LO
call RandomRange
mov [esi], eax
add esi, TYPE DWORD
loop fillLoop

pop ebp
ret 8

fillArray ENDP

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

sortList PROC

push ebp
mov ebp, esp

mov ecx, [ebp + 12]
dec ecx					;ecx begins at count - 1
mov edx, 0				;edx = i (i = k)
mov esi, [ebp + 8]		;esi = array[0]


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
mov ebx, [ebp + 16]		;restore edx for indexing in outer loop, and for swap
cmp ebx, 1				;if swap was made
je restoreEdx

continue:

mov ebx, [esi + edx]	;ebx = @array[k]
lea edi, [esi + edx]	;edi = array[k]

call exchange
					
add edx, TYPE DWORD		;i++ (because k++, and i = k)
pop ecx
loop sortLoop

jmp functionEnd			;avoids indexSwap when outer loop is finished

indexSwap:

mov eax, [ebp + 16]
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
mov [ebp + 16], ebx 
pop ebx
push edx
jmp continue2

functionEnd:

mov esp, ebp
pop ebp

sortList ENDP

exchange PROC

;ecx is currently array[i]
;edi is currently array[k]
;eax is currently @array[i]
;ebx is currently @array[k]

mov edi, eax		;@array[k] = array[i]
mov ecx, ebx		;@array[i] = array[k]

ret

exchange ENDP

END main