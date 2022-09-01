`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////
// Company:  KWU
// Engineer: SWL
// 
// Create Date:    03/20/2021 
// Module Name:    My_State_ROM 
// Project Name:   Multi-Cycle Processor
//
// Revision: 
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module My_State_ROM (i_op, i_funct, o_state);
  input [5:0] i_op, i_funct;
  output reg [7:0] o_state; 
  
  always @(*) begin
    if (i_op==6'b000000) begin        //////// R-type Instructions
      if (i_funct==6'b011000) begin  //mult
        o_state = 8'b00010000;       //   MICRO_ROM address 
      end
		else if (i_funct==6'b100111) begin  //nor
        o_state = 8'b00000110;
      end
		else if (i_funct==6'b000111) begin  //srav
        o_state = 8'b00001100;
      end
		else if (i_funct==6'b101010) begin  //slt
        o_state = 8'b00001000;
      end
		else if (i_funct==6'b001000) begin  //jr
        o_state = 8'b00000011;  
      end
		else if (i_funct==6'b010010) begin  //mflo
        o_state = 8'b00010011;
      end
      else begin
        o_state = 8'bxxxxxxxx;
      end
    end                              /////// Other Instructions
    else if (i_op==6'b001000) begin  //addi
      o_state = 8'b00001110;
    end
    else if (i_op==6'b001110) begin  //xori
      o_state = 8'b00010001;
    end
	 else if (i_op==6'b001010) begin  //slti
      o_state = 8'b00001010;
    end
	 else if (i_op==6'b000100) begin  //beq
      o_state = 8'b00000100; 
    end
	 else if (i_op==6'b000111) begin  //bgtz
      o_state = 8'b00000101; 
    end
	 else if (i_op==6'b000011) begin  //jal
      o_state = 8'b00000010; 
    end
    else begin
      o_state = 8'bxxxxxxxx; 
    end
  end
endmodule

//////////////////////////////////////////////////////////////////////////////////
