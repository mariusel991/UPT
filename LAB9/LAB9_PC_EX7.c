#include <stdio.h>
#include <string.h>

size_t mystrlen(const char *s){
    size_t i = 0;
    while(*(s+i) != '\0'){
        i++;   
    }
    return i;
}

char *mystrcpy(char *dest, const char *src){
    int i;
    ///printf("%d %d\n", sizeof(dest), sizeof(src));
    for(i = 0; src[i] != '\0'; i++){
        *(dest+i) = *(src+i);
    }
    *(dest+i)='\0';
    return dest;
}

char *mystrncpy(char *dest, const char *src, size_t n){
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';

    return dest;

}

char *mystrchr(char *s, const int c){
    while(*s != c && *s != '\0'){
        s++;
    }
    if(*s == c){
        return (char *)s;
    }
    else{
        return NULL;
    }
}

char *mystrstr(char* str, const char* strSub){
    for(int i = 0; i < mystrlen(str) - mystrlen(strSub); i++){
        int ok = 1;
        for(int j = 0; j < mystrlen(strSub); j++){
            if(*(str+i+j) != *(strSub+j)){
                ok = 0;
                break;
            }
        }
        if(ok == 1) return (char *)(str+i);
    }
    return NULL;
}

int mystrcmp(const char *s1, const char *s2){
    while(*s1 != '\0'){
        if(*s1 != *s2){
            break;
        }
        s1++;
        s2++;
    }
    return (unsigned const char*)s1 - (unsigned const char* )s2;
}

char *mystrcat(char *dest, const char *src){
    size_t ldest = mystrlen(dest);
    for(int i = 0; i < mystrlen(src); i++){
        *(dest + ldest + i) = *(src+i);
    }
    *(dest+mystrlen(dest)) = '\0';
    return dest;
}

int main(){
    char aux[20]="";
    char s[]="ana are mere";
    
    mystrcpy(aux,s);
    printf("%s\n", mystrstr(s,"r"));
    strcat(aux,"are mere");
    printf("%s\n", aux);
    
    
    return 0;
}
