
/*
	1bit Give 2x1 mux , 4x1 mux and 8x1 mux
*/

module _2_to_1_mux(input a, b, sel, output y);
	assign y = (sel) ? b : a;
endmodule

module _4_to_1_mux(input a,b,c,d, input [1:0] sel, output y);
	assign y = (sel[1]) ? ((sel[0]) ? (a) : (b)) : ((sel[0]) ? (c) : (d));
endmodule

// Here we have dont care contidions which only 1 of them can be 1 at the same time
module _8_to_1_mux(input a,b,c input [2:0] sel, output y);

	assign y = (sel[2]) ? (a) : ((sel[1]) ? (b) : (sel[0] ? (c)));

endmodule
