#include <stdio.h>
#include <stdlib.h>
 
void Ordena(int S[], int TamS){
    int x;
    int j;
    for(int i=1; i<TamS; i++){
        x = S[i];
        j = i-1;
        while(x<S[j] && j>=0){
            S[j+1] = S[j];
            j--;
        }
        S[j+1] = x;
    }
}

int ContaSoma(int S[], int TamS, int N){
    int cont = 0;
    int i = 0;
    int j = TamS-1;
    while(i<j){
        if(S[j]+S[i] == N){
            cont++;
            i++;
        }else if(S[j]+S[i]>N){
            j--;
        }else{
            i++;
        }
    }
 
    return cont;
}
 
int main(){
    int TamS, N;
    int *S;
    scanf("%i %i", &TamS, &N);
 
    S = (int *) malloc(TamS*(sizeof(int)));
 
    for(int i=0;i<TamS;i++){
        scanf("%i", &S[i]);
    }
    Ordena(S, TamS);
    
    printf("%i", ContaSoma(S, TamS, N));
 
    return 0;
}