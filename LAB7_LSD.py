import functools

#parcurgere
def afisare_graf(dictonar):
    return functools.reduce(lambda _,pereche: print_pereche(pereche), dictonar.items(), 0)

  
#afisare noduri - > arce
def print_pereche(pair):
    nod, nod_lista_asociat = pair
    functools.reduce(lambda _, nod_asociat: print(str(nod)+"->",str(nod_asociat)), nod_lista_asociat,0)




print(afisare_graf({1:[2,3], 2:[1], 3:[2]}))
