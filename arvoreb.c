#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "arvoreb.h"

struct no{
   int* chaves;
   int grau_min;
   No **filhos;
   int n_chaves;
   bool folha;
};

struct arvore{
    No * raiz;
    int grau_min;
};

Arvore* cria_arv(int grau_min){
    Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
    arv->raiz = NULL;
    arv->grau_min = grau_min;
    return arv;
}

void atravessa_arv(Arvore* arv){
    if(arv->raiz != NULL)
        atravessa_no(arv->raiz);
}

No* busca_arv(Arvore* arv, int val){
    return(arv->raiz == NULL)? NULL : busca_no(arv->raiz, val);
}

No* cria_no(int grau_min, bool folha){
    No * no = (No *) malloc(sizeof(No));
    no->grau_min = grau_min;
    no->folha = folha;
    no->chaves = (int*) malloc(sizeof(int)*2*grau_min-1);
    
    no->filhos = (No**) malloc(sizeof(No*) * 2*grau_min);
    for(int i=0; i<2*grau_min; i++)
        no->filhos[i] = (No*)malloc(sizeof(No));

    no->n_chaves = 0;

    return no;
}

int busca_chave(No* no, int val){
    int i = 0;
    while(i < no->n_chaves && no->chaves[i] < val)
        i++;
    return i;
}

void remove_folha(No* no, int i){
    for(int j = i+1; j < no->n_chaves; j++)
        no->chaves[j-1] = no->chaves[j];

    no->n_chaves-=1;
}

int procura_predecessor(No* no, int i){
    No* atual = no->filhos[i];
    while(!atual->folha)
        atual = atual->filhos[atual->n_chaves];

    return atual->chaves[atual->n_chaves-1];
}

int procura_sucessor(No* no, int i){
    No* atual = no->filhos[i+1];
    while(!atual->folha)
        atual = atual->filhos[0];

    return atual->chaves[0];
}

void junta(No* no, int i){
    No* filho = no->filhos[i];
    No* filho2 = no->filhos[i+1];

    filho->chaves[no->grau_min-1] = no->chaves[i];

    for(int j=0; j<filho2->n_chaves; j++)
        filho->chaves[j+no->grau_min] = filho2->chaves[j];
    
    if(!filho->folha){
        for(int j=0; j<=filho2->n_chaves; j++)
            filho->filhos[j+no->grau_min] = filho2->filhos[j];
    }

    for(int j = i+1; j<no->n_chaves; j++)
        no->chaves[j-1] = no->chaves[j];
    
    for(int j = i+2; j<=no->n_chaves; j++)
        no->filhos[j-1] = no->filhos[j];
    
    filho->n_chaves += filho2->n_chaves+1;
    no->n_chaves-=1;

    free(filho2);
}

void remove_nao_folha(No* no, int i){
    int k = no->chaves[i];

    if(no->filhos[i]->n_chaves >= no->grau_min){
        int predecessor = procura_predecessor(no, i);
        no->chaves[i] = predecessor;
        remove_no(no->filhos[i], predecessor);
    }
    else if (no->filhos[i+1]->n_chaves >= no->grau_min){
        int sucessor = procura_sucessor(no, i);
        no->chaves[i] = sucessor;
        remove_no(no->filhos[i+1], sucessor);
    }
    else{
        junta(no, i);
        remove_no(no->filhos[i], k);
    }
}

void empresta_anterior(No* no, int i){
    No* filho = no->filhos[i];
    No* filho2 = no->filhos[i-1];

    for(int j = filho->n_chaves-1; j>=0; j--)
        filho->chaves[j+1] = filho->chaves[j];
    
    if(!filho->folha){
        for(int j = filho->n_chaves; j>=0; j--)
            filho->filhos[j+1] = filho->filhos[j];
    }

    filho->chaves[0] = no->chaves[i-1];

    if(!filho->folha)
        filho->filhos[0] = filho2->filhos[filho2->n_chaves];
    
    no->chaves[i-1] = filho2->chaves[filho2->n_chaves-1];

    filho->n_chaves += 1;
    filho2->n_chaves -= 1;
}

void empresta_proximo(No* no, int i){
    No* filho = no->filhos[i];
    No* filho2 = no->filhos[i+1];

    filho->chaves[(filho->n_chaves)] = no->chaves[i];

    if(!(filho->folha))
        filho->filhos[(filho->n_chaves)+1] = filho2->filhos[0];
    
    no->chaves[i] = filho2->chaves[0];

    for(int j=1; j<filho2->n_chaves; j++)
        filho2->chaves[j-1] = filho2->chaves[j];
    
    if(!filho2->folha){
        for(int j=1; j<=filho2->n_chaves; j++)
            filho2->filhos[j-1] = filho2->filhos[j];
    }

    filho->n_chaves += 1;
    filho2->n_chaves -= 1;
}

