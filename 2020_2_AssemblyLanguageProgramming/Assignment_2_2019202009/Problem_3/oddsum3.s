	AREA ARMex, CODE, READONLY
		ENTRY
;Unrolling
start
	MOV r0, #11 ;set number
	MOV r1, #0 ;sum
	MOV r2,#2 ;loop count
	LDR r3,TEMPADDR1
Loop
	SUB r2, r2, #1
	ADD r1, r1, r0	;r1 += r0
	ADD r0, r0, #2	;r0 += 2, next odd number
	ADD r1, r1, r0	;repeat
	ADD r0, r0, #2
	ADD r1, r1, r0
	ADD r0, r0, #2
	ADD r1, r1, r0
	ADD r0, r0, #2
	ADD r1, r1, r0
	ADD r0, r0, #2
	CMP r2, #0 		;check loop count
	BEQ EndLoop
	B Loop
EndLoop
	STRB r1, [r3]	;save result
	MOV pc,lr

TEMPADDR1 & &00004000
	END