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



int main(){
    char aux[20];
    char s[]="ana";
    
    mystrcpy(aux,s);
    
    printf("%s\n",p);
    
    return 0;
}
