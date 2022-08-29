module mp_select(cur_state, opcode, alu_result, mul_result, to_Rd, w_we ); //[project] select operation result
	input [3:0] cur_state;
	input [3:0] opcode;
	input [63:0] alu_result, mul_result;
	output reg w_we;
	output reg [63:0] to_Rd;
	
	//state encoding
	parameter INIT			= 4'b0000;
	parameter OP_READ		= 4'b0001;
	parameter OP_WAIT1	= 4'b0010;
	parameter RA_READ		= 4'b0011;
	parameter RB_READ 	= 4'b0100;
	parameter OP_WAIT2 	= 4'b0101;
	parameter OP_CAL		= 4'b0110;
	parameter SELECT 		= 4'b0111;
	parameter RESULT 		= 4'b1000;
	
	
	always@ (*) begin
		case(cur_state)
			INIT : begin //init: save data
				w_we <= 1'b1;
			end
			SELECT: begin 		//select output, save at Rd
				if(opcode == 4'b0) begin //NOP
					w_we = 1'b0; //don't write
					to_Rd = 64'bx;
				end
				else if(opcode[3] == 1'b0) begin //use alu result
					w_we = 1'b1; //write ad Rd
					to_Rd = alu_result;
				end
				else if(opcode[3] == 1'b1) begin //use mul result
					w_we = 1'b1;
					to_Rd = mul_result;
				end
				else begin
					w_we = 1'bx;
					to_Rd = 64'bx;
				end
			end
			RESULT : begin //result: write interrupt 1
				w_we = 1'b1; //write
			end
			default begin
				w_we = 1'b0; //read
				to_Rd = 64'bx;
			end
		endcase
	end
endmodule