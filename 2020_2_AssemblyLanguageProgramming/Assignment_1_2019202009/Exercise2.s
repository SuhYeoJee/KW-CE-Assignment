	AREA ARMex, CODE, READONLY
		ENTRY
		
start
	MOV r0, #1 ;set register
	MOV r1, #2
	MOV r3, #3
	MOV r4, #4
	
	;r5, 04030201
	LDR r2, TEMPADDR1 ;Load memory address
	STRB r0, [r2], #1 ;save value and move 1byte
	STRB r1, [r2], #1
	STRB r3, [r2], #1
	STRB r4, [r2]
	
	LDR r2, TEMPADDR1 ;Load memory address
	LDR r5, [r2] ;save value
	
	;r6, 01020304
	LDR r2, TEMPADDR1 ;Load memory address
	STRB r4, [r2], #1 ;backward
	STRB r3, [r2], #1
	STRB r1, [r2], #1
	STRB r0, [r2]
	
	LDR r2, TEMPADDR1 ;Load memory address
	LDR r6, [r2] ;save value

TEMPADDR1 & &00001000
	MOV pc, lr
	END
			