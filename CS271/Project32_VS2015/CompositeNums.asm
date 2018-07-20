;Connor Shields
;CS270 Program 4
;2/18/18
;This program uses several different functions to 
;ask the user how many composite numbers they want to
;see, validates that number, calculates the number of
;composite numbers they asked for, and then prints
;them to the screen.

INCLUDE Irvine32.inc

.data

UPPERLIMIT = 400
myString BYTE "Composite Numbers			By Connor Shields", 13, 10, 10, 0
extraCredit BYTE "Extra Credit: The columns are aligned.", 13, 10, 10, 0

introduction BYTE "Enter the number of composite numbers you would like to see.", 0
condition BYTE "I'll accept orders for up to 400 composites", 0

direction BYTE "Enter the number of composites to display [1...400]: ", 0
errorMessage BYTE "Out of range. Try again.", 13, 10, 10, 0

farewell BYTE "Results certified by Connor. Goodbye.", 13, 10, 10, 0

composites DWORD ?
testComposite DWORD 4
testLoop DWORD ?
boolCheck dword 0
spaces BYTE "   ", 0
tensSpaces BYTE "  ", 0
hundredsSpaces BYTE " ", 0
countPerLine DWORD 0

.code
main PROC

	call greeting
	call compositeRequest
	call printComposites
	call goodbye

	exit

main ENDP

greeting PROC

mov edx, OFFSET myString
call writeString
mov edx, OFFSET extraCredit
call writeString

mov edx, OFFSET introduction
call writestring
call crlf
mov edx, OFFSET condition
call writeString
call crlf


	ret
greeting ENDP

compositeRequest PROC

mov edx, OFFSET direction
call writeString
call readInt
mov composites, eax
call validateData

	ret
compositeRequest ENDP

validateData PROC

jmp L2

L1:
mov edx, OFFSET errorMessage
call writeString
call compositeRequest

L2:

cmp composites, UPPERLIMIT
jg L1
cmp composites, 1
jl L1
ret

validateData ENDP


;PRINT COMPOSITES: THIS FUNCTION INCREMENTS THE NUMBER AND SENDS IT OVER TO TESTCOMPOSITES TO SEE IF IT'S COMPOSITE

printComposites PROC

mov ecx, composites

compositeLoop:

call IsComposite

mov edx, boolcheck
cmp edx, 1					;if "true", prints the number
je printLabel

inc testComposite
;mov edx, composites
;cmp edx, 0
;jg compositeLoop
LOOP compositeLoop
jmp endPrint			;jumps to the end of the function to prevent further printing

printLabel:

mov edx, countPerLine
cmp edx, 10
je lineBreak

continuePrint:

inc countPerLine
mov eax, testComposite
cmp eax, 10
jge greaterThanTen
			
call writeDec
mov edx, OFFSET spaces
call writeString
inc testComposite
dec composites
mov edx, composites
cmp edx, 0
jg compositeLoop

endPrint:
ret

lineBreak:
call crlf
mov countPerLine, 0
jmp continuePrint

greaterThanTen:

cmp eax, 100
jge greaterThan100
call writeDec
mov edx, OFFSET tensSpaces
call writeString
inc testComposite
dec composites
mov edx, composites
cmp edx, 0
jg compositeLoop
jmp endLoop

greaterThan100:

call writeDec
mov edx, OFFSET hundredsSpaces
call writeString
inc testComposite
dec composites
mov edx, composites
cmp edx, 0
jg compositeLoop

endLoop:
ret
printComposites ENDP


;ISCOMPOSITE: THIS FUNCTION TESTS EACH NUMBER TO SEE WHETHER OR NOT IT IS COMPOSITE


IsComposite PROC

push ecx
mov ecx, 0
mov ecx, testComposite
dec ecx

;LOOPS DOWNWARD FROM THE NUMBER IN QUESTION TO SEE IF IT'S DIVISIBLE BY ANY OTHER INTEGER

CompositeTester:

mov edx, 0
mov eax, testComposite
mov ebx, ecx
div ebx

cmp edx, 0
je endTest

loop CompositeTester
mov edx, 0
mov boolCheck, edx
pop ecx
ret

endTest:

cmp ecx, 1
je DividedByOne

mov edx, 1
mov boolCheck, edx
pop ecx
ret

;CHECKS THAT THE INTEGER THAT RETURNED A REMAINDER OF 0 IS NOT 1

DividedByOne:

mov edx, 0
mov boolCheck, edx
pop ecx
ret

IsComposite ENDP


goodbye PROC

call crlf
call crlf
mov edx, OFFSET farewell
call writestring

ret
goodbye ENDP

end main