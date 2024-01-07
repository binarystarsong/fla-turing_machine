
#Q = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,r0,halt_accept,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,c,_,I,l,e,g,a,n,p,u,t}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2


;main
0 __ __ ** 10
0 a_ a_ ** 1
0 b_ b_ ** 10
1 a_ a_ r* 1
1 __ __ l* 10
1 b_ b_ r* 2

2 b_ b_ r* 2
2 __ __ l* 12
2 a_ a_ ** 10

12 *_ *_ l* 12
12 __ __ r* 3


3 a_ __ r* 4
3 b_ b_ ** 7

4 a_ a_ r* 4
4 b_ b_ ** 5

5 b_ bc rr 5
5 __ __ l* 6

6 *_ *_ l* 6
6 __ __ r* 3

7 b_ __ r* 7
7 __ __ *l 8

8 _c cc ll 8
8 __ __ ll halt_accept

10 ** ** l* 10
10 *_ *_ l* 10
10 _* _* r* 11
10 __ __ r* 11

11 *_ __ r* 11
11 ** _* r* 11
11 _* _* ** r0
11 __ __ ** r0

r0 *_ __ l* r0
r0 __ __ r* 13
13 __ I_ r* 14
14 __ l_ r* 15
15 __ l_ r* 16
16 __ e_ r* 17
17 __ g_ r* 18
18 __ a_ r* 19
19 __ l_ r* 20
20 __ __ r* 21
21 __ I_ r* 22
22 __ n_ r* 23
23 __ p_ r* 24
24 __ u_ r* 25
25 __ t_ r* halt_reject
