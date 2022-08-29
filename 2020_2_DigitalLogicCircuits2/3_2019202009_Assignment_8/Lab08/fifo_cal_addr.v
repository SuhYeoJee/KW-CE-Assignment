module fifo_cal_addr(state, head, tail, data_count, we, re,
		next_head, next_tail, next_data_count);//[LAB08] calculate address logic
	input [2:0] state, head, tail;
	input [3:0] data_count;
	output reg we, re;
	output reg [2:0] next_head, next_tail;
	output reg [3:0] next_data_count;
	
	//state encoding
	parameter INIT 	= 3'b000;	
	parameter NO_OP 	= 3'b001;
	parameter READ 	= 3'b010;
	parameter RD_ERROR = 3'b011;
	parameter WRITE 	= 3'b100;
	parameter WR_ERROR = 3'b101;
	
	always @ (state or data_count or head or tail)begin
		case(state)	//for each state
			INIT: begin
				we=0;re=0;
				next_data_count=0;
				next_head=3'b000;
				next_tail=3'b000;
			end
			NO_OP: begin
				we=0;re=0;
				next_data_count=data_count;
				next_head=head;
				next_tail=tail;
			end
			READ: begin
				we=0;re=1;
				next_data_count=data_count-3'b1;
				if(head<7) next_head=head+3'b1;
				if(head==7) next_head=0;
				next_tail=tail;
			end
			RD_ERROR: begin
				we=0;re=0;
				next_data_count=data_count;
				next_head=head;
				next_tail=tail;
			end
			WRITE:begin
				we=1;re=0;
				next_data_count=data_count+3'b1;
				if(tail<7) next_tail=tail+3'b1;
				if(tail==7) next_tail=0;
			end
			WR_ERROR:begin
				we=0;re=0;
				next_data_count=data_count;
				next_head=head;
				next_tail=tail;
			end
			default: begin
				we=1'bx; re=1'bx;
				next_data_count=3'bxxx;
			end
		endcase
	end
endmodule