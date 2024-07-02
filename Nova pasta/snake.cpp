#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>

using namespace std;

struct Snake {
    int x[100]; 
    int y[100]; 
    int dir; 
    int tamanho;
    int score;
};



bool colisaoSnake(int x, int y, int mapa[25][25], Snake &snake) {
    if (mapa[x][y] != 0) {
        return false;
    } for (int i = 1; i < snake.tamanho; i++) {
        if (x == snake.x[i] && y == snake.y[i]) {
            return false;
        }
    }
    return true;
}

void movimentoSnake(Snake &snake, int tecla, int &contadorMov) {
    
    if (_kbhit()) {
        tecla = _getch();
        switch (tecla) {
            case 72: 
            case 'w': snake.dir = 1; contadorMov++; break;
            case 80: 
            case 's': snake.dir = 2; contadorMov++; break;
            case 77: 
            case 'd': snake.dir = 3; contadorMov++; break;
            case 75: 
            case 'a': snake.dir = 4; contadorMov++; break;
        }
    }

    // move as partes do corpo
    for (int i = snake.tamanho; i > 0; i--) {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
    }

    // move a cabeça da cobra na direção atual
    switch (snake.dir) {
        case 1: snake.x[0]--; break;
        case 2: snake.x[0]++; break;
        case 3: snake.y[0]++; break;
        case 4: snake.y[0]--; break;
    }
  

}


void gerarFruta(int mapa[25][25], int &frutaX, int &frutaY) {
    do {
        frutaX = rand() % 23 + 1;
        frutaY = rand() % 23 + 1; 
    } while (mapa[frutaX][frutaY] != 0); // verifica se nao eh parede
}


