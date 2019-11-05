	;CAMERON FOX
	;LAB4 CEG 3310

	.ORIG x4000

	Input	

	ST	R1, SaveR1
	ST	R2, SaveR2
	ST	R3, SaveR3
	ST	R4, SaveR4
	ST	R5, SaveR5
	ST	R7, SaveR7

	AND R1, R1, #0				; Resetting R1 to zero This is the postion count
	AND R2, R2, #0				; Resetting R2 to zero This is the temp count
	AND R0, R0, #0

	; LABLES for the numbers to check for when getting input from the user
	ZERO  .FILL x0030
	ONE   .FILL x0031
	TWO   .FILL x0032
	THREE .FILL x0033
	FOUR  .FILL x0034
	FIVE  .FILL x0035
	SIX   .FILL x0036
	SEVEN .FILL x0037
	EIGHT .FILL x0038
	NINE  .FILL x0039

	; LABLES for the letters to check for when getting input from the user
	A     .FILL x0041
	B     .FILL x0042
	C     .FILL x0043
	D     .FILL x0044
	E     .FILL x0045
	F     .FILL x0046

	x     .FILL x0078

	; Goes through getting input from the user
Loop	TRAP x20				 		; Start of Loop and gets a charater from the user
	TRAP x21				 		; Outputs the character to the console

	; Checks if the user enters 0
	LD R3, ZERO
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE0

	; Checks if the user enters 1
	LD R3, ONE
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE1

	; Checks if the user enters 2
	LD R3, TWO
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE2

	; Checks if the user enters 3
	LD R3, THREE
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE3

	; Checks if the user enters 4
	LD R3, FOUR
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE4

	; Checks if the user enters 5
	LD R3, FIVE
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE5

	; checks if the user enters 6
	LD R3, SIX
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE6

	; Checks if the user enters 7
	LD R3, SEVEN
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE7

	; Checks if the user enters 8
	LD R3, EIGHT
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE8

	; Checks if the user enters 9
	LD R3, NINE
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGE9

	; Checks if the user enters A
	LD R3, A
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGEA

	; Checks if the user enters B
	LD R3, B
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGEB

	; Checks if the user enters C
	LD R3, C
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGEC

	; Checks if the user enters D
	LD R3, D
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGED

	; Checks if the user enters E
	LD R3, E
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGEE

	; Checks if the user enters F
	LD R3, F
	NOT R3, R3
	AND R3, R3, R0
	BRz CHANGEF

	; Checks if the user hits the Enter Key
	STR R0, R1, #0				 		; Move input character to Memory

	ENT .FILL x000A				 		; Fills the Label ENT with x000A

	LD R2, ENT				 		; Loading in the label ENT into R2
	NOT R2, R2				 		; Taking R2 and Notting it
	AND R2, R2, R0				 		; And Not R2 with R0 and stores the result in R2
	BRz CHECK

	; Check If user enters a valid address of only four values!
	CHECK	.FILL x0034
	LD R6, CHECK
	NOT R6, R6
	AND R1, R1, R6
	BRz FINISH

	AND R0, R0, #0
	LD R0, ENT
	TRAP x21
	TRAP x21
	reprompt .STRINGZ "Re-Enter an Address with 4 Hex Values Only!!: x"	; Re-Prompting the user to enter a new address
	LEA R0, reprompt
	PUTS
	AND R1, R1, #0
	BRnzp Loop

	; Tests to check what value is entered by the user
CHANGE0	AND R0, R0, #0
	ADD R0, R0, #0
	BRnp TEST1

CHANGE1	AND R0, R0, #0
	ADD R0, R0, #1
	BRnp TEST1

CHANGE2	AND R0, R0, #0
	ADD R0, R0, #2
	BRnp TEST1

CHANGE3	AND R0, R0, #0
	ADD R0, R0, #3
	BRnp TEST1

CHANGE4	AND R0, R0, #0
	ADD R0, R0, #4
	BRnp TEST1

CHANGE5	AND R0, R0, #0
	ADD R0, R0, #5
	BRnp TEST1

CHANGE6	AND R0, R0, #0
	ADD R0, R0, #6
	BRnp TEST1

CHANGE7	AND R0, R0, #0
	ADD R0, R0, #7
	BRnp TEST1

CHANGE8	AND R0, R0, #0
	ADD R0, R0, #8
	BRnp TEST1

CHANGE9	AND R0, R0, #0
	ADD R0, R0, #9
	BRnp TEST1

CHANGEA	AND R0, R0, #0
	ADD R0, R0, #10
	BRnp TEST1

CHANGEB	AND R0, R0, #0
	ADD R0, R0, #11
	BRnp TEST1

CHANGEC	AND R0, R0, #0
	ADD R0, R0, #12
	BRnp TEST1

CHANGED	AND R0, R0, #0
	ADD R0, R0, #13
	BRnp TEST1

CHANGEE	AND R0, R0, #0
	ADD R0, R0, #14
	BRnp TEST1

CHANGEF	AND R0, R0, #0
	ADD R0, R0, #15
	BRnp TEST1

; Shifting the chars over four bits to the left

TEST1	ADD R0, R0, R0	
	ADD R1, R1, #1
	NOT R2, R2
	AND R2, R2, R1
	BRz Loop

TEST2	NOT R2, R2
	AND R2, R2, R1
	BRz Loop

TEST3	NOT R2, R2
	AND R2, R2, R1
	BRz Loop

	ADD R1, R1, #1
	ADD R5, R0, #0
	BRnp Loop

TEST4	NOT R2, R2
	AND R2, R2, R1
	BRz Loop

TEST5	NOT R2, R2
	AND R2, R2, R1
	
	ADD R5, R0, #0
	STR R0, R1, #0

	; Ending method to leave input and go back to main
FINISH

	LD	R1, SaveR1
	LD	R2, SaveR2
	LD	R3, SaveR3
	LD	R4, SaveR4
	LD	R5, SaveR5
	LD	R7, SaveR7
				
	RET			; Return to calling function
	SaveR1	.BLKW	1
	SaveR2	.BLKW	1
	SaveR3	.BLKW	1
	SaveR4	.BLKW	1
	SaveR5	.BLKW	1
	SaveR7	.blkw	1
	.END			; END of the program