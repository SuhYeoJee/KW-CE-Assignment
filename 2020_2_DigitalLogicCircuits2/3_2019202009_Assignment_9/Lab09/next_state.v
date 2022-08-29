module next_state(state, next_state, op_start, count, op_clear);//[Lab09] next state logic
	input [1:0] state; 
	input [63:0] count;
	input op_start, op_clear;
	output reg [1:0] next_state;
	
	//STATE ENCODING
	parameter INIT = 2'b00;	
	parameter LOAD = 2'b01;
	parameter MUL 	= 2'b10;
	parameter STAY = 2'b11;
	
	always @ (state or op_start or op_clear or count) begin
		case(state)	//for each state
			INIT: begin
				if((op_start==1'b1)&(op_clear==1'b0)) next_state = LOAD; //to load data
				else next_state = INIT;	//no start signal
			end
			LOAD: begin
				if(op_clear==1'b1) next_state = INIT; //clear
				else next_state = MUL;	//calculate
			end
			MUL: begin
				if(op_clear==1'b1) next_state = INIT;	//clear
				else if(count[63]==1'b1) next_state = STAY; //finish
				else next_state = MUL; //continue
			end
			STAY: begin
				if(op_clear == 1'b1) next_state = INIT; //clear
				else next_state = STAY;
			end
		endcase
	end
	
endmodule