#ifndef INICIO_H_INCLUDED
#define INICIO_H_INCLUDED

#define TAM 100

typedef struct{
    char nomeArquivo[100];
    int numArquivo;
}NumeroArquivo;

int inicio(int, char*[]);
int inicioArvore(int, char*[]);
int inicioHash(int, char*[]);
void retiraBarraN(char*);
int retornaQuantidadePalavras(char*);
char** retornaStringPalavras(char*, int);
FILE* abrirArquivo(char*);
char** alocaString(int);

#endif // INICIO_H_INCLUDED
