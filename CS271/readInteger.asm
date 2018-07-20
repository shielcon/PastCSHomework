;Connor Shields
;CS271 Program 4
;3/5/18
;This program prompts the user to enter how many numbers they want,
;displays those random numbers, shows the median, and then prints 
;the sorted array

INCLUDE Irvine32.inc


COMMENT @
displayString MACRO string				;macro for displaying a string

	push edx							;save edx in case the program needs it elsewhere
	mov edx, OFFSET string
	call writeString
	call CRLF
	pop edx								;restore the edx register

ENDM	;end of displayString
@

COMMENT @
getString MACRO currentnum, string			;macro for getting input string
											;will be used to prompt the user for input
	push ecx
	push edx
	displayString string				;calls previous--no need to assign to edx

	mov edx, OFFSET currentNum			;stores the current number in edx
	mov ecx, (sizeof currentNum) - 1	;counter for the currentNum

	call readString
	pop edx
	pop ecx


ENDM	;end of getString
@

.data

testString BYTE "test", 0

.code

main PROC

	;displayString testString				;uses macro for introduction
	







main ENDP

;*****************************
;getNums procedure:
;takes two parameters: an array and the indexer of the array
;passes those parameters to readVal in a loop
;returns the filled array

;*****************************
COMMENT @
getNums PROC

	pushad

	mov ebp, esp
	mov ecx, 10					;to loop 10 times

;	fillLoop:					;loop to fill array
;	push [ebp + ]
	

getNums ENDP   ;end of getNums


;*****************************

;readVal procedure

;*****************************

readVal PROC

	pushad			;push all registers
	mov ebp, esp

		

readVal ENDP
@

end main