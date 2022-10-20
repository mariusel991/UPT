#include <stdio.h>

void construct(int n){
    for(int j = 1; j <= n; j++){
        printf(" *");
    }
    printf("\n");
}
    
void corp(int n){
    for(int i=1; i <= n/2-1; i++){
        printf(" *");
        for(int j=1; j<=n; j++){
            printf("  ");
        }
        printf("\b\b\b");
        printf("*\n");
    }
}


int main(){
    int n;
    scanf("%d", &n);
    
    construct(n);
    corp(n);
    construct(n);
    corp(n);
    construct(n);
    
    return 0;
}
