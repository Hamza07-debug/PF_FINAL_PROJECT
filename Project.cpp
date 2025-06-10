//#include <iostream>
//#include <fstream>
//#include <string>
//#include <conio.h>
//#include <cstdlib>
//#include <windows.h>
//#include <ctime>
//
//using namespace std;
//
//bool gameover;
//int row = 15;
//int col = 25;
//int X = 1;
//int Y = 1;
//char board[100][100];
//DWORD lastmovetime = 0;
//const DWORD movedelay = 30;
//DWORD bomb_time = 0;
//int bombX, bombY;
//bool exploded = false;
//bool encounter = false;
//bool after_explosion = false;
//bool placement = false;
//int score = 0;
//int total_enemies = 0;
//int stage = 1;
//int enemies_per_stage = 4;
//
//
//int loadHighScore() {
//    ifstream file("highscore.txt");
//    int highScore = 0;
//    if (file.is_open()) {
//        file >> highScore;
//        file.close();
//    }
//    else {
//        cout << "No high score file found. Starting fresh!" << endl;
//    }
//    return highScore;
//}
//
//
//void saveHighScore(int score) {
//    ofstream file("highscore.txt", ios::trunc);
//    if (file.is_open()) {
//        file << score;
//        file.close();
//        cout << "High score saved successfully!" << endl;
//    }
//    else {
//        cerr << "Error: Unable to save high score." << endl;
//    }
//}
//
//void saveHighScoreList(int score) {
//    ofstream file("highscore.txt", ios::app);
//    if (file.is_open()) {
//        file << score << endl;
//        file.close();
//        cout << "High score saved successfully!" << endl;
//    }
//    else {
//        cerr << "Error: Unable to save high score." << endl;
//    }
//}
//
//void loadHighScores() {
//    ifstream file("highscore.txt");
//    if (file.is_open()) {
//        int scores[100];
//        int count = 0;
//        while (file >> scores[count]) {
//            count++;
//            if (count >= 100) {
//                break;
//            }
//        }
//        file.close();
//
//        for (int i = 0; i < count - 1; ++i) {
//            for (int j = 0; j < count - i - 1; ++j) {
//                if (scores[j] < scores[j + 1]) {
//                    int temp = scores[j];
//                    scores[j] = scores[j + 1];
//                    scores[j + 1] = temp;
//                }
//            }
//        }
//
//        cout << "High scores are: " << endl;
//        for (int i = 0; i < count; ++i) {
//            cout << scores[i] << endl;
//        }
//    }
//    else {
//        cerr << "Error! Unable to load high scores " << endl;
//    }
//}
//
//
//void grid() {
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            if (i == 0 || i == row - 1) {
//                board[i][j] = '-';
//            }
//            else if (j == 0 || j == col - 1) {
//                board[i][j] = '|';
//            }
//            else if (i % 2 == 0 && j % 2 == 0) {
//                board[i][j] = '#';
//            }
//            else {
//                board[i][j] = ' ';
//            }
//        }
//    }
//
//    int o = 0;
//    srand(time(0));
//    while (o < 10) {
//        int r = rand() % (row - 2) + 1;
//        int c = rand() % (col - 2) + 1;
//        if (board[r][c] == ' ') {
//            board[r][c] = 'O';
//            o++;
//        }
//    }
//
//    board[X][Y] = 'P';
//    int e = 0;
//    srand(time(0));
//    while (e < enemies_per_stage) {
//        int r = rand() % row;
//        int c = rand() % col;
//        if (board[r][c] == ' ') {
//            board[r][c] = 'E';
//            e++;
//            total_enemies++;
//        }
//    }
//}
//
//void bomb_placement() {
//    bombX = X, bombY = Y;
//    if (board[X][Y] == 'P') {
//        board[bombX][bombY] = 'B';
//        placement = true;
//        bomb_time = GetTickCount();
//        exploded = false;
//        after_explosion = false;
//        Beep(500, 200);
//    }
//}
//
//void bomb_explosion() {
//    if (placement && !(after_explosion) && (GetTickCount() - bomb_time) >= 3000) {
//        if (!(exploded)) {
//            Beep(2000, 300);
//
//         
//            for (int dy = 1; dy <= 3 && bombY + dy < col; dy++) {
//                if (board[bombX][bombY + dy] == 'O') {
//                    board[bombX][bombY + dy] = ' ';
//                    score += 10;
//                }
//                else if (board[bombX][bombY + dy] == 'E') {
//                    board[bombX][bombY + dy] = ' ';
//                    score += 50;
//                    total_enemies--;
//                }
//            }
//            for (int dy = 1; dy <= 3 && bombY - dy >= 0; dy++) {
//                if (board[bombX][bombY - dy] == 'O') {
//                    board[bombX][bombY - dy] = ' ';
//                    score += 10;
//                }
//                else if (board[bombX][bombY - dy] == 'E') {
//                    board[bombX][bombY - dy] = ' ';
//                    score += 50;
//                    total_enemies--;
//                }
//            }
//
//           
//            for (int dx = 1; dx <= 3 && bombX + dx < row; dx++) {
//                if (board[bombX + dx][bombY] == 'O') {
//                    board[bombX + dx][bombY] = ' ';
//                    score += 10;
//                }
//                else if (board[bombX + dx][bombY] == 'E') {
//                    board[bombX + dx][bombY] = ' ';
//                    score += 50;
//                    total_enemies--;
//                }
//            }
//            for (int dx = 1; dx <= 3 && bombX - dx >= 0; dx++) {
//                if (board[bombX - dx][bombY] == 'O') {
//                    board[bombX - dx][bombY] = ' ';
//                    score += 10;
//                }
//                else if (board[bombX - dx][bombY] == 'E') {
//                    board[bombX - dx][bombY] = ' ';
//                    score += 50;
//                    total_enemies--;
//                }
//            }
//
//            board[bombX][bombY] = 'X'; 
//            Sleep(500);
//            exploded = true;
//        }
//
//        if (exploded) {
//            board[bombX][bombY] = ' ';  
//            after_explosion = true;
//            placement = false;
//        }
//
//        if (exploded) {
//            if ((board[bombX][bombY + 1] == 'P') || (board[bombX + 1][bombY] == 'P' || (board[bombX - 1][bombY] == 'P') || (board[bombX][bombY - 1] == 'P'))) {
//                cout << "Player got hit by a bomb!" << endl;
//                gameover = true;
//            }
//        }
//    }
//}
//
//void enemy_movement() {
//    int dir[] = { 1, -1, 0, 0 };
//    int dir2[] = { 0, 0, 1, -1 };
//
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            if (board[i][j] == 'E') {
//                int direction = rand() % 4;
//                int newX = i + dir[direction];
//                int newY = j + dir2[direction];
//
//                if (newX > 0 && newX < row - 1 && newY > 0 && newY < col - 1 && board[newX][newY] == ' ') {
//                    board[i][j] = ' ';
//                    board[newX][newY] = 'E';
//                }
//            }
//        }
//    }
//    Sleep(400);
//}
//
//void draw() {
//
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
//
//    
//    cout << "Stage: " << stage << "    Score: " << score << "    Remaining Enemies: " << total_enemies << endl;
//    cout << "Controls: Arrow Keys to Move, 'b' to Place Bomb, 'q' to Quit" << endl;
//    cout << "----------------------------------------------------------" << endl;
//
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            cout << board[i][j];
//        }
//        cout << endl;
//    }
//}
//
//
//void input() {
//    if (_kbhit()) {
//        char input = _getch();
//        DWORD currentTime = GetTickCount();
//        if ((currentTime - lastmovetime) >= movedelay) {
//            lastmovetime = currentTime;
//            while (_kbhit()) {
//                input = _getch();
//                switch (input) {
//                case 72: 
//                    if (board[X - 1][Y] == ' ') {
//                        if (placement && (X == bombX && Y == bombY)) {
//                            board[X][Y] = 'B';
//                        }
//                        else {
//                            board[X][Y] = ' ';
//                        }
//                        X--;
//                        board[X][Y] = 'P';
//                        Beep(800, 100);
//                    }
//                    else if (board[X - 1][Y] == 'E') {
//                        encounter = true;
//                        gameover = true;
//                    }
//                    break;
//
//                case 75: 
//                    if (board[X][Y - 1] == ' ') {
//                        if (placement && (X == bombX && Y == bombY)) {
//                            board[X][Y] = 'B';
//                        }
//                        else {
//                            board[X][Y] = ' ';
//                        }
//                        Y--;
//                        board[X][Y] = 'P';
//                        Beep(600, 100);
//                    }
//                    else if (board[X][Y - 1] == 'E') {
//                        encounter = true;
//                        gameover = true;
//                    }
//                    break;
//
//                case 80:
//                    if (board[X + 1][Y] == ' ') {
//                        if (placement && (X == bombX && Y == bombY)) {
//                            board[X][Y] = 'B';
//                        }
//                        else {
//                            board[X][Y] = ' ';
//                        }
//                        X++;
//                        board[X][Y] = 'P';
//                        Beep(1000, 100);
//                    }
//                    else if (board[X + 1][Y] == 'E') {
//                        encounter = true;
//                        gameover = true;
//                    }
//                    break;
//
//                case 77: 
//                    if (board[X][Y + 1] == ' ') {
//                        if (placement && (X == bombX && Y == bombY)) {
//                            board[X][Y] = 'B';
//                        }
//                        else {
//                            board[X][Y] = ' ';
//                        }
//                        Y++;
//                        board[X][Y] = 'P';
//                        Beep(900, 100);
//                    }
//                    else if (board[X][Y + 1] == 'E') {
//                        encounter = true;
//                        gameover = true;
//                    }
//                    break;
//
//                case 'b':
//                    bomb_placement();
//                    break;
//
//                case 'q':
//                    cout << "Game-over";
//                    gameover = true;
//                }
//            }
//        }
//    }
//}
//
//int main() {
//    gameover = false;
//    int highScore = loadHighScore();
//
//    cout << "Welcome to the game!" << endl;
//    cout << "Current high score: " << highScore << endl;
//    cout << "Enter movement" << endl;
//
//    grid();  
//    while (!gameover) {
//        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
//        draw();
//        input();  
//        enemy_movement();  
//        bomb_explosion();  
//
//        if (total_enemies == 0) {
//            
//            cout << "Player has cleared Stage " << stage << endl;
//            stage++;
//            enemies_per_stage += 4; 
//            grid();
//            X = 1;   
//            Y = 1;
//            total_enemies = enemies_per_stage; 
//        }
//    }
//
//    if (encounter) {
//        cout << "Player was hit by an enemy!" << endl;
//    }
//    else if (exploded) {
//        cout << "Player was hit by a bomb!" << endl;
//    }
//
//    if (score > highScore) {
//        cout << "New high score " <<"is: "<< score << endl;
//        saveHighScore(score);
//    }
//    else {
//        cout << "Better luck next time! High score remains: " << highScore << endl;
//    }
//
//    saveHighScoreList(score);
//    loadHighScores();
//
//    if (stage > 2) {
//        cout << "All Stages Completed!" << endl;
//        gameover = true; 
//    }
//
//    system("pause");
//    return 0;
//}
