#include <stdio.h>
#include "arvoreb.h"

int main(){
    Arvore* arv = cria_arv(2);

    insere_arv(arv,1);
    insere_arv(arv,3);
    insere_arv(arv,4);
    insere_arv(arv,5);
    insere_arv(arv,6);
    insere_arv(arv,7);
    insere_arv(arv,8);
    insere_arv(arv,10);
    insere_arv(arv,11);
    insere_arv(arv,14);
    insere_arv(arv,15);
    insere_arv(arv,16);
    insere_arv(arv,17);
    insere_arv(arv,18);
    insere_arv(arv,20);
    insere_arv(arv,24);
    insere_arv(arv,25);
    insere_arv(arv,30);
    insere_arv(arv,31);
    insere_arv(arv,35);

    atravessa_arv(arv);

    remove_arv(arv, 25);
    printf("\nApos remocao do 25:\n");
    atravessa_arv(arv);

    remove_arv(arv, 5);
    printf("\nApos remocao do 5:\n");
    atravessa_arv(arv);

    remove_arv(arv, 6);
    printf("\nApos remocao do 6:\n");
    atravessa_arv(arv);

    remove_arv(arv, 4);
    printf("\nApos remocao do 4:\n");
    atravessa_arv(arv);

    remove_arv(arv, 7);
    printf("\nApos remocao do 7:\n");
    atravessa_arv(arv);

    printf("\n\n");

    busca_arv(arv, 20) ? 
        printf("Achou\n"):
        printf("Nao achou\n");

    busca_arv(arv, 14) ? 
        printf("Achou\n"):
        printf("Nao achou\n");

    busca_arv(arv, 35) ? 
        printf("Achou\n"):
        printf("Nao achou\n");

    busca_arv(arv, 125) ? 
        printf("Achou\n"):
        printf("Nao achou\n");

    busca_arv(arv, 250) ? 
        printf("Achou\n"):
        printf("Nao achou\n");

}