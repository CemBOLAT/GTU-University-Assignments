

// Control Unit Module
module ControlUnit(
    input [5:0] opcode,
    input [5:0] funct,
    output reg reg_dst,
    output reg alu_src,
    output reg mem_to_reg,
    output reg reg_write,
    output reg mem_read,
    output reg mem_write,
    output reg branch,
    output reg [2:0] alu_control
);
    always @(*) begin
        // Default signals
        reg_dst = 0;
        alu_src = 0;
        mem_to_reg = 0;
        reg_write = 0;
        mem_read = 0;
        mem_write = 0;
        branch = 0;
        alu_control = 3'b000;

        case (opcode)
            6'b000000: begin // R-type
                reg_dst = 1;
                reg_write = 1;
                case (funct)
                    6'b100000: alu_control = 3'b000; // ADD
                    6'b100010: alu_control = 3'b001; // SUB
                    6'b100100: alu_control = 3'b010; // AND
                    6'b100101: alu_control = 3'b011; // OR
                    6'b100110: alu_control = 3'b100; // XOR
                    6'b100111: alu_control = 3'b101; // NOR
                endcase
            end
            6'b100011: begin // LW
                alu_src = 1;
                mem_to_reg = 1;
                reg_write = 1;
                mem_read = 1;
            end
            6'b101011: begin // SW
                alu_src = 1;
                mem_write = 1;
            end
            6'b000100: begin // BEQ
                branch = 1;
                alu_control = 3'b001; // SUB
            end
            //Insert required case statement for ADDI Support
				//Determine the required output control signals 
				//so that ADDI instruction can be executed by this CPU
        endcase
    end
endmodule