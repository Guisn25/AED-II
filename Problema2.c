#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int senha;
    int valor;
    Tcomprador *prox;
}Tcomprador;

typedef struct{
    Tcomprador *comeco;
}Tfila;

void Insere(Tfila *Fila, int valor){
    static int senha=1;
    Tcomprador *Novo = malloc(sizeof(Tcomprador));
    if(Fila->comeco == NULL){
        Fila->comeco = Novo;
        Novo->prox = NULL;        
    }else{
        Tcomprador *aux = Fila->comeco;
        while(aux->prox != NULL && aux->prox->valor >= valor){
            aux = aux->prox;
        }
        Novo->prox = aux->prox;
        aux->prox = Novo;
    }
    Novo->senha = senha++;
    Novo->valor = valor;
}

void Remove(Tfila *Fila){
    Tcomprador *aux;
    print("%i\n", Fila->comeco->senha);
    aux = Fila->comeco;
    Fila->comeco = aux->prox;
    free(aux);
}

Free_Fila(Tfila *Fila){
    for(Tcomprador *aux = Fila->comeco; aux != NULL; aux = aux->prox){

    }

}

int main(){
    char acao;
    int valor;
    Tfila *Fila = malloc(sizeof(Tfila));
    Fila->comeco = NULL;
    while(1){
        scanf("%c", &acao);
        switch(acao){
            case 'c':
                scanf("%i", &valor);
                Insere(Fila, valor);
                break;
            case 'v':
                Remove(Fila);
                break;
            case 'f':
                Free_Fila(Fila);
                return 0;
                break;
        }
    }
}