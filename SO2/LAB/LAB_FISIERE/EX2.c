/*
2. Să se scrie un program care primește ca și argument în linie de comandă calea către o intrare de pe disc.
Programul va afișa pentru intrarea respectivă următoarele informații:

-Tipul intrării: director / fișier obișnuit / legătură simbolică
-Permisiunile pentru owner/user, sub forma: rwx, - dacă vreuna lipsește
-Dimensiunea în octeți 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>

const char *get_permissions(__mode_t st_mode){

    static char str[10]={0};

    for(int i = 0; i < 3; i++){
        
        (1 << 8) >> (3 * i) & st_mode ? (str[3 * i] = 'r') : (str[3 * i] = '-');  /// R perms
        (1 << 8) >> (3 * i + 1) & st_mode ? (str[3 * i + 1] = 'w') : (str[3 * i + 1] = '-');  /// W perms
        (1 << 8) >> (3 * i + 2) & st_mode ? (str[3 * i + 2] = 'x') : (str[3 * i + 2] = '-'); /// X perms
    }

    str[9] = 0;
    return str;
}

void file_type(char *pathname){

    struct stat sb;

    if (lstat(pathname, &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (S_ISREG(sb.st_mode)){
        printf("%s - FILE %ldB %s\n", basename(pathname), sb.st_size, get_permissions(sb.st_mode));
    }
    else if (S_ISDIR(sb.st_mode)){
        printf("%s - DIRECTORY %ldB %s\n", basename(pathname), sb.st_size, get_permissions(sb.st_mode));
    }
    else if (S_ISLNK(sb.st_mode)){
        printf("%s - LINK %ldB %s\n", basename(pathname), sb.st_size, get_permissions(sb.st_mode));
    }

}

int main(int argc, char **argv){

    if (argc != 2){
        fprintf(stderr, "Invalid args!!");
        exit(EXIT_FAILURE);
    }

    file_type(argv[1]);

    return 0;
}
