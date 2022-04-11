#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"
#include "lista.h"

/**
*   Função que cria um ponteiro para a raiz de uma árvore binária
*/
apontador criaArvore(){
  return NULL;
}

/**
*   Função que insere um elemento em um nodo da árvore e retorna a lista do mesmo
*/
lista insereNodoABP(apontador *p, TPalavras pa){
    if(*p == NULL){
        *p = (apontador)malloc(sizeof(TNodo));

        if(*p){
            strcpy((*p)->info.palavra, pa.palavra);
            (*p)->dir = NULL;
            (*p)->esq = NULL;
            (*p)->lista = criaLista();
            return (*p)->lista;
        }
    }

    else
        if(strcmp((*p)->info.palavra, pa.palavra) == 0)     //Se a palavra já existir é retornada a lista do nodo da palavra
            return (*p)->lista;

        else
            if(strcmp((*p)->info.palavra, pa.palavra) > 0)  //Se a palavra no nodo for maior que a palavra que vai ser indexada, então vai para a esquerda
                return insereNodoABP(&(*p)->esq, pa);

            else
                return insereNodoABP(&(*p)->dir, pa);

    return NULL;
}

/**
*   Função que pesquisa uma palavra na árvore e retorna a lista dela
*/
lista pesquisaABP(apontador p, char *palavra){
    if(p == NULL)
        return NULL;

    else
        if(strcmp(p->info.palavra, palavra) == 0)
            return p->lista;

        else
            if(strcmp(palavra, p->info.palavra) < 0)    //Se a palavra for menor vai para a esquerda, senão vai para a direita
                return pesquisaABP(p->esq, palavra);

            else
                return pesquisaABP(p->dir, palavra);
}

/**
*   Função que recebe a raíz da árvore binária, as palavras a serem consultadas, a tabela com os números dos arquivos e a quantidade de
*   arquivo e retorna uma lista ordenada pelo ranking
*/
lRanking ordenaDocumentosArvore(apontador p, char *palavraEntrada, NumeroArquivo NA[], int quantidadeArquivo){
    int quantidadePalavras = 0, indice = 0, *numDocumentos;
    char **string;
    lista l, aux;
    aux = criaLista();
    lRanking rankingDocs = criaListaRanking();

    quantidadePalavras = retornaQuantidadePalavras(palavraEntrada); //Recebe a quantidade de palavras que foram consultadas

    quantidadePalavras++;
    numDocumentos = (int*)malloc(sizeof(int) * quantidadePalavras);  //Vetor que receberá a quantidade de documentos de cada nodo das palavras

    string = retornaStringPalavras(palavraEntrada, quantidadePalavras); //Vetor de string contendo as palavras que foram consultadas

    for(indice = 0;indice < quantidadePalavras;indice++){
        l = pesquisaABP(p, string[indice]);
        numDocumentos[indice] = l->tamanho;
        insereNodoLista(l, aux);    //Insere os nodos em uma lista auxiliar
    }

    alteraLista(aux, quantidadePalavras);   //Remove os documentos que não possuem todas as palavras

    criaRanking(rankingDocs, aux, numDocumentos, quantidadeArquivo);    //Cria a lista de ranking
    encerraLista(aux);      //Encerra lista auxiliar
    verificaElementoRanking(rankingDocs);   //Verifica se a lista possui documentos repetidos, se tiver os remove
    ordenaLista(rankingDocs);   //Ordena a lista de ranking em ordem decrescente
    return rankingDocs;
}
