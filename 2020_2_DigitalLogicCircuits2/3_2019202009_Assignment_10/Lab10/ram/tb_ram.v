`timescale 1ns/100ps
module tb_ram;
	reg tb_clk, tb_cen, tb_wen;
	reg [4:0] tb_addr;
	reg [31:0]  tb_din;
	wire [31:0] tb_dout;
	
	ram U0_ram(.clk(tb_clk),.cen(tb_cen),.wen(tb_wen),.addr(tb_addr),.din(tb_din),.dout(tb_dout));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_cen=0; tb_wen=0; tb_addr = 4'b0; tb_din = 32'b0;
	#8; tb_cen = 1; // read 0
	#10; tb_wen = 1; tb_din = 32'hFFFF_FFFF; //write 0
	#10; tb_wen = 0; //read 0
	#10; tb_addr = 4'b00010; tb_wen = 1; tb_din = 32'h1234_5678; //write 2
	#10; tb_wen = 0; //read 2
	#10; tb_addr = 4'b00010; tb_wen = 1; tb_din = 32'h8765_4321; //write 2
	#10; tb_wen = 0; //read 2
	#20; $stop;
	end
endmodule
