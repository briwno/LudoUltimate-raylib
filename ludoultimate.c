
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h> 
#include <math.h>
// Variáveis globais
bool mostrar4Players = false;
bool mostrar3Players = false;
bool mostrar2Players = false; // Variável para controlar se a opção "2 Players" está sendo mostrada
bool mostrar1Player = false; // Variável para controlar se a opção "1 Player" está sendo mostrada
bool mostrarinicio = true; // Variável para controlar se a opção "
bool mostrarJogar = false; // Variável para controlar se a opção "Jogar" está sendo mostrada
bool mostrarJogo = false;
bool mostrarRanking = false; // Variável para controlar se a opção "Ranking" está sendo mostrada
bool mostrarRegras = false; // Variável para controlar se a opção "Regras" está sendo mostrada
bool mostrarSair = false; // Variável para controlar se a opção "Fechar" está sendo mostrada
bool mostrarSairJogo = false; // Variável para controlar se a op
bool pause = false; // Variável para controlar o estado de pausa da música
Music musicamenu; // Variável para armazenar a música do menu
Sound select;
Texture2D soundOnTexture; // Textura do botão de som ligado
Texture2D soundOffTexture; // Textura do botão de som desligado
Texture2D voltarTexture; // Textura do botão "voltar"
Texture2D prontoTexture; // Textura do botão "pronto"

Texture2D jogarButtonTexture; // Textura do botão jogar
Texture2D regrasButtonTexture; // Textura do botão "regras
Texture2D rankButtonTexture;
Texture2D sairButtonTexture;

Texture2D instaButtonTexture; // Textura do botão instagram

Rectangle voltarButtonRec; // Área de colisão do botão "voltar"
Rectangle soundButtonRec; // Área de colisão do botão de som
Rectangle prontoButtonRec; // Area de colisão do botão "pronto"
Rectangle jogarButtonRec; // Area de colisão do botão de jogar
Rectangle regrasButtonRec;
Rectangle rankButtonRec; // Area de colisão do botão
Rectangle sairButtonRec;
Rectangle instaButtonRec; // Area de colisão do botão de instagram

Rectangle dadoButtonRec; // Area de colisão do botão

//texbox 4players
Rectangle textBox = { 278, 584, 232, 84}; //
Rectangle textBox2 = { 620, 930, 232, 84};
Rectangle textBox3 = { 1097, 930, 232, 84};
Rectangle textBox4 = { 1409, 584, 232, 84};
//textbox 3players
Rectangle textBoxppp = {372, 636, 232, 84};
Rectangle textBoxppp2 = {803, 982, 232, 84};
Rectangle textBoxppp3 = {1297, 636, 232, 84};
bool mouseOnTextppp = false;
bool mouseOnTextppp2 = false;
bool mouseOnTextppp3 = false;
//textBox 2players
Rectangle textBoxpp = { 404, 716, 232, 84};
Rectangle textBoxpp2 = {1275, 716, 232, 84};
bool mouseOnTextpp = false;
bool mouseOnTextpp2 = false;

bool mouseOnText = false;
bool mouseOnText2 = false;
bool mouseOnText3 = false;
bool mouseOnText4 = false;

bool somselect = false; 

    float shakeOffsetJogar = 0;
    float shakeOffsetRegras = 0;
    float shakeOffsetRank = 0;
    float shakeOffsetSair = 0;

//varivel do nome
char name[6] = "\0";
char name2[6] = "\0";    
char name3[6] = "\0";    
char name4[6] = "\0";

int jogadorVencedor = -1;
//variavel da contagem de letras   
int letterCount = 0;
int letterCount2 = 0;
int letterCount3 = 0;
int letterCount4 = 0;
int framesCounter = 0;


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
const char* nomesJogadores[NUM_JOGADORES] = {name4, name, name3, name2};

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



int casavencedoraX[NUM_JOGADORES][NUM_PECAS] = {
        {63, 63, 63, 63},
        {1260, 1260, 1260, 1260},
        {63, 63, 63, 63},
        {1260, 1260, 1260, 1260}
    };
int casavencedoraY[NUM_JOGADORES][NUM_PECAS] = {
        {108, 157, 206, 257},
        {106, 156, 206, 256},
        {773, 823, 873, 923},
        {776, 823, 873, 923}
    };

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
            pecaEmJogo[jogador][indicePeca] = 4; // Estado para peça na última casa final



        }

    }else if (pecaEmJogo[jogador][indicePeca] == 4) {
            posicaoPecaX[jogador][indicePeca] = casavencedoraX[jogador][indicePeca]; 
            posicaoPecaY[jogador][indicePeca] = casavencedoraY[jogador][indicePeca];
            
            printf("Peça %d do jogador %d esta na casa vencedora!\n",indicePeca, jogador);

    }
}

