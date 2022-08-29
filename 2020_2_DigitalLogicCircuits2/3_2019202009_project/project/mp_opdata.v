module mp_opdata(cur_state, w_rData, cur_op, cur_Ra, cur_Rb, next_op, next_Ra, next_Rb);//[project] data to calculate
	input [3:0] cur_state;
	input [15:0] cur_op;
	input [31:0] cur_Ra, cur_Rb;
	input [63:0] w_rData;
	output reg [15:0] next_op;
	output reg [31:0] next_Ra, next_Rb;
	
	//state encoding
	parameter INIT			= 4'b0000;
	parameter OP_READ		= 4'b0001;
	parameter OP_WAIT1	= 4'b0010;
	parameter RA_READ		= 4'b0011;
	parameter RB_READ 	= 4'b0100;
	parameter OP_WAIT2 	= 4'b0101;
	parameter OP_CAL		= 4'b0110;
	parameter SELECT 		= 4'b0111;
	parameter OP_WAIT3 	= 4'b1000;
	parameter RESULT		= 4'b1001;
	
	always@ (*) begin
		case(cur_state)
			INIT : begin //init: save data
				next_op = 16'b0;
				next_Ra = 32'b0;
				next_Rb = 32'b0;
			end
			OP_WAIT1	:	begin //op_READ: get command, 
				next_op = w_rData[15:0];
				next_Ra = 32'b0;
				next_Rb = 32'b0;
			end
			RB_READ	:	begin //RA_READ: get RA, 
				next_op = cur_op;
				next_Ra = w_rData[31:0];
				next_Rb = 32'b0;
			end
			OP_WAIT2	:	begin //RB_READ: get RB, 
				next_op = cur_op;
				next_Ra = cur_Ra;
				next_Rb = w_rData[31:0];
			end
			default : begin
				next_op = cur_op;
				next_Ra = cur_Ra;		
				next_Rb = cur_Rb;	
			end
		endcase
	end
endmodule