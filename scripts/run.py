#!/usr/bin/env python3
from z3 import *

N = 3

a = BitVec('a', N)
b = BitVec('b', N)
c = BitVec('c', N)

f = Function('f', BitVecSort(N), BitVecSort(N), BitVecSort(N))


"""
search: function f (that is not equal to add), such that:

there does not exist any input a,b that breaks any rule.


R1(a,b) /\ R2(a,b) /\ ... are all valid.
"""

exp = And(
	Exists([a,b],
		f(a,b) != a & b),
	ForAll([a,b,c],
		And(
			f(a,b) == f(b,a), 
			f(a,0) == 0,
			f(a,-1) == a,
			f(a,a) == a,
			ULE(f(a,b), a),
			
#			f(a,b) == a & b,

			f(a,b) == f(a,f(b,c)) | f(a,f(b,~c)),


#			Implies(
#				(f(a,b) >> c) != 0,
#				And(
#					(a >> c) != 0,
#					(b >> c) != 0,
#				)
#			),
			
			f(a,b) == f(f(a,b),b),
			f(a,b) == f(f(a,b),a),


#			f(f(a,b), (1<<c)) == f(a, (1<<c))
#			
#			f(a,(1 << c)) == f(b,


#			Implies(
#				And(
#					(a & (1 << c)) != 0,
#					(b & (1 << c)) != 0
#				),
#				(f(a,b) & (1 << c)) != 0,
#			),
#			
#			Implies(
#				Or(
#					(a & (1 << c)) == 0,
#					(b & (1 << c)) == 0
#				),
#				(f(a,b) & (1 << c)) == 0,
#			),
			
#			f(a,b) == f(a,b) & a,
#			f(a,b) == f(a,b) & b,
			
#			f(a,b) == f(a,b) & a & b,
			
			
#			Implies(And((a&c)!=0, (b&c)!=0), (f(a,b)&c) != 0),
			
#			Implies(Or((a&c)==0, (b&c)==0), (f(a,b)&c) == 0)
			
#			f(a,b) == f(f(a,b|c), b)

#			f(a,b) == f(a,b & 3) | f(a,b & 4)
		)
	)
)


exp2 = simplify(exp)

#print(exp2)

#nexp = Not(exp2)

solve(exp2)



# proof(x) -> not(x) is unsat
