# P1

  # EX 1)
  
 '''
   Fiind dată o listă cu numere naturale, afișați toate elementele pare.
 '''

lista = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]


def cout(lst):
    if(len(lst) > 0):
        head = lst[0]
        tail = lst[1:]
        if(head % 2 == 0):
            print(head)
        return cout(tail)

print(cout(lista))

#----------------------------------------------------------------

  #EX 2)
  
  '''
   Fiind dată o listă cu șiruri de caractere, afișați toate elementele care au mai puțin de 3 caractere.
  '''
  
  
lista = ["abc", "abac", "cuc", "la", "cu"]


def caract(lst):
    if(len(lst) > 0):
        head = lst[0]
        tail = lst[1:]
        if(len(head) >= 3):
            print(head)
        return caract(tail)
    return "" #bypass None din fucntie

print(caract(lista))

#------------------------------------------------------------------

  #EX 3 (No idea la cum se poate sorta tipuri de date diferite)
  
#------------------------------------------------------------------

  #EX 4
  '''
   Să se sorteze o listă care conține numere întregi în funcție de ultima cifră a numărului ( în ordine crescătoare a ultimei cifre din număr).
  '''
  
lista = [991, 232, 814, 535]
lista.sort(key = lambda x: x%10) # acesam ultima cifra si o folosim ca filtru pt. sortare

print(lista)

#--------------------------------------------------------------------

  #EX 5
  
  '''
  Să se înmulțească toate elementele unei liste de numere reale. Se va folosi funcția reduce().
  '''
  
import functools

lista = [2.1, 3.5 , 4.0 , 5.5 , 6.33]
rez=functools.reduce(lambda x,y: x*y , lista, 1)

print(rez)

#----------------------------------------------------------------------

  #EX 6
  
  '''
   Să se creeze o nouă listă care să conțină toate elementele unei liste inițiale la puterea a 3-a. Se va folosi funcția map().
  '''

lista = [2, 3, 4, 5, 6, 7 ,8]

rez = map(lambda x: x**3, lista)
print(list(rez))

#-------------------------------------------------------------------------------

#EX 7

'''
Să se creeze o nouă listă care conține doar elementele numere prime dintr-o listă inițială. Se va folosi funcția filter(). 
'''

lista = [2, 3, 4, 5, 6, 7 ,8]

def prim(x):
    def aux(n, i=2):
        if(i > n/2):
            return True
        else:
            if(n % i == 0):
                return False
            else:
                return True and aux(n, i+1)
    return aux(x)

rez = filter(prim, lista)
print(list(rez))

#------------------------------------------------------------------------------------

#P II

  #EX 1 a)
  '''
  Implementați funcții care construiesc lista cifrelor unui număr care satisfac o condiție anume
  (cifre impare, pare, mai mici decât 7, etc. la alegere), în ordine normală și inversă
  '''
  
def cifre_a(n):
    if(n < 10):
        if(n % 2 == 1 and n < 7):
            return [n]
        else:
            return []
    else:
        uc= n%10
        if(uc % 2 ==1 and uc < 7):
            return  cifre_a(n//10) + [uc]
        else:
            return cifre_a(n//10) + []


print(cifre_a(1234567))

# EX 1 b)
'''
 Implementați o funcție care construiește lista cifrelor unui număr care satisfac o condiție dată ca parametru
 sub forma unei funcții cu tipul int -> bool.
'''

def cifre_conditie(n, conditie):
    if n <= 9:
        if conditie(n):
            return [n]
        else:
            return []
    else:
        ultima_cifra = n % 10
        if conditie(ultima_cifra):
            return cifre_conditie(n // 10, conditie) + [ultima_cifra]
        else:
            return cifre_conditie(n // 10, conditie)


print("lista cifre cond = ", end="")
print(cifre_conditie(123469, lambda x: x % 3 == 0))

#----------------------------------------------------------------------------

#c
'''
Invers, dată fiind o listă de cifre, construiți numărul format doar din cifrele care respectă o condiție (dată ca parametru funcție cu tipul int -> bool).
Rezolvați problema direct, recursiv, și apoi prin folosirea lui filter (selectarea cifrelor) cu reduce (pentru construirea numărului).
'''

lisa = [1,2,3,4,5,6,7,8,9]


def cifre_c(lista, cond):
    if(len(lista) > 0):
        h=lista[-1]
        t=lista[:-1]
        if(cond(h)):
            return h + cifre_c(t, cond)*10
        else:
            return cifre_c(t,cond)
    else:
        return 0

print(cifre_c(lisa,lambda x: x%3==1))

#------
from functools import reduce

def cr_lst_red(lista, cond):
    return reduce(lambda acc, element: acc*10 + element if cond(element) else acc,lista,0)

print(cr_lst_red([1, 2, 3, 4,6,7], lambda x: x % 2 == 0))
#------

def create_nr_reduce_filter(lista, cond):
    elem_filtru = filter(cond, lista)
    return functools.reduce(lambda acc, element: acc*10 + element, elem_filtru, 0)


print(create_nr_reduce_filter([2,3,4,5,6,7,8,9], lambda x:x%2==1))

#EX 2
'''
Implementați funcția fromto care generează lista numerelor întregi dintr-un interval dat, scrieți o funcție care creează
lista tuturor întregilor dintr-un interval dat, divizibili cu o valoare dată d.
Indicație: Găsiți cel mai mare număr divizibil din interval, și continuați pas cu pas.
'''

def fromto(a,b,d, rez=[]):
    if(a<=b):
        if(a%d == 0):
            rez.append(a)
            fromto(a+1,b,d)
        else:
            fromto(a+1,b,d)
    else:
        print(rez)
    return ""

print(fromto(12,20,2))

#EX 3
#a)
'''
Implementați funcția nth care returnează al n-lea element dintr-o listă.
'''

def nth(l,i):
    return l[i-1]

print("indicele cu numarul 3 =",nth([2,3,4,5,52], 3))

#----
#b)
'''
Implementați o funcție firstn care returnează o listă cu primele n elemente dintr-o listă dată.
'''

def firstn(l, n):
    return l[:n]

print(firstn([3,2,4,6,1,9], 2))

#----------------------------------------------------------------------------------------------
