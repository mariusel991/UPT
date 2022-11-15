def graf_serelule(graf, lista):
    if len(lista) > 0:
        nod, nod_asociat = lista[0]
        if nod_asociat not in graf[nod]:
            graf[nod]+= [nod_asociat]
        return  graf_serban(graf, lista[1:])
    else:
        return graf

print(graf_serelule({1:[2,3,4], 2:[1,3], 3:[1,4], 4:[1,3]} ,[(2,4), (3,2)]))
