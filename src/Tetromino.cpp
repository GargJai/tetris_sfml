#include "Tetromino.hpp"

Tetromino::Tetromino(int r, int c, std::vector<std::vector<sf::Color>>& game_matrix, sf::Color bgcolor)
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
        if (game_matrix[x][y] != background_color) {
            over = true;
        }
    }

    if (!over)
        drawcurr(game_matrix);
}

void Tetromino::drawcurr(std::vector<std::vector<sf::Color>>& game_matrix) {
    for (auto& xy : position) {
        auto [x, y] = xy;
        game_matrix[x][y] = color;
    }
}

void Tetromino::clearcurr(std::vector<std::vector<sf::Color>>& game_matrix) {
    for (auto& xy : position) {
        auto [x, y] = xy;
        game_matrix[x][y] = background_color;
    }
}

void Tetromino::movedown(std::vector<std::vector<sf::Color>>& game_matrix) {
    if (!over) {
        clearcurr(game_matrix);
        for (auto& xy : position) {
            auto [x, y] = xy;
            if (x + 1 >= rows || game_matrix[x + 1][y] != background_color) {
                contact = true;
                drawcurr(game_matrix);
                return;
            }
        }

        for (auto& xy : position) {
            xy.first++;
        }

        drawcurr(game_matrix);
    }
}

void Tetromino::moveleft(std::vector<std::vector<sf::Color>>& game_matrix) {
    if (!over) {
        clearcurr(game_matrix);
        for (auto& xy : position) {
            auto [x, y] = xy;
            if (y - 1 < 0 || game_matrix[x][y - 1] != background_color) {
                drawcurr(game_matrix);
                return;
            }
        }

        for (auto& xy : position) {
            xy.second--;
        }
        drawcurr(game_matrix);
    }
}

bool Tetromino::getcontact() {
    return contact;
}

void Tetromino::moveright(std::vector<std::vector<sf::Color>>& game_matrix) {
    if (!over) {
        clearcurr(game_matrix);
        for (auto& xy : position) {
            auto [x, y] = xy;
            if (y + 1 >= cols || game_matrix[x][y + 1] != background_color) {
                drawcurr(game_matrix);
                return;
            }
        }

        for (auto& xy : position) {
            xy.second++;
        }

        drawcurr(game_matrix);
    }
}

void Tetromino::moveup(std::vector<std::vector<sf::Color>>& game_matrix) {
    if (!over) {
        clearcurr(game_matrix);

        int pivotX = position[0].first;
        int pivotY = position[0].second;

        for (int i = 1; i < 4; i++) {
            int newx = pivotX + position[i].second - pivotY;
            int newy = pivotY - position[i].first + pivotX;

            if (newx < 0 || newx >= rows || newy < 0 || newy >= cols || game_matrix[newx][newy] != background_color) {
                clearcurr(game_matrix);
                return;
            }
        }

        for (auto& xy : position) {
            int x = xy.first;
            int y = xy.second;
            xy = std::make_pair<int, int>(pivotX + y - pivotY, pivotY - x + pivotX);
        }

        drawcurr(game_matrix);
    }
}
