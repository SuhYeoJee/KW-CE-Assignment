module calculate(multiplier, multiplicand, result, counter, next_m_nd, next_counter, next_result, state, o_nd); //[Lab09] multiplier
	input [1:0] state;
	input [63:0] multiplier, multiplicand, counter, o_nd;
	input [127:0] result;
	output [63:0] next_m_nd, next_counter;
	output[127:0] next_result;
	reg [63:0]  next_counter,w_result, next_m_nd;
	reg [127:0] next_result;
	wire [63:0] w_add, w_sub;

	parameter INIT = 2'b00;	//STATE ENCODING
	parameter LOAD = 2'b01;
	parameter MUL 	= 2'b10;
	parameter STAY = 2'b11;

	always@(state or multiplicand or counter) begin
		case (state)
			INIT: begin
				next_m_nd = 64'b0;
				next_counter = 64'b0;
				next_result = 128'b0;
			end
			LOAD: begin
				next_m_nd = o_nd;		//set data to calculate
				next_counter = 64'b1;
				next_result = 128'b0;
			end
			MUL: begin
				next_m_nd[62:0] = multiplicand[63:1]; //multiplicand LSR
				next_m_nd[63] = multiplicand[0];
				
				next_counter[63:1] = counter[62:0]; //counter LSL
				next_counter[0] = counter[63];	
				
				if(counter[0]==1) begin					//result ASR
					if(multiplicand[0]==1'b0) w_result[63:0] = result[127:64]; //first bit -> multiplicand[-1] = 0
					else w_result[63:0] = w_sub;
				end
				else begin
					case({multiplicand[0], multiplicand[63]})
						{1'b0,1'b0} : w_result[63:0] = result[127:64];
						{1'b1,1'b1} : w_result[63:0] = result[127:64];
						{1'b1,1'b0} : w_result[63:0] = w_sub;
						{1'b0,1'b1} : w_result[63:0] = w_add;
						default : w_result[63:0] = 64'bx;
					endcase	
				end
				next_result[62:0] = result[63:1];
				next_result[126:63] = w_result[63:0];
				next_result[127] = w_result[63];
			end
			STAY: begin
				next_m_nd = multiplicand;
				next_counter = 64'b0;
				next_result = result;
			end
			
		endcase
	end
	
	cla64 U7_cla64(.a(result[127:64]),.b(~multiplier),.ci(1'b1),.s(w_sub),.co()); //SUB
	cla64 U8_cla64(.a(result[127:64]),.b(multiplier),.ci(1'b0),.s(w_add),.co());  //ADD

endmodule