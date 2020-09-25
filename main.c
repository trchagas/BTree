#include <stdio.h>
#include "arvoreb.h"

int main(){
    Arvore* arv = cria_arv(3);

    insere_arv(arv,1); 
    insere_arv(arv,3); 
    insere_arv(arv,7); 
    insere_arv(arv,10); 
    insere_arv(arv,11); 
    insere_arv(arv,13); 
    insere_arv(arv,14); 
    insere_arv(arv,15); 
    insere_arv(arv,18); 
    insere_arv(arv,16); 
    insere_arv(arv,19); 
    insere_arv(arv,24); 
    insere_arv(arv,25); 
    insere_arv(arv,26); 
    insere_arv(arv,21); 
    insere_arv(arv,4); 
    insere_arv(arv,5); 
    insere_arv(arv,20); 
    insere_arv(arv,22); 
    insere_arv(arv,2); 
    insere_arv(arv,17); 
    insere_arv(arv,12); 
    insere_arv(arv,6); 

    atravessa_arv(arv);

    remove_arv(arv, 6);

    atravessa_arv(arv);

    remove_arv(arv, 13);

    atravessa_arv(arv);

    remove_arv(arv, 7);

    atravessa_arv(arv);

    remove_arv(arv, 4);

    atravessa_arv(arv);

    remove_arv(arv, 2);

    atravessa_arv(arv);

    remove_arv(arv, 16);

    atravessa_arv(arv);

    // printf("\n\n");

    // busca_arv(arv, 21) != NULL ? printf("bom") : printf("ruim");

}