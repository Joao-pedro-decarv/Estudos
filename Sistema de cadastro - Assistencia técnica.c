#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char marca[30];
    char modelo[30];
    char numeroSerie[30];
    char status[10]; // "Ativo" ou "Inativo"
} Equipamento;

void cadastrarEquipamento(){
    FILE *fp = fopen("equipamentos.txt", "a");
    Equipamento e;
    
    printf("\n--- Cadastro de Equipamento ---\n");
    printf("Nome do equipamento: ");
    scanf(" %[^\n]", e.nome);
    printf("Marca: ");
    scanf(" %[^\n]", e.marca);
    printf("Modelo: ");
    scanf(" %[^\n]", e.modelo);
    printf("Número de Série: ");
    scanf(" %[^\n]", e.numeroSerie);
    printf("Status (Ativo/Inativo): ");
    scanf(" %[^\n]", e.status);

    fprintf(fp, "%s|%s|%s|%s|%s\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status);
    fclose(fp);

    printf("✅ Equipamento cadastrado com sucesso!\n");
}

void listarEquipamentos() {
    FILE *fp = fopen("equipamentos.txt", "r");
    Equipamento e;

    printf("\n--- Lista de Equipamentos ---\n");
    while (fscanf(fp, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status) != EOF) {
        printf("Nome: %s | Marca: %s | Modelo: %s | Nº de Série: %s | Status: %s\n",
               e.nome, e.marca, e.modelo, e.numeroSerie, e.status);
    }
    fclose(fp);
}

void buscarPorNumeroSerie() {
    FILE *fp = fopen("equipamentos.txt", "r");
    Equipamento e;
    char numeroBuscado[30];
    int encontrado = 0;

    printf("\nDigite o número de série para buscar: ");
    scanf(" %[^\n]", numeroBuscado);

    while (fscanf(fp, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status) != EOF) {
        if (strcmp(e.numeroSerie, numeroBuscado) == 0) {
            printf("\n--- Equipamento Encontrado ---\n");
            printf("Nome: %s\nMarca: %s\nModelo: %s\nNúmero de Série: %s\nStatus: %s\n",
                   e.nome, e.marca, e.modelo, e.numeroSerie, e.status);
            encontrado = 1;
            break;
        }
    }
    fclose(fp);

    if (!encontrado) {
        printf("❌ Equipamento não encontrado.\n");
    }
}
void removerEquipamento() {
    FILE *fp = fopen("equipamentos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Equipamento e;
    char numeroBuscado[30];
    int removido = 0;

    printf("\nDigite o número de série do equipamento a ser removido: ");
    scanf(" %[^\n]", numeroBuscado);

    while (fscanf(fp, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status) != EOF) {
        if (strcmp(e.numeroSerie, numeroBuscado) != 0) {
            fprintf(temp, "%s|%s|%s|%s|%s\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status);
        } else {
            removido = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("equipamentos.txt");
    rename("temp.txt", "equipamentos.txt");

    if (removido)
        printf("✅ Equipamento removido com sucesso!\n");
    else
        printf("❌ Equipamento não encontrado.\n");
}

// Função para atualizar status
void atualizarStatus() {
    FILE *fp = fopen("equipamentos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Equipamento e;
    char numeroBuscado[30];
    int atualizado = 0;

    printf("\nDigite o número de série do equipamento para atualizar status: ");
    scanf(" %[^\n]", numeroBuscado);

    while (fscanf(fp, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status) != EOF) {
        if (strcmp(e.numeroSerie, numeroBuscado) == 0) {
            printf("Status atual: %s\nNovo status (Ativo/Inativo): ", e.status);
            scanf(" %[^\n]", e.status);
            atualizado = 1;
        }
        fprintf(temp, "%s|%s|%s|%s|%s\n", e.nome, e.marca, e.modelo, e.numeroSerie, e.status);
    }

    fclose(fp);
    fclose(temp);

    remove("equipamentos.txt");
    rename("temp.txt", "equipamentos.txt");

    if (atualizado)
        printf("✅ Status atualizado com sucesso!\n");
    else
        printf("❌ Equipamento não encontrado.\n");
}

int main() {
    int opcao;

    do {
        printf("\n====== Sistema de Cadastro de Equipamentos ======\n");
        printf("1. Cadastrar Equipamento\n");
        printf("2. Listar Equipamentos\n");
        printf("3. Buscar por Número de Série\n");
        printf("4. Remover Equipamento\n");
        printf("5. Atualizar Status\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarEquipamento(); break;
            case 2: listarEquipamentos(); break;
            case 3: buscarPorNumeroSerie(); break;
            case 4: removerEquipamento(); break;
            case 5: atualizarStatus(); break;
            case 6: printf("Saindo do sistema...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}