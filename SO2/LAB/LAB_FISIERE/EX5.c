/*
5. Să se scrie un program care primește un număr variabil de opțiuni din linia de comandă,
 urmate de minim 2 căii către intrări de pe disc.
În funcție de opțiunile primite, programul va afișa anumite informații pentru fiecare dintre
 intrările primite ca și argumente.
Opțiunile pot fi următoarele:

-i => afișare număr inode
-l => afișare număr de legături fizice
-u => afișare owner ID
-s => afișare dimensiune în octeți
-t => afișare data ultimei modificări
-a => afișare data ultimului acces
-pu => afișare permisiuni owner (format: rwx și -)
-pg => afișare permisiuni group (format: rwx și -)
-po => afișare permisiuni other (format: rwx și -)
-c => afișare conținut dacă este fișier, tipul intrării în caz contrar
Exemplu:
<program> -s -pu fisier1 fisier2 
fisier1   1234 bytes   rw-
fisier2   345 bytes     r--
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <time.h>

const char* file_perm(mode_t mode){

    static char perm[10]={0};
    
    perm[0] = (mode & S_IRUSR ? 'r' : '-');
    perm[1] = (mode & S_IWUSR ? 'w' : '-');
    perm[2] = (mode & S_IXUSR ? 'x' : '-');

    perm[3] = (mode & S_IRGRP ? 'r' : '-');
    perm[4] = (mode & S_IWGRP ? 'w' : '-');
    perm[5] = (mode & S_IXGRP ? 'x' : '-');

    perm[6] = (mode & S_IROTH ? 'r' : '-');
    perm[7] = (mode & S_IWOTH ? 'w' : '-');
    perm[8] = (mode & S_IXOTH ? 'x' : '-');

    perm[9]='\0';
    return perm;

}

int main(int argc, char **argv){

    int a_inode = 0;
    int a_leg_fiz = 0;
    int a_owner_id = 0;
    int a_dim = 0;
    int last_modif = 0;
    int last_acc = 0;
    int a_pu = 0;
    int a_pg = 0;
    int a_po = 0;
    int a_c = 0;

    int i = 1;
    

    for (; i < argc && argv[i][0] == '-'; i++){

        if (strcmp(argv[i], "-i") == 0) a_inode = 1;
        else if(strcmp(argv[i], "-l") == 0) a_leg_fiz = 1;
        else if (strcmp(argv[i], "-u") == 0) a_owner_id = 1;
        else if (strcmp(argv[i], "-s") == 0) a_dim = 1;
        else if (strcmp(argv[i], "-t") == 0) last_modif = 1;
        else if (strcmp(argv[i], "-a") == 0) last_acc = 1;
        else if (strcmp(argv[i], "-pu") == 0) a_pu = 1;
        else if (strcmp(argv[i], "-pg") == 0) a_pg = 1;
        else if (strcmp(argv[i], "-po") == 0) a_po = 1;
        else if (strcmp(argv[i], "-c") == 0) a_c = 1;
        else{
            fprintf(stderr, "invalid option\n");
        }
    }

    struct stat sb;

    if (argc - i < 2){
        fprintf(stderr, "at least 2 files expected!\n");
        exit(EXIT_FAILURE);
    }

    for (;i < argc; i++){

        if (lstat(argv[i], &sb) < 0){
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        printf("%s ",argv[i]);

        if (a_inode){
            printf("%ld ", sb.st_ino);
        }
        if(a_leg_fiz){
            printf("%ld ", sb.st_nlink);
        }
        if(a_owner_id){
            printf("%d ", sb.st_uid);
        }
        if(a_dim){
            printf("%ld ", sb.st_size);
        }
        if(last_modif){
            printf("%s ", ctime(&sb.st_mtime));
        }
        if(last_acc){
            printf("%s ", ctime(&sb.st_atime));
        }

        const char *prm = file_perm(sb.st_mode);
        
        if(a_pu){
            for(int i = 0; i < 3; i++) printf("%c", prm[i]);
            printf(" ");
        }
        if(a_pg){
            for(int i = 3; i < 6; i++) printf("%c", prm[i]);
            printf(" ");
        }
        if(a_po){
            for(int i = 6; i < 9; i++) printf("%c", prm[i]);
            printf(" ");
        }
        if(a_c){
            if(S_ISREG(sb.st_mode)){
                
                printf("\n");
                char cmd[32]={0};
                strcat(cmd,"cat ");
                strcat(cmd,argv[i]);

                usleep(1e5*2);
                system(cmd);
            }
            else if (S_ISDIR(sb.st_mode)){
                printf("Directory");
            }
            else if (S_ISLNK(sb.st_mode)){
                printf("LINK");
            }
        }

        printf("\n");
        
    }

    return 0;
}
