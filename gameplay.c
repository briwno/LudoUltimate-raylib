#include "raylib.h"
#include <time.h>

#define NUM_JOGADORES 4
#define NUM_PECAS 4
#define TAMANHO_CASA 52
#define NUM_CASAS 72

// 0 jogador verde
// 1 jogador vermelho
// 2 jogador amarelo
// 3 jogador azul

#define NUM_CASAS_BOMBA 4
int casasBomba[NUM_CASAS_BOMBA] = {44, 6, 20, 32};

int posicaoCasaX[NUM_CASAS];
int posicaoCasaY[NUM_CASAS];

#define NUM_CASAS_FINAIS 5

int casasFinaisVerde[NUM_CASAS_FINAIS] = {57, 58, 59, 60, 61};
int casasFinaisVermelho[NUM_CASAS_FINAIS] = {67, 68, 69, 70, 71};
int casasFinaisAmarelo[NUM_CASAS_FINAIS] = {52, 53, 54, 55, 56};
int casasFinaisAzul[NUM_CASAS_FINAIS] = {62, 63, 64, 65, 66};



int posicaoPecaX[NUM_JOGADORES][NUM_PECAS];
int posicaoPecaY[NUM_JOGADORES][NUM_PECAS];
int pecaEmJogo[NUM_JOGADORES][NUM_PECAS];
int passagensIniciais[NUM_JOGADORES][NUM_PECAS];

int baseX[NUM_JOGADORES][NUM_PECAS];
int baseY[NUM_JOGADORES][NUM_PECAS];

Color coresJogadores[NUM_JOGADORES] = {GREEN, RED, YELLOW, BLUE};
const char* nomesJogadores[NUM_JOGADORES] = {"Verde", "Vermelho", "Amarelo", "Azul"};

int jogadorAtual = 0;
int dado;
int pecaSelecionada = -1;

int passagensCasa41 = 0;
int passagensCasa2 = 0;
int passagensCasa28 = 0;
int passagensCasa15 = 0;

int posicaoInicialX[NUM_JOGADORES][NUM_PECAS];
int posicaoInicialY[NUM_JOGADORES][NUM_PECAS];

bool dadorolado = false;

Texture2D pecasAmarelas[NUM_PECAS], pecasVerdes[NUM_PECAS], pecasVermelhas[NUM_PECAS], pecasAzuis[NUM_PECAS];

int posicaoXPrimeiraCasa[4] = { 608, 609, 273, 777 };
int posicaoYPrimeiraCasa[4] = { 93, 594, 430, 430 };

void InicializarJogadores() {
    int posicaoInicialX[NUM_JOGADORES][NUM_PECAS] = {
        {415, 359, 415, 471},
        {901, 955, 848, 901},
        {415, 359, 415, 470},
        {899, 845, 899, 953}
    };
    int posicaoInicialY[NUM_JOGADORES][NUM_PECAS] = {
        {179, 234, 290, 234},
        {180, 235, 235, 291},
        {668, 722, 776, 722},
        {667, 722, 776, 722}
    };

    for (int i = 0; i < NUM_JOGADORES; i++) {
        for (int j = 0; j < NUM_PECAS; j++) {
            posicaoPecaX[i][j] = posicaoInicialX[i][j];
            posicaoPecaY[i][j] = posicaoInicialY[i][j];
            pecaEmJogo[i][j] = 0;
            passagensIniciais[i][j] = 0;

            baseX[i][j] = posicaoInicialX[i][j];
            baseY[i][j] = posicaoInicialY[i][j];
        }
    }
}

bool EhCasaBomba(int casa) {
    for (int i = 0; i < NUM_CASAS_BOMBA; i++) {
        if (casasBomba[i] == casa) {
            return true;
        }
    }
    return false;
}


void RolarDado() {

    if(!dadorolado){ 
    dado = GetRandomValue(1, 6);
    dadorolado = true;
    }
}

void resetarDado(){
    dadorolado = false;
}

void PassarTurno() {
    jogadorAtual = (jogadorAtual + 1) % NUM_JOGADORES;
    pecaSelecionada = -1;
    dado = 0;
    
}

