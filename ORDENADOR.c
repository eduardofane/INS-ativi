#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HISTORICO 50
#define MAX_TAM_VETOR 50

int historico[MAX_HISTORICO][MAX_TAM_VETOR];
int contador_historico = 0;
int tamanho_vetor_global = 0;
int contador_de_passos = 0;

void salvar_no_historico(int v[], int TAM) {
    if (contador_historico == 0) {
        for (int k = 0; k < TAM; k++)
            historico[contador_historico][k] = v[k];
        contador_historico++;
    } else {
        int diferente = 0;
        for (int k = 0; k < TAM; k++) {
            if (historico[contador_historico - 1][k] != v[k]) {
                diferente = 1;
                break;
            }
        }
        if (diferente && contador_historico < MAX_HISTORICO) {
            for (int k = 0; k < TAM; k++)
                historico[contador_historico][k] = v[k];
            contador_historico++;
        }
    }
}

void insertion_sort(int v[], int TAM) {
    int i, j, aux;

    salvar_no_historico(v, TAM); 

    for (i = 1; i < TAM; i++) {
        aux = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > aux) {
            v[j + 1] = v[j];
            j--;
            contador_de_passos++; 
            
        }

        if (v[j + 1] != aux) {
            v[j + 1] = aux;
            salvar_no_historico(v, TAM); 
        }
    }
}

void exibir_historico() {
    printf("\n==== HISTORICO DE ORDENACAO (PASSO A PASSO) ====\n");

    if (contador_historico == 0) {
        printf("Historico vazio.\n");
        return;
    }

    int TAM = tamanho_vetor_global;

    for (int i = 0; i < contador_historico; i++) {
        printf("Passo %d: [ ", i);
        for (int j = 0; j < TAM; j++)
            printf("%d ", historico[i][j]);
        printf("]\n");
    }

    printf("==== FIM DO HISTORICO ====\n");
}

void exibir_analise_de_passos(int TAM, int passos_caso_real) {
    int melhor_caso_qtd = 0;
    int pior_caso_qtd = (TAM * (TAM - 1)) / 2; 

    printf("\n==== ANALISE DE PASSOS (Deslocamentos) ====\n");
    printf("Melhor Caso (vetor já ordenado): %d deslocamentos\n", melhor_caso_qtd);
    printf("Pior Caso (vetor em ordem decrescente): %d deslocamentos\n", pior_caso_qtd);
    printf("Caso Real (vetor inicial do usuário): %d deslocamentos\n", passos_caso_real);
    printf("==================================================\n");
}

int main() {
    int TAM;
    int v[MAX_TAM_VETOR];

    printf("=== ORDENACAO POR INSERTION SORT COM HISTORICO ===\n");

    do {
        printf("Digite o tamanho do vetor (maximo %d):\n", MAX_TAM_VETOR);
        if (scanf("%d", &TAM) != 1 || TAM <= 0 || TAM > MAX_TAM_VETOR) {
            printf("Tamanho invalido ou excede o limite. Tente novamente.\n");
            while (getchar() != '\n');
        } else break;
    } while (1);

    tamanho_vetor_global = TAM;

    for (int i = 0; i < TAM; i++) {
        printf("Numero %d: ", i + 1);
        while (scanf("%d", &v[i]) != 1) {
            printf("Entrada invalida. Digite um NUMERO: ");
            while (getchar() != '\n');
        }
    }

    printf("\nVetor original: [ ");
    for (int i = 0; i < TAM; i++) printf("%d ", v[i]);
    printf("]\n");

    int passos_caso_real = 0;
    double soma_tempos = 0;

    int copia[MAX_TAM_VETOR];
    for (int i = 0; i < TAM; i++) copia[i] = v[i];

    contador_de_passos = 0;
    contador_historico = 0;

    insertion_sort(copia, TAM);
    exibir_historico();
    passos_caso_real = contador_de_passos;

    for (int repeticao = 0; repeticao < 5; repeticao++) {
        int temp[MAX_TAM_VETOR];
        for (int i = 0; i < TAM; i++) temp[i] = v[i];

        
        contador_de_passos = 0; 
        
        clock_t inicio = clock();
        
        insertion_sort(temp, TAM); 
        clock_t fim = clock();

        soma_tempos += (double)(fim - inicio) / CLOCKS_PER_SEC;
        
    }

    double tempo_medio = soma_tempos / 5.0;

    exibir_analise_de_passos(TAM, passos_caso_real);

    printf("\nResumo em formato CSV:\n");
    printf("algoritmo,tamanho,passos,tempo_medio\n");
    printf("insertion_sort,%d,%d,%.8f\n", TAM, passos_caso_real, tempo_medio);

    FILE *fp = fopen("resultados.csv", "w");
    if (fp != NULL) {
        fprintf(fp, "algoritmo,tamanho,passos,tempo_medio\n");
        fprintf(fp, "insertion_sort,%d,%d,%.8f\n", TAM, passos_caso_real, tempo_medio);
        fclose(fp);
    } else {
        printf("Erro ao criar arquivo CSV.\n");
    }

    return 0;
}
