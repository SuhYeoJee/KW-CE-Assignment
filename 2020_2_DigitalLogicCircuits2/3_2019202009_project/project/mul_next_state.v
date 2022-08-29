module mul_next_state(state, next_state, op_start, count, op_clear, op_done);//[Lab09] next state logic
	input op_start, op_clear;
	input [1:0] state;
	input [31:0] count;
	output reg  op_done;
	output reg [1:0] next_state;
	
	//STATE ENCODING
	parameter INIT 	= 2'b00;
	parameter MUL 		= 2'b01;
	parameter RESULT 	= 2'b10;
	
	always @* begin
		case(state)	//for each state
			INIT: begin
				op_done = 1'b0;
				if((op_start==1'b1)&(op_clear==1'b0)) next_state = MUL;
				else next_state = INIT;	//no start signal
			end
			MUL: begin
				op_done = 1'b0;
				if(op_clear==1'b1) next_state = INIT;	//clear
				else if(count[30]==1'b1) next_state = RESULT; //finish
				else next_state = MUL; //continue
			end
			RESULT: begin
				op_done = 1'b1;
				if(op_clear==1'b1) next_state = INIT;
				else next_state = RESULT; //stay clear signal
			end
			default : next_state = 1'bx;
		endcase
	end
	
endmodule