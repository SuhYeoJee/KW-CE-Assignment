`timescale 1ns/100ps
module tb_mp_ns;
	reg reset_n, op_start, interrupt;
	reg [1:0] cur_state;
	wire [1:0] next_state;
	
	mp_next_state mp_ns(reset_n, cur_state, next_state, op_start, interrupt);
	
	//parameter STEP =10;
	//always #(STEP/2) clk = ~clk; //clk changes every 5 ns
	
	initial begin
	//clk = 0; 
		  reset_n=0;  cur_state = 2'b00; op_start = 0; interrupt = 0;
	#10; reset_n=1;  cur_state = 2'b00; op_start = 0; interrupt = 0;
	#10; cur_state = 2'b00; op_start = 0; interrupt = 1;
	#10; cur_state = 2'b00; op_start = 1; interrupt = 0;
	#10; cur_state = 2'b00; op_start = 1; interrupt = 1;
	#40; cur_state = 2'b01; op_start = 0; interrupt = 0;
	#10; cur_state = 2'b01; op_start = 0; interrupt = 1;
	#10; cur_state = 2'b01; op_start = 1; interrupt = 0;
	#10; cur_state = 2'b01; op_start = 1; interrupt = 1;
	#40; cur_state = 2'b10; op_start = 0; interrupt = 0;
	#10; cur_state = 2'b10; op_start = 0; interrupt = 1;
	#10; cur_state = 2'b10; op_start = 1; interrupt = 0;
	#10; cur_state = 2'b10; op_start = 1; interrupt = 1;
	#20; $stop;
	end
endmodule