# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fulltest.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marhuber <falcino@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/14 23:48:19 by marhuber          #+#    #+#              #
#    Updated: 2025/12/22 11:07:08 by marhuber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import subprocess
import random
from itertools import chain

# Configuration
myexe = "./push_swap" 
check42 = "./checker_linux"
mycheck = "./checker"

# C int range
C_INT_MIN = -2147483648
C_INT_MAX = 2147483647
intrange = range(C_INT_MIN, C_INT_MAX + 1)

# Operations
ops = ["pa", "pb", "sa", "sb", "ss", "ra", "rb", "rr", "rra", "rrb", "rrr"]


def counter(args):
	cmd = [myexe] + args
	cmd = " ".join(cmd) + "| wc -l"
	result = subprocess.run(cmd, capture_output=True,  text=True, shell=True)
	return(result.stdout[:-1])

def checker(whichchecker, args):
	cmd = [myexe] + args + ["|"] + [whichchecker] + args
	cmd = " ".join(cmd)
	result = subprocess.run(cmd, capture_output=True, text=True, shell=True)
	return(result.stdout[:-1])

def testthechecker(whichchecker, args):
	cmd = [whichchecker] + args + ["< outinstructions.txt"]
	cmd = " ".join(cmd)
	result = subprocess.run(cmd, capture_output=True, text=True, shell=True)
	return(result.stdout[:-1])

def errortest(whichexe, argsstr):
	cmd = whichexe + " " + argsstr
	print(" ", cmd)
	result = subprocess.run(cmd, capture_output=True,  text=True, shell=True)
	if result.stderr:
		print(" ", result.stderr, end="")
	elif result.stdout:
		print("Unexpected: some stdout instead of stderr")

def singletest(args):
	output1 = checker(mycheck, args)
	output2 = checker(check42, args)
	if (output1 != output2 or output2 != "OK"):
		print(" ".join(args))
		print(output1, output2)
	print(" ", len(args), counter(args))

def constanttests():
	print("Test picking up errors")
	for argsstr in [ \
			" ", "0 a4b 4", "-jhu 445" "979- 754", \
			"-187 2149483647 3666", \
			"5 2147483648 34", \
			"566784 2147483649 2322435", \
			"566784 9147483649 2322435", \
			"76 -2147483649 78533",\
			"785784 -2147483650 2322435", \
			"-0 727 0", \
			"153 375 885 375 654", \
			"434 434 885 375 654", \
			"153 375 885 112 112", \
			"587 -523 549 925 1 -7878898 78793 12334 -523" \
			]:
		errortest(myexe, argsstr)
		errortest(mycheck, argsstr)
	print("Test limit cases")
	for args in [ \
			"-2147483648 -1 2147483646 0 -2147483647 1 2147483647".split(" "), \
			"-2147483646 1 -2147483645 0 2147483645 -1 2147483644".split(" "), \
			[str(x) for x in range(10)], \
			[str(pow(-1, x) * x) for x in range(10)], \
			[str(-x) for x in range(10)], \
			[str(x) for x in range(100)], \
			[str(pow(-1, x) * x) for x in range(100)], \
			[str(-x) for x in range(100)], \
			[str(x) for x in range(500)], \
			[str(pow(-1, x) * x) for x in range(500)], \
			[str(-x) for x in range(500)], \
			]:
		singletest(args)

def	rndtest(n, res): # n max ~2000
	# pick n unique random integers in C int range
	numbers = random.sample(intrange, n)
	args = [str(x) for x in numbers]
	res.append(int(counter(args)))
	ok = checker(check42, args)
	if ok != "OK":
		print(ok)
	if (ok != checker(mycheck, args)):
		print("ERROR my checker differs")

def rndtestseries(i, m):
	print(" ", i)
	res = []
	for _ in range(m):
		rndtest(i, res)
	print(" ", min(res), max(res))

def argctests():
	m = 4
	print("Arguments count tests\nRandom numbers, ", m, "repeats")
	for j in [4, 10, 50, 100, 200, 500, 600]:
		for i in range(j - 3, j + 3):
			rndtestseries(i, m)

def benchmarktests():
	m = 128
	print("Benchmark tests\nRandom numbers, ", m, "repeats")
	for i in [100, 500]:
		rndtestseries(i, m)

def genrandominstruction(l):
	res = ""
	for _ in range(l):
		res += random.sample(ops, 1)[0] + "\n"
	with open("outinstructions.txt", "w") as file:
		file.write(res)

def  checkertests():
	print("Testing my checker")
	for i in chain(range(1, 20), range(10, 10, 100)):
		numbers = random.sample(intrange, i)
		args = [str(x) for x in numbers]
		for j in [i, 2 * i, 4 * i, 5 * i, 6 * i, 7 * i]:
			for _ in range(10):
				# print(" ", i, j)
				genrandominstruction(j)
				ok1 = testthechecker(check42, args)
				ok2 = testthechecker(mycheck, args)
				if (ok1 != ok2):
					print("ERROR with checkers", ok1, ok2)
					print(" ".join(args))
					with open("outinstructions.txt", "r") as file:
						content = file.read()
						print(content)
					

constanttests()
argctests()
benchmarktests()
checkertests()