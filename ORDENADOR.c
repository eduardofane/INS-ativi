#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORICO 50
#define MAX_TAM_VETOR 50 

int historico[MAX_HISTORICO][MAX_TAM_VETOR];
int contador_historico = 0;
int tamanho_vetor_global = 0;
int contador_de_passos = 0; 

void salvar_no_historico(int v[], int TAM) {
    if (contador_historico < MAX_HISTORICO) {
        for (int k = 0; k < TAM; k++) {
            historico[contador_historico][k] = v[k];
        }
        contador_historico++;
    } else {
        printf("AVISO: Historico cheio (maximo %d).\n", MAX_HISTORICO);
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

        v[j + 1] = aux; 
      
        salvar_no_historico(v, TAM); 
    }
}

void exibir_historico() {
    printf("\n==== HISTORICO DE ORDENACAO (PASSOS) ====\n");
    printf("Total de passos de insercao salvos: %d / %d\n", contador_historico, MAX_HISTORICO);

    if (contador_historico == 0) {
        printf("Historico vazio.\n");
        return;
    }

    int TAM = tamanho_vetor_global;

    for (int i = 0; i < contador_historico; i++) {
        printf("\nPasso %d: ", i);

        if (i == 0) {
             printf("(Vetor Inicial)\n");
        } else {
             printf("(Elemento v[%d] inserido)\n", i);
        }

        printf("\t[ ");
        for (int j = 0; j < TAM; j++) {
            printf("%d ", historico[i][j]);
        }
        printf("]\n");
    }
    printf("\n==== FIM DO HISTORICO ====\n");
}


void exibir_analise_de_passos(int v_ordenado[], int TAM) {
    
    int melhor_caso_qtd = 0;
    int pior_caso_qtd = (TAM * (TAM - 1)) / 2;

    printf("\n==== ANALISE DE PASSOS (Deslocamentos) ====\n");
    printf("Para um vetor de tamanho %d, usando seus numeros:\n\n", TAM);
    
    printf("  -> Forma de MENOR Passos (Melhor Caso):\n");
    printf("     FORMA: Seus numeros ja em ordem crescente.\n");
    printf("     QUANTIDADE: %d deslocamentos necessarios.\n", melhor_caso_qtd);
    printf("     Exemplo de forma: [ ");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", v_ordenado[i]); 
    }
    printf("]\n");

    printf("\n  -> Forma de MAIOR Passos (Pior Caso):\n");
    printf("     FORMA: Seus numeros em ordem decrescente.\n");
    printf("     QUANTIDADE: %d deslocamentos necessarios.\n", pior_caso_qtd);
    printf("     Exemplo de forma: [ ");
    for (int i = TAM - 1; i >= 0; i--) { 
        printf("%d ", v_ordenado[i]); 
    }
    printf("]\n");

    printf("\n  -> SEU VETOR (Caso Real):\n");
    printf("     FORMA: O vetor original que voce digitou.\n");
    printf("     QUANTIDADE: %d deslocamentos necessarios.\n", contador_de_passos);
    printf("     Exemplo de forma: [ ");
    for (int i = 0; i < TAM; i++) { 
        printf("%d ", historico[0][i]); 
    }
    printf("]\n");
    
    printf("==================================================\n");

    
}


int main() {
    int TAM;
    int v[MAX_TAM_VETOR]; 
    int i;

    printf("=== ORDENACAO POR INSERTION SORT COM HISTORICO ===\n");

    do {
        printf("Digite o tamanho do vetor (maximo %d):\n", MAX_TAM_VETOR);
        if (scanf("%d", &TAM) != 1 || TAM <= 0 || TAM > MAX_TAM_VETOR) {
            printf("Tamanho invalido ou excede o limite. Tente novamente.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    tamanho_vetor_global = TAM;

    for (i = 0; i < TAM; i++) {
        printf("Numero %d: ", i + 1);
        
        while (scanf("%d", &v[i]) != 1) {
            printf("Entrada invalida. Digite um NUMERO: ");
            while (getchar() != '\n');
        }
    }

    printf("\nVetor original: ");
    for (i = 0; i < TAM; i++)
        printf("%d ", v[i]);
    printf("\n");

    insertion_sort(v, TAM); 

    printf("\nVetor ordenado: ");
    for (i = 0; i < TAM; i++)
        printf("%d ", v[i]);
    printf("\n");

    exibir_historico();

    exibir_analise_de_passos(v, TAM);

    return 0;
}
