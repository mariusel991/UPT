
def afis(p, val):
    if(p>0):
        print(val,end="")
        return afis(p-1, val)
    else:
        return ""

#print(afis(3,1))


def triunghi(n):
    def afis(p, val):
        if (p > 0):
            print(val, end=" ")
            return afis(p - 1, val)
        else:
            print("\r")
    if(n>0):
        triunghi(n-1)
    return afis(n,n)

triunghi(5)
