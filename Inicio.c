#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "lista.h"
#include "hash.h"
#include "ArvoreBinaria.h"
#include "Inicio.h"

/**
*   Função que inicia o programa
*/
int inicio(int argc, char **argv){
    if(argc != 3){
        printf("Erro!\nFaltam argumentos!\n");
        return 0;
    }
    inicioArvore(argc, argv);
    inicioHash(argc, argv);
    return 1;
}

/**
*   Função que retira o \n no final das palavras do arquivo de consulta
*/
void retiraBarraN(char *palavra){
    if(palavra[strlen(palavra)-1]!='\0')
        palavra[strlen(palavra)-1]='\0';
}

int retornaQuantidadePalavras(char *palavras){
    int quantidadePalavras = 0, indice = 0;

    while(palavras[indice] != '\0'){
        if(palavras[indice] == ' ')
            quantidadePalavras++;
        indice++;
    }

    return quantidadePalavras;
}

char** retornaStringPalavras(char *palavras, int quantidadePalavras){
    int indice = 0;
    char *token, **string;

    string = alocaString(quantidadePalavras);
    token = strtok(palavras, " ");
    while(token != NULL){
        strcpy(string[indice], token);
        token = strtok(NULL," ");
        indice++;
    }
    retiraBarraN(string[quantidadePalavras - 1]);

    return string;
}
/**
*   Função que recebe um nome e abre um arquivo com aquele nome e retorna o arquivo
*/
FILE* abrirArquivo(char *nomeArquivo){
    FILE *arq = fopen(nomeArquivo, "r");
    return arq;
}

/**
*   Função que cria um vetor dinãmico que armazena as palavras consultadas, sendo tamanho a quantidade de palavras que vão ser armazenadas
*/
char** alocaString(int tamanho){
    int indice;
    char **string = (char**)malloc(sizeof(char*) * tamanho);

    for(indice = 0;indice < tamanho;indice++)
        string[indice] = (char*)malloc(sizeof(char) * 30);

    return string;
}

/**
*   Função que exibe os documentos que possuem as palavras buscadas, sendo tamanho a quantidade de arquivos lidos no início
*/
void exibeNomeDocumentos(lRanking l, NumeroArquivo NA[], int tamanho, char *palavras){
    NodoRanking *p;
    int indice;

    p = l->first;
    retiraBarraN(palavras);
    printf("\n\nPalavras consultadas: %s", palavras);
    printf("\nDocumentos: ");
    while(p){
        for(indice = 0;indice < tamanho;indice++){
            if(p->info.arquivo == NA[indice].numArquivo){
                printf("%s ", NA[indice].nomeArquivo);
                break;
            }
        }
        p = p->next;
    }
}

/**
*   Função que lê as palavras no arquivo e salva na estrutura da árvore binária
*/
void lerArquivoArvore(apontador *p, FILE *arquivo, int numArquivo){
    Frequencia f;
    TPalavras pa;
    lista l;

    while(!feof(arquivo)){
        memset(pa.palavra, '\0', 100);  //limpa a string
        fscanf(arquivo, "%s", pa.palavra);  //Lendo as palavras do arquivo
        if(pa.palavra[0] == '\0')   //Se a string for vazia sai da função
            break;

        l = insereNodoABP(p, pa); //Inserindo palavra no nodo
        if(l->tamanho == 0){    //Se o tamanho da lista for igual a zero incrementa a frequência como 1
            f.arquivo = numArquivo;
            f.frequencia = 1;
            insereFinal(l, f);  //Inserindo o numero do arquivo e a frequência que a palavra aparece no arquivo na lista do nodo da árvore
        }

        else
            if(alteraFrequencia(l, numArquivo) == 1) //Se o número do arquivo ja estiver na lista a frequência é incrementada
                continue;

            else{       //Se o número do arquivo não estiver na lista acescenta com frequência igual a 1
                f.arquivo = numArquivo;
                f.frequencia = 1;
                insereFinal(l, f);
            }
    }
}