void MoverPeca(int jogador, int indicePeca, int passos, int dado) {
    printf("MoverPeca - Jogador: %d, Peça: %d, Passos: %d, Dado: %d\n", jogador, indicePeca, passos, dado);

    if (pecaEmJogo[jogador][indicePeca] == 0) {
        printf("Peça ainda não está em jogo.\n");
        if (dado == 6) {
            printf("Dado é 6, colocando a peça em jogo.\n");
            pecaEmJogo[jogador][indicePeca] = 1;
            passagensIniciais[jogador][indicePeca] = 0;
            int casaInicial;
            switch (jogador) {
                case 0: casaInicial = 41; break;
                case 1: casaInicial = 2; break;
                case 2: casaInicial = 28; break;
                case 3: casaInicial = 15; break;
                default: return; // Jogador inválido
            }
            posicaoPecaX[jogador][indicePeca] = posicaoCasaX[casaInicial];
            posicaoPecaY[jogador][indicePeca] = posicaoCasaY[casaInicial];
        }
    } else if (pecaEmJogo[jogador][indicePeca] == 1) {
        printf("Peça está em jogo.\n");
        int casaAtual = -1;
        for (int i = 0; i < 52; i++) {
            if (posicaoCasaX[i] == posicaoPecaX[jogador][indicePeca] && posicaoCasaY[i] == posicaoPecaY[jogador][indicePeca]) {
                casaAtual = i;
                break;
            }
        }

        printf("casaAtual: %d\n", casaAtual);
        if (casaAtual != -1) {
            int novaCasa = (casaAtual + passos) % 52;
            printf("novaCasa: %d\n", novaCasa);

            // Verifica se passou pela casa inicial
            int passouInicial = 0;
            switch (jogador) {
                case 0: passouInicial = (casaAtual < 41 && novaCasa >= 41) || novaCasa == 41; break;
                case 1: passouInicial = (casaAtual < 2 && novaCasa >= 2) || novaCasa == 2; break;
                case 2: passouInicial = (casaAtual < 28 && novaCasa >= 28) || novaCasa == 28; break;
                case 3: passouInicial = (casaAtual < 15 && novaCasa >= 15) || novaCasa == 15; break;
            }
            printf("passouInicial: %d\n", passouInicial);
            if (passouInicial) {
                passagensIniciais[jogador][indicePeca]++;
                printf("passagensIniciais[%d][%d]: %d\n", jogador, indicePeca, passagensIniciais[jogador][indicePeca]);

                if (passagensIniciais[jogador][indicePeca] == 1) {
                    printf("Peça vai para a casa final inicial.\n");
                    pecaEmJogo[jogador][indicePeca] = 2;
                    int casaFinal;
                    switch (jogador) {
                        case 0: casaFinal = casasFinaisVerde[0]; break;
                        case 1: casaFinal = casasFinaisVermelho[0]; break;
                        case 2: casaFinal = casasFinaisAmarelo[0]; break;
                        case 3: casaFinal = casasFinaisAzul[0]; break;
                        default: return; // Jogador inválido
                    }
                    posicaoPecaX[jogador][indicePeca] = posicaoCasaX[casaFinal];
                    posicaoPecaY[jogador][indicePeca] = posicaoCasaY[casaFinal];
                    return;
                }
            }

            int capturada = 0;
            for (int j = 0; j < NUM_JOGADORES; j++) {
                if (j != jogador) {
                    for (int k = 0; k < 4; k++) {
                        if (pecaEmJogo[j][k] == 1 && posicaoPecaX[j][k] == posicaoCasaX[novaCasa] && posicaoPecaY[j][k] == posicaoCasaY[novaCasa]) {
                            printf("Peça do jogador %d capturada!\n", j);
                            pecaEmJogo[j][k] = 0;
                            posicaoPecaX[j][k] = posicaoInicialX[j][k];
                            posicaoPecaY[j][k] = posicaoInicialY[j][k];
                            passagensIniciais[j][k] = 0;
                            capturada = 1;
                            break;
                        }
                    }
                    if (capturada) break;
                }
            }

            if (passagensIniciais[jogador][indicePeca] < 1) {
                posicaoPecaX[jogador][indicePeca] = posicaoCasaX[novaCasa];
                posicaoPecaY[jogador][indicePeca] = posicaoCasaY[novaCasa];
            }

            if (EhCasaBomba(novaCasa)) {
                printf("Peça caiu em uma casa bomba!\n");
                novaCasa = (novaCasa + 50) % 52;
                posicaoPecaX[jogador][indicePeca] = posicaoCasaX[novaCasa];
                posicaoPecaY[jogador][indicePeca] = posicaoCasaY[novaCasa];
            }

            // Verifica se a nova posição da peça está dentro dos limites do tabuleiro
            if (novaCasa < 0)
                novaCasa += 52;

            posicaoPecaX[jogador][indicePeca] = posicaoCasaX[novaCasa];
            posicaoPecaY[jogador][indicePeca] = posicaoCasaY[novaCasa];
        }
    } else if (pecaEmJogo[jogador][indicePeca] == 2) {
        printf("Peça do jogador %d está nas casas finais\n", jogador);
        int casaFinalAtual = -1;
        int* casasFinais;
        switch (jogador) {
            case 0: casasFinais = casasFinaisVerde; break;
            case 1: casasFinais = casasFinaisVermelho; break;
            case 2: casasFinais = casasFinaisAmarelo; break;
            case 3: casasFinais = casasFinaisAzul; break;
            default: return; // Jogador inválido
        }
        for (int i = 0; i < NUM_CASAS_FINAIS; i++) {
            if (posicaoCasaX[casasFinais[i]] == posicaoPecaX[jogador][indicePeca] && posicaoCasaY[casasFinais[i]] == posicaoPecaY[jogador][indicePeca]) {
                casaFinalAtual = i;
                break;
            }
        }

        printf("casaFinalAtual: %d\n", casaFinalAtual);
        if (casaFinalAtual != -1) {
            int novaCasaFinal = casaFinalAtual + 1;
            printf("novaCasaFinal: %d\n", novaCasaFinal);
            if (novaCasaFinal < NUM_CASAS_FINAIS) {
                posicaoPecaX[jogador][indicePeca] = posicaoCasaX[casasFinais[novaCasaFinal]];
                posicaoPecaY[jogador][indicePeca] = posicaoCasaY[casasFinais[novaCasaFinal]];
            } else if (novaCasaFinal == NUM_CASAS_FINAIS) {
                // Peça chegou na última casa final
                printf("Peça do jogador %d chegou na última casa final!\n", jogador);
                pecaEmJogo[jogador][indicePeca] = 3; // Estado para peça na última casa final
                posicaoPecaX[jogador][indicePeca] = posicaoCasaX[casasFinais[NUM_CASAS_FINAIS - 1]];
                posicaoPecaY[jogador][indicePeca] = posicaoCasaY[casasFinais[NUM_CASAS_FINAIS - 1]];
            }
        }
    } else if (pecaEmJogo[jogador][indicePeca] == 3) {
        // Verifica se o jogador tirou 6 para ganhar
        if (dado == 6) {
                        printf("Jogador %d ganha com a peça %d!\n", jogador, indicePeca);
            // Move a peça para o canto da tela para indicar que ela ganhou
            posicaoPecaX[jogador][indicePeca] = -100; // Valor hipotético para mover para o canto
            posicaoPecaY[jogador][indicePeca] = -100; // Valor hipotético para mover para o canto
        }
    }
}




