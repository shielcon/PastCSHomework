; Name: Connor Shields
; Email: shielcon@oregonstate.edu
; CS 271-400
; Programming Project #2
; Due: 1/28/2018

INCLUDE Irvine32.inc

.data


myString BYTE "Composite Numbers			By Connor Shields", 13, 10, 10, 0

introduction BYTE "Enter the number of composite numbers you would like to see.", 0
condition BYTE "I'll accept orders for up to 400 composites", 0

direction BYTE "Enter the number of composites to display", 13, 10, 10, 0
errorMessage BYTE "Out of range. Try again.", 13, 10, 10, 0

farewell BYTE "Results certified by Connor. Goodbye.", 13, 10, 10, 0


.code
main proc

call introduction
call compositeNumbers
call farewell


	invoke ExitProcess,0
main endp
end main

introduction PROC

	ret
introduction ENDP

CompositeNumbers PROC

	ret
compositeNumbers ENDP

farewell PROC

	ret
farewell ENDP



