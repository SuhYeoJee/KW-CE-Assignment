	AREA ARMex, CODE, READONLY
		ENTRY

start
	LDR r0, TEMPADDR1
	;MOV r1, #0x41E26666: 28.3
	MOV r1, #0x41
	LSL r1, #8
	ADD r1, r1, #0xE2
	LSL r1, #8
	ADD r1, r1, #0x66
	LSL r1, #8
	ADD r1, r1, #0x66
	
	;MOV r2, #0xBFE00000: 1.75
	MOV r2, #0xBF
	LSL r2, #8
	ADD r2, r2, #0xE0
	LSL r2, #8
	LSL r2, #8
	
	;save at memory
	STR r1, [r0], #4
	STR r2, [r0]


	;start
	;0) load data
	LDR r2, TEMPADDR1
	LDR r0, [r2], #4
	LDR r1, [r2]
	
	;floating-point add/subtraction
	;1) get bit data
	
	;r10,r11,r12: to get sign, Exponent, Mantissa
	MOV r10, #1			;sign bit is 1bit
	MOV r11, #0xFF		;Exponent bit is 8bit
	MOV r12, #0x7F		;Mantissa bit is 23bit
	LSL r12, #8
	ADD r12, r12, #0xFF
	LSL r12, #8
	ADD r12, r12, #0xFF
	
	;r4,r5,r6 = r0's sign, Exponent, Mantissa
	MOV r3, r0
	LSR r3, #31
	AND r4, r10, r3	;r4 is r0's sign bit
	
	MOV r3, r0
	LSR r3, #23
	AND r5, r11, r3 ;r5 is r0's exponent bit
	
	MOV r3, r0
	AND r6, r12, r3 ;r6 is r0's mantissa bit
	
	;r7,r8,r9 = r1's sign, Exponent, Mantissa
	MOV r3, r1
	LSR r3, #31
	AND r7, r10, r3	;r7 is r1's sign bit
	
	MOV r3, r1
	LSR r3, #23
	AND r8, r11, r3 ;r8 is r1's exponent bit
	
	MOV r3, r1
	AND r9, r12, r3 ;r9 is r1's mantissa bit
	
	;2) add 1 -> 1.Mantissa form
	;maintissa is 23bit data, so add 1 at 23th bit
	MOV r10, #8
	LSL r10, #20
	ADD r6, r6, r10
	ADD r9, r9, r10	;r10 is 23th bit
	
	;3) CMP exponent
	SUBS r11, r5, r8
	LSRMI r6, r11	;r5<r8
	MOVMI r11, r8	;r11 is result's exponent
	LSRHI r9, r11	;r5>r8
	MOVHI r11, r5
	
	;4) ADD/SUB
	CMP r4, r7
	ADDEQ r12, r6, r9 ;r12 is result's mantissa
	SUBNE r12, r6, r9
	
	;5) Normalize mantissa
	CMP r12,r10
Normalize
	BCS Break	;1x.xxx or 1.xxx
	LSL r12, #1
	MOV r0, r10
	AND r0, r0, r12
	CMP r0, r10
	B Normalize
Break
	MOV r0, r10
	LSL r0, #1
	AND r0, r0, r12
	CMP r0, #0
	LSRNE r12, #1 ;1x.xxx -> 1.xxx
	SUB r12, r10 ;1.mantissa - 1 -> 0.mantissa
	
	;6) get result
	; r11: exponent, r12: mantissa
	
	;get sign bit
	CMP r5, r8
	MOVHI r10, r4 ;r10: sign bit
	BHI result
	MOVMI r10, r7
	BMI result
	CMP r6,r9 	; same exponent -> cmp mantissa
	MOVHI r10, r4
	BHI result
	MOVMI r10, r7

result
	MOV r1, r10 ;sign bit
	LSL r1, #8
	ADD r1, r1, r11 ;exponent
	LSL r1, #23
	ADD r1, r1, r12 ;mantissa
	
	LDR r2, TEMPADDR2	;save at memory
	STR r1, [r2]
	
	MOV pc,#0

TEMPADDR1 & &30000000
TEMPADDR2 & &40000000
	END