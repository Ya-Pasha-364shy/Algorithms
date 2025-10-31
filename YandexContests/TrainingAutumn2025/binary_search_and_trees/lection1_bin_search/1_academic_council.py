"""
Задача про учебный совет (#1) из лекции
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
    print(n, k)
    return (k+m)*3 >= (n+m)


def main():
    n = 18 # всего человек
    k = 3  # из них k родителей

    l = 0
    r = n

    needle = lbinsearch(l, r, checkendownment, (n, k)) # 5
    print(needle)


if __name__ == '__main__':
    main()