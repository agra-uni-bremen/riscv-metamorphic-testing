#!/usr/bin/env python3
import itertools
import math

N = 4

def gen_funcs():
	return itertools.product(range(N), repeat=N**2)
	
def gen_inputs_2():
	return itertools.product(range(N), range(N))
	
def apply_fn(fn, a, b):
	return fn[N*a + b]


def check_rule_1(fn):
	for a,b in gen_inputs_2():
		x1 = apply_fn(fn, a, b)
		x2 = apply_fn(fn, b, a)
		if x1 != x2:
			return True	# found error
	return False # no error found with this rule for this function
	
def check_rule_2(fn):
	for a,b in gen_inputs_2():
		x1 = apply_fn(fn, a, b)
		x2 = apply_fn(fn, apply_fn(fn, a, math.ceil(b / 2)), math.floor(b / 2))
		if x1 != x2:
			return True	# found error
	return False # no error found with this rule for this function
	
def check_rule_3(fn):
	for a,b in gen_inputs_2():
		x1 = apply_fn(fn, a, b)
		if b == 0:
			if x1 != a:
				return True
		else:
			if x1 == a:
				return True
	return False # no error found with this rule for this function
	

passed = []
for idx,fn in enumerate(gen_funcs()):
	if idx & 16777215 == 16777215:
		print("> {}".format(idx))
	ans = check_rule_1(fn)
	if not ans:
		ans = check_rule_2(fn)
		if not ans:
			ans = check_rule_3(fn)
			if not ans:
				passed.append(idx)
				print("PASSED [{}]: {}".format(idx, fn))
				
print("{} functions passed".format(len(passed)))
