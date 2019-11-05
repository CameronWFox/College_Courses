	;CAMERON FOX
	;LAB4 CEG 3310

	;MAIN
	.ORIG					x3000 		; Start of the program

	AND R0, R0, #0						; Resets R0 to zero
	TRAP x40

	HALT
	.END