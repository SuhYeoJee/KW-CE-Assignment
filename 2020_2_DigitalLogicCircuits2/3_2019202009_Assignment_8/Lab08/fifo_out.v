module fifo_out(state, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err);
	//[LAB08] output logic
	input [2:0] state;
	input [3:0] data_count;
	output reg full, empty, wr_ack, wr_err, rd_ack, rd_err;

	//state encoding
	parameter INIT 	= 3'b000;
	parameter NO_OP 	= 3'b001;
	parameter READ 	= 3'b010;
	parameter RD_ERROR = 3'b011;
	parameter WRITE 	= 3'b100;
	parameter WR_ERROR = 3'b101;
	
	always @ (state or data_count)begin
		case(state)	//for each state
			INIT: begin
				wr_ack=0; wr_err=0;
				rd_ack=0; rd_err=0;
			end
			NO_OP: begin
				wr_ack=0; wr_err=0;
				rd_ack=0; rd_err=0;
				end
			READ: begin
				wr_ack=0; wr_err=0;
				rd_ack=1; rd_err=0;
				end
			RD_ERROR: begin
				wr_ack=0; wr_err=0;
				rd_ack=0; rd_err=1;
				end
			WRITE:begin
				wr_ack=1; wr_err=0;
				rd_ack=0; rd_err=0;
				end
			WR_ERROR:begin
				wr_ack=0; wr_err=1;
				rd_ack=0; rd_err=0;
				end
			default: begin
				wr_ack=1'bx; wr_err=1'bx;
				rd_ack=1'bx; rd_err=1'bx;
				end
		endcase
		
		if(data_count==0) begin
			empty=1; full=0;
			end
		else if(data_count==3'b100) begin
			empty=0; full=1;
			end
		else begin
			empty=0; full = 0;
			end
		end
endmodule

