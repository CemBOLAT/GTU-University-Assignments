module full_adder (
    input a,
    input b,
    input cin,
    output sum,
    output cout
);
    wire xor1_out, and1_out, and2_out, and3_out, or_out1;

    // Sum calculation
    xor (xor1_out, a, b);
    xor (sum, xor1_out, cin);

    // Carry-out calculation
    and (and1_out, a, b);
    and (and2_out, a, cin);
	 and (and3_out, cin, b);
	 
	 
    or (or_out1, and1_out, and2_out);
	 or (cout, or_out1, and3_out);
	 
endmodule