cr EQU 0x0d
	
	AREA strcpy, CODE, READONLY
		ENTRY
main
	ADR r0, Table	;r0 = address of string
	LDR r1, TEMPADDR1 ;to save strcpy result

Loop
	LDRB r2, [r0], #1	; read one byte
	STRB r2, [r1], #1	; copy 1 byte
	CMP r2, #cr			; string already copied
	BEQ Done			; r2==cr : break
	B  Loop			; to read next byte
	
Done
	MOV pc,#0

TEMPADDR1 & &40000000
Table
	ALIGN
	DCB "Why so serious?",cr

	END