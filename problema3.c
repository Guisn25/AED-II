#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int voto[3];
}Tcedula;


int PrimeiroTurno(int candidato[], int C){

    for(int i=0;i<C;i++){
        

    }

}

int main(){
    int V, C;
    int *candidato;
    Tcedula* cedula;

    scanf("%i %i", &V, &C);

    candidato = calloc(sizeof(int), C);
    cedula = malloc(V*sizeof(Tcedula));
    
    for(int i=0;i<V;i++){
        scanf("%i", cedula[i].voto[0]);
        if(cedula[i].voto[0] >= 1 && cedula[i].voto[0] <= C){
            candidato[cedula[i].voto[0]-1]++;
        }
        scanf("%i %i", cedula[i].voto[1], cedula[i].voto[2]);
    }
    
    PrimeiroTurno(candidato, C);

    return 0;
}