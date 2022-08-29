module fifo(clk, reset_n, rd_en, wr_en, d_in, d_out, full, empty, 
			wr_ack, wr_err, rd_ack, rd_err, data_count); //[LAB08] top module
	input clk, reset_n, rd_en, wr_en;
	input [31:0] d_in;
	output full, empty, wr_ack, wr_err, rd_ack, rd_err;
	output [3:0] data_count;
	output [31:0] d_out;
	wire we, re;
	wire [2:0] state, head, tail, next_state, next_head, next_tail;
	wire [3:0] data_count, next_data_count;
	wire [31:0] rData1, rData2;
	
	//next state logic
	fifo_ns U0_fifo_ns(.wr_en(wr_en), .rd_en(rd_en), .state(state), 
			.data_count(data_count), .next_state(next_state));
	//calculate address logic
	fifo_cal_addr U1_fifo_cal_addr(.state(next_state), .head(head), .tail(tail), 
			.data_count(data_count), .we(we), .re(re), 
			.next_head(next_head), .next_tail(next_tail), .next_data_count(next_data_count));
	//output logic
	fifo_out U2_fifo_out(.state(state), .data_count(data_count), 
			.full(full), .empty(empty), 
			.wr_ack(wr_ack), .wr_err(wr_err), .rd_ack(rd_ack), .rd_err(rd_err));
	//register file
	Register_file U3_Register_file(.clk(clk), .reset_n(reset_n), 
			.wData(d_in),.wAddr(tail),.we(we),
			.rData(rData1),.rAddr(head));
	//register
	register3_r U4_state_register(.clk(clk), .reset_n(reset_n), .d_in(next_state), .d_out(state));
	register4_r U5_data_count_register(.clk(clk), .reset_n(reset_n), .d_in(next_data_count), .d_out(data_count));
	register3_r U6_head_register(.clk(clk), .reset_n(reset_n), .d_in(next_head), .d_out(head));
	register3_r U7_tail_register(.clk(clk), .reset_n(reset_n), .d_in(next_tail), .d_out(tail));
	
	assign rData2 = (re==1)? rData1 : 32'b0; //output enable
	_dff_r U8_dff_r(.clk(clk), .reset_n(reset_n),.d(rData2),.q(d_out));
	
endmodule