/*
8. Să se scrie un program C, care primește ca și argumente în linie de comandă 3 elemente:
          <program> <cale-dir> <ext> <perm>
<cale-dir> reprezintă calea către un director de pe disc,
<ext> reprezintă un string care conține o extensie aleasă de către utilizator, începând
 cu punct și urmat de literele alese,
<perm> reprezină un grup de maxim 3 litere (r, w, x) alese de către utilizator.
Programul va procesa <cale-dir> și subdirectoarele acestuia, iar pentru fiecare fișier
 obișnuit cu extensia <ext> și având permisiunile <perm> pentru owner, va crea o copie
  a acelui fișier, având același nume, doar cu ''_copy'' la final. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/wait.h>


const char *get_perm(mode_t mode){

    static char perm[4] = {0};

    perm[0] = (mode & S_IRUSR ? 'r' : '-');
    perm[1] = (mode & S_IWUSR ? 'w' : '-');
    perm[2] = (mode & S_IXUSR ? 'x' : '-');
    perm[3] = '\0';

    return perm;
}

void parsare_director(char *pathname, const char *ext, const char *perm){

    DIR *dir = opendir(pathname);
    
    if(dir == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while((entry = readdir(dir)) != NULL){

        if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }
        
        char full_path[128]={0};
        snprintf(full_path,127, "%s/%.*s", pathname, (int)strlen(entry->d_name), entry->d_name);

        struct stat sb;

        if (lstat(full_path, &sb) < 0){
            perror("lstat");
            continue;
        }

        if (S_ISDIR(sb.st_mode)){
            parsare_director(full_path,ext,perm);
        }
        else if(S_ISREG(sb.st_mode)){

            if (strstr(entry->d_name,ext)){
                if(strcmp(get_perm(sb.st_mode),perm) == 0){

                    char copy_name[128] = {0};
                    strncpy(copy_name,entry->d_name,strlen(entry->d_name)-strlen(ext));
                    snprintf(copy_name+strlen(copy_name),strlen(ext)+6,"_copy%s",ext);

                    // printf("%s\n", copy_name);

                    char copy_path[128]={0};
                    char file_path[256]={0};

                    strcpy(copy_path,dirname(full_path));
                    sprintf(copy_path+strlen(copy_path),"/%s", copy_name);
                    snprintf(file_path,255,"%s/%.*s", full_path, (int)strlen(entry->d_name), entry->d_name);

                    // printf("%s\n%s\n", file_path, copy_path);


                    int pid;
                    if ((pid = fork()) < 0){
                        perror("fork");
                        continue;
                    }

                    if(pid == 0){

                        execlp("cp","cp", file_path,copy_path, NULL);
                        perror("exec");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }   

    closedir(dir);
}

int main(int argc, char **argv){

    if (argc != 4){
        fprintf(stderr,"args");
        exit(EXIT_FAILURE);

    }

    parsare_director(argv[1],argv[2],argv[3]);


    int w;
    int wstatus;

    while((w=waitpid(-1,&wstatus,0)) > 0){
        if (WIFEXITED(wstatus)){
            printf("Child with pid %d exited with %d\n", w, WEXITSTATUS(wstatus));
        }
    }


    return 0;
}
