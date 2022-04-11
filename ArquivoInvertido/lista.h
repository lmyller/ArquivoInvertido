#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "Inicio.h"

typedef struct{
    int arquivo, frequencia;
}Frequencia;

typedef struct NodoLista{
    Frequencia info;
    struct NodoLista *next;
}NodoLista;

typedef struct{
    NodoLista *first, *last;
    int tamanho;
}Lista;

typedef Lista *lista;

lista criaLista();
int insereInicio(lista, Frequencia);
int insereFinal(lista, Frequencia);
int alteraFrequencia(lista, int);
void insereNodoLista(lista, lista);
int removeElemento(lista, int);
int alteraLista(lista, int);
void encerraLista(lista);

typedef struct{
    int arquivo;
    float ranking;
}Ranking;

typedef struct NodoRanking{
    Ranking info;
    struct NodoRanking *next;
}NodoRanking;

typedef struct{
    NodoRanking *first, *last;
    int tamanho;
}ListaRanking;

typedef ListaRanking *lRanking;

lRanking criaListaRanking();
int insereInicioRanking(lRanking, Ranking);
int insereFinalRanking(lRanking, Ranking);
void criaRanking(lRanking, lista, int*, int);
void ordenaLista(lRanking);
int verificaElementoRanking(lRanking l);
int removeElementoRanking(lRanking, int);
void encerraListaRanking(lRanking);

#endif // LISTA_H_INCLUDED
