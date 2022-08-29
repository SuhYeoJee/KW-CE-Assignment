	AREA ARMex, CODE, READONLY
		ENTRY
		
start
	;save data in the memory
	MOV r0, #13 ;set register value
	MOV r1, #7
	MOV r2, #10
	
	LDR r3, TEMPADDR1 ;Load memory address
	STRB r0, [r3], #1 ;save value and move 1byte
	STRB r1, [r3], #1
	STRB r2, [r3]
	
	;start
	MOV r6, #10 ;for CMP
	LDR r3, TEMPADDR1 ;Load memory address
	
	LDRB r4, [r3], #1 ;Load 1byte and move 1byte
	CMP r4,r6 ;compare with 10
	MOVGT r5, #1 ;in this case, r5 = 1
	MOVMI r5, #2
	MOVEQ r5, #3
	
	LDRB r4, [r3], #1 ;Load 1byte and move 1byte
	CMP r4,r6 ;compare with 10
	MOVGT r5, #1 
	MOVMI r5, #2 ;in this case, r5 = 2
	MOVEQ r5, #3
	
	LDRB r4, [r3] ;Load 1byte
	CMP r4,r6 ;compare with 10
	MOVGT r5, #1
	MOVMI r5, #2
	MOVEQ r5, #3 ;in this case, r5 = 3
	
TEMPADDR1 & &00001000
	MOV pc, lr
	END
			