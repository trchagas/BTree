typedef struct no No;
typedef struct arvore Arvore;

Arvore* cria_arv(int grau_min);
void insere_arv(Arvore* arv, int k);
void atravessa_arv(Arvore* arv);
void remove_arv(Arvore* arv, int k);
No* busca_arv(Arvore* arv, int val);

void atravessa_no(No* no);
No* busca_no(No* no, int k);
void remove_no(No* no, int val);