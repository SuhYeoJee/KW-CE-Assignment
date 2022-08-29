`timescale 1ns/100ps
module tb_dff_rs_sync_async;
	reg tb_clk, tb_d, tb_set_n,tb_reset_n;
	wire tb_q_sync, tb_q_async;

	_dff_rs_sync_async U0_dff_rs_sync_async
	(.clk(tb_clk),.set_n(tb_set_n),.reset_n(tb_reset_n),.d(tb_d),.q_sync(tb_q_sync),.q_async(tb_q_async));			
	
	parameter STEP =20;
	always #(STEP/7) tb_clk = ~tb_clk; //clk changes every 20/7 ns
	always #(STEP/5) tb_d = ~tb_d; //data changes every 4 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=0; tb_set_n=0; tb_d = 0; //reset,set signal works (active low)
	#10; tb_set_n=1;		//reset works
	#10; tb_reset_n=1; 	//no reset,set signal
	#10; tb_set_n=0;		//set works
	#10; tb_reset_n=0;	//reset,set signal works
	#10; tb_set_n=1;		//reset works
	#10; tb_reset_n=1; 	//no reset,set signal
	#10; $stop;
	end
endmodule