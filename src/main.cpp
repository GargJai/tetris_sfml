#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tetromino.hpp"
#include "grid.hpp"
#include "score.hpp"

float cellSide = 33;
int rows = 20;
int cols = 10;
sf::Color backgroundColor = sf::Color(0x000000FF);

int main() {
    TetrisGame gameGrid(rows, cols, backgroundColor, cellSide);
    Tetromino tetromino(rows, cols, gameGrid, backgroundColor);

    // Create the window with a fixed size and no resize option
    sf::RenderWindow window(
        sf::VideoMode(cols * cellSide, rows * cellSide), 
        "tetris_sfml", 
        sf::Style::Titlebar | sf::Style::Close
    );

    sf::Music themeMusic;
    if (!themeMusic.openFromFile("./assets/sounds/theme.ogg")) {
        return -1;
    }

    themeMusic.play();
    themeMusic.setVolume(4.f);

    sf::SoundBuffer rotateBuffer;
    if (!rotateBuffer.loadFromFile("./assets/sounds/rotate.ogg")) {
        return -1;
    }

    sf::Sound rotateSound;
    rotateSound.setBuffer(rotateBuffer);
    rotateSound.setVolume(25.f);

    window.setFramerateLimit(8);

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Arial.ttf")) {
        return -1;
    }

    ScoreManager scoreManager(font, cols * cellSide);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                auto code = event.key.code;
                if (code == sf::Keyboard::D || code == sf::Keyboard::Right) {
                    tetromino.moveright(gameGrid);
                }
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left) {
                    tetromino.moveleft(gameGrid);
                }
                if (code == sf::Keyboard::Space || code == sf::Keyboard::W || code == sf::Keyboard::Up) {
                    rotateSound.play();
                    tetromino.moveup(gameGrid);
                }
            }
        }

        window.clear();

        tetromino.movedown(gameGrid);

        if (tetromino.getOver()) {
            gameGrid.reset();
            tetromino.over = false;
        }

        if (tetromino.getcontact()) {
            tetromino = Tetromino(rows, cols, gameGrid, backgroundColor);
        }

        gameGrid.updateGameMatrix();
        gameGrid.createGrid(window);

        scoreManager.draw(window, gameGrid.getScore(), gameGrid.highestScore);

        window.display();
    }

    return 0;
}

