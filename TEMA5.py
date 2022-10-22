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