void AdicionaraoRank(const char *jogador){
    FILE *arq;
    arq = fopen("ranking.txt", "a");
    if(arq!= NULL){
        fprintf(arq, "%s 3 Pontos\n", jogador);
        fclose(arq);
    }else{
        printf("Erro ao abrir o arquivo ranking.txt\n");
    }
}
void DesenharRank(){
    FILE *arq;
    char linha[100]; // Buffer para armazenar cada linha lida
    int y = 242; //altura da linha
    arq = fopen("ranking.txt", "r"); // Abre o arquivo em modo de leitura
    if(arq!= NULL){
        while (!feof(arq)){
            //ler a linha
while (fgets(linha, sizeof(linha), arq) != NULL) {
            // Desenha a linha lida
            DrawText(linha, 518, y, 20, WHITE);
            y += 30; // Move a posição y para a próxima linha
        }
        }
        fclose(arq);
    }else{
        printf("Erro ao abrir o arquivo ranking.txt\n");
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
    InicializarJogadores();
    Image jogo = LoadImage("logoprograma.png"); // Carrega a imagem do logotipo do programa
    // Inicializa a janela
    InitWindow(1920, 1080, "Ludo Ultimate");  // Inicializa a janela com tamanho e título especificados
    SetWindowIcon(jogo); // Define o ícone da janela
    SetTargetFPS(60); // Define a taxa de quadros por segundo
    MaximizeWindow(); // Maxima a tela, mantendo emm janela
    InitAudioDevice(); // Inicializa o dispositivo de áudio
    // Carrega a música
    musicamenu = LoadMusicStream("sons/musicamenu.wav"); // Carrega a música do menu
    SetMusicVolume(musicamenu, 0.5); // Define o volume da música
    // Toca a música em loop
    PlayMusicStream(musicamenu); // Toca a música do menu em loop

    // Carrega o som de seleção
    select = LoadSound("sons/selectsom.wav"); // Carrega o som de seleção

    // Carrega as texturas dos botões de som
    soundOnTexture = LoadTexture("sound_on.png"); // Carrega a textura do botão de som ligado
    soundOffTexture = LoadTexture("sound_off.png"); // Carrega a textura do botão de som desligado

    //textura botao do menu
    jogarButtonTexture = LoadTexture("botaojogar.png"); // Carrega a textura do botão "jogar"
    regrasButtonTexture = LoadTexture("botaoregras.png"); // Carrega a textura do botão "regras"
    rankButtonTexture = LoadTexture("botaorank.png"); // Carrega a textura do botão "ranking"
    sairButtonTexture = LoadTexture("botaofechar.png"); // Carrega a textura do botão "fechar"

    instaButtonTexture = LoadTexture("insta.png"); // Carrega a textura

    instaButtonRec = (Rectangle){ 1800, 670, (float)instaButtonTexture.width, (float)instaButtonTexture.height }; // Define a área de colisão do botão "insta"


    jogarButtonRec = (Rectangle){ 785, 280, (float)jogarButtonTexture.width, (float)jogarButtonTexture.height }; // Define a área de colisão do botão "jogar"
    regrasButtonRec = (Rectangle){ 785, 360, (float)regrasButtonTexture.width, (float)regrasButtonTexture.height }; // Define a área de colisão do botão "regras"
    rankButtonRec = (Rectangle){ 785, 440, (float)rankButtonTexture.width, (float)rankButtonTexture.height }; // Define a área de colisão do botão "ranking"
    sairButtonRec = (Rectangle){ 810, 520, (float)sairButtonTexture.width, (float)sairButtonTexture.height }; // Define a área de colisão do botão "fechar"

    

    voltarTexture = LoadTexture("voltar.png"); // Carrega a textura do botão "voltar"

    prontoTexture = LoadTexture("botaopronto.png"); // Carrega a text

    voltarButtonRec = (Rectangle){ 1790, 20, (float)voltarTexture.width, (float)voltarTexture.height }; // Define a área de colisão do botão "voltar"

    // Define a posição e o tamanho do botão de som
    soundButtonRec = (Rectangle){ 1750, 20, (float)soundOnTexture.width, (float)soundOnTexture.height };

    prontoButtonRec = (Rectangle){ 1500, 937, (float)prontoTexture.width, (float)prontoTexture.height };

        // Carrega as imagens dos dados
        Texture2D dado0texture = LoadTexture("dado0.png"); 
        Texture2D dado1texture = LoadTexture("dado1.png");
        Texture2D dado2texture = LoadTexture("dado2.png");
        Texture2D dado3texture = LoadTexture("dado3.png");
        Texture2D dado4texture = LoadTexture("dado4.png");
        Texture2D dado5texture = LoadTexture("dado5.png");
        Texture2D dado6texture = LoadTexture("dado6.png");
       

    // Fundo
    Image bgImage = LoadImage("fundojogo.png"); // Carrega a imagem de fundo do jogo
    Texture2D bgTexture = LoadTextureFromImage(bgImage); // Converte a imagem de fundo em textura
    UnloadImage(bgImage); // Descarrega a imagem original
    
    Image logo = LoadImage("logojogo.png"); // Carrega a imagem do logotipo do jogo
    Texture2D Texture = LoadTextureFromImage(logo); // Converte a imagem do logotipo em textura
    UnloadImage(logo); // Descarrega a imagem original
    
    Image regras = LoadImage("telaregras.png"); // Carrega a imagem da tela de regras
    Texture2D regrasTexture = LoadTextureFromImage(regras); // Converte a imagem da tela de regras em textura
    UnloadImage(regras); // Descarrega a imagem original

    Image ranking = LoadImage("telaranking.png"); // Carrega a imagem da tela de ranking
    Texture2D rankingTexture = LoadTextureFromImage(ranking); // Converte a imagem da tela de ranking em textura
    UnloadImage(ranking); // Descarrega a imagem original

    Image sair = LoadImage("sair.png"); // Carrega a imagem da opção de sair
    Texture2D sairTexture = LoadTextureFromImage(sair); // Converte a imagem da opção de sair em textura
    UnloadImage(sair); // Descarrega a imagem original

    Image vitoria = LoadImage("vitoriatela.png"); // Carrega
    Texture2D vitoriaTexture = LoadTextureFromImage(vitoria); // Converte a imagem da tela de vitoria em textura
    UnloadImage(vitoria); // Descarrega a imagem original

    Image botaosim = LoadImage("botaosim.png"); // Carrega a imagem do botão "sim"
    Texture2D botaosimTexture = LoadTextureFromImage(botaosim); // Converte a imagem do botão "sim" em textura
    UnloadImage(botaosim); // Descarrega a imagem original
    
    Image botaonao = LoadImage("botaonao.png"); // Carrega a imagem do botão "não"
    Texture2D botaonaoTexture = LoadTextureFromImage(botaonao); // Converte a imagem do botão "não" em textura
    UnloadImage(botaonao); // Descarrega a imagem original

    Image escolha = LoadImage("telaescolha.png"); // Carrega a imagem da tela de escolha
    Texture2D escolhaTexture = LoadTextureFromImage(escolha); // Converte a imagem da tela de escolha em textura
    UnloadImage(escolha); // Descarrega a imagem original

    Image tela4players = LoadImage("tela4players.png"); //
    Texture2D tela4playersTexture = LoadTextureFromImage(tela4players); // Converte a imagem da tela de 4 jogadores em textura
    UnloadImage(tela4players); // Descarrega a imagem original

    Image tela2players = LoadImage("tela2players.png"); //
    Texture2D tela2playersTexture = LoadTextureFromImage(tela2players); // Converte
    UnloadImage(tela2players);

    Image tela3players = LoadImage("tela3players.png");
    Texture2D tela3playersTexture = LoadTextureFromImage(tela3players);
    UnloadImage(tela3players);

    Image tabuleiro = LoadImage("telajogo.png");
    Texture2D jogoTexture = LoadTextureFromImage(tabuleiro); // Converte a imagem da tela de jogo em textura
    UnloadImage(tabuleiro); // Descarrega a imagem original

    Image pronto = LoadImage("botaopronto.png");
    Texture2D prontoTexture = LoadTextureFromImage(pronto); // Converte a imagem do botão "pronto" em textura
    UnloadImage(pronto); // Descarrega a imagem original

        for (int i = 0; i < NUM_PECAS; i++) {
        pecasAmarelas[i] = LoadTexture("pcamarela.png");
        pecasVerdes[i] = LoadTexture("pcverde.png");
        pecasVermelhas[i] = LoadTexture("pcvermelha.png");
        pecasAzuis[i] = LoadTexture("pcazul.png");
    }




    // Laço principal do menu principal
    while (!WindowShouldClose()) {
        UpdateMusicStream(musicamenu); // Atualiza o estado da música do menu 
        if(mostrarinicio){
        


 // Aplicar efeito de chacoalhar se o mouse estiver sobre os botões


                if(!somselect){
                    PlaySound(select);
                }
         if(CheckCollisionPointRec(GetMousePosition(), jogarButtonRec )){
            somselect = true; //
            shakeOffsetJogar = sin(GetTime() * 10) * 5;
         }
         else if(CheckCollisionPointRec(GetMousePosition(), regrasButtonRec )){
            somselect = true; //
            shakeOffsetRegras = sin(GetTime() * 10) * 5;
         }
         else if(CheckCollisionPointRec(GetMousePosition(), rankButtonRec )){
            somselect = true; //
            shakeOffsetRank = sin(GetTime() * 10) * 5;
         }
        else if(CheckCollisionPointRec(GetMousePosition(), sairButtonRec )){
            somselect = true; //
            shakeOffsetSair = sin(GetTime() * 10) * 5;
         }
         else{
            somselect = false;
            shakeOffsetJogar = 0;
            shakeOffsetRegras = 0;
            shakeOffsetRank = 0;
            shakeOffsetSair = 0;
         }




        // Limpa o fundo com uma cor
        
        ClearBackground(RAYWHITE); // Limpa o fundo da janela com a cor branca



        DrawTexture(bgTexture, 0, 0, WHITE); // Desenha a textura de fundo na tela
        DrawTexture(Texture, 470, 50, WHITE); // Desenha o logotipo do jogo na tela
        
        // Desenha o botão de som
        if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
        else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando
        
        // Desenha os créditos do jogo
        DrawText("Um projeto por Rivals Forge", 1500, 410, 20, WHITE); // Desenha os créditos do desenvolvedor
        DrawText("Pensado e Desenvolvido por \nBruno Alves e Nicolas Keyno", 1500, 430, 20, WHITE); // Desenha os nomes dos desenvolvedores
        DrawText("LUDO ULTIMATE 2024", 1500, 470, 20, BLUE); // Desenha o título do jogo
        
        DrawTexture(instaButtonTexture, (int)instaButtonRec.x, (int)instaButtonRec.y, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), instaButtonRec)){
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            OpenURL("https://www.instagram.com/ludoultimate/");
            printf("Aberto Link do instagram");
        }
    }

        // Desenhar botões com efeito de chacoalhar
        DrawTextureEx(jogarButtonTexture, (Vector2){ jogarButtonRec.x + shakeOffsetJogar, jogarButtonRec.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(regrasButtonTexture, (Vector2){ regrasButtonRec.x + shakeOffsetRegras, regrasButtonRec.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(rankButtonTexture, (Vector2){ rankButtonRec.x + shakeOffsetRank, rankButtonRec.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(sairButtonTexture, (Vector2){ sairButtonRec.x + shakeOffsetSair, sairButtonRec.y }, 0.0f, 1.0f, WHITE);
}
        
        // Abrir tela de regras
        if (CheckCollisionPointRec(GetMousePosition(), regrasButtonRec)) { // Se a posição do mouse estiver sobre a área da opção de regras
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                mostrarRegras = true; // Define a variável para mostrar as regras como true
                mostrarinicio = false; // Define a variável para mostrar
            }
        }

        // Se a variável para mostrar as regras estiver true, desenha a tela de regras
        if (mostrarRegras) { // Se a variável para mostrar as regras estiver true
            // Carrega e desenha a imagem das regras
            DrawTexture(regrasTexture, 0, 0, WHITE); // Desenha a tela de regras na tela
            if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
            else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando

            DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"
            
            // Se o botão "voltar" for pressionado, define a variável para mostrar as regras como false
            if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área do botão "voltar"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrarRegras = false; // Define a variável para mostrar as regras como false
                    mostrarinicio = true; // Define a variável para mostrar o menu principal como true
                }
            }
        }

        // Abrir tela de ranking
        if (CheckCollisionPointRec(GetMousePosition(), rankButtonRec)) { // Se a posição do mouse estiver sobre a área da opção de ranking
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                mostrarRanking = true; // Define a variável para mostrar o ranking como true
                mostrarinicio = false; // Define a variável para mostrar o menu principal como false
            }
        }

        // Se a variável para mostrar o ranking estiver true, desenha a tela de ranking
        if (mostrarRanking) { // Se a variável para mostrar o ranking estiver true
            DrawTexture(rankingTexture, 0, 0, WHITE); // Desenha a textura do ranking na tela

            //exibir rank
            DesenharRank();


            if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
            else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando

            DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"
            // Se o botão "voltar" for pressionado, define a variável para mostrar o ranking como false
            if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área do botão "voltar"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrarRanking = false; // Define a variável para mostrar o ranking como false
                    mostrarinicio = true; // Define a variável para mostrar o menu principal como true
                }
            }
        }

        // Mostrar opção de sair
        if (CheckCollisionPointRec(GetMousePosition(), sairButtonRec)) { // Se a posição do mouse estiver sobre a área da opção de sair
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                mostrarSair = true; // Define a variável para mostrar a opção de sair como true
            }
        }

        // Se a variável para mostrar a opção de sair estiver true, desenha a tela de sair
        if (mostrarSair) { // Se a variável para mostrar a opção de sair estiver true
            DrawTexture(sairTexture, 0, 0, WHITE); // Desenha a textura da opção de sair na tela
            DrawTexture(botaosimTexture, 540, 700, WHITE); // Desenha o botão "sim"
            DrawTexture(botaonaoTexture, 1100, 700, WHITE); // Desenha o botão "não"

            // Verifica se o botão "sim" ou "não" foi pressionado
            // Se o botão "sim" for pressionado, fecha a janela
            if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){540, 700, 200, 100})) { // Se a posição do mouse estiver sobre a área do botão "sim"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    CloseWindow(); // Fecha a janela
                }
            }
            // Se o botão "não" for pressionado, define a variável para mostrar a opção de sair como false
            if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){1100, 700, 200, 100})) { // Se a posição do mouse estiver sobre a área do botão "não"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrarSair = false; // Define a variável para mostrar a opção de sair como false
                }
            }

            // Desenha o texto "SIM" e "NÃO"
            DrawText("SIM", 625, 720, 60, RAYWHITE); // Desenha o texto "SIM"
            DrawText("NÃO", 1185, 720, 60, RAYWHITE); // Desenha o texto "NÃO"

            // Se o mouse estiver sobre o botão "sim" ou "não", muda a cor do texto para verde ou vermelho, respectivamente
            if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){540, 700, 200, 100})) { // Se a posição do mouse estiver sobre a área do botão "sim"
                DrawText("SIM", 625, 720, 60, GREEN); // Desenha o texto "SIM" em verde
            }
            if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){1100, 700, 200, 100})) { // Se a posição do mouse estiver sobre a área do botão "não"
                DrawText("NÃO", 1185, 720, 60, RED); // Desenha o texto "NÃO" em vermelho
            }
        }

        // Escolher jogar e exibir tela de escolha
        if (CheckCollisionPointRec(GetMousePosition(), jogarButtonRec)) { // Se a posição do mouse estiver sobre a área da opção "Jogar"
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                mostrarJogar = true; // Define a variável para mostrar a tela de escolha como true
                mostrarinicio = false; // Define a variável para mostrar o menu principal como false
            }
        }

        // Se a variável para mostrar a tela de escolha estiver true, desenha a tela de escolha
        if (mostrarJogar) { // Se a variável para mostrar a tela de escolha estiver true
            DrawTexture(escolhaTexture, 0, 0, WHITE); // Desenha a tela de escolha na tela
            if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
            else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando
            DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"
            //desenha 3 retangulos para escolha
            Rectangle escolha1 = { 235, 530, 350, 240 };
            DrawRectangleLinesEx(escolha1, 5, BLANK);
            Rectangle escolha2 = { 785, 530, 350, 240 };
            DrawRectangleLinesEx(escolha2, 5, BLANK);
            Rectangle escolha3 = { 1335, 530, 350, 240 };
            DrawRectangleLinesEx(escolha3, 5, BLANK);

            // Se o botão "voltar" for pressionado, define a variável para mostrar a tela de escolha como false
            if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área do botão "voltar"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrarJogar = false; // Define a variável para mostrar a tela de escolha como false
                    mostrarinicio = true; // Define a variável para mostrar o menu principal como true
                }
            }


            if (CheckCollisionPointRec(GetMousePosition(), escolha1)) {
                //deixa o retangulo vermelho
                DrawRectangleLinesEx(escolha1, 5, RED);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    mostrar2Players = true;
                    mostrarJogar = false;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), escolha2)) {
                //deixa o retangulo vermelho
                DrawRectangleLinesEx(escolha2, 5, RED);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    mostrar3Players = true;
                    mostrarJogar = false;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), escolha3)) {
                //deixa o retangulo vermelho
                DrawRectangleLinesEx(escolha3, 5, RED);
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        mostrar4Players = true;
                        mostrarJogar = false;
                    }
            }

        }


        if (mouseOnText){
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < 5))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else if (mouseOnText2){
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount2 < 5))
                {
                    name2[letterCount2] = (char)key;
                    name2[letterCount2+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount2++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount2--;
                if (letterCount2 < 0) letterCount2 = 0;
                name2[letterCount2] = '\0';
            }

        }
        else if (mouseOnText3){
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount3 < 5))
                {
                    name3[letterCount3] = (char)key;
                    name3[letterCount3+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount3++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount3--;
                if (letterCount3 < 0) letterCount3 = 0;
                name3[letterCount3] = '\0';
            }

        }
        else if (mouseOnText4){
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount4 < 5))
                {
                    name4[letterCount4] = (char)key;
                    name4[letterCount4+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount4++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount4--;
                if (letterCount4 < 0) letterCount4 = 0;
                name4[letterCount4] = '\0';
            }

        }

            else if (mouseOnTextpp){
                // Set the window's cursor to the I-Beam
                SetMouseCursor(MOUSE_CURSOR_IBEAM);

                int key = GetCharPressed();
                while (key > 0){
                    if ((key >= 32) && (key <= 125) && (letterCount < 5))
                    {
                        name[letterCount] = (char)key;
                        name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                        letterCount++;
                    }

                    key = GetCharPressed();  // Check next character in the queue
                }
                if (IsKeyPressed(KEY_BACKSPACE)){
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
         }

             else if (mouseOnTextpp2){
                // Set the window's cursor to the I-Beam
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                while (key > 0){
                    if ((key >= 32) && (key <= 125) && (letterCount4 < 5))
                    {
                        name4[letterCount4] = (char)key;
                        name4[letterCount4+1] = '\0'; // Add null terminator at the end of the string.
                        letterCount4++;
                    }
                    key = GetCharPressed();  // Check next character in the queue
                }if (IsKeyPressed(KEY_BACKSPACE)){
                    letterCount4--;
                    if (letterCount4 < 0) letterCount4 = 0;
                    name4[letterCount4] = '\0';
                }
             }

             else if(mouseOnTextppp){
                // Set the window's cursor to the I-Beam
                SetMouseCursor(MOUSE_CURSOR_IBEAM);

                int key = GetCharPressed();
                while (key > 0){
                    if ((key >= 32) && (key <= 125) && (letterCount < 5))
                    {
                        name[letterCount] = (char)key;
                        name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                        letterCount++;
                    }

                    key = GetCharPressed();  // Check next character in the queue
                }
                if (IsKeyPressed(KEY_BACKSPACE)){
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
             }

            else if (mouseOnTextppp2){
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                while (key > 0){
                    if ((key >= 32) && (key <= 125) && (letterCount3 < 5))
                    {
                        name3[letterCount3] = (char)key;
                        name3[letterCount3+1] = '\0'; // Add null terminator at the end of the string.
                        letterCount3++;
                    }
                    key = GetCharPressed();  // Check next character in the queue
                }if (IsKeyPressed(KEY_BACKSPACE)){
                    letterCount3--;
                    if (letterCount3 < 0) letterCount3 = 0;
                    name3[letterCount3] = '\0';
                }
            }

            else if (mouseOnTextppp3){
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                while (key > 0){
                    if ((key >= 32) && (key <= 125) && (letterCount4< 5))
                    {
                        name4[letterCount4] = (char)key;
                        name4[letterCount4+1] = '\0'; // Add null terminator at the end of the string.
                        letterCount4++;
                    }
                    key = GetCharPressed();  // Check next character in the queue
                }if (IsKeyPressed(KEY_BACKSPACE)){
                    letterCount4--;
                    if (letterCount4 < 0) letterCount4 = 0;
                    name4[letterCount4] = '\0';
                }
            }
                    else if (CheckCollisionPointRec(GetMousePosition(), soundButtonRec)) { // Se a posição do mouse estiver sobre a área do botão de som
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                // Alterna entre ligar e desligar o som da música
                pause = !pause; // Inverte o estado de pausa da música
                if (pause) PauseMusicStream(musicamenu); // Pausa a música se estiver tocando
                else ResumeMusicStream(musicamenu); // Resume a música se estiver pausada
            }
        }

        else if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }

        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if(mostrar2Players){
                mostrar4Players = false; // Define a variável para mostrar
                mostrar3Players = false; // Define a variável para mostrar

                

                DrawTexture(tela2playersTexture, 0, 0, WHITE);
                if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
                else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando

                DrawRectangleRec(textBoxpp, LIGHTGRAY);
                DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBoxpp.x - 20, (int)textBoxpp.y + 100, 20, RED);
                DrawRectangleRec(textBoxpp2, LIGHTGRAY);
                DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBoxpp2.x - 20, (int)textBoxpp2.y + 100, 20, GREEN);
        if (CheckCollisionPointRec(GetMousePosition(), textBoxpp)) mouseOnTextpp = true;
        else mouseOnTextpp = false;
        if (CheckCollisionPointRec(GetMousePosition(), textBoxpp2)) mouseOnTextpp2 = true;
        else mouseOnTextpp2 = false;
                if (mouseOnTextpp) DrawRectangleLines((int)textBoxpp.x, (int)textBoxpp.y, (int)textBoxpp.width, (int)textBoxpp.height, RED);
                if (mouseOnTextpp2) DrawRectangleLines((int)textBoxpp2.x, (int)textBoxpp2.y, (int)textBoxpp2.width, (int)textBoxpp2.height, GREEN);

                DrawText(name, (int)textBoxpp.x + 50, (int)textBoxpp.y + 36, 40, MAROON);
                DrawText(name4, (int)textBoxpp2.x + 50, (int)textBoxpp2.y + 36, 40, GREEN);

            if (mouseOnTextpp){
                if (letterCount < 5)
                {
                    // Draw blinking underscore char
                   DrawText("_", (int)textBoxpp.x + 50 + MeasureText(name, 40), (int)textBoxpp.y + 40, 40, MAROON);
                }

            } 
            if (mouseOnTextpp2){
                if (letterCount2 < 5)
                {
                    // Draw blinking underscore char
                    DrawText("_", (int)textBoxpp2.x + 50 + MeasureText(name4, 40), (int)textBoxpp2.y + 40, 40, GREEN);
                }
            }
                            //botao pronto
                DrawTexture(prontoTexture, (int)prontoButtonRec.x, (int)prontoButtonRec.y, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), prontoButtonRec)){
              SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
             if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrar4Players = false; // Define a variável para mostrar o ranking como false
                    mostrar2Players = false; // Define a variável para mostrar o ranking
                    mostrar3Players = false; // Define a variável para mostrar
                    mostrarJogo = true; // Define a variável para mostrar o jogo como true
                    }
                }
                //botao voltar
                DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"
                           if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área do botão "voltar"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrar2Players = false; // Define a variável para mostrar o ranking como false
                    mostrarJogar = true; // Define a variável para mostrar o
                }
                
            }

     }

            if(mostrar3Players){

                
                DrawTexture(tela3playersTexture, 0, 0, WHITE);
                if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
                else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando
                DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"

                            DrawRectangleRec(textBoxppp, LIGHTGRAY);
                            DrawRectangleRec(textBoxppp2, LIGHTGRAY);
                            DrawRectangleRec(textBoxppp3, LIGHTGRAY);

            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBoxppp.x - 50, (int)textBoxppp.y + 100, 20, RED);
            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBoxppp2.x + 250, (int)textBoxppp2.y + 30, 20, GOLD);
            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBoxppp3.x - 20, (int)textBoxppp3.y + 100, 20, GREEN);
        if (CheckCollisionPointRec(GetMousePosition(), textBoxppp)) mouseOnTextppp = true;
        else mouseOnTextppp = false;
        if (CheckCollisionPointRec(GetMousePosition(), textBoxppp2)) mouseOnTextppp2 = true;
        else mouseOnTextppp2 = false;
        if (CheckCollisionPointRec(GetMousePosition(), textBoxppp3)) mouseOnTextppp3 = true;
        else mouseOnTextppp3 = false;
            if (mouseOnTextppp) DrawRectangleLines((int)textBoxppp.x, (int)textBoxppp.y, (int)textBoxppp.width, (int)textBoxppp.height, RED);
            else DrawRectangleLines((int)textBoxppp.x, (int)textBoxppp.y, (int)textBoxppp.width, (int)textBoxppp.height, DARKGRAY);
            if (mouseOnTextppp2) DrawRectangleLines((int)textBoxppp2.x, (int)textBoxppp2.y, (int)textBoxppp2.width, (int)textBoxppp2.height, GOLD);
            else DrawRectangleLines((int)textBoxppp2.x, (int)textBoxppp2.y, (int)textBoxppp2.width, (int)textBoxppp2.height, DARKGRAY);
            if (mouseOnTextppp3) DrawRectangleLines((int)textBoxppp3.x, (int)textBoxppp3.y, (int)textBoxppp3.width, (int)textBoxppp3.height, GREEN);
            else DrawRectangleLines((int)textBoxppp3.x, (int)textBoxppp3.y, (int)textBoxppp3.width, (int)textBoxppp3.height, DARKGRAY);

            DrawText(name, (int)textBoxppp.x + 50, (int)textBoxppp.y + 36, 40, MAROON);
            DrawText(name3, (int)textBoxppp2.x + 50, (int)textBoxppp2.y + 36, 40, GOLD);
            DrawText(name4, (int)textBoxppp3.x + 50, (int)textBoxppp3.y + 36, 40, GREEN);

            if (mouseOnTextppp){
                if (letterCount < 5)
                {
                    // Draw blinking underscore char
                   DrawText("_", (int)textBoxppp.x + 50 + MeasureText(name, 40), (int)textBoxppp.y + 40, 40, MAROON);
                }

            } 
            if (mouseOnTextppp2){
                if (letterCount2 < 5)
                {
                    // Draw blinking underscore char
                    DrawText("_", (int)textBoxppp2.x + 50 + MeasureText(name3, 40), (int)textBoxppp2.y + 40, 40, GOLD);
                }
     

            }
            if (mouseOnTextppp3){
                if (letterCount3 < 5)
                {
                    // Draw blinking underscore char
                   DrawText("_", (int)textBoxppp3.x + 50 + MeasureText(name4, 40), (int)textBoxppp3.y + 40, 40, GREEN);
                }

            } 
                            mostrar2Players = false; // Define a variável para mostrar
                mostrar4Players = false; // Define a variável para mostrar
                          //botao pronto
                DrawTexture(prontoTexture, (int)prontoButtonRec.x, (int)prontoButtonRec.y, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), prontoButtonRec)){
              SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
             if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrar4Players = false; // Define a variável para mostrar o ranking como false
                    mostrar2Players = false; // Define a variável para mostrar o ranking
                    mostrar3Players = false; // Define a variável para mostrar
                    mostrarJogo = true; // Define a variável para mostrar o jogo como true
                    }
                } 
                           if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área do botão "voltar"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrar3Players = false; // Define a variável para mostrar o ranking como false
                    mostrarJogar = true; // Define a variável para mostrar
                }
                
            }
            
            }

            if(mostrar4Players){
                DrawTexture(tela4playersTexture, 0, 0, WHITE);
                    if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
                        else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando
                        DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"

            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBox.x - 50, (int)textBox.y + 100, 20, RED);
            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBox2.x - 20, (int)textBox2.y + 100, 20, BLUE);
            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBox3.x - 20, (int)textBox3.y + 100, 20, GOLD);
            DrawText("Passe o mouse por cima da caixa \ne escreva o nome desejado", (int)textBox4.x - 20, (int)textBox4.y + 100, 20, GREEN);

            DrawRectangleRec(textBox, LIGHTGRAY);
            DrawRectangleRec(textBox2, LIGHTGRAY);
            DrawRectangleRec(textBox3, LIGHTGRAY);
            DrawRectangleRec(textBox4, LIGHTGRAY);

        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;
        if (CheckCollisionPointRec(GetMousePosition(), textBox2)) mouseOnText2 = true;
        else mouseOnText2 = false;
        if (CheckCollisionPointRec(GetMousePosition(), textBox3)) mouseOnText3 = true;
        else mouseOnText3 = false;
        if (CheckCollisionPointRec(GetMousePosition(), textBox4)) mouseOnText4 = true;
        else mouseOnText4 = false;

            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
            if (mouseOnText2) DrawRectangleLines((int)textBox2.x, (int)textBox2.y, (int)textBox2.width, (int)textBox2.height, BLUE);
            else DrawRectangleLines((int)textBox2.x, (int)textBox2.y, (int)textBox2.width, (int)textBox2.height, DARKGRAY);
            if (mouseOnText3) DrawRectangleLines((int)textBox3.x, (int)textBox3.y, (int)textBox3.width, (int)textBox3.height, YELLOW);
            else DrawRectangleLines((int)textBox3.x, (int)textBox3.y, (int)textBox3.width, (int)textBox3.height, DARKGRAY);
            if (mouseOnText4) DrawRectangleLines((int)textBox4.x, (int)textBox4.y, (int)textBox4.width, (int)textBox4.height, GREEN);
            else DrawRectangleLines((int)textBox4.x, (int)textBox4.y, (int)textBox4.width, (int)textBox4.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 50, (int)textBox.y + 36, 40, MAROON);
            DrawText(name2, (int)textBox2.x + 50, (int)textBox2.y + 36, 40, BLUE);
            DrawText(name3, (int)textBox3.x + 50, (int)textBox3.y + 36, 40, GOLD);
            DrawText(name4, (int)textBox4.x + 50, (int)textBox4.y + 36, 40, GREEN);

            if (mouseOnText){
                if (letterCount < 5)
                {
                    // Draw blinking underscore char
                   DrawText("_", (int)textBox.x + 50 + MeasureText(name, 40), (int)textBox.y + 40, 40, MAROON);
                }

            } 
            if (mouseOnText2){
                if (letterCount2 < 5)
                {
                    // Draw blinking underscore char
                    DrawText("_", (int)textBox2.x + 50 + MeasureText(name2, 40), (int)textBox2.y + 40, 40, BLUE);
                }
     

            }
            if (mouseOnText3){
                if (letterCount3 < 5)
                {
                    // Draw blinking underscore char
                   DrawText("_", (int)textBox3.x + 50 + MeasureText(name3, 40), (int)textBox3.y + 40, 40, YELLOW);
                }

            }
            if (mouseOnText4){
                if (letterCount4 < 5)
                {
                    // Draw blinking underscore char
                    DrawText("_", (int)textBox4.x + 50 + MeasureText(name4, 40), (int)textBox4.y + 40, 40, GREEN);
                }

            }  

                              //botao pronto
                DrawTexture(prontoTexture, (int)prontoButtonRec.x, (int)prontoButtonRec.y, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), prontoButtonRec)){
              SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
             if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado

                    mostrarinicio = false;
                    mostrarJogar = false; //
                    mostrar4Players = false; // Define a variável para mostrar o ranking como false
                    mostrar2Players = false; // Define a variável para mostrar o ranking
                    mostrar3Players = false; // Define a variável para mostrar
                    mostrarJogo = true; // Define a variável para mostrar o jogo como true
                    }
                }
                          if(CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área do botão "voltar"
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                    mostrar4Players = false; // Define a variável para mostrar o ranking como false
                    mostrarJogar = true; // Define a variável para mostrar o jogo com
                }
                
            }


}

 

