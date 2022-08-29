module ns_logic(load, inc, state, next_state); //next state logic
	parameter IDLE_STATE = 3'b000;
	parameter LOAD_STATE = 3'b001;
	parameter INC_STATE 	= 3'b010;
	parameter INC2_STATE = 3'b011;
	parameter DEC_STATE 	= 3'b100;
	parameter DEC2_STATE = 3'b101;
	
	input	load, inc;
	input [2:0] state;
	output [2:0] next_state;
	reg [2:0] next_state;
	
	always@(load, inc, state) // when input changes
	begin
	case(state)			//sub case (load/inc(dec))
		IDLE_STATE	:	//load > inc
			if(load==1)			next_state <= LOAD_STATE;
			else if(inc==1)	next_state <= INC_STATE;
			else if(inc==0)	next_state <= DEC_STATE;
			else next_state<=3'bx;
		LOAD_STATE	:
			if(load==1)			next_state <= LOAD_STATE;
			else if(inc==1)	next_state <= INC_STATE;
			else if(inc==0)	next_state <= DEC_STATE;
			else next_state<=3'bx;
		INC_STATE	:
			if(load==1)			next_state <= LOAD_STATE;
			else if(inc==1)	next_state <= INC2_STATE;
			else if(inc==0)	next_state <= DEC_STATE;
			else next_state<=3'bx;
		INC2_STATE	:
			if(load==1)			next_state <= LOAD_STATE;
			else if(inc==1)	next_state <= INC_STATE;
			else if(inc==0)	next_state <= DEC_STATE;
			else next_state<=3'bx;
		DEC_STATE	:
			if(load==1)			next_state <= LOAD_STATE;
			else if(inc==1)	next_state <= INC_STATE;
			else if(inc==0)	next_state <= DEC2_STATE;
			else next_state<=3'bx;
		DEC2_STATE	:
			if(load==1)			next_state <= LOAD_STATE;
			else if(inc==1)	next_state <= INC_STATE;
			else if(inc==0)	next_state <= DEC_STATE;
			else next_state<=3'bx;
		default		:	next_state<=3'bx;
	endcase
	end
endmodule