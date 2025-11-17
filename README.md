# Ordenação e Análise de Desempenho em C

## Descrição do Projeto

> Este programa implementa o algoritmo Insertion Sort em C, incluindo registro completo do histórico de passos, análise de desempenho e interação com o usuário.

> O objetivo é mostrar, passo a passo, como o vetor evolui durante o processo de ordenação, além de comparar o número de deslocamentos realizados com o melhor caso, pior caso e caso real.

## Funcionalidades Implementadas

> Entrada Interativa
> - O usuário escolhe o tamanho do vetor.
> - Digita cada número manualmente, com validação de entrada.

> Ordenação via Insertion Sort
> - Ordena o vetor do usuário.
> - Conta o número total de deslocamentos realizados durante a ordenação.

> Registro de Histórico
> - Cada passo do algoritmo é armazenado em uma matriz historico[][].
> - O histórico mostra o vetor inicial e o estado do vetor após cada inserção.

> Análise Comparativa de Passos
> -  Melhor caso: vetor já ordenado (0 deslocamentos).
> -  Pior caso: vetor em ordem decrescente (n(n−1)/2 deslocamentos).
> -  Caso real: com base no vetor digitado e nas operações realmente realizadas.

## Como compilar e rodar o código
1. Abra o código no seu compilador C (Dev C++, Code::Blocks ou GDB Online).

2. Compile o programa:
```bash
gcc -O1 -std=c11 main.c -o ordena
```
3. Para rodar o programa:
```bash
./ordena
```

## Politicagem de Contagem de Passos

> O programa utiliza o número de deslocamentos internos do Insertion Sort como métrica de custo.

### O que conta como Passo?
> Um passo é contabilizado toda vez que um elemento é movido para a direita dentro do laço:
```bash
while (j >= 0 && v[j] > aux) {
    v[j + 1] = v[j];  // ← deslocamento contado
    j--;
    contador_de_passos++;
}
```

## Método de Medição de Tempo

> Como o tempo é medido:

```bash
clock_t inicio = clock();
insertion_sort(v, TAM);
clock_t fim = clock();
double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
```

## CSV com resultados

| algoritmo       | tamanho | passos | tempo_medio |
|-----------------|--------|--------|------------|
| insertion_sort  | 8      | 12     | 0.000200 |

## Discussão Crítica: Computabilidade × Escalabilidade

> Computabilidade: O algoritmo de Insertion Sort é computável e eficiente para vetores pequenos, registrando passo a passo cada movimentação dos elementos, o que permite analisar o comportamento da ordenação.

> Escalabilidade: Para vetores maiores, o número de passos e o histórico crescem rapidamente, tornando o registro detalhado impraticável. Isso evidencia que a escalabilidade do método é limitada; o Insertion Sort é mais adequado para pequenas quantidades de dados.

> - Melhor caso (vetor já ordenado) → mínima movimentação;
> - Pior caso (vetor invertido) → máxima movimentação;
> - Para grandes vetores, o histórico de todos os passos fica inviável de armazenar.

 > Conclusão do Melhor Método: O Insertion Sort é simples e eficiente para vetores pequenos e quase ordenados, mas não é escalável para grandes volumes de dados. O registro de histórico passo a passo é útil para análise pedagógica, mas impraticável para uso em sistemas de grande escala.
