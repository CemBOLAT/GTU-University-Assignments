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
wire incBTN = ~KEY[0];
wire decBTN = ~KEY[1];

counter c1(CLOCK_50, counterWire);
circuit cir(counterWire[22], incBTN, decBTN, LEDR[2:0], LEDR[9]);


endmodule

module counter(input clk, output reg [31:0]out);
    always @(posedge clk)
    begin
        out = out + 32'b1;
    end
endmodule

module circuit(input clk, incBTN, decBTN, output [2:0]nbr, output odd);
    reg [1:0]state;
    wire [1:0]nextState;

    always @ (posedge clk)
    begin
        state <= nextState;
    end

    assign odd = state[0];

    assign nbr[0] = state[0];
    assign nbr[1] = state[1];

    assign nextState[1] =    (~state[1] & ~state[0] & ~incBTN & decBTN) |
                                    (~state[1] & state[0] & incBTN & ~decBTN) |
                                    (state[1] & ~state[0] & ~decBTN) |
                                    (state[1] & state[0] & ~incBTN);

    assign nextState[0] =    (~state[1] & ~state[0] & ~incBTN & decBTN) |
                                    (~state[1] & ~state[0] & incBTN & ~decBTN) |
                                    (~state[1] & state[0] & ~incBTN & ~decBTN) |
                                    (state[1] & ~state[0] & ~incBTN & decBTN) |
                                    (state[1] & ~state[0] & incBTN & ~decBTN) |
                                    (~state[1] & state[0] & incBTN & ~decBTN) |
                                    (state[1] & state[0] & ~incBTN & ~decBTN);
endmodule
