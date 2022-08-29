	AREA subrout, CODE, READONLY
		ENTRY
start 
	MOV r0, #0 ;save data
	MOV r1, #1
	MOV r2, #2
	MOV r3, #3
	MOV r4, #4
	MOV r5, #5
	MOV r6, #6
	MOV r7, #7
	
	LDR sp, TEMPADDR1 ;start address
	
	STMFA sp!, {r2} ;stack insert
	STMFA sp!, {r0}
	STMFA sp!, {r3}
	STMFA sp!, {r5-r7}
	STMFA sp!, {r1}
	STMFA sp!, {r4}
	
	LDMFA sp!, {r0-r7} ;stack pop
	
	MOV pc, #0
TEMPADDR1 & &00040000
	END