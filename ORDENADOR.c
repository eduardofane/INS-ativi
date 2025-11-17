#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HISTORICO 50
#define MAX_TAM_VETOR 50

int historico[MAX_HISTORICO][MAX_TAM_VETOR];
int contador_historico = 0;
int tamanho_vetor_global = 0;
int contador_de_passos = 0;

// Salva vetor no histórico somente se diferente do último salvo
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

// Insertion Sort modificado para registrar SOMENTE o vetor após cada inserção final
void insertion_sort(int v[], int TAM) {
    int i, j, aux;

    salvar_no_historico(v, TAM); // Salva o vetor inicial

    for (i = 1; i < TAM; i++) {
        aux = v[i];
        j = i - 1;

        // Realiza os deslocamentos
        while (j >= 0 && v[j] > aux) {
            v[j + 1] = v[j];
            j--;
            // O contador registra todos os deslocamentos, essencial para a análise de O(n^2)
            contador_de_passos++; 
            
            // REMOVIDO: salvar_no_historico(v, TAM);
            // Removemos o salvamento de passos intermediários (deslocamentos)
        }

        // 2. Insere o elemento 'aux' na posição correta
        // Verifica se houve mudança para evitar salvar o mesmo vetor se 'aux' não se moveu.
        if (v[j + 1] != aux) {
            v[j + 1] = aux;
            // Salva o estado FINAL da iteração (o vetor parcialmente ordenado)
            salvar_no_historico(v, TAM); 
        }
    }
}

// Exibe histórico completo sem repetições
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

// Exibe análise de passos
void exibir_analise_de_passos(int TAM, int passos_caso_real) {
    int melhor_caso_qtd = 0;
    // Cálculo do pior caso: (n * (n - 1)) / 2 para n = TAM
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

    // Leitura do tamanho do vetor
    do {
        printf("Digite o tamanho do vetor (maximo %d):\n", MAX_TAM_VETOR);
        if (scanf("%d", &TAM) != 1 || TAM <= 0 || TAM > MAX_TAM_VETOR) {
            printf("Tamanho invalido ou excede o limite. Tente novamente.\n");
            while (getchar() != '\n');
        } else break;
    } while (1);

    tamanho_vetor_global = TAM;

    // Leitura dos elementos
    for (int i = 0; i < TAM; i++) {
        printf("Numero %d: ", i + 1);
        while (scanf("%d", &v[i]) != 1) {
            printf("Entrada invalida. Digite um NUMERO: ");
            while (getchar() != '\n');
        }
    }

    // Exibe vetor original
    printf("\nVetor original: [ ");
    for (int i = 0; i < TAM; i++) printf("%d ", v[i]);
    printf("]\n");

    // ======= Caso Real =======
    int passos_caso_real = 0;
    double soma_tempos = 0;

    int copia[MAX_TAM_VETOR];
    for (int i = 0; i < TAM; i++) copia[i] = v[i];

    contador_de_passos = 0;
    contador_historico = 0;

    // Ordenação com histórico passo a passo
    insertion_sort(copia, TAM);
    exibir_historico();
    passos_caso_real = contador_de_passos;

    // Calcula tempo médio (Repete o processo 5 vezes para média de tempo)
    for (int repeticao = 0; repeticao < 5; repeticao++) {
        int temp[MAX_TAM_VETOR];
        for (int i = 0; i < TAM; i++) temp[i] = v[i];

        // É importante resetar apenas o contador_de_passos
        contador_de_passos = 0; 
        
        clock_t inicio = clock();
        // Não precisamos do histórico nestas iterações, apenas do tempo e passos
        // A função insertion_sort deve ser usada, mas sem gerar histórico extra
        // Como contador_historico foi resetado antes da primeira chamada, ele só 
        // será preenchido novamente se o usuário chamar exibir_historico(), o que é aceitável.
        insertion_sort(temp, TAM); 
        clock_t fim = clock();

        soma_tempos += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }

    double tempo_medio = soma_tempos / 5.0;

    // Exibe análise de passos
    exibir_analise_de_passos(TAM, passos_caso_real);

    // CSV na tela
    printf("\nResumo em formato CSV:\n");
    printf("algoritmo,tamanho,passos,tempo_medio\n");
    printf("insertion_sort,%d,%d,%.8f\n", TAM, passos_caso_real, tempo_medio);

    // Salva em arquivo CSV
    FILE *fp = fopen("resultados.csv", "w");
    if (fp != NULL) {
        fprintf(fp, "algoritmo,tamanho,passos,tempo_medio\n");
        fprintf(fp, "insertion_sort,%d,%d,%.8f\n", TAM, passos_caso_real, tempo_medio);
        fclose(fp);
        printf("Arquivo 'resultados.csv' salvo com sucesso.\n");
    } else {
        printf("Erro ao criar arquivo CSV.\n");
    }

    return 0;
}
