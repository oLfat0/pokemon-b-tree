/*

Seja d um número natural. Uma árvore B de ordem d é uma árvore ordenada que é vazia
ou que satisfaz as seguintes condições:

(i) a raiz é uma folha ou possui no mínimo dois filhos;
(ii) cada nó interno (exceto a raiz) possui no mínimo d + 1 filhos;
(iii) cada nó possui no máximo 2d + 1 filhos;
(iv) todas as folhas estão no mesmo nível.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define d 2

typedef struct no{
    char *chave[d];         //Lista de String -> Cada chave é uma String
    struct no* filhos[d+1];
} No;

char *pokemons[] = {"Bulbasaur", "Charmander", "Squirtle"};

No* novo_no(int m);

int main(){

    printf("%d\n", strlen(pokemons));

    return 0;
}

No* novo_no(int m){  // m -> Quantidade de chaves
    No* pt = (No*) malloc(sizeof(No));

    for(int i=0; i<m; i++){
        pt->chave[i] = NULL;
        pt->filhos[i] = NULL;
        if(i==m-1){
            pt->filhos[i+1] = NULL;
        }
    }
    return pt;    
}