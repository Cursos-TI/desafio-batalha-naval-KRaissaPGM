#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define NAVIO 3
#define HABILIDADE 5
#define TAM_HAB 7   // Matrizes 7x7 de habilidades para melhor visualização
#define MEIO 3      // Centro da matriz de habilidade (7/2)

// ---------------- FUNÇÃO PARA LIMITE SEGURO -------------------

int dentroDoTabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// --------------- MATRIZES DE HABILIDADES -----------------------

// Preenche matriz de cone apontado para baixo
void gerarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // Cone cresce conforme desce: |j - MEIO| <= i
            if (abs(j - MEIO) <= i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Preenche matriz de cruz
void gerarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // Cruz: mesma linha central OU mesma coluna central
            if (i == MEIO || j == MEIO)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Preenche matriz de octaedro/losango
void gerarOctaedro(int oct[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // Distância de Manhattan ao centro <= tamanho do raio
            if (abs(i - MEIO) + abs(j - MEIO) <= MEIO)
                oct[i][j] = 1;
            else
                oct[i][j] = 0;
        }
    }
}

// ---------------- APLICAÇÃO DAS HABILIDADES --------------------

void aplicarHabilidade(int tab[TAM][TAM], int hab[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // Só aplica onde matriz vale 1
            if (hab[i][j] == 1) {

                int alvoLinha = origemLinha + (i - MEIO);
                int alvoColuna = origemColuna + (j - MEIO);

                if (dentroDoTabuleiro(alvoLinha, alvoColuna)) {
                    // Habilidade sobrepõe apenas se não for navio
                    if (tab[alvoLinha][alvoColuna] != NAVIO)
                        tab[alvoLinha][alvoColuna] = HABILIDADE;
                }
            }
        }
    }
}

// -------------------- FUNÇÃO PRINCIPAL -------------------------

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa com água
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    // ------------------------------------------------------------------
    // Inserindo navios (reaproveitado do desafio anterior para coerência)
    // ------------------------------------------------------------------

    // Horizontal
    for (int i = 0; i < 3; i++)
        tabuleiro[1][2 + i] = NAVIO;

    // Vertical
    for (int i = 0; i < 3; i++)
        tabuleiro[4 + i][7] = NAVIO;

    // Diagonal principal
    for (int i = 0; i < 3; i++)
        tabuleiro[6 + i][1 + i] = NAVIO;

    // Diagonal secundária
    for (int i = 0; i < 3; i++)
        tabuleiro[0 + i][9 - i] = NAVIO;

    // ------------------------------------------------------------------
    // CRIAÇÃO DAS MATRIZES DE HABILIDADES
    // ------------------------------------------------------------------

    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int oct[TAM_HAB][TAM_HAB];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(oct);

    // ------------------------------------------------------------------
    // APLICAÇÃO DAS HABILIDADES NO TABULEIRO
    // ------------------------------------------------------------------

    int origemConeLinha = 2, origemConeColuna = 2;
    int origemCruzLinha = 5, origemCruzColuna = 5;
    int origemOctLinha = 7, origemOctColuna = 7;

    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, oct, origemOctLinha, origemOctColuna);

    // ------------------------------------------------------------------
    // EXIBIÇÃO FINAL DO TABULEIRO
    // ------------------------------------------------------------------

    printf("\n=========== TABULEIRO FINAL - HABILIDADES NÍVEL MESTRE ===========\n\n");

    printf("Legenda: 0 = agua | 3 = navio | 5 = habilidade\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}