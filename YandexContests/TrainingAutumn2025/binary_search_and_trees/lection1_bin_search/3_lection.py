"""
Задача №3 из лекции
"""

def rbinsearch(l,r,check,checkparams):
	while l<r:
		m = (l+r+1)//2
		if check(m, checkparams):
			l = m
		else:
			r = m-1
	return l

def checkparams(m, params):
	w,h,n = params
	return (w//m)*(h//m) >= n

def main():
    # размер доски
	w = 20
	h = 40
	n = 100 # необходимое количество шпор

	# минимальное значение стороны квадратной шпоры = 0, а максимальное = w+h.
	l = 0 
	r = w+h

	needle_length_of_side = rbinsearch(l, r, checkparams, (w,h,n))
	print(needle_length_of_side) 

if __name__ == '__main__':
	main()