
// Data Memory Module
module DataMemory(
    input clk,
    input we,
    input [31:0] address,
    input [31:0] write_data,
    output reg [31:0] read_data
);
    reg [31:0] data_memory [0:255]; // Data memory (256 words)

    initial begin
        $readmemh("data.mem", data_memory); // Load data memory from file
    end

    always @(posedge clk) begin
        if (we) begin
            data_memory[address >> 2] <= write_data;
        end
    end

    always @(*) begin
        read_data = data_memory[address >> 2];
    end
endmodule