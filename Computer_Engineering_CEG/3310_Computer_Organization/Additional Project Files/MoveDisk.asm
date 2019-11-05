	; Cameron Fox
	; Lab5

	.ORIG x5000
MoveDisk
	LDR R5, R6, #0
        ADD R6, R6, #-1
        LDR R7, R6, #0
        ADD R6, R6, #-1
	
	; Beginning of the Lab
	; Tests to see if the disk number is greater than 1

	ADD R6, R6, #-3
	STR R5, R6, #1
	STR R7, R6, #2

	ADD R5, R6, #0

	LDR R0, R5, #4
	ADD R0, R0, #-1
	BRnz ELSE

	ADD R1, R1, #-1

	LDR R1, R5, #4
	LDR R2, R5, #5
	LDR R3, R5, #6
	LDR R4, R5, #7

	ADD R1, R1, #-1
	
	LD R0, Therty
	ADD R1, R1, R0

	ADD R1, R5, #-4
	LDR R1, R5, #0

	ADD R2, R5, #-3
	LDR R2, R5, #0
	
	ADD R3, R5, #-2
	LDR R3, R5, #0

	ADD R4, R5, #-1
	LDR R4, R5, #0

	ADD R6, R6, #-5
	
	JSR MoveDisk		; recurcivly recalls MoveDisk again

	ADD R6, R6, #5

	; Full Prompt one with adding in the post variables loaded from the stack
	AND R0, R0, #0
	LEA R0, prompt1a
	PUTS

	AND R0, R0, #0
	ADD R0, R1, #0
	TRAP x21

	; Second part of the prompt
	AND R0, R0, #0
	LEA R0, prompt1b

	AND R0, R0, #0
	ADD R0, R2, #0
	TRAP x21

	; Third part of the prompt
	AND R0, R0, #0
	LEA R0, prompt1c

	AND R0, R0, #0
	ADD R0, R4, #0
	TRAP x21
	; End of the first Prompt

	AND R0, R0, #0
	LD R0, ENT
	TRAP x21
	TRAP x21

	ADD R1, R1, #-1	; Subtrracting 1 from the number of disks

	; Loading values from the stack
	ADD R1, R1, R0
	LDR R1, R5, #4
	LDR R2, R5, #6
	LDR R3, R5, #7
	LDR R4, R5, #5

	ADD R1, R1, #-1 ; Subtrracting 1 from the number of disks
	
	; Storing variables onto the stack
	LD R0, Therty
	ADD R1, R1, R0

	ADD R1, R5, #-4
	LDR R1, R5, #0

	ADD R3, R5, #-3
	LDR R3, R5, #0
	
	ADD R4, R5, #-2
	LDR R4, R5, #0

	ADD R2, R5, #-1
	LDR R2, R5, #0

	ADD R6, R6, #-5
	
	JSR MoveDisk		; recurcivly recalls MoveDisk again

	ADD R6, R6, #5

	RET

ELSE	AND R0, R0, #0
	
	AND R0, R0, #0
	LEA R0, prompt2a
	PUTS

	AND R0, R0, #0
	ADD R0, R2, #0
	TRAP x21

	AND R0, R0, #0
	LEA R0, prompt2b

	AND R0, R0, #0
	ADD R0, R4, #0
	TRAP x21

	AND R0, R0, #0
	LD R0, ENT
	TRAP x21
	TRAP x21

	LDR	R7, R6, #2
	LDR	R5, R6, #1

	ADD R6, R6, #3

	RET

	ONE	.FILL	x0031
	ENT	.FILL	x000A
	Therty	.FILL	xFFD0

	prompt1a .STRINGZ "Move Disk "
	prompt1b .STRINGZ "from post "
	prompt1c .STRINGZ "to post "

	prompt2a .STRINGZ "Move Disk 1 from post "
	prompt2b .STRINGZ " to post "
	

	SaveR5	.BLKW 1
	SaveR7	.BLKW 1
	.END