//desenha a tela com o tabuleiro
if (mostrarJogo) {
    dadoButtonRec = (Rectangle){1650, 535, (float)dado0texture.width, (float)dado0texture.height };


    

        if(CheckCollisionPointRec(GetMousePosition(), dadoButtonRec)){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                RolarDado(); //
            }
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

//dsenhar tabuleiro
DrawTexture(jogoTexture, 0, 0, WHITE);

//desenhar os nomes

DrawText(TextFormat("%s", name), 1097, 290, 40, MAROON);
DrawText(TextFormat("%s", name2), 1097, 950, 40, BLUE);
DrawText(TextFormat("%s", name3), 123, 950, 40, GOLD);
DrawText(TextFormat("%s", name4), 127, 294, 40, GREEN);


// Loop para todos os jogadores
for (int i = 0; i < NUM_JOGADORES; i++) {
    // Loop para todas as peças de cada jogador
    for (int j = 0; j < NUM_PECAS; j++) {
        // Selecionar a textura da peça com base no jogador
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

        // Desenhar a peça na posição apropriada
        if (pecaEmJogo[i][j] == 1 || pecaEmJogo[i][j] == 2 || pecaEmJogo[i][j] == 3 || pecaEmJogo[i][j] == 4) {
            DrawTexture(textura, posicaoPecaX[i][j], posicaoPecaY[i][j], WHITE);
        } else if(pecaEmJogo[i][j] == 0){
            DrawTexture(textura, baseX[i][j], baseY[i][j], WHITE);
        }
    }
}


        DrawText(TextFormat("Resultado do dado (K): %i", dado), 10, 10, 20, WHITE);
        if(dado == 0){
            DrawTexture(dado0texture, 1650, 535, RAYWHITE);
        }
        if(dado == 1){
            DrawTexture(dado1texture, 1650, 535, RAYWHITE);
        }
        if(dado == 2){
            DrawTexture(dado2texture, 1650, 535, RAYWHITE);
        }
        if(dado == 3){
            DrawTexture(dado3texture, 1650, 535, RAYWHITE);
        }
        if(dado == 4){
            DrawTexture(dado4texture, 1650, 535, RAYWHITE);
        }
        if(dado == 5){
            DrawTexture(dado5texture, 1650, 535, RAYWHITE);
        }
        if(dado == 6){
            DrawTexture(dado6texture, 1650, 535, RAYWHITE);
        }





        DrawText(TextFormat("Jogador atual: %s", nomesJogadores[jogadorAtual]), 10, 40, 20, coresJogadores[jogadorAtual]);
        DrawText("Selecione uma peça (1-4):", 10, 70, 20, WHITE);
        if (pecaSelecionada != -1) {
            DrawText(TextFormat("Peça selecionada: %i", pecaSelecionada + 1), 10, 100, 20, BLACK);
        }


        bool jogadorVenceu = false;

        for (int i = 0; i < NUM_JOGADORES; i++) {
            int pecasNoEstado4 = 0;
            
            for (int j = 0; j < NUM_PECAS; j++) {
                if (pecaEmJogo[i][j] == 4) {
                    pecasNoEstado4++;
                }
            }
            
            if (pecasNoEstado4 == 4) {
                jogadorVenceu = true;
                jogadorVencedor = i;
                break; //para de contar dai
            }
        }

        if (jogadorVenceu) {
            DrawTexture(vitoriaTexture, 0, 0, WHITE);
            DrawText(TextFormat("%s Venceu!", nomesJogadores[jogadorVencedor]), 799, 499, 20, WHITE); // Texto indicando qual jogador venceu
            AdicionaraoRank(nomesJogadores[jogadorVencedor]);
        }



        //botao de som
       if (pause) DrawTexture(soundOffTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som desligado se a música estiver pausada
        else DrawTexture(soundOnTexture, (int)soundButtonRec.x, (int)soundButtonRec.y, WHITE); // Desenha o botão de som ligado se a música estiver tocando
        DrawTexture(voltarTexture, (int)voltarButtonRec.x, (int)voltarButtonRec.y, WHITE); // Desenha o botão "voltar"
                if (CheckCollisionPointRec(GetMousePosition(), voltarButtonRec)) { // Se a posição do mouse estiver sobre a área da opção de sair
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Se o botão esquerdo do mouse for pressionado
                mostrarSairJogo = true; // Define a variável para mostrar a opção de sair como true
            }
        }
        if(mostrarSairJogo){


        }


    









}








        EndDrawing(); // Finaliza o desenho do frame
    }

    // Fecha a janela ao sair do laço principal
    CloseWindow(); // Fecha a janela

    // Descarregar recursos
    UnloadTexture(soundOnTexture); // Descarrega a textura do botão de som ligado
    UnloadTexture(soundOffTexture); // Descarrega a textura do botão de som desligado
    UnloadTexture(bgTexture); // Descarrega a textura de fundo
    UnloadTexture(Texture); // Descarrega a textura do logotipo
    UnloadTexture(regrasTexture); // Descarrega a textura da tela de regras
    UnloadTexture(rankingTexture); // Descarrega a textura da tela de ranking
    UnloadTexture(sairTexture); // Descarrega a textura da opção de sair
    UnloadTexture(botaosimTexture); // Descarrega a textura do botão "sim"
    UnloadTexture(botaonaoTexture); // Descarrega a textura do botão "não"
    UnloadTexture(escolhaTexture); // Descarrega a textura da tela de escolha
    UnloadMusicStream(musicamenu); // Descarrega a música do menu
    CloseAudioDevice(); // Fecha o dispositivo de áudio

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}