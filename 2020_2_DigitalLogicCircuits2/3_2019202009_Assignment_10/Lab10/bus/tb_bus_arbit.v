`timescale 1ns/100ps
module tb_bus_arbit;
	reg tb_clk, tb_reset_n, tb_m1_req, tb_m0_req;
	wire tb_m1_grant, tb_m0_grant;
	
	bus_arbit U0(.clk(tb_clk), .reset_n(tb_reset_n),
	.m1_req(tb_m1_req), .m0_req(tb_m0_req), 
	.m1_grant(tb_m1_grant), .m0_grant(tb_m0_grant));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=0; tb_m1_req=0; tb_m0_req = 0;
	#8; tb_reset_n = 1; tb_m1_req = 1; // master -> m1
	#10; tb_m0_req = 1; 
	#10; tb_reset_n = 0; //reset
	#10; tb_reset_n=1;
	#10; tb_m0_req = 0; //master -> m0
	#20; $stop;
	end
endmodule

