#include <stdio.h>

#define TAM 10       // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3      // Valor usado para representar partes do navio
#define TAM_NAVIO 3  // Tamanho fixo dos navios

// Função para verificar se o navio cabe no tabuleiro (horizontal)
int validaHorizontal(int linha, int coluna) {
    return (coluna + TAM_NAVIO <= TAM);
}

// Função para verificar se o navio cabe no tabuleiro (vertical)
int validaVertical(int linha, int coluna) {
    return (linha + TAM_NAVIO <= TAM);
}

// Função para verificar sobreposição
int verificaSobreposicao(int tabuleiro[TAM][TAM], int linha, int coluna, int vertical) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (vertical) {
            if (tabuleiro[linha + i][coluna] == NAVIO)
                return 0; // Encontrou sobreposição
        } else {
            if (tabuleiro[linha][coluna + i] == NAVIO)
                return 0;
        }
    }
    return 1; // Sem sobreposição
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializando o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Coordenadas dos navios (definidas diretamente no código)
    int linhaH = 2, colunaH = 1; // Navio horizontal
    int linhaV = 5, colunaV = 5; // Navio vertical

    // Validação do navio horizontal
    if (!validaHorizontal(linhaH, colunaH)) {
        printf("Erro: navio horizontal nao cabe no tabuleiro.\n");
        return 1;
    }
    if (!verificaSobreposicao(tabuleiro, linhaH, colunaH, 0)) {
        printf("Erro: sobreposicao detectada no navio horizontal.\n");
        return 1;
    }

    // Posicionando navio horizontal
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = NAVIO;
    }

    // Validação do navio vertical
    if (!validaVertical(linhaV, colunaV)) {
        printf("Erro: navio vertical nao cabe no tabuleiro.\n");
        return 1;
    }
    if (!verificaSobreposicao(tabuleiro, linhaV, colunaV, 1)) {
        printf("Erro: sobreposicao detectada no navio vertical.\n");
        return 1;
    }

    // Posicionando navio vertical
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = NAVIO;
    }

    // Exibindo o tabuleiro
    printf("\n=== TABULEIRO ===\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}