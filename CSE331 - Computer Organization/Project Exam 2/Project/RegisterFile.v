// Register File Module
module RegisterFile(
    input clk,
    input we,
    input [4:0] rs,
    input [4:0] rt,
    input [4:0] rd,
    input [31:0] write_data,
    output reg [31:0] read_data1,
    output reg [31:0] read_data2
);
    reg [31:0] registers [0:31];

    initial begin
        $readmemh("reg.mem", registers); // Load data memory from file
    end

    always @(posedge clk) begin
        if (we && rd != 0) begin
            registers[rd] <= write_data;
        end
    end

    always @(*) begin
        read_data1 = registers[rs];
        read_data2 = registers[rt];
    end
endmodule