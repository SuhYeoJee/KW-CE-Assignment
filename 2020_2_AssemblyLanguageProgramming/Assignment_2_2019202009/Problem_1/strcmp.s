	AREA ARMex, CODE, READONLY
		ENTRY
		
start
	LDR r0, =string00 ;set register
	LDR r1, =string01
	LDR r3, TEMPADDR1
	
Loop
	LDRB r4, [r0], #1	 ;read 1 bit
	LDRB r5, [r1], #1
	CMP r4,r5 			;compare 1 bit
	
	BNE notEqual		;different string
	CMP r4, #0			;end of string
	MOVEQ r6, #0x0A 	;same string
	BEQ EndLoop	
	B Loop				;compare next bit

notEqual
	MOV r6, #0x0B
EndLoop
	STR r6, [r3]

TEMPADDR1 & &00004000
string00 DCB "12345",0
string01 DCB "12345",0

	END