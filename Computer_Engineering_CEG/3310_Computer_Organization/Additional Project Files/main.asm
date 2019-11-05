	;CAMERON FOX
	;LAB4 CEG 3310

	;MAIN
	.ORIG	x3000 						; Start of the program

	ST	R1, SaveR1
	ST	R2, SaveR2
	ST	R3, SaveR3
	ST	R4, SaveR4

	AND R0, R0, #0						; Resets R0 to zero
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0

	; Asking for the starting address
	prompt .STRINGZ "Enter starting memory Address:x"	; Prompt the user for a memory address input
	LEA R0, prompt						; Loads the string into R0
	PUTS							; Prints String to Console

	TRAP x40
	ADD R1, R0, #0

	AND R0, R0, #0

	; Asking for the ending address
	prompt2 .STRINGZ "Enter ending memory Address:x"	; Prompt the user for the ending memory address input
	LEA R0, prompt2						; Loads the string into R0
	PUTS							; Prints String to Console

	TRAP x40
	ADD R2, R0, #0

	; The third prompt statement for the resulting data
	AND R0, R0, #0
	prompt3 .STRINGZ "The Memory Contents: "
	LEA R0, prompt3
	PUTS

	; Checks that the ending address is greater than the starting address
TEST	LDR R3, R1, #0
	LDR R4, R2, #0
	NOT R4, R4
	ADD R4, R4, R3
	BRn CHECK

	AND R0, R0, #0
	reprompt .STRINGZ "Re-Enter a valid 4 Hex character address: x"
	LEA R0, reprompt
	PUTS
	BRnzp	TEST
	; Checks to see if I am at the last address to check or not
CHECK	LDR R5, R1, #0
	LDR R6, R2, #0
	ADD R5, R5, #1
	NOT R5, R5
	ADD R5, R5, R6
	BRz LAST

	TRAP x41
	BRnzp TEST

LAST	ADD R0, R2, #0
	TRAP x41

	LD	R1, SaveR1
	LD	R2, SaveR2
	LD	R3, SaveR3
	LD	R4, SaveR4

	HALT

	SaveR1	.BLKW 1
	SaveR2	.BLKW 1
	SaveR3	.BLKW 1
	SaveR4	.BLKW 1

	.END