#include "grid.hpp"

TetrisGame::TetrisGame(int rows, int cols, sf::Color backgroundColor, float cellSide)
    : rows(rows), cols(cols), backgroundColor(backgroundColor), cellSide(cellSide),
      gameMatrix(rows, std::vector<sf::Color>(cols, backgroundColor)) {}

void TetrisGame::updateGameMatrix() {
    std::vector<std::vector<sf::Color>> lgameMatrix(rows, std::vector<sf::Color>(cols, backgroundColor));
    int currRow = rows - 1;

    for (int i = currRow; i >= 0; i--) {
        int cnt = 0;
        for (int j = 0; j < cols; j++) {
            if (gameMatrix[i][j] != backgroundColor) cnt++;
        }

        if (cnt != cols) {
            for (int j = 0; j < cols; j++) {
                lgameMatrix[currRow][j] = gameMatrix[i][j];
            }
            currRow--;
        }
        else {
            score += 10; 
            highestScore = std::max(highestScore, score); 
        }
    }

    gameMatrix = lgameMatrix;
}

void TetrisGame::createGrid(sf::RenderWindow& window) {
    sf::RectangleShape cell;
    cell.setSize({cellSide, cellSide});

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (gameMatrix[i][j] != backgroundColor) {
                cell.setOutlineThickness(-2.f);
                cell.setOutlineColor(sf::Color::Black);
            } else {
                cell.setOutlineColor(backgroundColor);
            }
            cell.setFillColor(gameMatrix[i][j]);
            cell.setPosition(j * cellSide, i * cellSide);
            window.draw(cell);
        }
    }
}

void TetrisGame::reset() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gameMatrix[i][j] = backgroundColor; 
        }
    }
}

sf::Color TetrisGame::getColor(int r, int c) {
    return gameMatrix[r][c]; 
} 

void TetrisGame::setColor(int r, int c, sf::Color clr) {
    gameMatrix[r][c] = clr; 
}

void TetrisGame::setOver(bool flg) {
    over = flg; 
}

int TetrisGame::getScore() {
    return score; 
}
