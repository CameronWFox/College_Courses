; SHIFTR: A simple assembly language subroutine to shift the value
;         in R0 right by one bit.  Feel free to use this code as-is
;         or modify it for use in your lab.

; NOTE - this is not a complete assembly language file, you must
;        cut/paste it into your main.asm to use the SHIFTR subroutine.

;=================================================================================
; SHIFTR - Shift the value in R0 right by one bit
;---------------------------------------------------------------------------------
; R0 is shifted right by one bit
; All other registers (except R7) are callee-saved and restored.
; R7 is modified, as it is with all subroutine calls.
;=================================================================================
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
		ADD R1, R1, #1		;force LSB to 1							
		ADD R0, R0, R0		;shift original value left; check next bit			
													
TestDone	ADD R2, R2, #-1										
		BRP NextBit										
													
Done		ADD R0, R1, #0		; Move result to R0						
	        LD  R2, R2SAVE		; Restore callee-save registers					
                LD  R1, R1SAVE										
                RET			; Return to calling program								
													
R1SAVE		.BLKW 1											
R2SAVE		.BLKW 1	
