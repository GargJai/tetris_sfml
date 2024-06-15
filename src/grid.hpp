#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class TetrisGame {
public:
    TetrisGame(int rows, int cols, sf::Color backgroundColor, float cellSide);

    void updateGameMatrix();
    void createGrid(sf::RenderWindow& window);
    void reset(); 
    sf::Color getColor(int r, int c); 
    void setColor(int r, int c, sf::Color); 
    void setOver(bool flg); 
    int getScore(); 
    int highestScore = 0;

private:
    int score = 0; 
    bool over = false; 
    std::vector<std::vector<sf::Color>> gameMatrix;
    int rows;
    int cols;
    sf::Color backgroundColor;
    float cellSide;
};

#endif // TETRISGAME_H
