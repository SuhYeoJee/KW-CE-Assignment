`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:  KWU
// Engineer: SWL
// 
// Create Date:    03/17/2021 
// Module Name:    MyControl 
// Project Name:   Single Cycle Processor
//
// Revision: 
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module MyControl(op,func,RegDst,Jump,Branch,MemtoReg,ALUop,ALUsrc,ALUctrl,MemWrite,DatWidth,RegWrite,RegDatSel,ExtMode);
	input [5:0] op, func;
	output reg MemtoReg, ExtMode, MemWrite, RegWrite;
	output reg [1:0] RegDst, RegDatSel, Jump, DatWidth, ALUsrc;
	output reg [2:0] Branch;
	output reg [4:0] ALUop; 
	output reg [3:0] ALUctrl;

	always@(*) begin
		if(op==6'b000000) begin   // R_TYPE
			if (func==6'b101010) begin    // R-type slt	//$d = ($s < $t)
				ALUop    = 5'b10000;		//Set Less Than
				ALUctrl  = 4'b0000;
				RegDst   = 2'b01;		//$rd
				ALUsrc   = 2'b00;		//$rt
				RegWrite = 1'b1;    	//register write enable
				MemtoReg = 1'b0;    
				MemWrite = 1'b0;    
			  DatWidth = 2'b00;
				Jump     = 2'b00;    // pc+4
				Branch   = 3'b000;    
				RegDatSel= 2'b00;		//alu result
				ExtMode  = 1'bx;
			end
			else if (func==6'b100111) begin    // R-type nor	//$d = ~($s|$t)
				ALUop    = 5'b00010;		// bitwise nor
				ALUctrl  = 4'b0000;
				RegDst   = 2'b01;		//$rd
				ALUsrc   = 2'b00;		//$rt
				RegWrite = 1'b1;   	//register write enable
				MemtoReg = 1'b0;    
				MemWrite = 1'b0;    
			  DatWidth = 2'b00;
				Jump     = 2'b00;    //pc+4
				Branch   = 3'b000;
				RegDatSel= 2'b00;		//alu result
				ExtMode  = 1'bx; 
			end
			else if(func==6'b000111) begin // R-type srav		// $d = $t >>> $s
				ALUop    = 5'b01111;	//Shift Right Arithmatic
				ALUctrl  = 4'b0011;	//Exchanged alu input, shift = $rs
				RegDst   = 2'b01;   	//$rd
				ALUsrc   = 2'b00;    //$rt
				RegWrite = 1'b1;   	//register write enable
				MemtoReg = 1'b0;   
				MemWrite = 1'b0;   
			DatWidth = 2'b00;
				Jump     = 2'b00;    //pc+4   
				Branch   = 3'b000;     
				RegDatSel= 2'b00;		//alu result
				ExtMode  = 1'bx;
			end
			else if(func==6'b011000) begin // R-type mult	// hi:lo = $s * $t
				ALUop    = 5'b01001;	// a x b
				ALUctrl  = 4'b0000;
				RegDst   = 2'bxx;   
				ALUsrc   = 2'b00;    //$rt
				RegWrite = 1'b0;   
				MemtoReg = 1'b0;  
				MemWrite = 1'b0;  
			DatWidth = 2'b00;
				Jump     = 2'b00;      //pc+4
				Branch   = 3'b000;    
				RegDatSel= 2'bxx;
				ExtMode  = 1'bx; 
			end
			else if(func==6'b010010) begin // R-type mflo 	// $d = lo
				ALUop    = 5'bxxxxx;
				ALUctrl  = 4'bxxxx;
				RegDst   = 2'b01;   	//$rd
				ALUsrc   = 2'bxx;    
				RegWrite = 1'b1;   	//register write enable
				MemtoReg = 1'b0;  
				MemWrite = 1'b0;  
			DatWidth = 2'b00;
				Jump     = 2'b00;      //pc+4
				Branch   = 3'b000;    
				RegDatSel= 2'b01;		// lo
				ExtMode  = 1'bx; 
			end
			else if(func==6'b001000) begin // R-type jr	// pc = $s
				ALUop    = 5'bxxxxx;
				ALUctrl  = 4'bxxxx;
				RegDst   = 2'bxx;   
				ALUsrc   = 2'bxx;    
				RegWrite = 1'bx;  
				MemtoReg = 1'bx;  
				MemWrite = 1'bx;  
			DatWidth = 2'b00;
				Jump     = 2'b10;      // User $rs
				Branch   = 3'bxxx;    
				RegDatSel= 2'bxx;
				ExtMode  = 1'bx; 
			end 
			else begin    // UNDEFINED INSTRUCTION. DO NOT MODIFY.
				ALUop    = 5'bxxxxx; RegDst   = 2'bxx; ALUsrc   = 2'bxx;
				RegWrite = 1'bx;     MemtoReg = 1'bx;  MemWrite = 1'bx;    
			  DatWidth = 2'bxx;    Jump     = 2'bxx; Branch   = 3'bxxx;
			  RegDatSel= 2'bxx;    ExtMode  = 1'bx;  ALUctrl  = 4'bxxxx;
			end
		end
		else if(op==6'b000100) begin // beq		// if($s = $t) pc += i<<2
			ALUop    = 5'b00110;  // a - b
 			ALUctrl  = 4'b0000;
			RegDst   = 2'bxx;
			ALUsrc   = 2'b00;     //$rt
			RegWrite = 1'b0;   
			MemtoReg = 1'b0;   
			MemWrite = 1'b0;   
      DatWidth = 2'bxx;
			Jump     = 2'b00;      //pc+4 or pc+imm
			Branch   = 3'b100;    
			RegDatSel= 2'bxx;
			ExtMode  = 1'b1;		//immediate extension
		end
		else if(op==6'b001000) begin // addi	//$t = $s + SE(i)
			ALUop    = 5'b00100;	// a + b
 			ALUctrl  = 4'b0000;
			RegDst   = 2'b00;   // $rt
			ALUsrc   = 2'b01;    //immediate
			RegWrite = 1'b1;  	//register write enable
			MemtoReg = 1'b0;  
			MemWrite = 1'b0;  
      DatWidth = 2'b00;
			Jump     = 2'b00;      //pc+4
			Branch   = 3'b000;    
			RegDatSel= 2'b00;			//alu result
			ExtMode  = 1'b1; 		//immediate extension
		end 
		else if(op==6'b000011) begin // jal		// $31 = pc; pc += i<<2
			ALUop    = 5'bxxxxx;
 			ALUctrl  = 4'bxxxx;
			RegDst   = 2'b10;   //$r31
			ALUsrc   = 2'bxx;    
			RegWrite = 1'b1;  	//register write enable
			MemtoReg = 1'b0;  
			MemWrite = 1'b0;  
      DatWidth = 2'b00;
			Jump     = 2'b00;     // pc + imm
			Branch   = 3'b011;    
			RegDatSel= 2'b11;		//pc
			ExtMode  = 1'b1; 	//immediate extension
		end 
		else if(op==6'b000111) begin // bgtz	// if($s>0) pc += i<<2
			ALUop    = 5'b10000;	// Set less than
 			ALUctrl  = 4'b0010;	// exchanged alu input
			RegDst   = 2'bxx;   
			ALUsrc   = 2'b10;    //zero
			RegWrite = 1'b0;  
			MemtoReg = 1'b0;  
			MemWrite = 1'b0;  
      DatWidth = 2'b00;
			Jump     = 2'b00;      //pc+4 or pc+imm
			Branch   = 3'b101;    
			RegDatSel= 2'bxx;
			ExtMode  = 1'b1; 		//immediate extension
		end 
		else if(op==6'b001110) begin // xori	// $t = $s^ZE(i)
			ALUop    = 5'b00011;	//bitwise xor
 			ALUctrl  = 4'b0000;
			RegDst   = 2'b00;  	//$rt
			ALUsrc   = 2'b01;    //immediate
			RegWrite = 1'b1;  	//register write enable
			MemtoReg = 1'b0;  
			MemWrite = 1'b0;  
      DatWidth = 2'b00;
			Jump     = 2'b00;      //pc+4
			Branch   = 3'b000;    
			RegDatSel= 2'b00;		//alu result
			ExtMode  = 1'b0; 		//immediate extension
		end
		else if(op==6'b001010) begin // slti	// $t = ($s<SE(i))
			ALUop    = 5'b10000;	// set less than
 			ALUctrl  = 4'b0000;
			RegDst   = 2'b00;   //$rt
			ALUsrc   = 2'b01;    //immediate
			RegWrite = 1'b1;  	//register write enable
			MemtoReg = 1'b0;  
			MemWrite = 1'b0;  
      DatWidth = 2'b00;
			Jump     = 2'b00;      //pc+4
			Branch   = 3'b000;    
			RegDatSel= 2'b00;		//alu result
			ExtMode  = 1'b1; 		//immediate extension
		end 
		else begin   // UNDEFINED INSTRUCTION. DO NOT MODIFY.
			ALUop    = 5'bxxxxx; RegDst   = 2'bxx; ALUsrc   = 2'bxx;  
			RegWrite = 1'bx;     MemtoReg = 1'bx;  MemWrite = 1'bx;
      DatWidth = 2'bxx;    Jump     = 2'bxx; Branch   = 3'bxxx;  
			RegDatSel= 2'bxx;    ExtMode  = 1'bx;  ALUctrl  = 4'bxxxx;
		end
	end
endmodule
