/*
    Aplicația 4.0: Să se creeze o structură care reține următoarele informații despre un student: nume (maxim 20 de
caractere), nota. Să se citească un element din structură și să se afișeze pe ecran.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

/// Declaratii struct , typedef


typedef struct student{
    char nume[20];
    float nota;
}student;

void citire_student_info(student *s){

    printf("Introduceti numele:");
    fgets(s->nume,20, stdin);

    if(s->nume[strlen(s->nume) - 1] == '\n'){
        s->nume[strlen(s->nume) - 1] = 0;
    }

    printf("Nota:");
    scanf("%f", &s->nota);
}

void afisare_student_info(const student s){
    printf("%s\n",s.nume);
    printf("%f\n", s.nota);
}

int main()
{
    student s;

    citire_student_info(&s);
    afisare_student_info(s);

    return 0;
}
