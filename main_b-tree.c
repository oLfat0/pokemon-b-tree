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
    int n;                        //Quantidade de chaves no Nó
    char *chaves[2*D];            //Lista de String -> Cada chave é uma String
    struct no* filhos[2*D+1];

}No;

No* novo_no(int n);
int menu();
int busca(No* pt, char *x);
void insere(No* pai, No* pt, char *nome);
int add_key(No* pt, char *key);
void split(No* pai, No* pt,  char *key);        //No livro do Jayme ele define essa função como 'cisão'

No* raiz = NULL;

int main(){
    while (1)
    {
        if(menu()==9){      //Caso o usuário selecione a opção '[9] - Finalizar'
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
        char nome[20];
        printf("Digite o nome do Pokemon a inserir: ");
        scanf("%s", nome);
        insere(NULL, raiz, nome);   // Inicia com pai = NULL
        return i;
    }
    else if(i == 9){
        printf("Finalizando programa...\n");
        return i;
    }
    else{
        printf("Digite um valor valido >:(\n");
        return 0;
    }
}

int busca(No* pt, char *x){
    if(pt == NULL){
        printf("Pokemon '%s' nao encontrado :(\n", x);
        return 0;
    }

    int i = 0;

    while(i < pt->n && strcmp(x, pt->chaves[i])>0){     //Vai percorrendo a chave (Esq->Dir)
        i++;
    }

    if(i < pt->n && strcmp(x, pt->chaves[i])==0){
        printf("Pokemon '%s' encontrado! Posicao %d do No :)\n", x, i);
        return 1;
    }

    busca(pt->filhos[i], x);                            //Desce para o filho[i]
}

void insere(No* pai, No* pt, char *nome){
    char *copia = strdup(nome);     //Faço uma cópia temporária do novo nome com strdup para que nenhum nome seja sobreescrito na próxima chamada de 'insere()' quando voltar para o menu

    if(raiz == NULL){               //Caso a árvore seja VAZIA
        raiz = novo_no(0);
        raiz->chaves[0] = copia;
        raiz->n++;
        printf("Elemento '%s' inserido na primeira posicao da raiz ;)\n", nome);
        return;
    }

    // A partir daqui pt nunca é NULL (aogra pt = raiz ou pt = filho válido)

    //Função "Busca()":
    int i = 0;

    while(i < pt->n && strcmp(copia, pt->chaves[i])>0){     //Vai percorrendo as chaves do Nó (Esq->Dir)
        i++;
    }

    if(i < pt->n && strcmp(copia, pt->chaves[i])==0){
        printf("Elemento ja se encontra na arvore. Nenhuma acao necessaria :|\n");
        free(copia);
        return;
    }
    else if(pt->filhos[i] == NULL){
        // Nó folha: tenta inserir diretamente
        if(add_key(pt, copia) != -1){
            printf("Elemento '%s' inserido com sucesso! :)\n", nome);
            return;
        }
        else{
            // Nó cheio: faz split e depois insere novamente a partir da raiz
            split(pai, pt, copia);
            // Após o split a chave ainda não foi inserida; reinsere a partir da raiz
            insere(NULL, raiz, nome);
            free(copia);
        }
    }
    else if(pt->filhos[i]->n >= 2*D){       //Caso o número de elementos no Nó filho exceda o máximo. Propriedade (a)
        split(pt, pt->filhos[i], copia);

        i = 0;                              //Recalculando o valor de 'i'
        while(i < pt->n && strcmp(copia, pt->chaves[i])>0){
            i++;
        }
        free(copia);
        return insere(pt, pt->filhos[i], nome);  //Desce para o filho[i]
    }

    else{
        free(copia);
        return insere(pt, pt->filhos[i], nome);  //Desce para o filho[i]
    }
}

int add_key(No* pt, char *key){
    /*
    Função responsável por organizar a posição da nova chave inserida de forma ordenada 
    em determinado Nó pt
    */
    int nmr = pt->n;                                    //Número de chaves no Nó

    if(nmr < 2*D){
        if(nmr == 0){                                   //Caso não haja nenhuma chave no Nó
            pt->chaves[0] = key;
            pt->n++;
            return 0;
        }

        for(int i=0; i<nmr; i++){
            if(strcmp(key, pt->chaves[i])<0){           //Caso a key seja ALFABETICAMENTE MENOR
                
                for(int j=nmr; j>i; j--){
                    pt->chaves[j] = pt->chaves[j-1];
                }
    
                pt->chaves[i] = key;
                pt->n++;
                return i;
            }    
            else if(i==nmr-1){                          //Caso a key seja ALFABETICAMENTE MAIOR que todos
                pt->chaves[nmr] = key;
                pt->n++;
                return nmr;
            }   
        }
    }
    return -1;                                          //Caso a quantidade de elementos dentro do Nó VÁ EXCEDER o máximo           
}

void split(No* pai, No* pt,  char *key){                //No livro do Jayme ele define essa função como 'cisão'
    int meio = D;

    int posi = -1;
    if(pai != NULL){                                    //Caso não estejamos na raiz
        posi = add_key(pai, strdup(pt->chaves[meio]));  //Sobe o elemento do meio para o pai
    }

    char* chave_meio = pt->chaves[meio];                //Salvando a chave do meio
    No* no_dir = novo_no(0);

    //Copia a metade direita (após o meio) para no_dir [COPIANDO CHAVES {pt -> no_dir}]
    int j = meio + 1;
    int k = 0;
    while(j < 2*D){
        no_dir->chaves[k] = pt->chaves[j];
        pt->chaves[j] = NULL;                       //Vai limpando os elementos do nó original(No* pt) asism que eles são copiados para no_dir
        
        no_dir->n++;
        j++;
        k++;
    }

    // Limpa o elemento do meio e a metade direita do nó original (No* pt)
    pt->chaves[meio] = NULL;
    pt->n = meio;                                   //pt agora tem 'meio' chaves (metade esquerda)

    //Caso pt NÃO seja folha
    if(pt->filhos[0] != NULL){                      
    //Copia a metade direita (após o meio) para no_dir [COPIANDO NÓS FILHO {pt -> no_dir}]
        int f = meio + 1;
        int g = 0;
        while(f <= 2*D){
            no_dir->filhos[g] = pt->filhos[f];
            pt->filhos[f] = NULL;
            f++;
            g++;
        }
    }

    //Cuidando da redistribuição dos nós 'splitados' de pt
    if(posi != -1){
        for(int k=pai->n; k>posi+1; k--){
            pai->filhos[k] = pai->filhos[k-1];
        }
        pai->filhos[posi+1] = no_dir;
    }
    else{                                           //Split da RAIZ (não possui 'pai')
        raiz = novo_no(0);
        raiz->chaves[0] = chave_meio;
        raiz->n++;

        raiz->filhos[0] = pt;
        raiz->filhos[1] = no_dir;
    }
}