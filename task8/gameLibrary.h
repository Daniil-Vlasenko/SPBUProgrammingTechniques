#ifndef TASK8_GAMELIBRARY_H
#define TASK8_GAMELIBRARY_H
#include <random>
#include "terminal.h"
#include <cassert>
#include <stack>


struct Cell {
    int x{};
    int y{};
    bool isWay{};   // true, если проход
    bool isRightWay{};   // true, если проход от старта к финишу
    bool isNotRightWay{};   // true, если точно не проход от старта к финишу

    Cell(int x, int y): x{x}, y{y} {}
    Cell()= default;
};

class Game {
    bool gameOver{};
    const int width{};
    const int height{};
    Cell **labyrinth, *start, *finish, *gamer;
    enum class eDirection {STOP, LEFT, RIGHT, UP, DOWN} dir{};
//    eDirection dir{};
    Term::Terminal term = Term::Terminal(true, false);
public:
    Game(int width, int height);
    ~Game();
    bool getGameOver();

    // Генерация лабиринта
    void generateMaze();
    // Поиск верного пути
    void generateWay();
    // Отрисовка карты
    void drawMaze();
    // Отслеживание нажатий
    void input();
    // Логика игры
    void logic();
};


#endif //TASK8_GAMELIBRARY_H