void Numeronascasa() {
    int numeros[] = {
        1, 2, 3,
        52, 68, 4,
        51, 69, 5,
        50, 70, 6,
        49, 71, 7,
        48, 72, 8,


        34, 57, 22, 
        33, 56, 23, 
        32, 55, 24, 
        31, 54, 25,
        30, 53, 26, 
        29, 28, 27, 

        42, 41, 40, 
        43, 58, 39,
        44, 59, 38, 
        45, 60, 37, 
        46, 61, 36, 
        47, 62, 35,


        9, 67, 21,
        10, 66, 20,
        11, 65, 19,
        12, 64, 18,
        13, 63, 17,
        14, 15, 16,
    };

    int indice = 0;

for (int tabuleiro = 0; tabuleiro < 4; tabuleiro++) {
    for (int linha = 0; linha < 6; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            int posX;
            int posY;
            if (tabuleiro == 2 || tabuleiro == 3) {
                posX = posicaoXPrimeiraCasa[tabuleiro] + linha * TAMANHO_CASA;
                posY = posicaoYPrimeiraCasa[tabuleiro] + coluna * TAMANHO_CASA;
            } else {
                posX = posicaoXPrimeiraCasa[tabuleiro] + coluna * TAMANHO_CASA;
                posY = posicaoYPrimeiraCasa[tabuleiro] + linha * TAMANHO_CASA;
            }

            posicaoCasaX[numeros[indice] - 1] = posX;
            posicaoCasaY[numeros[indice] - 1] = posY;

            DrawText(TextFormat("%02d", numeros[indice]), posX, posY, 20, BLACK);
            indice++;
            }
        }
    }
}


