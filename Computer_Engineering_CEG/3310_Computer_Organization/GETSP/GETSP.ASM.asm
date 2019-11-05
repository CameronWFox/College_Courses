	;CAMERON FOX
	;LAB3 CEG 3310

	;MAIN
	.ORIG		x3000				; Start of the program
	
	AND R0, R0, #0					; Resetting R0 to 0

	hello .STRINGZ "Enter a string to echo:"	; The string to prompt for input
	LEA R0, hello					; Loading in the string
	PUTS						; Printing out the string
	DATA .FILL x3100				; Declaring the Label DATA
	LD R1, DATA					; Starting location of input String

Loop	TRAP x20					; Start of Loop and gets a charater from the user
	TRAP x21					; Outputs the character to the console
	AND R5, R5, #0					; Resetting R5 to zero
	ADD R5, R0, #0					; Putting char from R0 into R5
	
	ENT .FILL x000A					; Fills the Label ENT with x000A
	LD R2, ENT					; Loading in the label ENT into R2
	NOT R2, R2					; Taking R2 and Notting it
	AND R2, R2, R0					; And Not R2 with R0 and stores the result in R2
	BRz Check1					; Branchs if CC is zero

	TRAP x20					; Getting character from user
	TRAP x21					; Outputs character to the console
	LD R2, ENT					; Loading in the label ENT into R2
	NOT R2, R2					; Taking R2 and Notting it
	AND R2, R2, R0					; And Not R2 with R0 and stores the result in R2
	BRz Check1					; Branchs if CC is zero

	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself
	ADD R0, R0, R0					; Adding Currect R0 to itself

	ADD R0, R0, R5					; Adding the currect R0 with R5

	STR R0, R1, #0					; Storing input into Memory
	ADD R1, R1, #1					; Adds 1 to R1 every time the loops re-runs
	
	BRnp Loop					; End of Loop

	BRz Check1					; Branchs to Check1 if CC is zero

	BRnzp Finish					; Branchs to Finish no matter what
	
Check1	STR R5, R1, #0					; Stores the Data input from R1 into R0
	
Finish	LD R0, DATA					; Loads in the Label DATA to R0
	PUTS						; Prints out the echo of the input String
	HALT						; Stops the program
	.END						; End of the program	