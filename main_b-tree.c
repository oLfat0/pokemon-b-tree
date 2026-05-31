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
    char *chaves[2*D];            //Lista de String -> Cada chave é uma String
    struct no* filhos[2*D+1];

}No;

No* novo_no(int n);
int menu();
int busca(No* pt, char *x);
void insere(No* pai, No* pt, char *nome);
int add_key(No* pt, char *key);
void split(No* pai, No* pt,  char *key);

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

    for(int i=0; i<2*D; i++){
        novo->chaves[i] = '\0';
    }

    for(int i=0; i<2*D+1; i++){
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

void insere(No* pai, No* pt, char *nome){
    if(pt==NULL){                   //Caso a árvore seja vazia
        pt = novo_no(0);
        pt->chaves[0] = nome;
        pt->n++;

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
    else if(pt->filhos[i] == NULL){
        if(add_key(pt, nome)==1) return;                           //Insere a nova chave no Nó
        else{
            split(pai, pt, nome);           //Função Split
        }
    }
    else if(pt->filhos[i]->n >= 2*D){
        split(pt, pt->filhos[i], nome);

        i = 0;                                                 //Recalculando o valor de 'i'
        while(i < pt->n && strcmp(nome, pt->chaves[i])>0){     //Vai percorrendo a chave (Esq->Dir)
            i++;
        }

        return insere(pt, pt->filhos[i], nome);  //Desce para o filho[i]
    }

    else{
        return insere(pt, pt->filhos[i], nome);  //Desce para o filho[i]
    }
}

int add_key(No* pt, char *key){
    /*
    Função responsável por organizar a posição da nova chave inserida de forma ordenada 
    em determinado Nó pt
    */
    int nmr = pt->n;                                    //Número de chaves no Nó

    if(nmr<2*D){                                        //Caso a quantidade de elementos dentro do Nó não exceda o máximo 
        for(int i=0; i<nmr; i++){
            if(strcmp(key, pt->chaves[i])<0){           //Caso a key seja ALFABETICAMENTE MENOR que todos os elementos no Nó
                
                for(int j=nmr; j>i; j--){
                    pt->chaves[j] = pt->chaves[j-1];
                }
    
                pt->chaves[i] = key;                    //Adicionar na posição i após mover todos os outros elementos para a direita
                pt->n++;
                return i;                               //Retorna a posição em que 'key' foi inserido
            }    
            else if(i==nmr-1){                          //Caso a key seja ALFABETICAMENTE MAIOR que todos os elementos no Nó 
                pt->chaves[nmr] = key;
                pt->n++;
                return i;                               //Retorna a posição em que 'key' foi inserido
            }   
        }
    }
    return -1;                                           //Caso a quantidade de elementos dentro do Nó VÁ EXCEDER o máximo com a adição de 'key'
}

void split(No* pai, No* pt, char *key){
    int posi = -1;
    if(pai != NULL){
        posi = add_key(pai, pt->chaves[D-1]);       //Primeiro, adicionamos esse elemento no nó do pai
    }

    char* chave_meio = pt->chaves[D-1];             //Salvando a chave do meio
    No* no_dir = novo_no(D-1);

    int j=D;
    for(int i=0; i<D-1; i++){
        no_dir->chaves[i] = pt->chaves[j];          //Copiando os valores da metade direita do filho de pt no novo 'no_dir'
        j++;
    }
    for(int j=D-1; j<2*D; j++){
        if(pt->chaves[j] != NULL){                  //Limpa os valores do nó antigo que já foram copiados para 'no_dir'
            pt->chaves[j] = NULL;
            pt->n--;
        }
    }

    //Caso pt NÃO seja folha
    if(pt->filhos[0] != NULL){
        int j=0;
        for(int i=D-1; i<2*D+1; i++){
            no_dir->filhos[j] = pt->filhos[i];
            j++;

            pt->filhos[i] = NULL;                   //Limpa os filhos de pt depois de serem copiados para 'no_dir'
        }
    }

    //Cuidando da redistribuição dos nós 'splitados' de pt
    
    if(posi != -1){
        for(int k=pai->n; k>posi+1; k--){
            pai->filhos[k] = pai->filhos[k-1];          //Passando os filhos do nó pai para direita, "abrindo" espaço para 'no_dir'
        }
        pai->filhos[posi+1] = no_dir;
    }
    else{                               //No caso de fazer o split da RAIZ (Não possui 'pai')
        raiz = novo_no(0);
        raiz->chaves[0] = chave_meio;
        raiz->n++;

        raiz->filhos[0] = pt;
        raiz->filhos[1] = no_dir;
    }
}