int main() {
    InitWindow(0, 0, "Jogo de Ludo");
    InicializarJogadores();

    for (int i = 0; i < NUM_PECAS; i++) {
        pecasAmarelas[i] = LoadTexture("pcamarela.png");
        pecasVerdes[i] = LoadTexture("pcverde.png");
        pecasVermelhas[i] = LoadTexture("pcvermelha.png");
        pecasAzuis[i] = LoadTexture("pcazul.png");
    }

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_K)) {
            RolarDado();
        }

        if (pecaSelecionada != -1 && dadorolado) {
            MoverPeca(jogadorAtual, pecaSelecionada, dado, dado);
            PassarTurno();
            resetarDado();
        }

        if (IsKeyPressed(KEY_ONE)) pecaSelecionada = 0;
        if (IsKeyPressed(KEY_TWO)) pecaSelecionada = 1;
        if (IsKeyPressed(KEY_THREE)) pecaSelecionada = 2;
        if (IsKeyPressed(KEY_FOUR)) pecaSelecionada = 3;

        BeginDrawing();
        ClearBackground(RAYWHITE);


for (int tabuleiro = 0; tabuleiro < 4; tabuleiro++) {
    for (int linha = 0; linha < 6; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            int posX;
            int posY;
            if (tabuleiro == 2 || tabuleiro == 3) {
                posX = posicaoXPrimeiraCasa[tabuleiro] + linha * TAMANHO_CASA;
                posY = posicaoYPrimeiraCasa[tabuleiro] + coluna * TAMANHO_CASA;
            } else {
                posX = posicaoXPrimeiraCasa[tabuleiro] + coluna * TAMANHO_CASA;
                posY = posicaoYPrimeiraCasa[tabuleiro] + linha * TAMANHO_CASA;
            }

            DrawRectangle(posX, posY, TAMANHO_CASA, TAMANHO_CASA, LIGHTGRAY);
            DrawRectangleLinesEx((Rectangle){ posX, posY, TAMANHO_CASA, TAMANHO_CASA }, 1, DARKGRAY);
        }
    }
}


        Numeronascasa();

for (int i = 0; i < NUM_JOGADORES; i++) {
    for (int j = 0; j < NUM_PECAS; j++) {
        if (pecaEmJogo[i][j] == 1 || pecaEmJogo[i][j] == 2 || pecaEmJogo[i][j] == 3) {
            Texture2D textura;
            if (i == 0) {
                textura = pecasVerdes[j];
            } else if (i == 1) {
                textura = pecasVermelhas[j];
            } else if (i == 2) {
                textura = pecasAmarelas[j];
            } else {
                textura = pecasAzuis[j];
            }
            DrawTexture(textura, posicaoPecaX[i][j], posicaoPecaY[i][j], WHITE);
        } else {
            Texture2D textura;
            if (i == 0) {
                textura = pecasVerdes[j];
            } else if (i == 1) {
                textura = pecasVermelhas[j];
            } else if (i == 2) {
                textura = pecasAmarelas[j];
            } else {
                textura = pecasAzuis[j];
            }
            DrawTexture(textura, baseX[i][j], baseY[i][j], WHITE);
        }
    }
}


        DrawText(TextFormat("Resultado do dado (K): %i", dado), 10, 10, 20, BLACK);
        DrawText(TextFormat("Jogador atual: %s", nomesJogadores[jogadorAtual]), 10, 40, 20, coresJogadores[jogadorAtual]);
        DrawText("Selecione uma peça (1-4):", 10, 70, 20, BLACK);
        if (pecaSelecionada != -1) {
            DrawText(TextFormat("Peça selecionada: %i", pecaSelecionada + 1), 10, 100, 20, BLACK);
        }

        EndDrawing();
    }

    for (int i = 0; i < NUM_PECAS; i++) {
        UnloadTexture(pecasAmarelas[i]);
        UnloadTexture(pecasVerdes[i]);
        UnloadTexture(pecasVermelhas[i]);
        UnloadTexture(pecasAzuis[i]);
    }

    CloseWindow();
    return 0;
}

