`timescale 1ns/100ps
module tb_fifo;
	reg tb_clk, tb_reset_n, tb_rd_en, tb_wr_en;
	reg [31:0] tb_d_in;
	wire tb_full, tb_empty, tb_wr_ack, tb_wr_err, tb_rd_ack, tb_rd_err;
	wire [3:0] tb_data_count;
	wire [31:0] tb_d_out;

	fifo U0_fifo(.clk(tb_clk), .reset_n(tb_reset_n), .rd_en(tb_rd_en), .wr_en(tb_wr_en),
			.d_in(tb_d_in), .d_out(tb_d_out), .full(tb_full), .empty(tb_empty), 
			.wr_ack(tb_wr_ack), .wr_err(tb_wr_err), .rd_ack(tb_rd_ack), .rd_err(tb_rd_err), .data_count(tb_data_count));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=0; tb_rd_en=0; tb_wr_en = 0; tb_d_in = 32'h0000_0000;
	#8;	tb_reset_n=1;tb_rd_en=1;	//rd_err
	#10;	tb_rd_en=0; tb_wr_en=1; tb_d_in = 32'hffff_ffff; //wr_ack
	#10;	tb_d_in = 32'h1234_5678; //wr_ack
	#10;	tb_d_in = 32'haaaa_1111; //wr_ack
	#10;	tb_rd_en=1; tb_wr_en=0; //rd_ack
	#60; $stop;	//rd_err
	end
endmodule