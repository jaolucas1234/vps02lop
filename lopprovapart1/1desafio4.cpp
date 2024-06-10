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
float totalGeral = 0.0;

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

float Reembolso(int distancia, float preco) {
    return distancia * preco / 3;
}

void calcularTotal() {
    totalGeral = 0;
    for(i=0; i < totalViagens; i++) {
        viagens[i].total = Reembolso(viagens[i].distancia, viagens[i].preco);
        totalGeral += viagens[i].total;
    }
}

int compararFuncionarios(const void *a, const void *b) {
    Viagem *va = (Viagem *)a;
    Viagem *vb = (Viagem *)b;
    return strcmp(va->funcionario, vb->funcionario);
}

void mostrarDados()
{
    float totalFuncionario = 0.0;
    char ultimoFuncionario[50];
    int primeiro = 1;

    printf("Viagens ACME:\n");
    printf("%-10s %-20s %-10s %-20s %-20s %-10s %-10s %-10s\n", "Matricula", "Funcionario", "Data", "Origem", "Destino", "Distancia", "Preco", "Total");

    qsort(viagens, totalViagens, sizeof(Viagem), compararFuncionarios);

    FILE *arq_saida;
    arq_saida = fopen("RelatorioViagens.md", "w");
    if (arq_saida == NULL)
    {
        printf("Erro ao criar o arquivo de saída\n");
    }
    else
    {
        fprintf(arq_saida, "Viagens ACME:\n");
        fprintf(arq_saida, "| Matricula | Funcionario | Data | Origem | Destino | Distancia | Preco | Total |\n");
        fprintf(arq_saida, "| --- | --- | --- | --- | --- | --- | --- | --- |\n");

        for(i=0; i < totalViagens; i++)
        {
            if(strcmp(viagens[i].funcionario, ultimoFuncionario)!= 0) {
                if(!primeiro) {
                    fprintf(arq_saida, "\nTotal do funcionário %s: R$ %.2f\n", ultimoFuncionario, totalFuncionario);
                }
                strcpy(ultimoFuncionario, viagens[i].funcionario);
                totalFuncionario = 0.0;
                primeiro = 0;
            }
            totalFuncionario += viagens[i].total;
            printf("%-10d %-20s %-10s %-20s %-20s %-10d %-10.2f %-10.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,  viagens[i].destino, viagens[i].distancia, viagens[i].preco,  viagens[i].total);
           fprintf(arq_saida, "| %-10d | %-20s | %-10s | %-20s | %-20s | %-10d | %-10.2f | %-10.2f |\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem, viagens[i].destino, viagens[i].distancia, viagens[i].preco, viagens[i].total);
        }
        fprintf(arq_saida, "\nTotal do funcionário %s: R$ %.2f\n", ultimoFuncionario, totalFuncionario);
        fprintf(arq_saida, "\nValor total que a empresa vai ter que reembolsar: R$ %.2f\n", totalGeral);
    }
    fclose(arq_saida);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularTotal();
    mostrarDados();
    return 0;
}