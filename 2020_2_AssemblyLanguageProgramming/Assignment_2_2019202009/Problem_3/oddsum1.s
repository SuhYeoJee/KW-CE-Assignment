	AREA ARMex, CODE, READONLY
		ENTRY
;using LOOP	
start
	MOV r0, #1
	LSL r1,r0,r0 ;r1==2
	LSL r2,r1,r1 ;r2==8
	ADD r3,r2,r1
	ADD r3,r3,r0 ;r3==11
	ADD r4,r2,r1 ;r4==10, loop count
	LDR r5,TEMPADDR1
	
	MOV r6, r3
Loop
	SUB r4, r4, r0
	ADD r3, r3, r1	;next odd number
	ADD r6, r6, r3	;new sum
	CMP r4, r0		;check Loop count
	BEQ EndLoop
	B Loop
EndLoop
	STR r6, [r5] ;save result
	MOV pc,lr

TEMPADDR1 & &00004000
	END