	AREA ARMex, CODE, READONLY
		ENTRY
;using n(n+10)
start
	MOV r0, #1
	LSL r1,r0,r0 ;r1==2
	LSL r2,r1,r1 ;r2==8
	ADD r0,r1,r2 ;r0==10
	LDR r3,TEMPADDR1
	
	MOV r1,r0	 ;n = r1==10
	ADD r2,r1,r0 ;n+10
	MUL r0,r1,r2 ;n(n+10)
	STRH r0, [r3] ;save result

TEMPADDR1 & &00004000
	END