#include <stdio.h>
#include <stdlib.h>

void CriaTabela(char ****TabelaRNA, int N){
    TabelaRNA = (char ***) malloc(N*sizeof(char **));
    for(int i=0;i<N;i++){
        TabelaRNA[i] = (char **) malloc(N*sizeof(char *);
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            TabelaRNA[i][j] = (char *) malloc(N*sizeof(char));
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;i<N;j++){
            memset(TabelaRNA[i][j], '*', sizeof(TabelaRNA[i][j][0])*N);
        }
    }
}

int main(){
    char RNAET[4];
    char Aminoacido;
    char ***TabelaRNA;
    int N;
    scanf("%i", &N);
    CriaTabela(&TabelaRNA, N);

    for(int i=0;i<N;i++){
        scanf("%s", RNAET);
        scanf("%c", Aminoacido);
        vetor()
    }
    return 0;
}