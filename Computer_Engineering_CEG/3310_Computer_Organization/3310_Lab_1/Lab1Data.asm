	.ORIG	x3500
	.FILL	#-5		; Signed value at x3500
	.FILL	x8201		; Unsigned value at x3501 (#33821)
	.STRINGZ "Hi mom!"	; String at x3502

	; Skip to address x4000
	.BLKW	x0AF6

	; Linked list + some obscuring values
	.FILL	1
	.FILL	x400F
	.FILL	x4004
	.FILL	2
	.FILL	3
	.FILL	x732F
	.FILL	3
	.FILL	x4017
	.FILL	4
	.FILL	3
	.FILL	x0000
	.FILL	x2003
	.FILL	x3004
	.FILL	x400F
	.FILL	3
	.FILL	2
	.FILL	x4006
	.FILL	6
	.FILL	0
	.FILL	5
	.FILL	x0000
	.FILL	x400A
	.FILL	x4016
	.FILL	4
	.FILL	x4013
	.FILL	3
	.FILL	x4003
	.FILL	2
	.FILL	1
	.FILL	x7250
	.END