/**
*   Função que inicia as operações com a estrutura da árvore binária
*/
int inicioArvore(int argc, char* argv[]){
    NumeroArquivo NA[TAM];
    DIR *dp;
    struct dirent *d;
    FILE *arq, *entrada;
    char caminhoArquivo[100], palavraEntrada[60], palavras[60];
    int numVetor = 0, quantidadeArquivo = 0, quantidadePalavras = 0, indice;
    lRanking l;
    apontador raiz = criaArvore();

    printf("\nÁrvore:");
    dp = opendir(argv[1]);
    while((d = readdir(dp)) != NULL){ //Abrindo o diretório
        strcpy(NA[numVetor].nomeArquivo, d->d_name);
        NA[numVetor].numArquivo = numVetor + 1;
        quantidadeArquivo++;

        strcat(caminhoArquivo, argv[1]);    //Montando caminho para o arquivo
        strcat(caminhoArquivo, "/");
        strcat(caminhoArquivo, d->d_name);

        arq = abrirArquivo(caminhoArquivo);    //Abrindo o arquivo com as palavras que serão indexadas

        if(arq == NULL){
            printf("\nErro ao abrir o arquivo!\nO programa será encerrado\n");
            return 0;
        }

        lerArquivoArvore(&raiz, arq, NA[numVetor].numArquivo);

        fclose(arq);

        numVetor++;

        memset(caminhoArquivo, '\0', 100);
    }

    entrada = abrirArquivo(argv[2]);
    if(entrada == NULL){
        printf("\nErro ao abrir o arquivo!\nO programa será encerrado\n");
        return 0;
    }

    fscanf(entrada,"%d\n", &quantidadePalavras);    //Lê a quantidade de consultas que irá fazer

    for(indice = 0;indice < quantidadePalavras;indice++){
        fgets(palavraEntrada, 60, entrada); //Lê a linha do arquivo
        strcpy(palavras, palavraEntrada);

        l = ordenaDocumentosArvore(raiz, palavraEntrada, NA, quantidadeArquivo);

        exibeNomeDocumentos(l, NA, quantidadeArquivo, palavras);
        encerraListaRanking(l);
        memset(palavraEntrada, '\0', 60);   //Limpa a string
    }

    printf("\n");
    fclose(entrada);
    closedir(dp);
    return 0;
}

/**
*   Função que lê as palavras no arquivo e salva na estrutura da tabela hash
*/
void lerArquivoHash(tabela t, FILE *arquivo, int numArquivo){
    Frequencia f;
    TPalavras pa;

    while(!feof(arquivo)){
        memset(pa.palavra, '\0', 100);
        fscanf(arquivo, "%s", pa.palavra);
        if(pa.palavra[0] == '\0')
            break;

        f.arquivo = numArquivo;
        f.frequencia = 1;
        insereTabela(t, pa.palavra, f);
    }
}

/**
*   Função que inicia as operações com a estrutura hash
*/
int inicioHash(int argc, char* argv[]){
    NumeroArquivo NA[TAM];
    DIR *dp;
    struct dirent *d;
    FILE *arq, *entrada;
    char caminhoArquivo[100], palavraEntrada[60], palavras[60];
    int numVetor = 0, quantidadeArquivo = 0, quantidadePalavras = 0, indice;
    lRanking l;
    tabela t = criaTabela();

    printf("\n\nHash:");
    dp = opendir(argv[1]);
    while((d = readdir(dp)) != NULL){   //Abrindo o diretório
        strcpy(NA[numVetor].nomeArquivo, d->d_name);
        NA[numVetor].numArquivo = numVetor + 1;
        quantidadeArquivo++;

        strcat(caminhoArquivo, argv[1]); //Montando o caminho para o arquivo
        strcat(caminhoArquivo, "/");
        strcat(caminhoArquivo, d->d_name);

        arq = abrirArquivo(caminhoArquivo);
        if(arq == NULL){
            printf("\nErro ao abrir o arquivo!\nO programa será encerrado\n");
            return 0;
        }

        lerArquivoHash(t, arq, NA[numVetor].numArquivo);

        fclose(arq);

        numVetor++;

        memset(caminhoArquivo, '\0', 100);  //limpa string que guarda o nome do arquivo
    }

    entrada = abrirArquivo(argv[2]);
    if(entrada == NULL){
        printf("\nErro ao abrir o arquivo!\nO programa será encerrado\n");
        return 0;
    }

    fscanf(entrada,"%d\n", &quantidadePalavras);//Lê a quantidade de consultas que irá fazer//Lê a quantidade de consultas que irá fazer

    for(indice = 0;indice < quantidadePalavras;indice++){
        fgets(palavraEntrada, 60, entrada); //Lê a linha do arquivo
        strcpy(palavras, palavraEntrada);

        l = ordenaDocumentosHash(t, palavraEntrada, NA, quantidadeArquivo);

        exibeNomeDocumentos(l, NA, quantidadeArquivo, palavras);
        encerraListaRanking(l);
        memset(palavraEntrada, '\0', 60);   //Limpa a string
    }

    printf("\n");
    fclose(entrada);
    closedir(dp);
    return 0;
}

