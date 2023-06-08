#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// Definim structura corespunzatoare
typedef struct{
    char title[128];
    int year;
    int budget;
}film;

int compare_year(const void *a, const void *b){
    film *p1 = (film *)a;
    film *p2 = (film *)b;
    
    return p1->year - p2->year;
}

int compare_budget(const void *a, const void *b){
    film *p1 = (film *)a;
    film *p2 = (film *)b;
    
    return p1->budget - p2->budget;
}

int compare_title(const void *a, const void *b){
    film *p1 = (film *)a;
    film *p2 = (film *)b;
    
    return strcmp(p1->title,p2->title);
}


int main(){
    FILE *f;
    
    ///Verificam daca putem deschide fisierul
    if((f = fopen("movies.csv","r")) == NULL){
        perror("ERROR: ");
        exit(1);
    }
    
    ///Citim fiecare linie din fisier dinamic -- PAS 1
    const size_t line_size = 256;
    char *line = malloc(line_size*sizeof(char));
    
    if(line == NULL){///Nu am putut aloca memorie
        perror("Fatal error: ");
        exit(-1);
    }
    
        ///Alocam un array de filme
        film* lista_filme = NULL;
        size_t nr_filme = 0;
        ////
    
    
    while(fgets(line,line_size,f) != NULL){///CITIRE LINIE - PAS 2
        
        size_t lung = strlen(line);
        //Verificam daca a incaput tot in buffer
        
        if(line[lung - 1] != '\n'){
            ///Nu a incaput tot deci realocam pentru a avea spatiu
            size_t aux;
            aux = lung;
            
            while(line[lung - 1] != '\n'){
                aux = aux * 2;
                line = realloc(line, aux*sizeof(char));
                
                ///Verificam cazul de eroare
                if(line == NULL) /// Nu s a putut aloca memorie
                {
                    perror("ERROR: Not enough memory!");
                    exit(-1);
                }
                
                ///citim continuarea ce a nu a intrat in buffer
                fgets(line + lung, aux - lung, f);
                lung = strlen(line);
            }
        }
        ///printf("%s", line);
        
        
        size_t i = 0;
        char *lista_campuri[7];
        char *val_camp = strtok(line,",");
        
        while(val_camp != NULL && i <= 6){
            lista_campuri[i++] = val_camp;
            val_camp = strtok(NULL, ",");
        }
        
        film sablon;
        strcpy(sablon.title, lista_campuri[2]);
        sablon.year = atoi(lista_campuri[0]);
        sablon.budget = atoi(lista_campuri[6]);
        
        lista_filme = realloc(lista_filme, sizeof(film)*(nr_filme + 1));
        lista_filme[nr_filme++] = sablon;
        
        
    }
   free(line);
   fclose(f);
   
   ///PARTEA out1.txt
   
   /* 
    for(int cnt = 0; cnt < nr_filme; cnt++){
        printf("%s\n", lista_filme[cnt].title);
    }
    */
   qsort(lista_filme, nr_filme, sizeof(film), compare_year);
   
   /*
   for(int cnt = 0; cnt < nr_filme; cnt++){
        printf("%d %s\n",lista_filme[cnt].year, lista_filme[cnt].title);
    }
    */
    
   ///deschidem/creem fisierul fisierul out1.txt
   if((f = fopen("out1.txt","w")) == NULL){
        perror("Error opening file");
        exit(1);
    }
    
    for(int i = 0; i < nr_filme; i++){
        fprintf(f, "%d %s %d\n",lista_filme[i].year, lista_filme[i].title, lista_filme[i].budget);
    }
    fclose(f);
   /// ---------------------------------------------------------------------
    
    ///PARTEA out2.txt.
    if((f = fopen("out2.txt","w")) == NULL){
        perror("Error opening file");
        exit(1);
    }
    
    qsort(lista_filme, nr_filme, sizeof(film), compare_title);
    
    for(int i = 0; i < nr_filme; i++){
        fprintf(f, "%d %s %d\n",lista_filme[i].year, lista_filme[i].title, lista_filme[i].budget);
    }
    fclose(f);
    ///-------------------------------------------------------------------------
    
    ///Partea out3.txt
    if((f = fopen("out3.txt","w")) == NULL){
        perror("Error opening file");
        exit(1);
    }
    
    qsort(lista_filme, nr_filme, sizeof(film), compare_budget);
    
    for(int i = 0; i < nr_filme; i++){
        fprintf(f, "%d %s %d\n",lista_filme[i].year, lista_filme[i].title, lista_filme[i].budget);
    }
    fclose(f);
    free(lista_filme);

    return 0;
}
