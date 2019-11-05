	;CAMERON FOX
	;LAB4 CEG 3310

	.ORIG x5000
	Output

	ST	R0, SaveR0
	ST	R3, SaveR3
	ST	R4, SaveR4
	ST	R5, SaveR5
	ST	R6, SaveR6
	ST	R7, SaveR7
	
	ADD R0, R1, #0
	AND R3, R3, #0
	ADD R3, R3, #4

	; This loop goes trough and calls the SHIFTR to move the bits and mask them
Loop	
	ADD R3, R3, #-1
	NOT R4, R4
	ADD R4, R3, R4	
	BRp SHIFTR
	LD R6, CHANGE
	AND R1, R1, R6
	BRnzp CHECK0

	; Checks the value to see what is being compared
CHECK0	LDI R5, #0
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK1	LDI R5, #1
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK2	LDI R5, #2
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK3	LDI R5, #3
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK4	LDI R5, #4
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK5	LDI R5, #5
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK6	LDI R5, #6
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK7	LDI R5, #7
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK8	LDI R5, #8
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHECK9	LDI R5, #9
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHANGEA LDI R5, #10
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHANGEB	LDI R5, #11
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHANGEC	LDI R5, #12
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHANGED	LDI R5, #13
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHANGEE	LDI R5, #14
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT

CHANGEF	LDI R5, #15
	NOT R5, R5
	ADD R0, R5, R0
	BRz PRINT


	; Prints out the address then the data stored at the address currently used
PRINT	ADD R0, R1, #0
	TRAP x21

	ADD R3, R3, #5
	ADD R3, R3, #-1
	NOT R5, R5
	ADD R5, R3, R5
	BRnp CHECK0
	BRz FINISH


	; This chunk of code is used to take the my stored input and shift
SHIFTR		ST  R1, R1SAVE		; Save callee-save registers					
		ST  R2, R2SAVE									
														
		AND R1, R1, #0		; R1 holds the itermediate result				
		AND R2, R2, #0		; R2 holds count for number of bits examined			
		ADD R2, R2, #15										
													
NextBit		ADD R0, R0, #0		; Test MSB for 1 or 0						
		BRn MSBIS1									
													
MSBIS0		ADD R1, R1, R1		;shift result left 						
					;force LSB to 0							
		ADD R0, R0, R0		;shift original value left; check next bit			
		BR  TestDone									
													
MSBIS1		ADD R1, R1, R1		;shift running total right					
		ADD R1, R1, #3		;force LSB to 1							
		ADD R0, R0, R0		;shift original value left; check next bit			
													
TestDone	ADD R2, R2, #-1										
		BRP NextBit										
													
Done		ADD R0, R1, #0		; Move result to R0						
	        LD  R2, R2SAVE		; Restore callee-save registers					
                LD  R1, R1SAVE										
                RET			; Return to calling program								
													
R1SAVE		.BLKW 1											
R2SAVE		.BLKW 1	

FINISH
	
	LD	R0, SaveR0
	LD	R3, SaveR3
	LD	R4, SaveR4
	LD	R5, SaveR5
	LD	R6, SaveR6
	LD	R7, SaveR7
	
	RET

	SaveR0	.BLKW 1
	SaveR3	.BLKW 1
	SaveR4	.BLKW 1
	SaveR5	.BLKW 1
	SaveR6	.BLKW 1
	SaveR7	.BLKW 1

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

	; Masking Labels
	CHANGE	.FILL xF000

	.END