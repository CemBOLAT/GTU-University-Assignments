

// Instruction Fetch Module
module InstructionFetch(
    input [31:0] pc,
    output reg [31:0] instruction
);
    reg [31:0] instruction_memory [0:255]; // Instruction memory (256 words)

    initial begin
        $readmemb("instructions.mem", instruction_memory); // Load instructions from file
    end

    always @(*) begin
        instruction = instruction_memory[pc >> 2];
    end
endmodule

