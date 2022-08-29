	AREA ARMex, CODE, READONLY
	ENTRY
	
start
	LDR r0, tempaddr
	MOV r1, #1 ;Loop count, r4 = r1!
	
Loop				; n! = n * 1 * 2 * ... * (n-1)
	MOV r2, r1
	MOV r3, #1
Loop2	
	MUL r4, r2, r3		; ex) r4 = {n*(1)*(2)} * (3)
	ADD r3, r3, #1
	CMP r1, r3
	BLE break	;r4 = r1!
	MOV r2, r4
	B Loop2
break
	STR r4, [r0], #4	;save memory
	ADD r1, r1, #1
	CMP r1, #11			;end program
	BNE Loop
	
Endline
	MOV pc, lr
	
tempaddr & &40000

END