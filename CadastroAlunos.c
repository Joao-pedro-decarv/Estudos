#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
    int idade;
    float altura;
    char nome[50];
    int matricula;

    printf("Digite sua idade: \n");
    scanf("%d", &idade);

    printf("Digite sua altura: \n");
    scanf("%f", &altura);
    
    printf("Digite seu nome: \n");
    scanf(" %s", &nome);

    printf("Digite sua matricula: \n");
    scanf("%d", &matricula);

    printf("Nome do aluno: %s - Matrícula: %d", nome , matricula);
    printf("Idade: %d - Altura: %f", idade, altura);

    return 0;

}