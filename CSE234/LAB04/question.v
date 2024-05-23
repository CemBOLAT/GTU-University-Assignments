/*
Give me a question that includes finite state machine

Design a finite state machine (FSM) that detects a sequence of "101" in a stream of input bits.
The FSM should have one input (X) and one output (Z).
The output Z should be high (1) whenever the sequence "101" has been detected in the input stream, and low (0) otherwise.
The FSM should reset to the initial state after detecting the sequence.
*/



s1 | s0 | x | n1 | n0 | z
0  | 0  | 0 | 0  | 0  | 0
0  | 0  | 1 | 0  | 1  | 0
--------------------------
0  | 1  | 0 | 1  | 0  | 0
0  | 1  | 1 | 0  | 0  | 0
--------------------------
1  | 0  | 0 | 0  | 0  | 0
1  | 0  | 1 | 1  | 1  | 0
--------------------------
1  | 1  | 0 | 0  | 0  | 1
1  | 1  | 1 | 0  | 0  | 1


z = s1 & s0
n0 = x & ~s0
n1 = (~s1 & ~ s0 & ~x) | (s1 & ~s0 & x)

