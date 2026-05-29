/*

Seja d um número natural. Uma árvore B de ordem d é uma árvore ordenada que é vazia
ou que satisfaz as seguintes condições:

(i) a raiz é uma folha ou possui no mínimo dois filhos;
(ii) cada nó interno (exceto a raiz) possui no mínimo d + 1 filhos;
(iii) cada nó possui no máximo 2d + 1 filhos;
(iv) todas as folhas estão no mesmo nível.


Um nó de uma árvore B é chamado página. Uma página armazena então diversos nós da tabela original. A estrutura
apresentada satisfaz ainda as propriedades seguintes.

(a) Seja m o número de chaves em uma página P NÃO folha. Então P tem m + 1 filhos. Consequentemente, cada página
possui entre d e 2d chaves, exceto o nó raiz, que possui entre 1 e 2d chaves.

(b) Em cada página P, as chaves estão ordenadas: s1, …, sm, d ≤ m ≤ 2d, exceto para a raíz onde 1 ≤ m ≤ 2d. 
E mais, P contém m + 1 ponteiros p0, p1, …, pm para os filhos de P. Nas páginas correspondentes às folhas, 
esses ponteiros indicam λ.

(c) Seja uma página P com m chaves:
    - para qualquer chave y, pertencente à página apontada por p0, y < s1;
    - para qualquer chave y, pertencente à página apontada por pk, 1 ≤ k ≤ m – 1, sk < y < sk+1;
    - para qualquer chave y, pertencente à página apontada por pm, y > sm.

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
int menu();
int busca(No* pt, char *x);
void insere(No* raiz, char *nome);

No* raiz = NULL;

int main(){
    while (1)
    {
        if(menu()==9){
            break;
        }
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

int menu(){
    int i = 0;
    printf("// ----- // ----- // ARVORE B // ----- // ----- //\n");
    printf("[1] - Buscar\n");
    printf("[2] - Inserir\n");
    printf("[9] - Finalizar\n");

    scanf("%d",&i);
    if(i == 1){
        char nome[20];
        printf("Digite o nome do Pokemon: ");
        scanf("%s", nome);
        busca(raiz, nome);
        return i;
    } 

    else if(i == 2){
        //insere();
        return i;
    }
    else if(i == 9){
        printf("Finalizando programa...\n");
        return i;
    }
    else{
        printf("Digite um valor válido\n");
        return 0;
    }
}

int busca(No* pt, char *x){
    if(pt == NULL){
        printf("Elemento nao encontrado\n");
        return 0;
    }

    int i = 0;

    while(i < pt->n && strcmp(x, pt->chaves[i])>0){     //Vai percorrendo a chave (Esq->Dir)
        i++;
    }

    if(i < pt->n && strcmp(x, pt->chaves[i])==0){
        printf("Elemento encontrado!\n");
        return 1;
    }

    busca(pt->filhos[i], x);                            //Desce para o filho[i]
}

void insere(No* pt, char *nome){
    if(pt==NULL){                   //Caso a árvore seja vazia
        pt->chaves[0] = nome;
        printf("Elemento '%s' inserido na primeira posicao da raiz...\n", nome);
        return;
    }

    //Função Busca():
    int i = 0;

    while(i < pt->n && strcmp(nome, pt->chaves[i])>0){     //Vai percorrendo a chave (Esq->Dir)
        i++;
    }

    if(i < pt->n && strcmp(nome, pt->chaves[i])==0){
        printf("Elemento ja se encontra na arvore. Nenhuma acao necessaria...\n");
        return;
    }
    

    insere(pt->filhos[i], nome);  //Desce para o filho[i]
}

void add_key(No* pt, char *key){
    /*
    Função responsável por organizar a posição da nova chave inserida de forma ordenada 
    em determinado Nó pt
    */
    int nmr = pt->n;                                    //Número de chaves no Nó

    for(int i=0; i<nmr; i++){
        if(strcmp(key, pt->chaves[i])<0 && nmr<D){      //Caso a key seja MENOR que os valores da chave no Nó && ainda haja espaço no nó para adicionar novas chaves
            
            for(int j=nmr; j>i; j--){
                pt->chaves[j] = pt->chaves[j-1];
            }

            pt->chaves[i] = key;                        //Adicionar na posição i após mover todos os outros elementos para a direita
            pt->n++;
            return;
        }       
    }
}
