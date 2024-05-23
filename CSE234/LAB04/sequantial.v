

module sqeuential {
	input  CLOCK_50,

	input [3:0] KEY,

	output [9:0] LEDR,

	input [9:0] SW

};

wire [31:0] clockWire;
wire btn = ~KEY[0];
counter c1(CLOCK_50, clockWire);
circuit cir(clockWire[25], btn, LEDR[0]);

endmodule

module circuit(input clk, input btn, output led, output [1:0] nextstate);
	reg [1:0] state;
	wire [1:0] next;

	always @(posedge clk)
	begin
		state <= next;
	end

	assign next[0] = (state[0] & ~state[1]);
	assign next[1] = ((~state[1] & ~state[0] & ~btn) | (state[1] & ~state[0] & btn));
	assign led = state[0] & state[1];

	assign nextstate = next;
endmodule

module counter(input clk, output reg [31:0] count);
	always @(posedge clk)
	begin
		count <= count + 32'b1;
	end
endmodule
