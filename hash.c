#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/**
*   Função que recebe uma string e retorna uma chave para inserir na tabela hash
*/
unsigned int hash(char *palavra){
    unsigned int soma = 0,i = 0;

    while(palavra[i] != '\0'){
        soma += (palavra[i] * (i +1 ));
        i++;
    }

    return soma % M;
}

/**
*   Função que cria uma tabela hash e retorna a tabela
*/
tabela criaTabela(){
    int i;
    tabela t = (TTabela*)malloc(sizeof(TTabela));

    if(t){
        t->numElementos = 0;
        for(i = 0;i < M;i++)
            t->elementos[i] = criaLista();
    }

    return t;
}

/**
*   Função que insere um elemento na tabela, se o elemento já existir é alterado a frequência do elemento
*/
int insereTabela(tabela t, char *palavra, Frequencia f){
    int indice = hash(palavra);
    if(t->elementos[indice]->tamanho == 0)
        return insereFinal(t->elementos[indice], f);

    else
        if(alteraFrequencia(t->elementos[indice], f.arquivo) == 0)
            insereFinal(t->elementos[indice], f);
    return 1;
}

/**
*   Função que pesquisa uma palavra na tabela
*/
lista pesquisaTabela(tabela t, char *palavra){
    int indice = hash(palavra);
    return t->elementos[indice];
}

/**
*   Função que recebe a tabela hash, as palavras a serem consultadas, a tabela com os números dos arquivos e a quantidade de
*   arquivo e retorna uma lista ordenada pelo ranking
*/
lRanking ordenaDocumentosHash(tabela t, char *palavraEntrada, NumeroArquivo NA[], int quantidadeArquivo){
    int quantidadePalavras = 0, indice = 0, *numDocumentos;
    char **string;
    lista l, aux;
    aux = criaLista();
    lRanking rankingDocs = criaListaRanking();

    quantidadePalavras = retornaQuantidadePalavras(palavraEntrada); //Recebe a quantidade de palavras que foram consultadas

    quantidadePalavras++;
    numDocumentos = (int*)malloc(sizeof(int) * quantidadePalavras); //Vetor que receberá a quantidade de documentos de cada nodo das palavras
    string = retornaStringPalavras(palavraEntrada, quantidadePalavras);     //Vetor de string contendo as palavras que foram consultadas

    for(indice = 0;indice < quantidadePalavras;indice++){
        l = pesquisaTabela(t, string[indice]);
        numDocumentos[indice] = l->tamanho;
        insereNodoLista(l, aux);     //Insere os nodos em uma lista auxiliar
    }

    alteraLista(aux, quantidadePalavras);      //Remove os documentos que não possuem todas as palavras

    criaRanking(rankingDocs, aux, numDocumentos, quantidadeArquivo);     //Cria a lista de ranking
    encerraLista(aux);      //Encerra lista auxiliar
    verificaElementoRanking(rankingDocs);   //Verifica se a lista possui documentos repetidos, se tiver os remove
    ordenaLista(rankingDocs);       //Ordena a lista de ranking em ordem decrescente
    return rankingDocs;
}
