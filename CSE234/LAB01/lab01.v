
/*
4 bits number if the ones are odd turn on the led


a b c d | led

0 0 0 0 | 0
0 0 0 1 | 1
0 0 1 0 | 1
0 0 1 1 | 0
-----------
0 1 0 0 | 1
0 1 0 1 | 0
0 1 1 0 | 0
0 1 1 1 | 1
-----------
1 0 0 0 | 1
1 0 0 1 | 0
1 0 1 0 | 0
1 0 1 1 | 1
-----------
1 1 0 0 | 0
1 1 0 1 | 1
1 1 1 0 | 1
1 1 1 1 | 0


karnaugh map
cd   00  01  11  10
ab |---------------
00 | 0   1   0   1
01 | 1   0   1   0
11 | 0   1   0   1
10 | 1   0   1   0

cannot be simplified

*/

module lab01(input a, b, c, d, output led);
	assign led = (~a & ~b & ~c & d) | (~a & ~b & c & ~d) | (~a & b & ~c & ~d) | (a & ~b & c & d)
					| (a & b & ~c & d) | (a & b & c & ~d) | (~a & b & c & d) | (a & ~b & ~c & ~d);
endmodule
