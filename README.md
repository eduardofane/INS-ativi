📚 Análise de Algoritmos: Insertion Sort com Histórico
Este projeto em C implementa o algoritmo de ordenação Insertion Sort e o aprimora com uma funcionalidade de histórico e análise de passos. Ele salva o estado do vetor após cada inserção para demonstrar visualmente como o algoritmo funciona e, em seguida, compara o número real de deslocamentos com o melhor e o pior caso.

⚙️ Estrutura do Código (Explicação Linha por Linha)
1. Inclusão de Bibliotecas e Definições
C

#include <stdio.h>    // Funções de entrada/saída (printf, scanf)
#include <stdlib.h>   // Funções de utilidade geral (exit, etc.)
#include <string.h>   // Funções de manipulação de strings (embora pouco usado, é comum)

#define MAX_HISTORICO 50 // Limite máximo de estados do vetor que o histórico pode armazenar
#define MAX_TAM_VETOR 50 // Limite máximo do tamanho do vetor que o usuário pode ordenar
2. Variáveis Globais (Estado do Programa)
C

int historico[MAX_HISTORICO][MAX_TAM_VETOR]; // Matriz que armazena o histórico dos vetores (o estado do vetor em cada passo do sort)
int contador_historico = 0;                 // Conta quantos passos/estados já foram salvos no histórico
int tamanho_vetor_global = 0;               // Armazena o tamanho (TAM) do vetor digitado pelo usuário (usado nas funções de exibição)
int contador_de_passos = 0;                 // Contador para registrar o número de deslocamentos (v[j+1] = v[j]) feitos pelo Insertion Sort
3. Função: salvar_no_historico
C

void salvar_no_historico(int v[], int TAM) {
    if (contador_historico < MAX_HISTORICO) { // Verifica se ainda há espaço no histórico
        for (int k = 0; k < TAM; k++) {
            historico[contador_historico][k] = v[k]; // Copia cada elemento do vetor atual para a próxima linha livre do histórico
        }
        contador_historico++; // Incrementa o contador para apontar para o próximo espaço vazio
    } else {
        printf("AVISO: Historico cheio (maximo %d).\n", MAX_HISTORICO); // Alerta se o limite foi atingido
    }
}
4. Função: insertion_sort
C

void insertion_sort(int v[], int TAM) {
    int i, j, aux;

  salvar_no_historico(v, TAM); // Salva o estado INICIAL do vetor (Passo 0)

  for (i = 1; i < TAM; i++) { // Loop principal: itera sobre os elementos não ordenados (a partir do segundo elemento, índice 1)
        aux = v[i];           // 'aux' é o elemento atual a ser inserido na sub-lista ordenada
        j = i - 1;            // 'j' é o índice do último elemento da sub-lista ordenada

  while (j >= 0 && v[j] > aux) { // Loop interno: Compara o elemento 'aux' com os elementos à sua esquerda
            v[j + 1] = v[j];        // DESLOCAMENTO: Move o elemento maior (v[j]) uma posição para a direita
            j--;                    // Move para o próximo elemento à esquerda
            contador_de_passos++;   // Contabiliza o deslocamento para a análise de desempenho
        }

  v[j + 1] = aux;         // INSERÇÃO: Coloca 'aux' (o elemento que estava em v[i]) na sua posição correta
        
   salvar_no_historico(v, TAM); // Salva o estado do vetor após a inserção (Passo 1, 2, 3...)
    }
}
5. Função: exibir_historico
C

void exibir_historico() {
    // ... (Imprime cabeçalho e verifica se o histórico está vazio) ...

  int TAM = tamanho_vetor_global; // Recupera o tamanho do vetor do usuário

  for (int i = 0; i < contador_historico; i++) { // Itera sobre os passos salvos
        printf("\nPasso %d: ", i);

  if (i == 0) {
             printf("(Vetor Inicial)\n"); // Rótulo para o primeiro passo
        } else {
             printf("(Elemento v[%d] inserido)\n", i); // Rótulo para os passos de inserção
        }

  printf("\t[ ");
        for (int j = 0; j < TAM; j++) {
            printf("%d ", historico[i][j]); // Imprime o vetor do passo 'i'
        }
        printf("]\n");
    }
    // ... (Imprime rodapé) ...
}
6. Função: exibir_analise_de_passos
C

void exibir_analise_de_passos(int v_ordenado[], int TAM) {
    
  int melhor_caso_qtd = 0; // O Insertion Sort tem 0 deslocamentos no melhor caso (vetor já ordenado)
    // Calcula o número MÁXIMO de deslocamentos (Pior Caso: ordem decrescente).
    // A complexidade é O(n^2), dada pela soma de 1 a n-1: n * (n - 1) / 2
    int pior_caso_qtd = (TAM * (TAM - 1)) / 2;

  // ... (Imprime cabeçalho da análise) ...

  // --- (Melhor Caso: Imprime 0 deslocamentos e a forma do vetor ordenado) ---
    printf(" -> Forma de MENOR Passos (Melhor Caso):\n");
    printf("      QUANTIDADE: %d deslocamentos necessarios.\n", melhor_caso_qtd);
    // Imprime o vetor ordenado (Melhor Caso é igual ao resultado)

  // --- (Pior Caso: Imprime o máximo de deslocamentos e a forma do vetor invertido) ---
    printf("\n -> Forma de MAIOR Passos (Pior Caso):\n");
    printf("      QUANTIDADE: %d deslocamentos necessarios.\n", pior_caso_qtd);
    // Imprime o vetor em ordem decrescente (o pior caso para o Insertion Sort)

  // --- (Caso Real: Imprime a contagem de passos do vetor digitado) ---
    printf("\n -> SEU VETOR (Caso Real):\n");
    printf("      QUANTIDADE: %d deslocamentos necessarios.\n", contador_de_passos);
    // Imprime o vetor original (resgatado do primeiro passo do histórico)
    
// ... (Imprime rodapé) ...
}
7. Função Principal: main
C

int main() {
    int TAM;
    int v[MAX_TAM_VETOR];
    int i;

  // --- Entrada do Tamanho do Vetor ---
    do {
        printf("Digite o tamanho do vetor (maximo %d):\n", MAX_TAM_VETOR);
        // Garante que o usuário digite um número válido e dentro do limite
        if (scanf("%d", &TAM) != 1 || TAM <= 0 || TAM > MAX_TAM_VETOR) {
            // ... (Tratamento de erro e limpeza de buffer) ...
        } else {
            break;
        }
    } while (1);

  tamanho_vetor_global = TAM; // Define o tamanho global

  // --- Entrada dos Elementos do Vetor ---
    for (i = 0; i < TAM; i++) {
        printf("Numero %d: ", i + 1);
        // Garante que o usuário digite um número (tratamento de erro)
        while (scanf("%d", &v[i]) != 1) {
            // ... (Tratamento de erro e limpeza de buffer) ...
        }
    }

  // --- Execução e Exibição ---
    printf("\nVetor original: ..."); // Exibe o vetor antes da ordenação
    
  insertion_sort(v, TAM); // CHAMA O ALGORITMO DE ORDENAÇÃO

  printf("\nVetor ordenado: ..."); // Exibe o vetor ordenado
    
  exibir_historico(); // Exibe cada passo da ordenação
    
  exibir_analise_de_passos(v, TAM); // Compara o desempenho do caso real com o melhor e pior caso
   
  return 0; // Encerra o programa
}
2. Variáveis Globais (Estado do Programa)
C

