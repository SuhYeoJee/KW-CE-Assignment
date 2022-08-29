	AREA ARMex, CODE, READONLY
	ENTRY
	
start
	LDR r0, tempaddr
	MOV r1, #1 ;Loop count, r2 = r1!
	
Loop				; n! = n * 1 * 2 * ... * (n-1)
	MOV r2, r1			;r2=a1
	CMP r1, #2
	BLE break		;r1==1 or 2
	
	LSL r2, r2,#1		;a2=a1*2
	CMP r1, #3
	BEQ break		;r1==3
	
	ADD r2,r2,r2,lsl#1	;a3=a2*3
	CMP r1, #4
	BEQ break		;r1==4
	
	LSL r2,r2,#2		;a4=a3*4
	CMP r1, #5
	BEQ break		;r1==5
	
	ADD r2,r2,r2,lsl#2	;a5=a4*5 
	CMP r1, #6
	BEQ break		;r1==6
	
	ADD r3,r2,r2,lsl#2	
	ADD r2,r2,r3		;a6=a5*6
	CMP r1, #7
	BEQ break		;r1==7
	
	ADD r3,r2,r2,lsl#1
	ADD r2,r3,lsl#1		;a7=a6*7
	CMP r1, #8
	BEQ break		;r1==8
	
	LSL r2,#3			;a8=a7*8
	CMP r1, #9
	BEQ break		;r1==9
	
	ADD r2,r2,r2,lsl#3	;a9=a8*9
					;r1==10
break
	STR r2, [r0], #4
	ADD r1, r1, #1
	CMP r1, #11
	BNE Loop
	
Endline
	MOV pc, lr
	
tempaddr & &40000

END