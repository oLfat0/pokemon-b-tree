#include <stdio.h>
#include <string.h>

#define D 5

typedef struct no
{
    int n;                      //Quantidade de chaves no Nó
    char *chaves[D];            //Lista de String -> Cada chave é uma String
    struct no* filhos[D+1];

}No;

void add_key(No* pt, char *key);
No* novo_no(int n);

int main(){
    const int n = 4;
    No* raiz = novo_no(n);

    raiz->chaves[0] = "B";
    raiz->chaves[1] = "C";
    raiz->chaves[2] = "D";
    raiz->chaves[3] = "F";



    for(int i=0; i<D; i++){
        printf("Chave[%d]: %s\n", i, raiz->chaves[i]);
    }

    add_key(raiz, "A");

    printf("\nAdicionando Valor:\n");
    for(int i=0; i<D; i++){
        printf("Chave[%d]: %s\n", i, raiz->chaves[i]);
    }
    printf("Novo numero de chaves: %d\n", raiz->n);

    return 0;
}

No* novo_no(int n){
    No* novo = malloc(sizeof(No));
    novo->n = n;

    for(int i=0; i<n; i++){
        novo->chaves[i] = '\0';
    }

    for(int i=0; i<n+1; i++){
        novo->filhos[i] = NULL;
    }


    return novo;
}

void add_key(No* pt, char *key){
    int nmr = pt->n;                                    //Número de chaves no Nó

    for(int i=0; i<nmr; i++){
        if(strcmp(key, pt->chaves[i])<0 && nmr<D){      //caso a key seja MENOR que os valores da chave no Nó && ainda haja espaço no nó para adicionar novas chaves
            
            for(int j=nmr; j>i; j--){
                pt->chaves[j] = pt->chaves[j-1];
            }

            pt->chaves[i] = key;                        //Adicionar na posição i após mover todos os outros elementos para a direita
            pt->n++;
            return;
        }       
    }
}