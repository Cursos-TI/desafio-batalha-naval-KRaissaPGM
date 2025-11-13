#include <stdio.h>

#define TAM 10         // Tamanho do tabuleiro 10x10
#define NAVIO 3        // Valor que representa o navio no tabuleiro
#define TAM_NAVIO 3    // Tamanho fixo dos navios

// ---------------------- VALIDAÇÕES ----------------------------

// Valida se navio horizontal cabe no tabuleiro
int validaHorizontal(int linha, int coluna) {
    return (coluna + TAM_NAVIO <= TAM);
}

// Valida se navio vertical cabe no tabuleiro
int validaVertical(int linha, int coluna) {
    return (linha + TAM_NAVIO <= TAM);
}

// Valida se navio diagonal crescente (\) cabe no tabuleiro
int validaDiagonalPrincipal(int linha, int coluna) {
    return (linha + TAM_NAVIO <= TAM && coluna + TAM_NAVIO <= TAM);
}

// Valida se navio diagonal decrescente (/) cabe no tabuleiro
int validaDiagonalSecundaria(int linha, int coluna) {
    return (linha + TAM_NAVIO <= TAM && coluna - (TAM_NAVIO - 1) >= 0);
}

// Verifica sobreposição horizontal ou vertical
int verificaSobreposicaoLinear(int tab[TAM][TAM], int linha, int coluna, int vertical) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (vertical) {
            if (tab[linha + i][coluna] == NAVIO)
                return 0;
        } else {
            if (tab[linha][coluna + i] == NAVIO)
                return 0;
        }
    }
    return 1;
}

// Verifica sobreposição diagonal
int verificaSobreposicaoDiagonal(int tab[TAM][TAM], int linha, int coluna, int secundaria) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha + i;
        int c = secundaria ? (coluna - i) : (coluna + i);
        
        if (tab[r][c] == NAVIO)
            return 0;
    }
    return 1;
}

// ---------------------- FUNÇÃO PRINCIPAL ----------------------------

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa tabuleiro com água (0)
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    // -----------------------------------------------------------
    // DEFINIÇÃO DAS COORDENADAS DOS NAVIOS
    // (todas definidas diretamente no código, conforme o desafio)
    // -----------------------------------------------------------

    // Navios horizontais e verticais
    int hLinha = 1, hColuna = 2;   // Horizontal
    int vLinha = 4, vColuna = 7;   // Vertical

    // Navios diagonais
    int d1Linha = 6, d1Coluna = 1; // Diagonal principal  ( \ )
    int d2Linha = 0, d2Coluna = 9; // Diagonal secundária ( / )

    // ---------------------- POSICIONAMENTO ----------------------------

    // NAVIO HORIZONTAL
    if (!validaHorizontal(hLinha, hColuna) ||
        !verificaSobreposicaoLinear(tabuleiro, hLinha, hColuna, 0)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[hLinha][hColuna + i] = NAVIO;

    // NAVIO VERTICAL
    if (!validaVertical(vLinha, vColuna) ||
        !verificaSobreposicaoLinear(tabuleiro, vLinha, vColuna, 1)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[vLinha + i][vColuna] = NAVIO;

    // NAVIO DIAGONAL PRINCIPAL (\)
    if (!validaDiagonalPrincipal(d1Linha, d1Coluna) ||
        !verificaSobreposicaoDiagonal(tabuleiro, d1Linha, d1Coluna, 0)) {
        printf("Erro ao posicionar navio diagonal principal!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[d1Linha + i][d1Coluna + i] = NAVIO;

    // NAVIO DIAGONAL SECUNDÁRIA (/)
    if (!validaDiagonalSecundaria(d2Linha, d2Coluna) ||
        !verificaSobreposicaoDiagonal(tabuleiro, d2Linha, d2Coluna, 1)) {
        printf("Erro ao posicionar navio diagonal secundaria!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[d2Linha + i][d2Coluna - i] = NAVIO;

    // ---------------------- EXIBIÇÃO DO TABULEIRO ----------------------------

    printf("\n======= TABULEIRO BATALHA NAVAL (Nível Aventureiro) =======\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}