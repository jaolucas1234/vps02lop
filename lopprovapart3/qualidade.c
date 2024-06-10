#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTROS 100

typedef struct {
    int numero_de_serie;
    float resistencia;
    float durabilidade;
} Produto;

Produto produtos[MAX_REGISTROS];

void carregaDados() {
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("parametros.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fgets(linha, 100, arquivo); // Ignorar a primeira linha
    int i = 0;
    while (fgets(linha, 100, arquivo)!= NULL && i < MAX_REGISTROS) {
        char numero_de_serie_str[10];
        char resistencia_str[10];
        char durabilidade_str[10];
        sscanf(linha, "%[^;];%[^;];%s", numero_de_serie_str, resistencia_str, durabilidade_str);
        produtos[i].numero_de_serie = atoi(numero_de_serie_str);
        produtos[i].resistencia = atof(resistencia_str);
        produtos[i].durabilidade = atof(durabilidade_str);
        i++;
    }
    fclose(arquivo);
}

void analise() {
    FILE *arquivo_saida;
    arquivo_saida = fopen("qualidade.md", "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao abrir o arquivo de saída\n");
        return;
    }

    int quantidade = 0;
    float soma_resistencia = 0;
    float soma_durabilidade = 0;
    float max_resistencia = -1;
    float min_resistencia = 100;
    float max_durabilidade = -1;
    float min_durabilidade = 100;
    int indice_max_resistencia = -1;
    int indice_min_resistencia = -1;
    int indice_max_durabilidade = -1;
    int indice_min_durabilidade = -1;

    for (int i = 0; i < MAX_REGISTROS; i++) {
        if (produtos[i].numero_de_serie!= 0) {
            quantidade++;
            soma_resistencia += produtos[i].resistencia;
            soma_durabilidade += produtos[i].durabilidade;

            if (produtos[i].resistencia > max_resistencia) {
                max_resistencia = produtos[i].resistencia;
                indice_max_resistencia = i;
            }
            if (produtos[i].resistencia < min_resistencia) {
                min_resistencia = produtos[i].resistencia;
                indice_min_resistencia = i;
            }

            if (produtos[i].durabilidade > max_durabilidade) {
                max_durabilidade = produtos[i].durabilidade;
                indice_max_durabilidade = i;
            }
            if (produtos[i].durabilidade < min_durabilidade) {
                min_durabilidade = produtos[i].durabilidade;
                indice_min_durabilidade = i;
            }
        }
    }

    float media_resistencia = soma_resistencia / quantidade;
    float media_durabilidade = soma_durabilidade / quantidade;

    fprintf(arquivo_saida, "Média de resistência: %.2f\n", media_resistencia);
    fprintf(arquivo_saida, "Média de durabilidade: %.2f\n", media_durabilidade);

    fprintf(arquivo_saida, "Produto com maior resistência: %d (%.2f)\n", produtos[indice_max_resistencia].numero_de_serie, max_resistencia);
    fprintf(arquivo_saida, "Produto com menor resistência: %d (%.2f)\n", produtos[indice_min_resistencia].numero_de_serie, min_resistencia);

    fprintf(arquivo_saida, "Produto com maior durabilidade: %d (%.2f)\n", produtos[indice_max_durabilidade].numero_de_serie, max_durabilidade);
    fprintf(arquivo_saida, "Produto com menor durabilidade: %d (%.2f)\n", produtos[indice_min_durabilidade].numero_de_serie, min_durabilidade);

    int acima_media_resistencia = 0;
    int abaixo_media_resistencia = 0;
    int acima_media_durabilidade = 0;
    int abaixo_media_durabilidade = 0;

    for (int i = 0; i < MAX_REGISTROS; i++) {
        if (produtos[i].resistencia > media_resistencia) {
            acima_media_resistencia++;
        } else {
            abaixo_media_resistencia++;
        }

        if (produtos[i].durabilidade > media_durabilidade) {
            acima_media_durabilidade++;
        } else {
            abaixo_media_durabilidade++;
        }
    }

fprintf(arquivo_saida, "Existem %d produtos acima da média de resistência e %d abaixo.\n", acima_media_resistencia, abaixo_media_resistencia);
    fprintf(arquivo_saida, "Existem %d produtos acima da média de durabilidade e %d abaixo.\n", acima_media_durabilidade, abaixo_media_durabilidade);

    fclose(arquivo_saida);
}

int main() {
    carregaDados();
    analise();
    return 0;
}