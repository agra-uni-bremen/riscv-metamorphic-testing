#!/usr/bin/env python3
from z3 import *

N = 3

a = BitVec('a', N)
b = BitVec('b', N)

f = Function('f', BitVecSort(N), BitVecSort(N), BitVecSort(N))


"""
search: function f (that is not equal to add), such that:

there does not exist any input a,b that breaks any rule.


R1(a,b) /\ R2(a,b) /\ ... are all valid.
"""

exp = And(
	Exists([a,b],
		f(a,b) != a+b),
	ForAll([a,b],
		And(
			f(a,b) == f(b,a), 
	
			If(b%2==0, 
				f(a,b) == f(f(a, UDiv(b,2)), UDiv(b,2)),
				f(a,b) == f(f(a, UDiv(b,2)+1), UDiv(b,2))),
	
			If(b==0, f(a,b)==a, f(a,b)!=a)
		)
	)
)


exp2 = simplify(exp)

#print(exp2)

#nexp = Not(exp2)

solve(exp2)



# proof(x) -> not(x) is unsat
