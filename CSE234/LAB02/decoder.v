
/*
	1bit 1x2 decoder, 2x4 decoder, 3x8 decoder
*/


module _1_to_2_decoder(input a, output [1:0]out);
	assign out = (a == 0) ? 2'b01  :
							2'b10 ;
endmodule

module _2_to_4_decoder(input [1:0]a, output [3:0] out);
	assign out =	(a == 2'b00) ? 4'b0001 :
					(a == 2'b01) ? 4'b0010 :
					(a == 2'b10) ? 4'b0100 :
					(a == 2'b11) ? 4'b1000;
endmodule

module _3_to_8_decoder(input [2:0]a, output [7:0] out);
	assign out =	(a == 3'b000) ? 8:00000001 :
					(a == 3'b001) ? 8:00000010 :
					(a == 3'b010) ? 8:00000100 :
					(a == 3'b011) ? 8:00001000 :
					(a == 3'b100) ? 8:00010000 :
					(a == 3'b101) ? 8:00100000 :
					(a == 3'b110) ? 8:01000000 :
					(a == 3'b111) ? 8:10000000 :
endmodule


