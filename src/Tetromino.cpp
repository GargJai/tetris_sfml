#include "Tetromino.hpp"

Tetromino::Tetromino(int r, int c, TetrisGame& gameGrid, sf::Color bgcolor)
    : rows(r)
    , cols(c)
    , background_color(bgcolor)
{
    srand(time(0));
    int idx = rand() % 7;
    color = COLORS[idx];

    for (int i = 0; i < 4; i++) {
        position[i] = {POSITIONS[idx][i][0], POSITIONS[idx][i][1]};
    }

    for (auto& xy : position) {
        auto [x, y] = xy;
        if (gameGrid.getColor(x, y) != background_color) {
            over = true;
        }
    }

    if (!over)
        drawcurr(gameGrid);
}

void Tetromino::drawcurr(TetrisGame& gameGrid) {
    for (auto& xy : position) {
        auto [x, y] = xy;
        gameGrid.setColor(x, y, color); 
    }
}

void Tetromino::clearcurr(TetrisGame& gameGrid) {
    for (auto& xy : position) {
        auto [x, y] = xy;
        gameGrid.setColor(x, y, background_color); 
    }
}

void Tetromino::movedown(TetrisGame& gameGrid) {
    if (!over) {
        clearcurr(gameGrid);
        for (auto& xy : position) {
            auto [x, y] = xy;
            if (x + 1 >= rows || gameGrid.getColor(x + 1, y) != background_color) {
                contact = true;
                drawcurr(gameGrid);
                return;
            }
        }

        for (auto& xy : position) {
            xy.first++;
        }

        drawcurr(gameGrid);
    }
}

void Tetromino::moveleft(TetrisGame& gameGrid) {
    if (!over) {
        clearcurr(gameGrid);
        for (auto& xy : position) {
            auto [x, y] = xy;
            if (y - 1 < 0 || gameGrid.getColor(x, y - 1) != background_color) {
                drawcurr(gameGrid);
                return;
            }
        }

        for (auto& xy : position) {
            xy.second--;
        }
        drawcurr(gameGrid);
    }
}

bool Tetromino::getcontact() {
    return contact;
}

void Tetromino::moveright(TetrisGame& gameGrid) {
    if (!over) {
        clearcurr(gameGrid);
        for (auto& xy : position) {
            auto [x, y] = xy;
            if (y + 1 >= cols || gameGrid.getColor(x, y + 1) != background_color) {
                drawcurr(gameGrid);
                return;
            }
        }

        for (auto& xy : position) {
            xy.second++;
        }

        drawcurr(gameGrid);
    }
}

void Tetromino::moveup(TetrisGame& gameGrid) {
    if (!over) {
        clearcurr(gameGrid);

        int pivotX = position[0].first;
        int pivotY = position[0].second;

        for (int i = 1; i < 4; i++) {
            int newx = pivotX + position[i].second - pivotY;
            int newy = pivotY - position[i].first + pivotX;

            if (newx < 0 || newx >= rows || newy < 0 || newy >= cols || gameGrid.getColor(newx, newy) != background_color) {
                clearcurr(gameGrid);
                return;
            }
        }

        for (auto& xy : position) {
            int x = xy.first;
            int y = xy.second;
            xy = std::make_pair<int, int>(pivotX + y - pivotY, pivotY - x + pivotX);
        }

        drawcurr(gameGrid);
    }
}
