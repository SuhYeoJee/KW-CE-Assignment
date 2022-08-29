module ram(clk, cen, wen, addr, din, dout); //[Lab10]
	input clk, cen, wen;
	input [4:0] addr;
	input [31:0] din;
	output reg [31:0] dout;
	
	reg [31:0] mem [0:31];
	integer i;
	
	initial begin
	for(i=0;i<32;i=i+1) begin
		mem[i] = 32'b0;	//memory initialization with 0
	end
	end
	
	always @(posedge clk) begin
		if(cen == 0) dout=32'b0; //chip disable
		else if(wen == 1) begin //write
			mem[addr] = din;
			dout = 32'b0;
		end
		else dout = mem[addr]; //read
	end
	
	endmodule