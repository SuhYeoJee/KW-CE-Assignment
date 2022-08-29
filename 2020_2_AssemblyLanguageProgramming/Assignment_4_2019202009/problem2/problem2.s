	AREA subrout, CODE, READONLY
		ENTRY

start
	MOV r0, #10 ;save data
	MOV r1, #11 
	MOV r2, #12 
	MOV r3, #13 
	MOV r4, #14 
	MOV r5, #15 
	MOV r6, #16 
	MOV r7, #17 
	
	LDR r8, TEMPADDR1
	
	STMIA r8, {r0-r7} ;save at memory
	
	BL doRegister
	BL doGCD
	BL doADD
	
	LDR r8, TEMPADDR1 ; save at memory
	STMIA r8!, {r9} ; GCD
	STMIA r8, {r0-r7} ;r0-r7
	B stop
	
doRegister
	ADD r0, r0, #0 ;r' - add index
	ADD r1, r1, #1 
	ADD r2, r2, #2 
	ADD r3, r3, #3 
	ADD r4, r4, #4 
	ADD r5, r5, #5 
	ADD r6, r6, #6 
	ADD r7, r7, #7 
	
	MOV r9, #0 ; sum of r0'~r7'
	ADD r9, r9, r0
	ADD r9, r9, r1
	ADD r9, r9, r2
	ADD r9, r9, r3
	ADD r9, r9, r4
	ADD r9, r9, r5
	ADD r9, r9, r6
	ADD r9, r9, r7
	MOV pc, lr
	
doGCD
	MOV r10, #160
	MOV r11, r9
loop 	;get remainder		;r = a%b
	SUB r11, r11, r10
	CMP r11, #0
	BLE endloop 
	B loop
endloop
	ADDLT r11, r11, r10
	MOV r9, r10				;a = b
	MOV r10, r11			;b = r
	MOV r11, r9	 ;to get next remainder

	CMP r10, #0	
	MOVEQ pc,lr ; when r9 is GCD, return
	B loop
	
doADD
	LDMIA r8!, {r12}	;get r
	ADD r0, r0, r12		; r* = r + r'
	LDMIA r8!, {r12}
	ADD r1, r1, r12
	LDMIA r8!, {r12}
	ADD r2, r2, r12
	LDMIA r8!, {r12}
	ADD r3, r3, r12
	LDMIA r8!, {r12}
	ADD r4, r4, r12
	LDMIA r8!, {r12}
	ADD r5, r5, r12
	LDMIA r8!, {r12}
	ADD r6, r6, r12
	LDMIA r8!, {r12}
	ADD r7, r7, r12
	MOV pc, lr
	
stop
	MOV pc, #0	

TEMPADDR1 &  &00040000
	END