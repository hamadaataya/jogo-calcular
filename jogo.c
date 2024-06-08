#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int pontos;
    int nivel;
    char nome[50];
} Jogador;

Jogador* inicializarJogador() {
    Jogador* jogador = malloc(sizeof(Jogador));
    jogador->pontos = 0;
    jogador->nivel = 1;
    printf("Digite seu nome: ");
    scanf("%s", jogador->nome);
    return jogador;
}

void imprimirMenuInicial() {
    printf("Bem-vindo ao jogo!\n");
    printf("1. Iniciar jogo\n");
    printf("2. Sair do jogo\n");
}

void imprimirMenuJogo(Jogador* jogador) {
    printf("Pontos: %d\n", jogador->pontos);
    printf("Nivel: %d\n", jogador->nivel);
    printf("Nome: %s\n", jogador->nome);
    printf("1. Avancar\n");
    printf("2. Cancelar\n");
    printf("3. Reiniciar\n");
    printf("4. Sair do jogo\n");
    printf("Escolha uma opcao: ");
}

int gerarNumeroAleatorio(int min, int max) {
    return rand() % (max - min + 1) + min;
}

char escolherOperacaoAleatoria() {
    char operacoes[] = {'+', '-', '*', '/'};
    int indice = rand() % 4;
    return operacoes[indice];
}

void jogarRound(Jogador* jogador) {
    int min = 1 + (jogador->nivel - 1) * 2;
    int max = 10 + (jogador->nivel - 1) * 2;

    int num1 = gerarNumeroAleatorio(min, max);
    int num2 = gerarNumeroAleatorio(min, max);
    char operacao = escolherOperacaoAleatoria();
    int resposta;
    float resultado;

    if (operacao == '/' && num2 == 0) {
        num2 = 1;
    }

    switch (operacao) {
        case '+':
            resultado = num1 + num2;
            printf("Qual e o resultado da soma de %d + %d?\n", num1, num2);
            break;
        case '-':
            resultado = num1 - num2;
            printf("Qual e o resultado da subtracao de %d - %d?\n", num1, num2);
            break;
        case '*':
            resultado = num1 * num2;
            printf("Qual e o resultado da multiplicacao de %d * %d?\n", num1, num2);
            break;
        case '/':
            resultado = (float)num1 / num2;
            printf("Qual e o resultado da divisao de %d / %d?\n", num1, num2);
            break;
    }

    scanf("%d", &resposta);
    if ((operacao == '/' && fabsf(resposta - resultado) < 0.001) || (operacao!= '/' && resposta == resultado)) {
        jogador->pontos += 10;
        jogador->nivel += 1;
        printf("Parabens! Voce acertou!\n");
    } else {
        printf("Errou! O resultado correto e %.2f.\n", resultado);
    }
}

void pausarJogo() {
    printf("Jogo pausado. Pressione enter para continuar...\n");
    getchar();
    getchar();
}

void reiniciarJogo(Jogador* jogador) {
    jogador->pontos = 0;
    jogador->nivel = 1;
    printf("Jogo reiniciado!\n");
}

int main() {
    srand(time(NULL));
    Jogador* jogador = inicializarJogador();

    int opcao;
    do {
        imprimirMenuInicial();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                while (1) {
                    imprimirMenuJogo(jogador);
                    int opcaoJogo;
                    scanf("%d", &opcaoJogo);
                    switch (opcaoJogo) {
                        case 1:
                            jogarRound(jogador);
                            break;
                        case 2:
                            pausarJogo();
                            break;
                        case 3:
                            reiniciarJogo(jogador);
                            break;
                        case 4:
                            free(jogador);
                            return 0;
                    }
                }
                break;
            case 2:
                free(jogador);
                return 0;
        }
    } while (1);

    return (0);
}
