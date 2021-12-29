#include <iostream>
#include "gameLibrary.h"


int main(int argc, char *argv[]) {
    int width = argc > 1 ? std::stoi(argv[1]) : 11, height = argc > 2 ? std::stoi(argv[2]) :11;
    width = width <= 80 ? width : 80; height = height <= 40 ? height : 40;
    srand(time(nullptr));
    Game game(width, height);
    game.generateMaze();
//    system("clear");
    system("cls");
    while(!game.getGameOver()) {
        game.drawMaze();
        game.input();
        game.logic();
    }
    game.generateWay();
    game.drawMaze();

    return 0;
}
