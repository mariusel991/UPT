/*
 Un fisier binar incepe cu un numar fara semn pe 32 de biti care reprezinta numarul de inregistrari din
 fisier. Dupa acesta urmeaza inregistrarile, implementate prin structura urmatoare:
- an - nr fara semn pe 16 biti
- luna - nr fara semn pe 8 biti
- zi - nr fara semn pe 8 biti
- idx senzor - nr fara semn pe 8 biti
- valoare - nr cu semn pe 16 biti
O inregistrare codifica valoarea citita de un senzor la o anumita data. Valorile corecte pot fi in
intervalul [-1000,1000]. Daca un senzor da din cand in cand valori in afara intervalului, atunci se
considera ca are probleme. Daca toate valorile sunt in afara intervalului, atunci senzorul este defect.
Cerinte:
- sa se scrie o functie care creaza un fisier de test, ce cuprinde valori pentru un senzor care merge,
altul care are probleme
si altul defect.
- sa se citeasca fisierul de test si sa se afiseze care senzor merge, care are probleme si care e defect.
- se cere de la tastatura un an si o luna. Se cere sa se afiseze toate valorile senzorilor din acel an/luna.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


#define MIN_VALUE -1000
#define MAX_VALUE  1000

#define MAX_SENORS 256
#define MAX_RECORDS 100





typedef struct{
    
    uint8_t zi;
    uint8_t luna;
    uint16_t an;
    uint8_t idx_senzor;
    int16_t valoare;
    
}inregistrare;

typedef struct{
    uint32_t aparitii;
    uint32_t probleme;
}sensor_data;





void create_test_file();
void read_values(uint8_t luna, uint16_t an);





int main(){
    
    uint16_t year;
    uint8_t month;
    printf("Introduceti luna (in cifre): ");
    scanf("%hhu", &month);
    printf("Introduceti anul: ");
    scanf("%hu", &year);
    
    create_test_file();
    read_values(month,year);
    
}



void read_values(uint8_t luna, uint16_t an){
    
    ///Deschidem fiserul test creat
    FILE *f;
    f = fopen("test.bin","rb");
    
    ///Nu am putut deschide fiserul test
    if(f == NULL){
        perror("ERROR ");
        return;
    }
    
    ///Citim cate aparitii de inregistrari avem
    uint32_t aparitii;
    
    if(fread(&aparitii,sizeof(uint32_t),1,f) == 0){
        fprintf(stderr,"Test reading values error\n");
        fclose(f);
        return;
    }
    
    sensor_data *p = malloc(MAX_SENORS*sizeof(sensor_data));
    
    if(p == NULL){
        fprintf(stderr,"Memory error for storing sensor data\n");
    }
    ///Initializam structura p
    memset(p, 0, MAX_SENORS * sizeof(sensor_data));
    int i_max = -1;
    
    
    ///Verificam daca avem inregistrari in luna x si anul y
    uint8_t ok = 0;
    
    ///Citim inregistrarile
    inregistrare senzor;///Decalram o variabila de tip structura pentru organizarea datelor
    while(fread(&senzor,sizeof(inregistrare),1,f) == 1){
        ///Am putut citi inregistrea
        if(senzor.luna == luna && senzor.an == an){
            
            ok = 1;///Avem o inregistrare;
            
            printf("An: %d\n", senzor.an);
            printf("Luna: %d\n", senzor.luna);
            printf("Zi: %d\n", senzor.zi);
            printf("Senzor idx: %d\n", senzor.idx_senzor);
            printf("Valoare: %d\n", senzor.valoare);
            printf("\n");
        }
        if(senzor.idx_senzor > i_max) i_max = senzor.idx_senzor;
        p[senzor.idx_senzor].aparitii++;
        
        if(senzor.valoare < MIN_VALUE || senzor.valoare > MAX_VALUE){
            p[senzor.idx_senzor].probleme++;
        }
        
    }
    
    for(uint8_t poz = 0; poz <= i_max; poz++){
       
        if(p[poz].probleme == 0){
            printf("Senzorul cu idx[%hhu] functionaza perfect\n",poz);
        }
        else if(p[poz].probleme < p[poz].aparitii){
            printf("Senzorul cu idx[%hhu] are probleme\n",poz);
        }
        else{
            printf("Senzorul cu idx[%hhu] este defect\n",poz);
        }
    }
    
    if(ok == 0){
        printf("Nu exista valori pentru luna %hhu si anul %hu\n",luna,an);
        fclose(f);
        return;
    }
    
    ///clean up
    free(p);
    fclose(f);
    
    
}

void create_test_file(){

    inregistrare array[MAX_RECORDS];
    int32_t range;
    range = MAX_VALUE - MIN_VALUE;
    ///Genereram inregistrari pozitive si negative
    srand(time(NULL));
    
    for(int i = 0; i < MAX_RECORDS; i++){
        array[i].zi = rand() % 31 + 1;
        array[i].luna = rand() % 12 + 1;
        array[i].an = 2020 + rand() % 4;
        array[i].idx_senzor = rand() % 255;
        array[i].valoare = rand() % range + MIN_VALUE + 1000;
    }
    
    FILE *fp;
    
    fp = fopen("test.bin","wb");
    if(fp == NULL){
       fprintf(stderr,"Error creating/opening file\n");
       return;
    }
    
    uint32_t aparitii = sizeof(array)/sizeof(inregistrare);
    
    fwrite(&aparitii,sizeof(uint32_t),1,fp);///scriem in fisier aparitiile
    fwrite(array, sizeof(inregistrare), aparitii,fp);///apoi datele pe rand
    
    fclose(fp);
    
}
