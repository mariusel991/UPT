#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void read_transform2hex(FILE *in, FILE *out);

int main(int argc, char *argv[]){
    
    if(argc != 3){
        fprintf(stderr,"Argument error\n");
        fprintf(stderr,"Usage %s <input_file> <output_file>\n",argv[0]);
        exit(1);
    }
    
    //Deschidem fisierul binar pt citire
    FILE *in;
    
    if((in = fopen(argv[1],"rb")) == NULL){
        perror("Error opening input file");
        exit(2);
    }
    
    ///Deschidem fisierul pentru scrierea in hex
    
    FILE *out;
    
    if((out = fopen(argv[2],"w")) == NULL){
        perror("Error opening output file");
        fclose(in);
        exit(3);
    }
    
    read_transform2hex(in,out);
    
    fclose(in);
    fclose(out);
    
    return 0;
}

void read_transform2hex(FILE *in, FILE *out){
    
    uint32_t nr;
    
    ///citim fiecare numar binar pe 4 bytes in
    
    while(fread(&nr,sizeof(uint32_t),1,in) != 0){
        
        ///fprintf(out,"%08X ", nr); /// - DEBUG
        
        ///CONVERSIE NUMAR IN HEX format TEXT
        char aux[9]="";
        sprintf(aux,"%08X",nr);
        fprintf(out,"%s",aux);
    }
}
