#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <SFML/Graphics.hpp>
#include <vector>

class TetrisGame {
public:
    TetrisGame(int rows, int cols, sf::Color backgroundColor, float cellSide);

    void updateGameMatrix();
    void createGrid(sf::RenderWindow& window);
    void reset(); 
    sf::Color getColor(int r, int c); 
    void setColor(int r, int c, sf::Color); 

private:
    std::vector<std::vector<sf::Color>> gameMatrix;
    int rows;
    int cols;
    sf::Color backgroundColor;
    float cellSide;
};

#endif // TETRISGAME_H
