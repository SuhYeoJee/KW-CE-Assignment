`timescale 1ns/100ps
module tb_cntr8;
	reg tb_clk, tb_reset_n, tb_inc, tb_load;
	reg [7:0] tb_d_in;
	wire [7:0] tb_d_out;
	wire [2:0] tb_o_state;
	
	//module instance
	cntr8 U0_cntr8(.d_in(tb_d_in),.inc(tb_inc),.load(tb_load),.o_state(tb_o_state),
					.d_out(tb_d_out),.clk(tb_clk),.reset_n(tb_reset_n));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 1; tb_reset_n=0; tb_d_in=8'b0; tb_load=0;tb_inc=0;
	#23; tb_reset_n=1; tb_inc=1;
	#50; tb_inc=0;
	#50; tb_load=1; tb_d_in = 8'b01000100;
	#20; tb_load=0; tb_d_in=0; tb_inc=1;
	#40; tb_reset_n=0; tb_inc=0;
	#10; tb_reset_n=1;
	#40; $stop;
	end
endmodule