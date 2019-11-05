	;CAMERON FOX
	;LAB3 CEG 3310

	;MAIN
	.ORIG		x3000			 	; Start of the program
	
	AND R0, R0, #0				 	; Resetting R0 to 0

	hello .STRINGZ "Enter a string to echo:" 	; The string to prompt for input
	LEA R0, hello				 	; Loading in the string
	PUTS					 	; Printing out the string
	DATA .FILL x3100			 	; Declaring the Label DATA
	LD R1, DATA				 	; Starting location of input String

Loop	TRAP x20				 	; Start of Loop and gets a charater from the user
	TRAP x21				 	; Outputs the character to the console

	STR R0, R1, #0				 	; Move input character to Memory
	ADD R1, R1, #1				 	; Adds 1 to R1 every time the loops re-runs
	ENT .FILL x000A				 	; Fills the Label ENT with x000A
	LD R2, ENT				 	; Loading in the label ENT into R2
	NOT R2, R2				 	; Taking R2 and Notting it
	AND R2, R2, R0				 	; And Not R2 with R0 and stores the result in R2
	BRnp Loop				 	; End of Loop
	
	STR R4, R1, #-1				 	; Removes the x000A from being stored
	LD R0, DATA				 	; Loads in the Label DATA to R0
	PUTS					 	; Prints out the echo of the input String
	HALT					 	; Stops the program
	.END						; End of the program