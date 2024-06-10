
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("viagens.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq)!= NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            totalViagens++;
        }
    }
    fclose(arq);
}

void calcularTotalReembolso() {
    for (i = 0; i < totalViagens; i++) {
        viagens[i].total = (viagens[i].preco / 100) * viagens[i].distancia / 3.0;
    }
}

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("%-10s %-20s %-10s %-20s %-20s %-10s %-10s %-10s\n", "Matricula", "Funcionario", "Data", "Origem", "Destino", "Distancia", "Preco", "Total");
    for(i=0; i < totalViagens; i++)
    {
        printf("%-10d %-20s %-10s %-20s %-20s %-10d %-10.2f %-10.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,  viagens[i].destino, viagens[i].distancia, viagens[i].preco,  viagens[i].total);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularTotalReembolso();
    mostrarDados();
    return 0;
}