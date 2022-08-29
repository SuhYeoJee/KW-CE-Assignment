module mul_calculate(op_start, multiplier, multiplicand, cur_state,  cur_multiplicand, cur_result, cur_counter, 
							next_multiplicand, next_result, next_counter); //[Lab09] multiplier
	input op_start;
	input [1:0] cur_state;
	input [31:0] multiplier, multiplicand, cur_counter, cur_multiplicand;
	input [63:0] cur_result;
	output reg [31:0] next_multiplicand, next_counter;
	output reg [63:0] next_result;
	reg [31:0] w_result;
	wire [31:0] w_add, w_sub;

	//STATE ENCODING
	parameter INIT 	= 2'b00;
	parameter MUL 		= 2'b01;
	parameter RESULT 	= 2'b10;

	always@* begin //(cur_state or cur_multiplicand or cur_counter or op_start) begin
		case (cur_state)
			INIT: begin
				next_multiplicand <= multiplicand;
				if (cur_counter[31]==1'b1) begin		//data already exist
					next_counter <= cur_counter;
					next_result <= cur_result;
				end
				else if (op_start==1'b1) begin		//start calculate
					next_counter <= 32'b0;
					next_result <= 64'b0;
				end
				else begin
					next_counter <= 32'bx;
					next_result <= 64'bx;
				end
			end
			MUL: begin
				next_multiplicand[30:0] <= cur_multiplicand[31:1]; //multiplicand LSR
				next_multiplicand[31] <= cur_multiplicand[0];
				
				next_counter[31:1] <= cur_counter[30:0]; 		//counter LSL
				next_counter[0] <= cur_counter[31];	
				
				//get result's upper 32bit
				if(cur_counter==32'b0) begin		// calculate first bit
					next_counter <=31'b0001;	//set counter
					if(cur_multiplicand[0]==1'b0) w_result[31:0] <= cur_result[63:32]; //first bit -> multiplicand[-1] = 0
					else w_result[31:0] <= w_sub;
				end
				else begin
					case({cur_multiplicand[0], cur_multiplicand[31]})	//multiplicand(x,x-1)
						{1'b0,1'b0} : w_result[31:0] <= cur_result[63:32];	//(0,0)
						{1'b1,1'b1} : w_result[31:0] <= cur_result[63:32];	//(1,1)
						{1'b1,1'b0} : w_result[31:0] <= w_sub;				//(1,0)
						{1'b0,1'b1} : w_result[31:0] <= w_add;				//(0,1)
						default : w_result[31:0] <= 32'bx;
					endcase	
				end
				
				next_result[30:0] <= cur_result[31:1];			//result ASR
				next_result[62:31] <= w_result[31:0];
				next_result[63] <= w_result[31];
			end
			RESULT: begin
				next_multiplicand <= multiplicand;
				next_counter <= cur_counter;
				next_result <= cur_result;
			end
			default: next_result <= 64'bx;
		endcase
	end
	
	cla32 sub(.a(cur_result[63:32]),.b(~multiplier),.ci(1'b1),.s(w_sub),.co()); //SUB
	cla32 add(.a(cur_result[63:32]),.b(multiplier),.ci(1'b0),.s(w_add),.co());  //ADD

endmodule