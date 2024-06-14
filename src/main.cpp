#include <iostream> 
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tetromino.hpp"
#include "grid.hpp"

float cellSide = 33; 
int rows = 20; 
int cols = 10; 
sf::Color backgroundColor = sf::Color(0x000000FF); 

int main() {
    TetrisGame gameGrid(rows, cols, backgroundColor, cellSide);
    Tetromino tetromino(rows, cols, gameGrid, backgroundColor);
    sf::RenderWindow window(sf::VideoMode(cols * cellSide, rows * cellSide), "Terrace"); 

    sf::Music theme_music; 
    if (!theme_music.openFromFile("./assets/sounds/theme.ogg")) {
        return -1; 
    }

    theme_music.play(); 
    theme_music.setVolume(4.f); 


    sf::SoundBuffer gunshot_buffer; 
    gunshot_buffer.loadFromFile("./assets/sounds/rotate.ogg"); 

    sf::Sound gunshot_sound; 
    gunshot_sound.setBuffer(gunshot_buffer); 
    gunshot_sound.setVolume(30.f); 

    window.setFramerateLimit(10); 

    while (window.isOpen()) {
        sf::Event event; 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); 
            }
            else if (event.type == sf::Event::KeyPressed) {
                auto code = event.key.code; 
                if (code == sf::Keyboard::D || code == sf::Keyboard::Right) {
                    tetromino.moveright(gameGrid); 
                }
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left) {
                    tetromino.moveleft(gameGrid); 
                }
                if (code == sf::Keyboard::Space || code == sf::Keyboard::W || code == sf::Keyboard::Up) {
                    gunshot_sound.play(); 
                    tetromino.moveup(gameGrid); 
                }
            }
		}

        window.clear();  

        tetromino.movedown(gameGrid);  
        if (tetromino.getcontact()) {
            tetromino = Tetromino(rows, cols, gameGrid, backgroundColor); 
        }
        
        gameGrid.updateGameMatrix(); 
        gameGrid.createGrid(window); 

        window.display(); 
    }

    return 0;
}
