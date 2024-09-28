


/*
I want you to give me half adder and full adder modules.

Half adder

a b | sum carry
0 0 | 0		0
0 1 | 1		0
1 0 | 1		0
1 1 | 0		1

carry = a & b
sum = a ^ b


FULL adder

a b cin | sum carry
0 0  0  | 0		0
0 0  1  | 1		0
0 1  0  | 1		0
0 1  1  | 0		1
1 0  0  | 1		0
1 0  1  | 0		1
1 1  0  | 0		1
1 1  1  | 1		1

ab  | 00 01 11 10
cin
0   | 00 10 01 10
1   | 10 01 11 01

carry = (a & b) | (b & cin) | (a & cin)
sum = (cin & ~a & ~b) | (~cin & ~a & b) | (~cin & a & ~b) | (cin & a & b)

sum---carry

*/

module half_adder(input a, b, output sum, carry);
	assign carry = a & b;
	assign sum = a ^ b;
endmodule

// without usign half adder
module full_adder(input a,b, cin, output sum, carry);
	assign sum = (cin & ~a & ~b) | (~cin & ~a & b) | (~cin & a & ~b) | (cin & a & b);
	assign carry = (a & b) | (b & cin) | (a & cin);
endmodule


/*

a  ----			  cin------------------
		half_adder                    or --- cout
b  ----			  sum----       cin----
						half_adder
cin----------------------        sum-------- sum

*/

// using half adder
module full_adder(input a,b, cin, output sum, carry);
	wire sum1, carry1;
	half_adder ha1(a,b,sum1,carry1);
	half_adder ha2(sum1,cin,sum,carry);
	assign carry = carry1 | carry;
endmodule

// 5 bit adder
module _5_bit_adder(input [4:0]a, b, output [4:0]sum, cout);
	wire c1, c2, c3, c4;
	full_adder fa1(a[0],b[0],0,sum[0],c1);
	full_adder fa2(a[1],b[1],c1,sum[1],c2);
	full_adder fa3(a[2],b[2],c2,sum[2],c3);
	full_adder fa4(a[3],b[3],c3,sum[3],c4);
	full_adder fa5(a[4],b[4],c4,sum[4],cout);
endmodule

module _5_bit_substractor(input [4:0]a, b, output [4:0]sum, cout);
	wire c1, c2, c3, c4;
	full_adder fa1(a[0],~b[0],1,sum[0],c1);
	full_adder fa2(a[1],~b[1],c1,sum[1],c2);
	full_adder fa3(a[2],~b[2],c2,sum[2],c3);
	full_adder fa4(a[3],~b[3],c3,sum[3],c4);
	full_adder fa5(a[4],~b[4],c4,sum[4],cout);
endmodule

