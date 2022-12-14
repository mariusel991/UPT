######################################################################################################################
#                                                     PARTEA I                                                       #
######################################################################################################################
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
          
# OPTIMIZARE #

def cifre_a_optimizat(n, cond):
    if(n < 0):
        return cifre_a_optimizat(abs(n), cond)
    if(n < 10):
        if cond(n):
            return [n]
    else:
        return [n%10] + cifre_a_optimizat(n//10, cond) if cond(n%10) else cifre_a_optimizat(n//10, cond)

print(cifre_a_optimizat(-123123, lambda x: x%2==1 and x < 7))



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
lista1 = [1,3,5,5,5,7,9,11,14]
lista2 = [5,6,8,10,12,15,19,20,21]

def nth1(lista, i, k=0):
    if (k == i - 1):
        rez = lista[0]
        return rez
    else:
        return nth(lista[1:], i, k+1)

### SAU ###

print(nth1(lista1, 3))

def nth(l,i):
    return l[i-1]

print("indicele cu numarul 3 =",nth([2,3,4,5,52], 3))

#----
#b)
'''
Implementați o funcție firstn care returnează o listă cu primele n elemente dintr-o listă dată.
'''

lista1 = [1,3,5,5,5,7,9,11,14]
lista2 = [5,6,8,10,12,15,19,20,21]

def firstn1(lista, i, k=0, sol=[]):
    if (k <= i - 1):
        sol.append(lista[k])
    else:
        return sol
    return firstn1(lista, i, k+1)


print(firstn1(lista1, 3))

### SAU ###

def firstn(l, n):
    return l[:n]

print(firstn([3,2,4,6,1,9], 2))

#----------------------------------------------------------------------------------------------

####################################################################################################
#                                   PARCURGERI DE LISTE                                            #
####################################################################################################

#EX 5
#a)
'''
 Implementați o funcție numita filter, cu acelasi comportament ca si functia predefintita filter, folosind reduce().
'''

def filter2(lista, conditie):
    return functools.reduce(lambda lista_noua, element: [element] + lista_noua if conditie(element) else lista_noua,
                            lista, [])


print("filter2 = ", end="")
print(filter2([1, 2, 3, 4], lambda x: x % 2 == 0))

#b)
'''
 Implementați funcția exists care determină (returnează adevărat/fals) dacă există
 un element din listă care satisface o condiție (o funcție de element cu valoare booleană, dată ca parametru).
'''

import functools
def exists(lista, cond):
    return True if functools.reduce(lambda acc, x: acc + 1 if cond(x) else acc + 0, lista, 0) > 0 else False

print(exists([2,4,5,6], lambda x: x==7))

# Programul verifica daca in lista exista un element 7
'''
in reduce functia lambda are obligatoriu 2 param.
    - pirmul acc se refera la val acumulata, se initializeaza la final dupa ,lista cu 0
    - al doolea argument, x se refera la elementul curent din lista care conditia
    - in if, if(x) deoarece verificam pentru elementul x conditia propusa
'''

#-----------------------------------------------------------------------------------------------------------

#EX 6
#a)

'''
Implementați folosind reduce o funcție countif care ia ca parametru o funcție f cu valori boolene și o 
listă și returnează numărul de elemente pentru care funcția f e adevărată.
'''

import functools

def countif(f, lista):
    return functools.reduce(lambda intial, element: intial + 1 if f(element) else intial, lista, 0)

print(countif(lambda x:x%2==1, [2,3,4,5,7,9]))
#---
#b)

import functools

def sumif(f, lista):
    return functools.reduce(lambda intial, element: intial + element if f(element) else intial, lista, 0)

print(sumif(lambda x:x%2==0, [2,3,4,5,7,9,10]))

#--------------------------------------------------------------------------------------------------

#EX 7
'''
Implementați funcțiile split și combine care transformă o listă de perechi într-o pereche de liste, și invers.
Ex: split([ (1,2), (3,4), 5,6)]) -> ([1,3,5], [2,4,6])  

combine([1,3,5], [2,4,6]) -> [ (1,2), (3,4), 5,6)]
'''

#--------------------------------------------------------------------------------------------------

#EX 8

'''
Implementați funcția partition care ia ca parametru o funcție cu valori boolene și o listă și returnează o pereche de liste, cu elementele care satisfac, respectiv nu satisfac funcția f.
# partition (lambda x : x >= 5) [4,6,7,5,4,8,9] -> ([6, 7, 5, 8, 9], [4, 4])
'''

#### VARIANTA SUS(PECTA) ####

import functools
# partition (lambda x : x >= 5) [4,6,7,5,4,8,9] -> ([6, 7, 5, 8, 9], [4, 4])

def nott(f):
    @functools.wraps(f)
    def g(*args,**kwargs):
        return not f(*args,**kwargs)
    g.__name__ = f'negate({f.__name__})'
    return g

def partition(f, lista):
    rez1 = list(filter(f, lista))
    rez2 = list(filter(nott(f), lista))
    print(rez1, rez2)

#Disclaimer: Partea cu functia nott e copiata pentru ca nu aveam idee de cum pot nega o functie lambda (expresia), ex: lambda x: x <=5 ---> lambda x: not(x<=5)


### VARIANTA LEGIT ###

def partition(f, lista):
    def part_aux(f, lista, rez1=[], rez2=[]):
        if(len(lista) > 0):
            h = lista[0]
            t = lista[1:]
            rez1.append(h) if f(h) else rez2.append(h)
            part_aux(f, t)
        else:
            print (rez1, rez2)
    part_aux(f,lista)


print(partition(lambda x: x >=5, [4,6,7,5,4,8,9]))

#---------------------------------------------------------------------------------

#EX 9
'''
Scrieți o funcție care ia o listă de cifre și returnează valoarea numărului cu cifrele respective.
'''
import functools

#M1

def numar(l):
    return functools.reduce(lambda nr, x: nr*10 + x, l, 0)

#M2
def cife(lista):
    if (len(lista) > 1):
        return lista[-1] + 10 * cife(lista[:-1])
    else:
        return lista[0]

print(numar([2,3,4,5]))
print(cife([2,3,4,5]))

#-------------------------------------------------------------------------

#EX 10
'''
Scrieți o funcție care elimină duplicatele consecutive: ia ca parametru o listă și construiește o listă în care toate 
secvențele de elemente consecutive egale au fost înlocuite cu un singur element.
'''

def duplicate(l):
    return list(set(l))

print(duplicate([2,2,3,4,5,5]))

#EX 11

#------

######################################################################################################################
#                                                 INTERCLASARE                                                       #
######################################################################################################################

#EX 12

'''
Scrieți o funcție care interclasează două liste, fiecare ordonată crescător, adică returnează lista cu elementele din ambele liste, ordonate.
Comparați primele elemente din ambele liste pentru a decide care va fi primul în rezultat, și apoi continuați cu listele rămase. 
'''

lista1 = [1,3,5,5,5,7,9,11,14]
lista2 = [5,6,8,10,12,15,19,20,21]

def interclasare(l1, l2):
    i = 0
    j = 0
    sol = []

    while(i < len(l1) and j < len(l2)):
        if(l1[i] < l2[j]):
            sol.append(l1[i])
            i=i+1
        else:
            sol.append(l2[j])
            j=j+1

    while(i<len(l1)):
        sol.append(l1[i])
        i=i+1

    while (j < len(l2)):
        sol.append(l2[j])
        j = j + 1

    return sol

print(interclasare(lista1,lista2))

#-------------------------------------------------------------------------------

#EX 13

'''
Scrieți o funcție care desparte o listă în două liste a căror lungime diferă cu cel mult 1, punând alternativ
câte un element în fiecare din liste. (Funcția va returna o pereche de liste).
'''

lista1 = [1,3,5,5,5,7,9,11,14]
lista2 = [5,6,8,10,12,15,19,20,21]

def desparte_rec(lst, st =[], dr=[], i=1):
    if(len(lst)>0):
        h = lst[0]
        t = lst[1:]
        if (i % 2 == 1):
            st.append(h)
        else:
            dr.append(h)
        return desparte_rec(t, i=i+1)
    else:
        return st,dr

print(desparte_rec(lista1))

#-------------------------------------------------------------------------------

#EX 14

'''

'''


lista3= [23,32,45,2,5,8,1,6,8,19]

def interclass(l1):
    def interclasare(l1, l2):
        i = 0
        j = 0
        sol = []

        while (i < len(l1) and j < len(l2)):
            if (l1[i] < l2[j]):
                sol.append(l1[i])
                i = i + 1
            else:
                sol.append(l2[j])
                j = j + 1

        while (i < len(l1)):
            sol.append(l1[i])
            i = i + 1

        while (j < len(l2)):
            sol.append(l2[j])
            j = j + 1

        return sol


    def desparte_rec(lst, st=[], dr=[], i=1):
        if (len(lst) > 0):
            h = lst[0]
            t = lst[1:]
            if (i % 2 == 1):
                st.append(h)
            else:
                dr.append(h)
            return desparte_rec(t, i=i + 1)
        else:
            return interclasare(qs(st), qs(dr))


    def qs(lst):
        if (len(lst) == 0):
            return []
        elif (len(lst) == 1):
            return [lst[0]]
        else:
            pivot = lst[0]
            st = []
            dr = []
            for i in range(1, len(lst)):
                if (lst[i] > pivot):
                    dr.append(lst[i])
                else:
                    st.append(lst[i])
            return qs(st) + [pivot] + qs(dr)
    return desparte_rec(l1)

print(interclass(lista3))
