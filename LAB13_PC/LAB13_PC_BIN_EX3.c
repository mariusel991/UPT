#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

void copy_bin2file(FILE *in, FILE *out);

int main(int argc, char *argv[]){
    
    ///Verificam corectitudinea argumentelor
    if(argc != 3){
        
        fprintf(stderr,"error\n");
        fprintf(stderr,"Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
        
    }
    
    ///Deschidem fisierul binar de input
    FILE *in;
    
    if((in = fopen(argv[1],"rb")) == NULL){
        
        perror("Error opening input file");
        exit(2);
    }
    
    ///Deschidem fisierul de output in write mode
    FILE *out;
    
    if((out = fopen(argv[2],"wb")) == NULL){
        
        perror("Error opening output file");
        fclose(in);
        exit(3);
        
    }
    
    copy_bin2file(in,out);
    
    fclose(in);
    fclose(out);
    
    printf("Operation successful!\n");
    return 0;
}

void copy_bin2file(FILE *in, FILE *out){
    
    ///Creeam un buffer temporar pt a retine informatia
    char buffer[BUFFER_SIZE];
    long int bytes_read;
    
    /*
    char *read_buffer = malloc(BUFFER_SIZE);
    if(read_buffer == NULL){
        perror("Error allocating buffer");
        fclose(in);
        fclose(out);
        exit(-1);
    }
    */

    while((bytes_read = fread(buffer,1,BUFFER_SIZE,in)) > 0){///Am putut citi cel putin un bytes
        
         // Write the data to the destination file
        if (fwrite(buffer, 1, bytes_read, out) != bytes_read) {
            fprintf(stderr, "Error writing to file\n");
            fclose(in);
            fclose(out);
            ///free(read_buffer);
            exit(4);
        }
        
    }
}


