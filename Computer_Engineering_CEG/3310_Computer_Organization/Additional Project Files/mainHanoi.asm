	;CAMERON FOX
	;LAB3 CEG 3310

	;MAIN
	.ORIG		x3000			 	; Start of the program

	ST	R7, SaveR7
	LD R5, MoveDisk

	ENT	.FILL	x000A
	AND R0, R0, #0
	
	LEA R0, prompt1
	PUTS

	AND R0, R0, #0
	LD R0, ENT
	TRAP x21
	TRAP x21

	AND R0, R0, #0
	LEA R0, prompt2		; Asks the user for the number of disks
	PUTS

	TRAP x20
	TRAP x21

	ADD R1, R0, #0		; Saves the number of disks into R1

	AND R0, R0, #0
	LD R0, ENT
	TRAP x21
	TRAP x21

	AND R0, R0, #0
	LEA R0, prompt3		; starts the last prompt of main
	PUTS

	AND R0, R0, #0
	ADD R0, R1, #0
	TRAP x21		; Inserts the number od disks into the statement

	AND R0, R0, #0
	LEA R0, prompt4
	PUTS			; Finishes the last statement

	AND R0, R0, #0
	LD R6, Start
	LD R5, MoveDisk

	LD R2, StartPost
	LD R3, MidPost
	LD R4, EndPost

	LD R0, Therty
	ADD R1, R1, R0
	STR R1, R5, #-4
	STR R2, R5, #-3
	STR R4, R5, #-2
	STR R3, R5, #-1

	ADD R6, R6, #-4


	JSRR R6		; Calls the MoveDisk Subroutine

	ADD R6, R6, #4

	LD	R7, SaveR7

	prompt1	.STRINGZ "--Towers of Hanoi--"
	prompt2	.STRINGZ "How many disks? "
	prompt3	.STRINGZ "Instructions to move "
	prompt4 .STRINGZ " disks from post 1 to post 3:"

	HALT	

; LABELS for the three post positions used
	StartPost	.FILL	x0001
	MidPost		.FILL	x0002
	EndPost		.FILL	x0003

	Therty		.FILL	xFFD0
	Start		.FILL	x5000
	MoveDisk	.FILL	x5000

	SaveR7 .BLKW 1
	.END