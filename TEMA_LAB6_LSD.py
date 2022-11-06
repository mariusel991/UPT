print("EXERCITII CU MULTIMI\n")

m1 = {1,2,3,4,5,6}

'''
1. Scrieți o funcție care ia ca parametru o mulțime și o tipărește pe o linie, între acolade { } și cu virgulă între elemente. 

Input: {1,2,3}; Output: {1,2,3}
'''

import functools

def afisare_multime(m):
    print("{", end="")
    functools.reduce(lambda acc, elem_curent: print(elem_curent, end=","), m, None)
    print("\b",end="")
    print("}",end="")


afisare_multime(m1)

#-------------------------------------------------------------------------------------/

'''
2. Scrieți o funcție care ia o listă de perechi (de tip precizat) și returnează mulțimea elementelor de pe 
prima poziție din fiecare pereche (variante: a doua poziție; ambele poziții, dacă sunt de același tip).

Input: [(1,2), (3,4)]; Output: {1,3}
'''

def lista_multime_perechi(lst):
    if len(lst) > 0 :
        a, b = lst[0] # a = 1 , b = 2 - iau sucesiv valorile din primul tuplu
        return {a} | lista_multime_perechi(lst[1:])
    else:
        return set()


print() # <--- asta e un '\n' mai pe buget
print(lista_multime_perechi([(1,2), (3,4)]))

#---------------------------------------------------------------------------/

'''
3. Implementați funcția standard filter care ia ca parametri o funcție booleană f și o mulțime s și returnează mulțimea 
elementelor din s care satisfac funcția f.

Input: lambda x: x % 2 == 0, {1, 2, 3, 4}; Output: {2, 4}
'''

def filter_multime(f, s):
    return functools.reduce(lambda acc, element: acc | {element} if f(element) else acc, s, set())

print(filter_multime(lambda x: x % 2 ==0, {1,2,3,4,5,6}))

#-------------------------------------------------------------------------------------------------/

'''
4. Implementați funcția standard partition care ia ca parametri o funcție booleană f și o mulțime s și 
returnează o pereche de mulțimi, cu elementele din s care satisfac, respectiv nu satisfac funcția f.

Input: lambda x: x % 2 == 0, {1, 2, 3, 4}; Output: ({2, 4}, {1, 3})
'''

def std_partition(functie, multime):
    return functools.reduce(lambda acc, element: ({element} | acc[0], acc[1]) if functie(element)
                            else ({element} | acc[1], acc[0]), multime,(set(),set()))

print(std_partition(lambda x: x % 2 == 0, {1, 2, 3, 4}))

#-----------------------------------------------------------------------------------------------/

'''
5. Scrieți o funcție care ia o lista de mulțimi (de exemplu, de șiruri), și returnează reuniunea 
(variantă: intersectia) mulțimilor.

Input: [{1, 2, 3}, {1, 2, 3, 4}, {3, 5, 6, 7}]; Output: reuniune: {1, 2, 3, 4, 5, 6, 7}; intersectie: {3}
'''

def reuniunie_liste_multimi(lista):
    m_final=set()
    def f_aux(lista , m_final):
        if(len(lista) > 0):
            m_aux = functools.reduce(lambda acc, elem: acc | {elem}, lista[0], set())
            #print(m_aux)
            return f_aux(lista[1:], m_final | m_aux)
        else:
            return m_final
    return f_aux(lista, m_final)

print("reuniune:", reuniunie_liste_multimi([{1, 2, 3}, {1, 2, 3, 4}, {3, 5, 6, 7}]))

def intersectie_liste_multitmi(lista_cu_multimi):
    def f_aux(lista , m_intersectie):
        if(len(lista) > 0):
            m_aux = functools.reduce(lambda acc, elem: acc | {elem}, lista[0], set())
            #print(m_aux)
            return f_aux(lista[1:], m_intersectie & m_aux)
        else:
            return m_intersectie

    return f_aux(lista_cu_multimi, lista_cu_multimi[0]) # Prima multime o folosim pentru a compara cu intersectia

print("intersectie:",intersectie_liste_multitmi([{1, 2, 3}, {1, 2, 3, 4}, {3, 5, 6, 7}]))

#------------------------------------------------/

'''
6. Scrieți o funcție care returnează mulțimea cifrelor unui număr. Scrieți apoi altă funcție care ia o mulțime 
de numere și returnează reuniunea/intersecția dintre mulțimile cifrelor lor.

Input: {1234, 123, 127}; Output: reuniune: {1, 2, 3, 4, 7}; intersectie: {1, 2}
'''

