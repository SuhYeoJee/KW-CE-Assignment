`timescale 1ns/100ps
module tb_rf;
	reg clk, reset_n, we;
	reg [15:0] Addr;
	reg [63:0] wData;
	wire [63:0] rData;

	rf rf(clk, reset_n, Addr, wData, we, rData);//[Lab07] register file
	
	parameter STEP =10;
	always #(STEP/2) clk = ~clk; //clk changes every 5 ns
	
	initial begin
	clk = 0; reset_n=0; we=0; Addr = 16'b0110; wData=64'h1111;
	#8; reset_n=1;we=0; Addr = 16'h0120; 	//read 0x0110 (err)
	#10; we = 1;									//write 0x0120 (1111)
	#10;Addr=16'h0001;wData=64'h2222; 		//write 0x0001 (err)
	#10;Addr=16'h0105; 							//write 0x0105 (2222)
	#10;Addr=16'h0101; wData=64'h3333;		//write 0x0101 (3333)
	#10;we=0; Addr = 16'h0120; 				//read 0x0110 (1111)
	#10;Addr=16'h0001;							//read 0x0001 (err)
	#10;Addr=16'h0105; 							//read 0x0105 (2222)
	#10;Addr=16'h0101; 							//read 0x0101 (3333)
	#20; $stop;
	end
endmodule









