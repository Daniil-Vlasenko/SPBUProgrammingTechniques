#include "gameLibrary.h"
#include <iostream>


bool operator == (Cell c1, Cell c2) {
    return c1.x == c2.x && c1.y == c2.y;
}

bool Game::getGameOver() {return gameOver;}

Game::Game(int width, int height) :
    width{ width & 1 ? width : ++width}, height{height & 1 ? height : ++height} {
    labyrinth = new Cell*[height];
    for(size_t y = 0; y < height; ++y)
        labyrinth[y] = new Cell[width];
    // Инициализируем массив
    for(int y = 0; y < height; ++y)
        for(int x = 0; x < width; ++x) {
            labyrinth[y][x].x = x;
            labyrinth[y][x].y = y;
            labyrinth[y][x].isWay = false;
        }
}
Game::~Game() {
    for(size_t i = 0; i != height; ++i)
        delete labyrinth[i];
    delete labyrinth;
}

// Генерация лабиринта
void Game::generateMaze() {
    // Выбираем начальную точку для алгоритма - четное число
    int x = 2 * (rand() % (width / 2)) + 1, y = 2 * (rand() % (height / 2)) + 1;
    labyrinth[y][x].isWay = true;

    // Создаем стек
    std::stack<Cell> path;
    path.push(labyrinth[y][x]);

    while(!path.empty()) {
        Cell currentCell = path.top();

        // Смотрим варианты, в какую сторону можно пойти
        std::vector<Cell> nextStep;
        if (currentCell.x > 1 && !labyrinth[currentCell.y][currentCell.x - 2].isWay)
            nextStep.push_back(labyrinth[currentCell.y][currentCell.x - 2]);
        if (currentCell.x < width - 2 && !labyrinth[currentCell.y][currentCell.x + 2].isWay)
            nextStep.push_back(labyrinth[currentCell.y][currentCell.x + 2]);
        if (currentCell.y > 1 && !labyrinth[currentCell.y - 2][currentCell.x].isWay)
            nextStep.push_back(labyrinth[currentCell.y - 2][currentCell.x]);
        if (currentCell.y < height - 2 && !labyrinth[currentCell.y + 2][currentCell.x].isWay)
            nextStep.push_back(labyrinth[currentCell.y + 2][currentCell.x]);

        if(!nextStep.empty()) {
            //  Выбираем сторону из возможных вариантов
            Cell next = nextStep[rand() % nextStep.size()];

            //  Удаляем стену между ячейками и помечаем новую ячейку как путь
            if (next.x != currentCell.x) {
                if (currentCell.x - next.x > 0)
                    labyrinth[currentCell.y][currentCell.x - 1].isWay = true;
                else
                    labyrinth[currentCell.y][currentCell.x + 1].isWay = true;
            }
            if (next.y != currentCell.y) {
                if (currentCell.y - next.y > 0)
                    labyrinth[currentCell.y - 1][currentCell.x].isWay = true;
                else
                    labyrinth[currentCell.y + 1][currentCell.x].isWay = true;
            }
            labyrinth[next.y][next.x].isWay = true;
            //  Добавляем новую ячейку в стек
            path.push(next);
        }
        else
            //  Если попали в тупик, удаляем ячейку из стека
            path.pop();
    }

    // Генерация старта и финиша
    start = labyrinth[height - 2] + 1;
    gamer = start;
    finish = labyrinth[1] + width - 2;
//    int x1 = 2 * (rand() % (width / 2)) + 1, y1 = 2 * (rand() % (height / 2)) + 1, x2, y2;
//    start = labyrinth[y1] + x1;
//    do {
//        x2 = 2 * (rand() % (width / 2)) + 1, y2 = 2 * (rand() % (height / 2)) + 1;
//    } while(x1 == x2 && y1 == y2);
//    finish = labyrinth[y2] + x2;
}