void preenche(No* no, int i){
    if(i!=0 && no->filhos[i-1]->n_chaves >= no->grau_min)
        empresta_anterior(no, i);
    else if(i!= no->n_chaves && no->filhos[i+1]->n_chaves == no->grau_min)
        empresta_proximo(no, i);
    else{
        if(i != no->n_chaves)
            junta(no, i);
        else
            junta(no, i-1);
    }
}

void remove_no(No* no, int val){
    int i = busca_chave(no, val);

    if(i < no->n_chaves && no->chaves[i] == val){
        if(no->folha)
            remove_folha(no, i);
        else
            remove_nao_folha(no, i);
    }
    else{
        if(no->folha){
            printf("Valor nao encontrado.\n");
            return;
        }

        bool flag = ((i==no->n_chaves)? true : false);

        if(no->filhos[i]->n_chaves < no->grau_min)
            preenche(no, i);

        if(flag && i > no->n_chaves)
            remove_no(no->filhos[i-1], val);
        else
            remove_no(no->filhos[i], val);
    }
}

void separa_filho(No* no, int i, No* no2){
    No* no3 = cria_no(no2->grau_min, no2->folha);
    no3->n_chaves = no->grau_min-1;

    for(int j = 0; j< no->grau_min-1; j++)
        no3->chaves[j] = no2->chaves[j+no->grau_min];

    if(!no2->folha){
        for(int j = 0; j < no->grau_min; j++)
            no3->filhos[j] = no2->filhos[j+no->grau_min];
    }

    no2->n_chaves = no->grau_min-1;

    for(int j = no->n_chaves; j >= i+1; j--)
        no->filhos[j+1] = no->filhos[j];
    
    no->filhos[i+1] = no3;

    for(int j = no->n_chaves-1; j >= i; j--)
        no->chaves[j+1] = no->chaves[j];

    no->chaves[i] = no2->chaves[no->grau_min-1];

    no->n_chaves+=1;
}

void insere_nao_cheio(No* no, int k){
    int i = no->n_chaves-1;

    if(no->folha){
        while(i >= 0 && no->chaves[i] > k){
            no->chaves[i+1] = no->chaves[i];
            i--;
        }

        no->chaves[i+1] = k;
        no->n_chaves+=1;
    }
    else{
        while(i >= 0 && no->chaves[i] > k)
            i--;
        
        if(no->filhos[i+1]->n_chaves == 2*no->grau_min-1){
            separa_filho(no, i+1, no->filhos[i+1]);

            if(no->chaves[i+1] < k)
                i++;
        }
        insere_nao_cheio(no->filhos[i+1], k);
    }
}

void insere_arv(Arvore* arv, int k){
    if(arv->raiz == NULL){
        arv->raiz = cria_no(arv->grau_min, true);
        arv->raiz->chaves[0] = k;
        arv->raiz->n_chaves = 1;
    }
    else{
        if(arv->raiz->n_chaves == 2*arv->grau_min-1){
            No* novo = cria_no(arv->grau_min, false);

            novo->filhos[0] = arv->raiz;
            separa_filho(novo, 0, arv->raiz);

            int i = 0;
            if(novo->chaves[0] < k)
                i++;
            insere_nao_cheio(novo->filhos[i], k);

            arv->raiz = novo;
        }
        else
            insere_nao_cheio(arv->raiz, k);
    }
}

void atravessa_no(No* no){
    int i;
    for(i = 0; i<no->n_chaves; i++){
        if(!no->folha)
            atravessa_no(no->filhos[i]);
        printf("%d\n", no->chaves[i]);
    }

    if(!no->folha)
        atravessa_no(no->filhos[i]);
}

No* busca_no(No* no, int k){
    int i = 0;
    while(i < no->n_chaves && k > no->chaves[i])
        i++;
    
    if(no->chaves[i] == k)
        return no;
    
    if(no->folha)
        return NULL;
    
    return busca_no(no->filhos[i], k);
}

void remove_arv(Arvore* arv, int k){
    if(!arv->raiz){
        printf("Arvore vazia\n");
        return;
    }

    remove_no(arv->raiz, k);

    if(arv->raiz->n_chaves==0){
        No* temp = arv->raiz;
        if(arv->raiz->folha)
            arv->raiz = NULL;
        else
            arv->raiz = arv->raiz->filhos[0];
        free(temp);
    }
}


