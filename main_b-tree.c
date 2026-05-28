#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D 2

typedef struct no
{
    int n;
    char chaves[2*D][15];
    struct no* filhos[(2*D)+1];
}no;

no* novo_no();
void menu();
void busca(no* raiz, char c[]);
void insere(no* raiz, char nome[]);

no* raiz = NULL;

int main()
{
    while (1)
    {
        menu();
    }
}

void menu()
{
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

no* novo_no()
{
    no* novo = malloc(sizeof(no));
    novo->n = 0;
    for(int i = 0; i < (2*D)+1; i++)
    {
        novo->filhos[i] = NULL;
    }
    for(int i = 0; i <2*D; i++)
    {
        novo->chaves[i][0] = '\0';
    }
    return novo;
}

void busca(no* raiz, char c[])
{
    if(raiz == NULL)
    {
        printf("Elemento nao encontrado\n");
        return;
    }
    int i = 0;
    while(i < raiz->n && strcmp(c,raiz->chaves[i])>0){i++;}

    if(strcmp(c,raiz->chaves[i])==0)
    {
        printf("Elemento encontrado!\n");
        return;
    }
    busca(raiz->filhos[i],c);
}
void insere(no* raiz, char nome[])
{
    if(raiz == NULL)
    {
        raiz = novo_no();
        for(int i = 0; i <= strlen(nome); i ++)
            raiz->chaves[0][i] = nome[i];
        raiz->n++;
        return;
    }
    

}