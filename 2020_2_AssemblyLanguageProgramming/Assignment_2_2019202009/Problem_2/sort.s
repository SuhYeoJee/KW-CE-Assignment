	AREA ARMex, CODE, READONLY
		ENTRY
		
start
	LDR r0, =Array
	LDR r1, TEMPADDR1
	MOV r2, #10 ;Loop count, order
	
Loop
	SUB r2, #1
	ADD r4, r1,r2 	;save from behind 
	LDRB r3, [r0], #1 ;read 1 bit
	STRB r3, [r4]	;save at memory
	CMP r2, #0		;check loop count
	BEQ EndLoop
	B Loop		;next bit
EndLoop
	MOV pc,lr

TEMPADDR1 & &00004000
Array DCB 10,9,8,7,6,5,4,3,2,1
	END