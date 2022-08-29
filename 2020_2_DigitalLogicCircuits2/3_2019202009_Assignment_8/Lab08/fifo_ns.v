module fifo_ns ( wr_en, rd_en, state, data_count, next_state);//[LAB08] next state logic
	input wr_en, rd_en;
	input [2:0] state;
	input [3:0] data_count;
	output reg [2:0] next_state;
	
	//state encoding
	parameter INIT 	= 3'b000;
	parameter NO_OP 	= 3'b001;
	parameter READ 	= 3'b010;
	parameter RD_ERROR = 3'b011;
	parameter WRITE 	= 3'b100;
	parameter WR_ERROR = 3'b101;
	
	always @ (wr_en or rd_en or data_count)begin
		if(rd_en==1) begin
			if(data_count==0) next_state=RD_ERROR;	//no data in fifo
			else if(data_count>0) next_state=READ;	
			else next_state=3'bxxx;
			end
		else if(wr_en==1) begin
			if(data_count==8) next_state=WR_ERROR;	//no empty register
			else if(data_count<8) next_state=WRITE;
			else next_state=3'bxxx;
			end
		else next_state=NO_OP;
		end
endmodule