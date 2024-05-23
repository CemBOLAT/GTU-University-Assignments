

/*
	1bit 2x1 encoder, 4x2 encoder, 8x3 encoder
*/

module _2_to_1_encoder(input [1:0]in, output out);
	assign out =	(in[0]) ? 0 : 1;
endmodule

module _4_to_2_encoder(input [3:0]in, output out);
	assign out =	(in[3]) ? 2'b00 :
					(in[2]) ? 2'b01 :
					(in[1]) ? 2'b10 : 2'b11;
endmodule

module _8_to_3_encoder(input [7:0]in, output [2:0]out);
	assign out =	(in[7]) ? 3'b000 :
					(in[6]) ? 3'b001 :
					(in[5]) ? 3'b010 :
					(in[4]) ? 3'b011 :
					(in[3]) ? 3'b100 :
					(in[2]) ? 3'b101 :
					(in[1]) ? 3'b110 : 3'b111;
endmodule