def multime_cifre_numar(nr):
    if nr < 10:
        return {nr}
    else:
        return {nr%10} | multime_cifre_numar(nr//10)


def multime_numere(m):
    return functools.reduce(lambda acc, element: multime_cifre_numar(element) | acc ,m,set())

def multime_numere_intersectie(m):
    return functools.reduce(lambda acc, element: multime_cifre_numar(element) & acc, m, functools.reduce(lambda acc, element: multime_cifre_numar(element) | acc ,m,set()))

print("reuniune ex6:",multime_numere({1234, 123, 127}))
print("intersectie ex6:", multime_numere_intersectie({1234, 123, 127}))

###    END OF PROBLEME CU MULTIMI    ###

print("\n","EXERCITII CU DICTIONARE\n")

'''
1. Scrieți o funcție care ia o listă de asociere cu perechi de tip (șir, întreg)
și creează un dicționar în care fiecare șir e asociat cu suma tuturor valorilor cu care e asociat în listă.

Input: [('a', 7), ('b', 5), ('c', 2), ('a', 3), ('b', 3)]; Output: {'a': 10, 'b': 8, 'c': 2}
'''

def adaugare_pereche(dictionar, pereche):
    cheie, valoare = pereche
    if cheie in dictionar.keys() :
        dictionar[cheie] += valoare
    else:
        dictionar[cheie] = valoare

    return dictionar

def creare_dictionar_prin_ascociere_lista(lista):
    return functools.reduce(lambda dictinar_final, pereche: adaugare_pereche(dictinar_final, pereche), lista, {})

print("dictionar - lista asociere: ", end = "")
print(creare_dictionar_prin_ascociere_lista([('a', 7), ('b', 5), ('c', 2), ('a', 3), ('b', 3)]))

#----------------------------------------------------------------------------------------------------/

'''
2. Scrieți o funcție care ia o listă de șiruri de caractere și creează un dicționar în care fiecare șir e asociat cu numărul aparițiilor din listă.

Input: ["aaa", "bbb", "aabbb"]; Output: {'a': 5, 'b': 6}
'''

#print(dict.items({'a': 5, 'b': 6}))

def lista_convert_dicitonar_litere(lista):
    return functools.reduce(lambda dictonar_final, cuvant: creare_dictionar(dictonar_final, cuvant), lista, {})

def creare_dictionar(dictionar, cuvant):
    if len(cuvant) > 0:
        cheie = cuvant[0]
        if cheie in dictionar.keys():
            dictionar[cheie] += 1
        else:
            dictionar[cheie] = 1

        return creare_dictionar(dictionar , cuvant[1:])
    else:
        return dictionar

print("dictionar_creat:",lista_convert_dicitonar_litere(["aaa", "bbb", "aabbb"]))

#--------------------------------------------------------------------------------------------/

'''
3. Implementați cu ajutorul lui reduce funcția filter care creează un nou dicționar doar cu perechile din 
dicționarul dat care satisfac o funcție dată.

Input: dict: {'a': 5, 'b': 7, 'c': 1}; conditie: valoare >= 5; Output: {'a': 5, 'b': 7}
'''

def filter_dictionar(dictionar, conditie):
    return functools.reduce(lambda dictionar_nou, elemente_pereche: adaugare_pereche(dictionar_nou, elemente_pereche) if conditie(elemente_pereche)
                            else dictionar_nou, dictionar.items(), {})

def conditie_dict(dictionar_elem):
    cheie, valoare = dictionar_elem
    if valoare >= 5 :
        return True
    else:
        return False

''' Functie creata mai sus
def adaugare_pereche(dictionar, pereche):
    cheie, valoare = pereche
    if cheie in dictionar.keys() :
        dictionar[cheie] += valoare
    else:
        dictionar[cheie] = valoare

    return dictionar
'''

print(filter_dictionar({'a': 5, 'b': 7, 'c': 1}, conditie_dict))

#--------------------------------------------------------------------------/

def exists(cond, dictionar):
    return functools.reduce(lambda rezultat,pereche : True or rezultat if cond(pereche) else rezultat, dictionar.items(), False)

def conditie(pereche):
    cheie,valoare = pereche
    if valoare >= 5:
        return True
    else:
        return False

print(exists(conditie, {'a': 5, 'b': 7, 'c': 1}))


def for_all(cond1, dictionar2):
    return functools.reduce(lambda rezultat, pereche: True and rezultat if  cond1(pereche) else False, dictionar2.items(), True)

print(for_all(conditie, {'a': 5, 'b': 7, 'c': 1}))

#-------------------------------------------------------------------------------------------/

'''
5. Implementați cu ajutorul lui reduce funcția map care construiește un dicționar în care toate valorile au fost transformate 
folosind o funcție dată ca parametru.

Input: {'a': 5, 'b': 7, 'c': 6}, lambda x: x + 1; Output: {'a': 6, 'b': 8, 'c': 7}
'''

def map_dictionar(dictionar, functie):
    return functools.reduce(lambda acc, pereche: f(acc, pereche, functie), dictionar.items(), {})

def f(dictionar, pereche, f):
    cheie, valoare = pereche
    valoare = f(valoare)
    dictionar[cheie] = valoare
    #print(dictionar)
    return dictionar

print(map_dictionar({'a': 5, 'b': 7, 'c': 6}, lambda x: x + 1))

#--------------------------------------------------------------------------------------------------/
'''
6. Scrieți o funcție care primește un dicționar de la șiruri la întregi și o listă de șiruri și returnează mulțimea 
tuturor valorilor din dicționar care corespund șirurilor din listă.

Input: {'aa': 5, 'bb': 7, 'ca': 6}, ['aa', 'bb', 'c']; Output: {5, 7}
'''

def ex6(d1, list1):
    def f_aux(d1, lista, m_final):
        if len(lista) > 0 :
            if lista[0] in d1.keys():
                m_final = m_final | {d1[lista[0]]}
            return f_aux(d1,lista[1:], m_final)
        else:
            return m_final
    return f_aux(d1, list1, set())


def ex6_a(d1, lista2): # Alternativa
    return functools.reduce(lambda m, elem: m | {d1[elem]} if elem in d1.keys() else m, lista2, set())

print(ex6({'aa': 5, 'bb': 7, 'ca': 6}, ['aa', 'bb', 'c']))
print(ex6_a({'aa': 5, 'bb': 7, 'ca': 6}, ['aa', 'bb', 'c']))