void salvarPontuacao(Snake& snake) {
    ofstream arquivo("pontuacao.txt");
    if (arquivo.is_open()) {
        arquivo << snake.score;
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo de pontuacao.txt  :(" << endl;
    }
}


void lerPontuacao(Snake& snake) {
    ifstream arquivo("pontuacao.txt");
    if (arquivo.is_open()) {
        arquivo >> snake.score;
        arquivo.close();
    } else {
        cout << "Arquivo de pontuacao.txt nao encontrado. Pontuacao inicial sera zero." << endl;
        snake.score = 0;
    }
}


void definirDirecao(Snake &snake, int frutaX, int frutaY, int mapa[25][25]) {
    int dx = frutaX - snake.x[0];
    int dy = frutaY - snake.y[0];

    // Tentativa de mover na direção da fruta, priorizando eixo x
    if (abs(dx) > abs(dy)) {
        if (dx > 0 && !colisaoSnake(snake.x[0] + 1, snake.y[0], mapa, snake)) {
            snake.dir = 2; // Baixo
        } else if (dx < 0 && !colisaoSnake(snake.x[0] - 1, snake.y[0], mapa, snake)) {
            snake.dir = 1; // Cima
        } else if (dy > 0 && !colisaoSnake(snake.x[0], snake.y[0] + 1, mapa, snake)) {
            snake.dir = 3; // Direita
        } else if (dy < 0 && !colisaoSnake(snake.x[0], snake.y[0] - 1, mapa, snake)) {
            snake.dir = 4; // Esquerda
        }
    } else {
        if (dy > 0 && !colisaoSnake(snake.x[0], snake.y[0] + 1, mapa, snake)) {
            snake.dir = 3; // Direita
        } else if (dy < 0 && !colisaoSnake(snake.x[0], snake.y[0] - 1, mapa, snake)) {
            snake.dir = 4; // Esquerda
        } else if (dx > 0 && !colisaoSnake(snake.x[0] + 1, snake.y[0], mapa, snake)) {
            snake.dir = 2; // Baixo
        } else if (dx < 0 && !colisaoSnake(snake.x[0] - 1, snake.y[0], mapa, snake)) {
            snake.dir = 1; // Cima
        }
    }
}

int main() {
    /// ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
    // INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    // FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    // INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    /// ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    Snake snake;
    snake.dir = 1;
    snake.x[0] = 12; snake.y[0] = 12;
    snake.x[1] = 12; snake.y[1] = 13;
    snake.x[2] = 12; snake.y[2] = 14;
    snake.tamanho = 3;
    int tecla;
    bool jogoRodando = false;
    bool jogo2Rodando = false;
    bool jogo3Rodando = false;
    int frutaX, frutaY;
    char opcaoMenu;
    int contadorMov = 0;
    

    cout << "-----------------------\n\n";
    cout << "        BEM VINDO      \n\n";
    cout << "-----------------------\n\n";
    cout << "(1) INICIAR NOVO JOGO \n";
    cout << "(2) SCORE \n";
    cout << "(3) MODO DESAFIO \n";
    cout << "(4) AUTOMACAO \n";
    cout << "(5) SAIR";
    cin >> opcaoMenu;


    switch(opcaoMenu){
        case '1': jogoRodando = true; break;
        case '2': cout <<"arquivo de pontuacao"; break;
        case '3': jogo2Rodando =  true; break;
        case '4': jogo3Rodando = true; break;
        case '5': system("cls"); 
            cout<<"-----------------------\n\n";
            cout << " OBRIGADO POR JOGAR      \n\n";
            cout << "-----------------------\n\n";
            break;
    }


    int mapa[25][25] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


    gerarFruta(mapa, frutaX, frutaY);
    lerPontuacao(snake);

    while (jogoRodando) {
            SetConsoleCursorPosition(out, coord);

        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                bool desenhou = false;
                if (i == frutaX && j == frutaY) {
                    cout << "@";
                    desenhou = true;
                }
                for (int k = 0; k < snake.tamanho; k++) {
                    if (i == snake.x[k] && j == snake.y[k]) {
                        cout << char(1);
                        desenhou = true;
                        break;
                    }
                }
                if (!desenhou) {
                    if (mapa[i][j] == 0) {
                        cout << " ";
                    } else {
                        cout << char(219);
                    }
                }
            }
            cout << endl;
        }

        movimentoSnake(snake, tecla, contadorMov);

        cout<<"Movimentos: "<<contadorMov<<endl;
        cout<<"score: "<<snake.score<<endl;

         if (snake.x[0] == frutaX && snake.y[0] == frutaY) {
            snake.tamanho++;
            snake.score = snake.score + 5;
            gerarFruta(mapa, frutaX, frutaY); // gera uma nova fruta
        }


        if (!colisaoSnake(snake.x[0], snake.y[0], mapa, snake)) {
            jogoRodando = false;
            system("cls");
            cout << "Você Perdeu!" << endl;
        }

        if (snake.tamanho == 100){
            jogoRodando = false;
            system("cls");
            cout<<"-----------------------\n\n";
            cout << "   VOCÊ GANHOU!!      \n\n";
            cout<<"          :)              \n\n";
            cout<<"SEU SCORE FOI: "<<snake.score<<endl<<endl;
            cout << "-----------------------\n\n";
        }
        Sleep(150);
    }

    if (jogo2Rodando) {
        snake.dir = 1;
        snake.x[0] = 12; snake.y[0] = 12;
        snake.x[1] = 12; snake.y[1] = 13;
        snake.x[2] = 12; snake.y[2] = 14;
        snake.tamanho = 100;

    while (jogo2Rodando) {
        SetConsoleCursorPosition(out, coord);

        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                bool desenhou = false;
                for (int k = 0; k < snake.tamanho; k++) {
                    if (i == snake.x[k] && j == snake.y[k]) {
                        cout << char(1);
                        desenhou = true;
                        break;
                    }
                }
                if (!desenhou) {
                    if (mapa[i][j] == 0) {
                        cout << char(219);
                    } else {
                        cout << "#";
                    }
                }
            }
            cout << endl;
        }

        movimentoSnake(snake, tecla, contadorMov);

        if (!colisaoSnake(snake.x[0], snake.y[0], mapa, snake)) {
            cout << "VOCE PERDEU :(" << endl;
            Sleep(3000);
            jogo2Rodando = false;
        }

        if (snake.x[0] == 23 && snake.y[0] == 23) {
            cout << "PARABENS VOCE VENCEU" << endl;
            Sleep(3000);
            jogo2Rodando = false;
        }

        Sleep(100);
        }
    }
    
    if (jogo3Rodando) {
    snake.dir = 1;
    snake.x[0] = 12; snake.y[0] = 12;
    snake.x[1] = 12; snake.y[1] = 13;
    snake.x[2] = 12; snake.y[2] = 14;
    snake.tamanho = 3;

    gerarFruta(mapa, frutaX, frutaY);
    
    
    


    while(jogo3Rodando){
        SetConsoleCursorPosition(out, coord);
        
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                bool desenhou = false;
                for (int k = 0; k < snake.tamanho; k++) {
                    if (i == snake.x[k] && j == snake.y[k]) {
                        cout << char(1);
                        desenhou = true;
                        break;
                    }
                }
                if (!desenhou) {
                    if (mapa[i][j] == 0) {
                        cout << " ";
                    } else {
                        cout << char(219);
                    }
                }
            }
            cout << endl;
        }

        definirDirecao(snake, frutaX, frutaY, mapa);
        movimentoSnake(snake, tecla, contadorMov);

    }
    
    }
    
    return 0;
}
