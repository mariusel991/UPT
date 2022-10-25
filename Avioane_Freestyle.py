#Quick Sort - LISTE RECURSIV - Sort a.i sa apara fiecarele elem sa fie unic

def quicksort(lst):
    if(len(lst) == 0):
        return []
    elif(len(lst) == 1):
        return [lst[0]]
    else:
        def split_st(lst2, st=[], pivot = None):
            if(len(lst2) > 0):
                if(pivot == None):
                    return split_st(lst2[1:], st, pivot=lst[0])

                if(lst2[0] < pivot):
                    st.append(lst2[0])
                return split_st(lst2[1:], st, pivot)
            else:
                return st

        def split_dr(lst2, dr = [], pivot = None):
            if (len(lst2) > 0):
                if (pivot == None):
                    return split_dr(lst2[1:], dr, pivot=lst[0])

                if (lst2[0] > pivot):
                    dr.append(lst2[0])
                return split_dr(lst2[1:], dr, pivot)
            else:
                return dr
        return quicksort(split_st(lst)) + [lst[0]] + quicksort(split_dr(lst))

lista1 = [7,2,241,35,0,-2,12,77]
print(quicksort(lista1))

#---------------------------------------------------------------------------------------------

#Conversie Binara din baza 10

def conv_binar(n):
    if(n == 1):
        return n
    elif(n == 0):
        return 0
    else:
        return n%2 + conv_binar(n//2) * 10

print(conv_binar(127))

#Modulo_K LAB3.py

def modulo_p(a, p):
    def aux(a, p, exp=1, init=a):
        if(a % p == 1):
            return exp
        else:
            return aux(a*init, p ,exp+1, init)
    return  aux(a, p)

print(modulo_p(4, 7))