// Поиск верного пути
void Game::generateWay() {
    // Создаем стек
    std::stack<Cell> path;
    path.push(*start);
    start->isRightWay = true;

    Cell currentCell;
    while(!((currentCell = path.top()) == *finish)) {
        // Смотрим варианты, в какую сторону можно пойти
        std::vector<Cell> nextStep;
        if (labyrinth[currentCell.y][currentCell.x - 1].isWay &&
            !labyrinth[currentCell.y][currentCell.x - 1].isRightWay && !labyrinth[currentCell.y][currentCell.x - 1].isNotRightWay)
            nextStep.push_back(labyrinth[currentCell.y][currentCell.x - 1]);
        if (labyrinth[currentCell.y][currentCell.x + 1].isWay &&
            !labyrinth[currentCell.y][currentCell.x + 1].isRightWay && !labyrinth[currentCell.y][currentCell.x + 1].isNotRightWay)
            nextStep.push_back(labyrinth[currentCell.y][currentCell.x + 1]);
        if (labyrinth[currentCell.y - 1][currentCell.x].isWay &&
            !labyrinth[currentCell.y - 1][currentCell.x].isRightWay && !labyrinth[currentCell.y - 1][currentCell.x].isNotRightWay)
            nextStep.push_back(labyrinth[currentCell.y - 1][currentCell.x]);
        if (labyrinth[currentCell.y + 1][currentCell.x].isWay &&
            !labyrinth[currentCell.y + 1][currentCell.x].isRightWay && !labyrinth[currentCell.y + 1][currentCell.x].isNotRightWay)
            nextStep.push_back(labyrinth[currentCell.y + 1][currentCell.x]);

        if(!nextStep.empty()) {
            //  Выбираем сторону из возможных вариантов
            Cell next = nextStep[rand() % nextStep.size()];

            //  Отмечаем, что это верный путь и добавляем новую ячейку в стек
            labyrinth[next.y][next.x].isRightWay = true;
            path.push(next);
        }
        else if (!(currentCell == *start)){
            //  Если попали в тупик, удаляем ячейку из стека и отмечаем как точно неверный путь
            labyrinth[currentCell.y][currentCell.x].isNotRightWay = true;
            labyrinth[currentCell.y][currentCell.x].isRightWay = false;
            path.pop();
        }
    }
}

// Отрисовка карты
void Game::drawMaze() {
    // Создаем строку-лабиринт и выводим ее
    using Term::bg;
    using Term::color;
    using Term::cursor_off;
    using Term::cursor_on;
    using Term::fg;
    using Term::Key;
    using Term::move_cursor;
    using Term::style;
    using Term::Terminal;

    std::string out;

    out.append(cursor_off());
    out.append(move_cursor(1, 1));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if(labyrinth[y][x].isWay) {
                if(labyrinth[y] + x == start)
                    out += color(bg::reset) + color(bg::bright_blue) + "  ";
                else if(labyrinth[y] + x == finish)
                    out += color(bg::reset) + color(bg::bright_red) + "  ";
                else if(labyrinth[y] + x == gamer)
                    out += color(bg::reset) + color(bg::bright_magenta) + "  ";
                else if(gameOver && labyrinth[y][x].isRightWay)
                    out +=  color(bg::reset) + color(bg::bright_yellow) + "  ";
                else
                    out += color(bg::reset) + "  ";
            }
            else
                out += color(bg::reset) + color(bg::white) + "  ";
        }
        out += color(bg::reset) + '\n';
    }

    out.append(cursor_on());
    std::cout << out << std::endl;
}

// Отслеживание нажатий
void Game::input() {
    using Term::Key;

    // Цикл прерывается, когда вводится направление для хода
    bool rightKey = false;
    while(!rightKey) {
        int key = term.read_key();
        switch (key) {
            case Key::ARROW_LEFT:
                dir = eDirection::LEFT; rightKey = true; break;
            case Key::ARROW_RIGHT:
                dir = eDirection::RIGHT; rightKey = true; break;
            case Key::ARROW_UP:
                dir = eDirection::UP; rightKey = true; break;
            case Key::ARROW_DOWN:
                dir = eDirection::DOWN; rightKey = true; break;
            case Key::ESC:
                gameOver = true; rightKey = true; break;
            default:
                continue;
        }
    }
}

// Логика игры
void Game::logic() {
    // Прекращаем игру, если игрок нажал ESC
    if(gameOver) {return;}

    if(dir == eDirection::LEFT && labyrinth[gamer->y][gamer->x - 1].isWay)
        gamer = labyrinth[gamer->y] + gamer->x - 1;
    else if(dir == eDirection::RIGHT && labyrinth[gamer->y][gamer->x + 1].isWay)
        gamer = labyrinth[gamer->y] + gamer->x + 1;
    else if(dir == eDirection::UP && labyrinth[gamer->y - 1][gamer->x].isWay)
        gamer = labyrinth[gamer->y - 1] + gamer->x;
    else if(dir == eDirection::DOWN && labyrinth[gamer->y + 1][gamer->x].isWay)
        gamer = labyrinth[gamer->y + 1] + gamer->x;
    // Если ход в стену, издается звук удара
    else if (dir == eDirection::LEFT && !labyrinth[gamer->y][gamer->x - 1].isWay ||
            dir == eDirection::RIGHT && !labyrinth[gamer->y][gamer->x + 1].isWay ||
            dir == eDirection::UP && !labyrinth[gamer->y - 1][gamer->x].isWay ||
            dir == eDirection::DOWN && !labyrinth[gamer->y + 1][gamer->x].isWay)
//        system("mpg123 -q hitSound.mp3");

    // Прекращаем игру, если игрок дошел до финиша
    if(gamer == finish) {gameOver = true; return;}
}
