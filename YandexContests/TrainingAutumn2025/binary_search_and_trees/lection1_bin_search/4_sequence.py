"""
Задача №4 из лекции
"""

def lbinsearch(l,r,check,checkparams):
	while l != r:
		m = (l+r)//2
		if check(m, checkparams):
			r = m
		else:
			l = m+1
	return l

def check(m, checkparams):
	seq, x = checkparams
	return seq[m] >= x

def main():
	seq = [1, 2, 4, 5, 10, 16]
	print("Checking sequence: ", seq)

	x = 3
	ans = lbinsearch(0, len(seq), check, (seq, x))
	if (ans >= len(seq)):
		print("cannot find this num, return N: ", len(seq))
	else:
		print("idx = ", ans, "; value = ", seq[ans])

	x = 9
	ans = lbinsearch(0, len(seq), check, (seq, x))
	if (ans >= len(seq)):
		print("cannot find this num, return N: ", len(seq))
	else:
		print("idx = ", ans, "; value = ", seq[ans])

	x = 10
	ans = lbinsearch(0, len(seq), check, (seq, x))
	if (ans >= len(seq)):
		print("cannot find this num, return N: ", len(seq))
	else:
		print("idx = ", ans, "; value = ", seq[ans])

	x = 40
	ans = lbinsearch(0, len(seq), check, (seq, x))
	if (ans >= len(seq)):
		print("cannot find this num, return N: ", len(seq))
	else:
		print("idx = ", ans, "; value = ", seq[ans])

if __name__ == '__main__':
	main()