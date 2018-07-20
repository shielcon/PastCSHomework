;Connor Shields
;shielcon@oregonstate.edu
;CS 271
;Due 3/18/18

INCLUDE Irvine32.inc

;getString Macro:
;takes a string address and length as parameters
;places user input in the new string

getString MACRO string, strlen

	push edx
	push ecx
	mov edx, string
	mov ecx, strlen
	call readString
	pop ecx
	pop edx

ENDM

;Macro for printing a string
;takes a string as the parameter
;prints the string to the console

displayString MACRO displayString

	push edx
	mov edx, OFFSET displayString
	call writeString
	pop edx

ENDM

.data

currentNum BYTE 255 DUP(0)
currentString BYTE 32 DUP(?)

intro BYTE	"PROGRAMMING ASSIGNMENT 6: Designing low-level I/O procedures", 13, 10,
			"Written by: Connor Shields", 13, 10,
			"Please provide 10 unsigned decimal integers.", 13, 10, 0

description BYTE			"Each number needs to be small enough to fit inside a 32 bit register.", 13, 10,
							"After you have finished inputting the raw numbers I will display a list", 13, 10,
							"of the integers, their sum, and their average value.", 13, 10, 0

errorMessage BYTE "ERROR: You did not enter an unsigned number or your number was too big.", 13, 10, 0
inputPrompt BYTE "Please enter an unsigned number: ", 0
printSum BYTE "The sum of these numbers is: ", 0
printAvg BYTE "The average is: ", 0
arrPrint BYTE "You entered the following numbers:", 13, 10, 0

sum DWORD ?
average DWORD ?
array DWORD 10 DUP(0)
currentInt DWORD ?

farewell BYTE "Thanks for playing!", 13, 10, 0

.code
main PROC

	displayString intro
	displayString description

	mov ecx, 10					;loop through array to read 10 numbers
	mov edi, OFFSET array

	;*******

	;loop for filling array

	;*******

	fillLoop:

		displayString inputPrompt
		push OFFSET currentNum
		push 255							;the size of currentNum
		call readVal

		mov eax, DWORD PTR currentNum		;setup for next array element
		mov [edi], eax
		add edi, 4

	loop fillLoop

	mov ecx, 10
	mov esi, OFFSET array

	;**********

	;loop for printing array

	;**********

	displayString arrPrint
	printLoop:

		mov eax, [esi]
		mov currentInt, eax
		call writeVal
		call crlf
		add esi, 4

	loop printLoop

	displayString farewell

	exit

main ENDP

;***************************

;readVal procedure:
;parameter: the address of the current number
;result; user input is validated and stored in currentNum as an integer

;***************************

readVal PROC

	push ebp
	mov ebp, esp
	pushad

	jmp Open

	errorSection:

		displayString errorMessage
		displayString inputPrompt

	Open:

		;mov eax, 0
		;ecx has size of DWORD, edx has address of currentNum
		mov edx, [ebp + 12]
		mov ecx, [ebp + 8]
		getString edx, ecx

		mov esi, edx
		mov ecx, 0
		mov ebx, 10
		mov eax, 0

	stringLoop:							;pushes chars from string in as integers
		
		lodsb
		cmp ax, 0						;if at end of string - exit condition
		je endRead
		
		;conditional statement to validate that input is an integer:
		
		cmp ax, 48
		jb errorSection
		cmp ax, 57
		ja errorSection
		sub ax, 48
		xchg eax, ecx			;checks if number is too large
		mul ebx
		jc errorSection

		;setup for next loop:

		add eax, ecx
		xchg eax, ecx		;switch them back from before
		jmp stringLoop
	endRead:
		xchg ecx, eax
		mov DWORD PTR currentNum, eax
		popad
		pop ebp
		ret 4

readVal ENDP

;*************************

;writeVal procedure:
;parameters: the currentNum and currentString
;output: currentNum is parsed to a string and placed in currentString

;*************************
writeVal PROC

	push ebp
	mov ebp, esp
	pushad
	mov ebx, 10
	mov edi, OFFSET currentString
	mov eax, currentInt
	push 0
	std

	parser:
	
		;push ecx
		mov edx, 0
		div ebx
		add edx, 48
		push edx				;remainders individually pushed onto stack
		cmp eax, 0
		jne parser

	returnDigits:
	
		pop [edi]
		mov eax, [edi]
		inc edi
		cmp eax, 0				;0 pushed on stack earlier to mark end of string here
		je endLoop
		
	jmp returnDigits
	
	endLoop:
	
	mov edx, OFFSET currentString
	displayString currentString
		
	popad
	pop ebp
	ret 8

writeVal ENDP



END main