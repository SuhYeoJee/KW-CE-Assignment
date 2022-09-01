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
      if (i_funct==6'bxxxxxx) begin
        o_state = 8'bxxxxxxxx;       //   MICRO_ROM address
      end
      else if (i_funct==6'bxxxxxx) begin  
        o_state = 8'bxxxxxxxx;
      end
      else begin
        o_state = 8'bxxxxxxxx;
      end
    end                              /////// Other Instructions
    else if (i_op==6'bxxxxxx) begin  
      o_state = 8'bxxxxxxxx;
    end
    else if (i_op==6'bxxxxxx) begin  
      o_state = 8'bxxxxxxxx;
    end
    else begin
      o_state = 8'bxxxxxxxx;
    end
  end
endmodule

//////////////////////////////////////////////////////////////////////////////////
