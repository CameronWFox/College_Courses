	.ORIG x3000

	LD R0, DATA		: x3000
	NOT R1, R0		: x3001
	ADD R2, R1, R0		: x3002
	ST R2, DATA		: x3003


	HALT			: x3004

DATA:	.FILL x000A		: x3005

	.END			