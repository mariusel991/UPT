#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef Node* Node_t;

typedef struct List{
    Node_t prim;
    Node_t ultim;
}List;

void init(List *lst){
    lst->prim = NULL;
    lst->ultim = NULL;
}

Node_t new(int data, Node_t pointer){

    Node_t e = (Node_t)malloc(sizeof(Node));
    if(!e)return NULL;

    e->data = data;
    e->next = pointer;

    return e;
}

void add_front(List *lst, int data){
    
    if(lst == NULL){/// Lista Nula
        return;
    }

    Node_t prim = lst->prim;
    if(!prim){/// Lista nu are nici un element
        prim = new(data,NULL);
        lst->prim = prim;
        lst->ultim = prim;
        return;
    }

    /// Avem elemente in lista
    prim = new(data,NULL);
    prim->next = lst->prim;
    lst->prim = prim;
    return;
}

void add_back(List *lst,int data){

    if(lst == NULL){
        return;
    }

    Node_t ultim = lst->ultim;
    if(!ultim){/// Daca ultim e Null nu avem nici un element
        
        ultim = new(data,NULL);
        if(!ultim)  return;

        lst->prim = ultim;
        lst->ultim = ultim;
        return;
    }

    ///Avem deja o lista cu elemente
    ultim = new(data,NULL);
    lst->ultim->next = ultim;
    lst->ultim = ultim;

    return;
}

void afisare(List *lst){
    Node_t iterator = lst->prim;
    
    while(iterator != NULL){
        printf("%d\n",iterator->data);
        iterator=iterator->next;
    }
}

void delete(List *lst){
    
    Node_t itr = lst->prim;
    Node_t tmp = NULL;
    
    while(itr != NULL){
        tmp = itr->next;
        free(itr);
        itr = tmp;
    }
    return;
}

/*
Pentru implementarea listei care memorează ultimul element, să se scrie o funcție care primește
două liste sortate și returnează lista sortată care conține toate elementele lor. Pentru lista rezultată se va folosi
doar operația de adăugare la sfârșit de listă.
Exemplu: {1, 2, 7, 8} și {2, 9} -> {1, 2, 2, 7, 8, 9}
*/
List *interclasare_liste(List *l1, List *l2){
    
    List *Sol = NULL;
    Sol = malloc(sizeof(List));
    if(!Sol) return NULL;
    
    init(Sol);

    Node_t i = l1->prim;
    Node_t j = l2->prim;

    while((i != NULL) && (j != NULL)){
        if(i->data < j->data){
            add_back(Sol,i->data);
            i=i->next;
        }
        else if(i->data == j->data){
            add_back(Sol,i->data);
            add_back(Sol,j->data);
            i=i->next;
            j=j->next;
        }
        else{
            add_back(Sol,j->data);
            j=j->next;
        }
    }

    while(i != NULL){
        add_back(Sol,i->data);
        i = i->next;
    }

    while(j != NULL){
        add_back(Sol,j->data);
        j = j->next;
    }
    
    return Sol;
}

int main(){

    List l1,l2, *L = NULL;
    init(&l1);
    init(&l2);

    add_back(&l1,1);
    add_back(&l1,2);
    add_back(&l1,7);
    add_back(&l1,8);
    add_back(&l2,2);
    add_back(&l2,9);

    L = interclasare_liste(&l1,&l2);

    //afisare(&l1);
    delete(&l1);
    afisare(L);

    return 0;
}
