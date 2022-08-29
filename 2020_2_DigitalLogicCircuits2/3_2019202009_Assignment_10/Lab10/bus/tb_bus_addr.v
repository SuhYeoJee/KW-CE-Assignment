`timescale 1ns/100ps
module tb_bus_addr;
	reg [7:0] tb_s_addr;
	wire tb_s0_sel, tb_s1_sel;
	
	bus_addr U0(.s_addr(tb_s_addr), .s0_sel(tb_s0_sel), .s1_sel(tb_s1_sel));
	
	initial begin
	tb_s_addr = 8'b0;
	#8; tb_s_addr = 8'h13;
	#10; tb_s_addr = 8'h02;
	#10; tb_s_addr = 8'h2A;
	#10; tb_s_addr = 8'h4F;
	#10; tb_s_addr = 8'h3F;
	#20; $stop;
	end
endmodule
