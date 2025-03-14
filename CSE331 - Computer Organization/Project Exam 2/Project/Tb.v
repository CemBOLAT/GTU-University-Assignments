// Testbench for Single Cycle MIPS Processor

module Tb();
    reg clk;
    reg rst;
    integer i;
    integer file;

    // Instantiate the Single Cycle MIPS Processor
    SingleCycleMIPS uut (
        .clk(clk),
        .rst(rst)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10 time units clock period
    end

    // Testbench process
    initial begin
        // Reset the processor
        rst = 1;
        #10;
        rst = 0;

        // Wait for the program to execute
        #500; // Adjust this time based on your instruction execution timing

        // Open a file to write the results
        file = $fopen("testbench_output.txt", "w");

        // Dump Register Contents
        $fwrite(file, "Register Contents:\n");
        for (i = 0; i < 32; i = i + 1) begin
            $fwrite(file, "$%0d = %h\n", i, uut.rf_module.registers[i]);
        end

        // Dump Memory Contents
        $fwrite(file, "\nMemory Contents:\n");
        for (i = 0; i < 16; i = i + 1) begin // Adjust range as needed for your memory size
            $fwrite(file, "Mem[%0d] = %h\n", i * 4, uut.dm_module.data_memory[i]);
        end

        $fclose(file);

        // End simulation
        $stop;
    end

    initial begin
        $dumpfile("waveform.vcd");
        $dumpvars(0, Tb);
    end
endmodule
