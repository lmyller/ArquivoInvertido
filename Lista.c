#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/**
*   Função que cria uma lista e retorna a lista
*/
lista criaLista(){
    lista l = (lista)malloc(sizeof(Lista));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho = 0;
    }
    return l;
}

/**
*   Função que recebe uma lista e uma struct do tipo frequência e insere no início da lista os elementos da struct
*/
int insereInicio(lista l, Frequencia f){
    NodoLista *p = (NodoLista*)malloc(sizeof(NodoLista));
    if(!p)
        return 0;

    p->info = f;
    p->next = NULL;
    l->first = p;
    l->last = p;
    l->tamanho++;
    return 1;
}

/**
*   Função que recebe uma lista e uma struct do tipo frequência e insere no final da lista os elementos da struct
*/
int insereFinal(lista l, Frequencia f){
    NodoLista *p;
    if(l->tamanho == 0)
        return insereInicio(l, f);

    p = (NodoLista*)malloc(sizeof(NodoLista));
    if(!p)
        return 0;

    p->info = f;
    p->next = NULL;
    l->last->next = p;
    l->last = p;
    l->tamanho++;
    return 1;
}

/**
*   Função que recebe uma lista e o número de um arquivo, se o arquivo existir na lista aumenta a variável frequência
*/
int alteraFrequencia(lista l, int NumArquivo){
    NodoLista *p;
    if(l->tamanho == 0)
        return 0;

    p = l->first;
    while(p){
        if(p->info.arquivo == NumArquivo){
            p->info.frequencia++;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

/**
*   Função que cria a lista auxiliar
*/
void insereNodoLista(lista l, lista listAux){
    Frequencia f;
    NodoLista *p, *aux;

    p = l->first;
    if(listAux->tamanho == 0){
        while(p){
            f.arquivo = p->info.arquivo;
            f.frequencia = p->info.frequencia;
            insereFinal(listAux, f);
            p = p->next;
        }
    }

    else
        while(p){
            aux = listAux->first;
            while(aux){
                if(p->info.arquivo == aux->info.arquivo){
                    f.arquivo = p->info.arquivo;
                    f.frequencia = p->info.frequencia;
                    insereFinal(listAux, f);
                    break;
                }
                aux = aux->next;
            }
            p = p->next;
        }
}

/**
*   Função que recebe a lista de documentos onde poosuem as palavras requisitadas e a quantidade de palavras, a função
*   remove da lista os documentos que não comtém todas as palavras
*/
int alteraLista(lista l, int quantidade){
    NodoLista *p, *aux;
    int contador;

    if(l->tamanho == 0)
        return 0;

    p = l->first;
    while(p){
        contador = 0;
        aux = l->first;
        while(aux){
            if(p->info.arquivo == aux->info.arquivo)
                contador++;
            aux = aux->next;
        }
        aux = p;
        p = p->next;
        if(contador < quantidade)   //Se o documento aparecer na lista menos vezes que a quantidade de palavras, o documento é removido
            removeElemento(l, aux->info.arquivo);
    }
    return 1;
}

/**
*   Função que remove da lista de documentos que possuem as palavras, todos os elementos com o número de documento passado por parâmetro
*/
int removeElemento(lista l, int documento){
    NodoLista *p, *ant, *aux;
    if(l->tamanho == 0)
        return 0;

    p = l->first;
    while(p){
        if(p->info.arquivo == documento){
            if(p == l->first){
                l->first = l->first->next;
                aux = p;
                p = p->next;
                l->tamanho--;
            }

            else if(p == l->last){
                l->last = ant;
                l->last->next = NULL;
                aux = p;
                p = p->next;
                l->tamanho--;
            }

            else{
                ant->next = p->next;
                aux = p;
                p = p->next;
                l->tamanho--;
            }
            free(aux);
        }

        else{
            ant = p;
            p = p->next;
        }
    }
    return 1;
}

/**
*   Função que cria e retorna lista de ranking
*/
lRanking criaListaRanking(){
    lRanking l = (lRanking)malloc(sizeof(ListaRanking));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho = 0;
    }
    return l;
}

/**
*   Função que calcula o ranking dos documentos
*/
void criaRanking(lRanking lR, lista l, int *numDocumentos, int qtdeArquivos){
    NodoLista *p, *aux;
    Ranking r;
    int indice;
    float soma, qtde;

    p = l->first;
    while(p){
        soma = 0;
        indice = 0;
        aux = l->first;
        while(aux){
            if(p->info.arquivo == aux->info.arquivo){
                qtde = qtdeArquivos * 1.0;
                soma += (aux->info.frequencia * (qtde / numDocumentos[indice]));    //Calculando o ranking
            }
            aux = aux->next;
        }
        r.arquivo = p->info.arquivo;
        r.ranking = soma;
        insereFinalRanking(lR, r);  //Inserindo na lista de ranking
        p = p->next;
    }
}

/**
*   Função que recebe uma lista e uma struct do tipo ranking e insere no início da lista os elementos da struct
*/
int insereInicioRanking(lRanking l, Ranking r){
    NodoRanking *p = (NodoRanking*)malloc(sizeof(NodoRanking));
    if(!p)
        return 0;

    p->info = r;
    p->next = NULL;
    l->first = p;
    l->last = p;
    l->tamanho++;
    return 1;
}

/**
*   Função que recebe uma lista e uma struct do tipo ranking e insere no final da lista os elementos da struct
*/
int insereFinalRanking(lRanking l, Ranking r){
    NodoRanking *p;
    if(l->tamanho == 0)
        return insereInicioRanking(l, r);

    p = (NodoRanking*)malloc(sizeof(NodoRanking));
    if(!p)
        return 0;

    p->info = r;
    p->next = NULL;
    l->last->next = p;
    l->last = p;
    l->tamanho++;
    return 1;
}

/**
*   Função que coloca os valores da lista em ordem decrescente
*/
void ordenaLista(lRanking l){
    NodoRanking *p, *aux;
    int num;
    float rankingDoc;

    p = l->first;
    while(p){
        aux = l->first->next;
        while(aux){
            if(aux->info.ranking > p->info.ranking){
                num = p->info.arquivo;
                p->info.arquivo = aux->info.arquivo;
                aux->info.arquivo = num;
                rankingDoc = p->info.ranking;
                p->info.ranking = aux->info.ranking;
                aux->info.ranking = rankingDoc;
            }
            aux = aux->next;
        }
        p = p->next;
    }
}

/**
*   Função que verifica se existem elementos repetidos na lista de ranking
*/
int verificaElementoRanking(lRanking l){
    NodoRanking *p, *aux;
    int contador;

    if(l->tamanho == 0)
        return 0;

    p = l->first;
    while(p){
        aux = l->first;
        contador = 0;
        while(aux){
            if(p->info.arquivo == aux->info.arquivo)
                contador++;
            if(contador > 1)                                //Verificando se o elemento ocorre mais de uma vez, se sim remove o elemento
                removeElementoRanking(l, aux->info.arquivo);
            aux = aux->next;
        }
        p = p->next;
    }
    return 1;
}

/**
*   Função que remove um elemento da lista de ranking
*/
int removeElementoRanking(lRanking l, int numArquivo){
    NodoRanking *p, *ant;
    p = l->first;
    while(p){
        if(p->info.arquivo == numArquivo){
            if(p == l->first)
                l->first = l->first->next;
            else
                if(p == l->last){
                    l->last = ant;
                    l->last->next = NULL;
                }
                else
                    ant->next = p->next;
            free(p);
            l->tamanho--;
            return 1;
        }
        ant = p;
        p = p->next;
    }
    return 0;
}

/**
*   Função que encerra uma lista removendo todos os seus elementos
*/
void encerraLista(lista l){
    NodoLista *p, *aux;

    p = l->first;
    while(p){
        aux = p;
        p = p->next;
        l->first = p;
        free(aux);
    }
    free(l);
}

/**
*   Função que encerra uma lista de ranking removendo todos os seus elementos
*/
void encerraListaRanking(lRanking l){
    NodoRanking *p, *aux;

    p = l->first;
    while(p){
        aux = p;
        p = p->next;
        l->first = p;
        free(aux);
    }
    free(l);
}
