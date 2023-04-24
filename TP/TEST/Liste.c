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

Node_t nou_nod(int nr, Node_t p){
    
    Node_t elem = (Node_t)malloc(sizeof(Node));
    if(NULL == elem){
        return NULL;
    }

    elem->data = nr;
    elem->next = p;

    return elem;
}

void init(List *lst){
    lst->prim = NULL;
    lst->ultim = NULL;
}

void afisare_lista(const List *lst){
    for(Node_t p = lst->prim; p!=NULL; p = p->next){
        printf("%d\n",p->data);
    }
}

int add_front(List *lst, int data){

    if(lst == NULL){
        return 0;
    }

    Node_t prim = lst->prim;

    if(!prim){/// lista este vida =>primul element estre si ultimul
        Node_t nod = nou_nod(data,NULL);
        if(!nod) return 0;
        lst->prim = lst->ultim = nod;
    }
    else{
        Node_t nod = nou_nod(data, prim);
        if(!nod) return 0;
        lst->prim = nod;
    }
    return 1;
}

int add_back(List *lst, int data){

    if(lst == NULL){
        return 0;
    }

    Node_t ultim = nou_nod(data,NULL);
    if(!ultim) return 0;
    
    if(lst->ultim){
        lst->ultim->next = ultim;
    }
    else{
        lst->ultim = lst->prim = ultim;
    }
    lst->ultim = ultim;

    return 1;
}


void reverse(List *lst){

    Node_t curr = lst->prim;
    Node_t prev = NULL;
    Node_t tmp = NULL;

    lst->ultim = curr;

    while(curr != NULL){
        tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    lst->prim=prev;
}

void reuniune(List *L, const List *l1, const List *l2){

    for(Node_t p1 = l1->prim; p1 != NULL; p1 = p1->next){
        int ok = 1;
        for(Node_t p2 = l2->prim; p2 != NULL; p2 = p2->next){
            if(p1->data == p2->data){
                ok = 0;
                break;
            }
        }
        if(ok) add_back(L,p1->data);
    }

    for(Node_t p1 = l2->prim; p1 != NULL; p1 = p1->next){
        int ok = 1;
        for(Node_t p2 = l1->prim; p2 != NULL; p2 = p2->next){
            if(p1->data == p2->data){
                ok = 0;
                break;
            }
        }
        if(ok) add_front(L,p1->data);
    }
}

int liste_egale(const List *l1, const List *l2){
    
    int ok;
    Node_t p1 = l1->prim;
    
    for(;p1 != NULL; p1 = p1->next){
        ok = 0;
        for(Node_t p2 = l2->prim;p2 != NULL; p2 = p2->next){
            if(p1->data == p2->data){
                ok = 1;
                break;
            }
        }
        if(ok == 0) return 0;
    }
    return 1;
}

/*
Aplicația 7.6: Să se scrie o funcție care primește ca parametri o listă (posibil vidă) de elemente sortate și un
element. Funcția va insera în listă noul element, astfel încât lista să rămână sortată. Folosind aceasta funcție, să
se scrie o funcție de sortare a unei liste, care primește ca parametru o listă nesortată și returnează una sortată.
Programul nu va folosi niciun vector.
*/

///Inserare pe pozitia curenta
Node_t nod_prev(List *lst, Node_t curr){
    Node_t aux = lst->prim;
    
    if(!aux) return NULL;
    else if(!(aux->next)) return NULL;

    while(aux->next != curr){
        aux = aux->next;
    }

    return aux;     
}

void inseare_cresc(List *lst, int data){
    
    Node_t curr = lst->prim;
    Node_t prev = NULL;
    Node_t nou = nou_nod(data,NULL);

    if(lst == NULL){
        return;
    }

    if((lst->prim == NULL) || (lst->ultim == NULL)){
        lst->prim = lst->ultim = nou;
        return;
    }

    if(curr->next == NULL){
        if(data <= curr->data){
            nou->next = curr;
            lst->prim = nou;
        }
        else{
            curr->next = nou;
            lst->ultim = nou;
        }
        return;
    }
    
    while(curr->next != NULL){
       
        if(data <= curr->data){
            prev->next = nou;
            nou->next = curr;
        }

        prev = curr;
        curr = curr->next;
    }

    if(curr->next == NULL){
        if(data > curr->data){
            curr->next = nou;
            lst->ultim = nou;
        }
        else{
            nou->next = curr;
            prev->next = nou;
        }
        return;
    }

}

List sort_list(List *lst){
    List New;
    init(&New);

    Node_t curr = lst->prim;
    while(curr != NULL){
        //printf("%d\n",curr->data);
        inseare_cresc(&New,curr->data);
        curr=curr->next;
    }

    return New;
}

void sterge_lista(List *lst){
    Node_t iterator = lst->prim;
    while(iterator != NULL){
        Node_t tmp = iterator->next;
        free(iterator);
        iterator = tmp;
    }
}


int main(int argc, char *argv[]){
    
    List lst1,L, lst2; //, lst3;
    init(&lst1);
    //init(&lst2);
    //init(&lst3);

    //add_back(&lst1,1);
    //add_back(&lst1,2);
    //add_back(&lst1,3);
    //add_back(&lst1,4);
   // add_back(&lst1,5);
    add_back(&lst2,7);
    add_back(&lst2,1);
    add_back(&lst2,3);
    add_back(&lst2,7);

    //afisare_lista(&lst1);
    //printf("\n");
    //afisare_lista(&lst2);
    //printf("\n");
    //reuniune(&lst3, &lst1, &lst2);
    //afisare_lista(&lst3);
    //printf("\nListele sunt:%d\n", liste_egale(&lst1,&lst2));
    //inseare_cresc(&lst1,-1);
    //inseare_cresc(&lst1,8);
    //inseare_cresc(&lst1,12);
    //inseare_cresc(&lst1,5);
    //afisare_lista(&lst1);

    init(&L);
    L = sort_list(&lst2);
    afisare_lista(&L);
    sterge_lista(&L);
    sterge_lista(&lst2);
    

    return 0;
}
