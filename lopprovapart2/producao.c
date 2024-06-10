#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAQUINAS 4
#define MAX_REGISTROS 100
#define MAX_DIAS 30

typedef struct {
    int quantidade;
} Producao;

Producao producao[MAX_MAQUINAS][MAX_DIAS];

void carregaDados() {
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("producao.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fgets(linha, 100, arquivo); // Ignorar a primeira linha
    int i = 0;
    while (fgets(linha, 100, arquivo) != NULL && i < MAX_REGISTROS) {
        char data[10];
        int dia, maquina;
        sscanf(linha, "%[^;];%*[^;];%d", data, &maquina);
        sscanf(data, "%d/%*d/%*d", &dia);
        producao[maquina - 1][dia - 1].quantidade++;
        i++;
    }
    fclose(arquivo);
}

void salvarRelatorio() {
    FILE *arquivo;
    arquivo = fopen("explosivos.md", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo\n");
        return;
    }
    fprintf(arquivo, "| Dia | Máquina 1 | Máquina 2 | Máquina 3 | Máquina 4 |\n");
    fprintf(arquivo, "| --- | --- | --- | --- | --- |\n");
    for (int i = 0; i < MAX_DIAS; i++) {
        fprintf(arquivo, "| %02d |", i + 1);
        for (int j = 0; j < MAX_MAQUINAS; j++) {
            fprintf(arquivo, " %3d |", producao[j][i].quantidade);
        }
        fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "| --- | --- | --- | --- | --- |\n");
    fprintf(arquivo, "| Total |");
    for (int j = 0; j < MAX_MAQUINAS; j++) {
        int total = 0;
        for (int i = 0; i < MAX_DIAS; i++) {
            total += producao[j][i].quantidade;
        }
        fprintf(arquivo, " %3d |", total);
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

int main() {
    for (int i = 0; i < MAX_MAQUINAS; i++) {
        for (int j = 0; j < MAX_DIAS; j++) {
            producao[i][j].quantidade = 0;
        }
    }
    carregaDados();
    salvarRelatorio();
    return 0;
}