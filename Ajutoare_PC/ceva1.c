#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct{
    
    uint8_t tag;
    uint32_t data;
    
}numar;

size_t citire_date_fisier(FILE *in, numar *nr);
void hex2text(uint32_t nr, char *rez);


int main(int argc, char *argv[]){
    
    /// Verificarea argumentelor de executie
    if(argc != 3){
        fprintf(stderr,"Incorrect argument number\n");
        fprintf(stderr,"USAGE %s <file_input> <file_output>\n", argv[0]);
        exit(1);
    }
    
    FILE *in;
    FILE *out;
    
    /* Deschidem fisierele asociate in (argv[1]) pt citire rb,
      respectiv out(argv[2]) pt scriere 'w'
    */
    
    in = fopen(argv[1],"rb");
    
    if (in == NULL){
        
        perror("Open error: ");
        exit(2);
    }
    
    out = fopen(argv[2],"w");
    if (out == NULL){
        
        fprintf(stderr,"Error oprning/creating the file\n");
        fclose(in);
        exit(3);
    }
    
    /// Partea de executie (functii)
    
    
    numar nr;
    size_t erori = 0;
    
    while (citire_date_fisier(in, &nr) != 0) { 
        
        //printf("%X\n",nr.tag);
       /// Avem un numar uint pe 4 bytes
        if(nr.tag == 0x55){
            fprintf(out,"uint: %u\n",nr.data);
        }
        ///Avem text
        else if(nr.tag == 0x98){
            
            char txt[5]="";
            hex2text(nr.data,txt);
            fprintf(out,"text: %s\n",txt);
        }
        
        else{
            erori++;
        }
    }
    
    fclose(in);
    fclose(out);
    
    return 0;
}

void hex2text(uint32_t nr, char *rez){
    
    char aux[32] = "";
    char tmp[3]="";
    uint8_t ch;
    uint8_t i = 0;
    
    sprintf(aux,"%X",nr);
    
    while(strlen(aux) > 0){
        
        tmp[0] = aux[0];
        tmp[1] = aux[1];
        tmp[2] = 0;
        
        ch = strtoll(tmp,NULL,16);
        rez[i++] = ch;
        
        strcpy(aux,aux+2);
    }
    
    rez[i] = '\0';
    
}

size_t citire_date_fisier(FILE *in, numar *nr){
    
    uint8_t v1 = 0;
    uint32_t v2 = 0;
    
    if(fread(&v1,sizeof(uint8_t),1,in) != 1){
       
       fprintf(stderr,"Reading type_error\n");
       return 0;
    }
    
    if(fread(&v2,sizeof(uint32_t),1,in) != 1){
       
       fprintf(stderr,"Reading data_error\n");
       return 0;
    }
    
    //printf("%X\n",v1);
    //printf("%X\n",v2);
    
    nr->tag = v1;
    nr->data = v2;
    
    
    return 1;
}
