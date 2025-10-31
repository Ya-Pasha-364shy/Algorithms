"""
Задача №2 из лекции 
"""

def lbinsearch(l,r,check,checkparams):
	while l < r:
		m = (l+r)//2
		if check(m, checkparams):
			r = m
		else:
			l = m+1
	return l

def checkendownment(m, params):
	n, k = params
	return ((2*k+m-1)*m)//2 >= n

def main():
	n = 100 # всего задач
	k = 0 # сначала не решено задач вообще.

	l = 0
	r = n

	needle = lbinsearch(l, r, checkendownment, (n, k))
	print(needle)


if __name__ == '__main__':
    main()