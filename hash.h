#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "lista.h"

#define M 1000001

typedef struct{
    lista elementos[M];
    int numElementos;
}TTabela;

typedef TTabela *tabela;

tabela criaTabela();
int insereTabela(tabela, char*, Frequencia);
lista pesquisaTabela(tabela, char*);
lRanking ordenaDocumentosHash(tabela, char *, NumeroArquivo[], int);

#endif // HASH_H_INCLUDED
