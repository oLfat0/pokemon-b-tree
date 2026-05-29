/*

Seja d um número natural. Uma árvore B de ordem d é uma árvore ordenada que é vazia
ou que satisfaz as seguintes condições:

(i) a raiz é uma folha ou possui no mínimo dois filhos;
(ii) cada nó interno (exceto a raiz) possui no mínimo d + 1 filhos;
(iii) cada nó possui no máximo 2d + 1 filhos;
(iv) todas as folhas estão no mesmo nível.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D 2

typedef struct no
{
    int n;                      //Quantidade de chaves no Nó
    char *chaves[D];            //Lista de String -> Cada chave é uma String
    struct no* filhos[D+1];

}No;

No* novo_no(int n);
void menu();
void busca(No* pt, char *x[]);
void insere(No* raiz, char nome[]);

No* raiz = NULL;

int main()
{
    while (1)
    {
        menu();
    }
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

void menu(){
    int i= 0;
    printf("// ----- // ----- // ARVORE B // ----- // ----- //\n");
    printf("[1] - Buscar\n");
    printf("[2] - Inserir\n");
    printf("[9] - Finalizar\n");
    scanf("%d",&i);
    if(i == 1)
    {
        char nome[20];
        printf("Digite o nome do pokemon: ");
        scanf("%s",nome);
        busca(raiz,nome);
    } 
    if(i == 2)
    {
        //insere();
    }
    if(i == 9)
    {

    }
}

void busca(No* pt, char *x){
    if(pt == NULL){
        printf("Elemento nao encontrado\n");
        return;
    }

    int i = 0;

    while(i < pt->n){
        if(strcmp(x, pt->chaves[i])>0){
            i++;
        }
    }

    if(strcmp(x, pt->chaves[i])==0){
        printf("Elemento encontrado!\n");
        return;
    }

    busca(pt->filhos[i], x);
}

void insere(No* raiz, char *nome){
    if(raiz==NULL){                 //Caso a árvore seja vazia
        raiz->chaves[0] = nome;
    }

    int i=0;
    while(raiz->chaves[i]!='\0'){
        if(strcmp(raiz->chaves[i], nome) == 0){

        }
    }
}