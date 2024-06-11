#ifndef TETROMINO_H
#define TETROMINO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib> 

const sf::Color COLORS[7] = {
    sf::Color(0xFF6347FF),  // Carrot Orange
    sf::Color(0x42A5F5FF),  // Sky Blue
    sf::Color(0xFFD700FF),  // Gold Yellow
    sf::Color(0x66BB6AFF),  // Lime Green
    sf::Color(0xFF69B4FF),  // Hot Pink
    sf::Color(0xBA68C8FF),  // Violet Purple
    sf::Color(0xF06292FF)   // Salmon Pink
};

const int POSITIONS[7][4][2] = {
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}},
    {{2, 4}, {0, 5}, {1, 5}, {2, 5}},
    {{0, 4}, {1, 4}, {0, 5}, {1, 5}},
    {{1, 4}, {2, 4}, {0, 5}, {1, 5}},
    {{1, 4}, {0, 5}, {1, 5}, {2, 5}},
    {{0, 4}, {1, 4}, {1, 5}, {2, 5}},
};

class Tetromino {
public:
    std::vector<std::pair<int, int>> position{4};
    sf::Color color;
    bool contact = false;
    bool over = false;
    int rows;
    int cols;
    sf::Color background_color;

    Tetromino(int r, int c, std::vector<std::vector<sf::Color>> &game_matrix, sf::Color bgcolor);
    void drawcurr(std::vector<std::vector<sf::Color>> &game_matrix);
    void clearcurr(std::vector<std::vector<sf::Color>> &game_matrix);
    void movedown(std::vector<std::vector<sf::Color>> &game_matrix);
    void moveleft(std::vector<std::vector<sf::Color>> &game_matrix);
    void moveright(std::vector<std::vector<sf::Color>> &game_matrix);
    void moveup(std::vector<std::vector<sf::Color>> &game_matrix);
    bool getcontact();
};

#endif // TETROMINO_H
