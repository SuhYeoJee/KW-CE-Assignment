module mp_next_state(reset_n, cur_state, next_state, op_start,op_done, interrupt);//[project] next state logic
	input reset_n, op_start,op_done, interrupt;
	input [3:0] cur_state;
	output reg [3:0] next_state;
	
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
	
	
	always @* begin	
		case(cur_state)
			INIT: begin
				if(reset_n==1'b0) next_state = INIT;
				else if(op_start==1'b1) next_state = OP_READ;
				else next_state = INIT; 
			end
			OP_READ: begin
				if(reset_n==1'b0) next_state = INIT;
				else next_state = OP_WAIT1;
			end
			OP_WAIT1: begin
				if(reset_n==1'b0) next_state = INIT;
				else next_state = RA_READ;
			end
			RA_READ: begin
				if(reset_n==1'b0) next_state = INIT;
				else next_state = RB_READ;
			end
			RB_READ: begin
				if(reset_n==1'b0) next_state = INIT;
				else next_state = OP_WAIT2;
			end
			OP_WAIT2: begin
				if(reset_n==1'b0) next_state = INIT;
				else next_state = OP_CAL;
			end
			OP_CAL: begin
				if(reset_n==1'b0) next_state = INIT;
				else if(op_done==1'b1) next_state = SELECT;
				else next_state = OP_CAL;
			end
			SELECT: begin
				if(reset_n==1'b0) next_state = INIT;
				else if(interrupt == 1'b1) next_state = RESULT;
				else next_state = OP_READ;
			end
			RESULT: begin
				if(reset_n==1'b0) next_state = INIT;
				else next_state = RESULT;
			end
			default: next_state = 3'bx;
		endcase
	end
endmodule