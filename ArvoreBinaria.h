#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED

#include "lista.h"

typedef struct{
    char palavra[100];
}TPalavras;

typedef struct Nodo{
    TPalavras info;
    struct Nodo *esq, *dir;
    Lista *lista;
}TNodo;

typedef TNodo *apontador;

apontador criaArvore();
lista insereNodoABP(apontador*, TPalavras);
lista pesquisaABP(apontador, char*);
lRanking ordenaDocumentosArvore(apontador, char*, NumeroArquivo[], int);

#endif // ARVOREBINARIA_H_INCLUDED
