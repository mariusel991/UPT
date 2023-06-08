import functools

graf_orientat = {1: [2, 3], 2: [1], 3: [2,1]}
graf_neorientat = {1: [2,3], 2: [3], 3: [2,1]}

def parcurgere_garf_orientat(graf_orientat):
    return functools.reduce(lambda _, graf_nod: afisare_graf(graf_nod), graf_orientat.items(), 0)

def afisare_graf(pereche):
    nod, muchie = pereche
    return functools.reduce(lambda _, noduri_asociate: print(str(nod)+" -> "+str(noduri_asociate)), muchie, 0)


print(parcurgere_garf_orientat(graf_orientat))

def verificare_graf_complet(graf_dict):
    rez = functools.reduce(lambda l_muchii, pereche_nod_nod_ascociat: adauga_pereche(pereche_nod_nod_ascociat, l_muchii), graf_dict.items(), [])
    n = len(graf_dict.keys())-1
    if (len(rez) == (n*(n+1)/2)):
        return True
    else:
        return False

def adauga_pereche(pereche,lista_muchii):
    nod, lista_noduri_asociate = pereche
    return functools.reduce(lambda lista_muchii, nod_pereche: lista_muchii if (nod, nod_pereche) in lista_muchii or (nod_pereche,nod) in
                            lista_muchii else [(nod, nod_pereche)] + lista_muchii, lista_noduri_asociate, lista_muchii)

print(verificare_graf_complet(graf_neorientat))


def existenta_arc(graf_o, nod1, nod2):
    if nod2 not in graf_o[nod1]:
        graf_o[nod1]+=[nod2]
        print(graf_o)
        return True
    else:
        return False

print(existenta_arc(graf_orientat, 2, 3))


