module read_operation (clk, Addr, Data, 
		from_reg0, from_reg1, from_reg2, from_reg3, from_reg4, from_reg5, from_reg6, from_reg7,
		from_reg8, from_reg9, from_reg10, from_reg11, from_reg12, from_reg13, from_reg14, from_reg15, 
		from_reg16, from_reg17, from_reg18, from_reg19, from_reg20, from_reg21, from_reg22); //[Lab07] rf read
	
	input clk;
	input [63:0] from_reg0, from_reg1, from_reg2, from_reg3, from_reg4, from_reg5, from_reg6, from_reg7,
					from_reg8, from_reg9, from_reg10, from_reg11, from_reg12, from_reg13, from_reg14, from_reg15, 
					from_reg16, from_reg17, from_reg18, from_reg19, from_reg20, from_reg21, from_reg22;
	input [15:0] Addr;
	output reg [63:0] Data;
	
	//16 to 1 MUX (24case - with default)
	always@(posedge clk) //when input changes
	begin 
		case(Addr)
			16'h0100	:	Data=from_reg0;
			16'h0101	:	Data=from_reg1;
			16'h0102	:	Data=from_reg2;
			16'h0103	:	Data=from_reg3;
			16'h0104	:	Data=from_reg4;
			16'h0105	:	Data=from_reg5;
			16'h0106	:	Data=from_reg6;
			16'h0107	:	Data=from_reg7;
			16'h0108	:	Data=from_reg8;
			16'h0109	:	Data=from_reg9;
			16'h0110	:	Data=from_reg10;
			16'h0111	:	Data=from_reg11;
			16'h0112	:	Data=from_reg12;
			16'h0113	:	Data=from_reg13;
			16'h0114	:	Data=from_reg14;
			16'h0115	:	Data=from_reg15;
			16'h0116	:	Data=from_reg16;
			16'h0117	:	Data=from_reg17;
			16'h0118	:	Data=from_reg18;
			16'h0119	:	Data=from_reg19;
			16'h0120	:	Data=from_reg20;
			16'h0121	:	Data=from_reg21;
			16'h0122	:	Data=from_reg22;
			default	: 	Data=32'bx; //`test
		endcase
	end
endmodule