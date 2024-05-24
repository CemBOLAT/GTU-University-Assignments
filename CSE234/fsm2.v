//=======================================================
//  This code is generated by Terasic System Builder
//=======================================================

module FSM(

    //////////// CLOCK //////////
    input                           CLOCK_50,

    //////////// KEY //////////
    input              [3:0]        KEY,

    //////////// LED //////////
    output             [9:0]        LEDR,

    //////////// SW //////////
    input              [9:0]        SW
);

wire [31:0]counterWire;

counter c1(CLOCK_50, counterWire);
circuit cir(counterWire[22], LEDR[2:0]);

endmodule

module circuit(input clk, output [2:0]out);

	wire [2:0]tmp;
	reg	[2:0]register;

	always @(posedge clk)
	begin
		register <= tmp;
	end

	assign tmp[0] = ~register[0];
	assign tmp[1] = register[0] ^ register[1];

	assign out[0] = register[1] | (~register[1] & register[0]);
	assign out[1] = ~register[1] | (register[1] & register[0]);
	assign out[2] = register[1];

endmodule

module counter(input clk, output reg [31:0]bus);
	always @ (posedge clk)
	begin
		bus = bus + 1;
	end
endmodule
