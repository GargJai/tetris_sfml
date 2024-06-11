#include <iostream> 
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tetromino.hpp"

float CELL_SIDE = 33; 
int ROWS = 20; 
int COLS = 10; 
sf::Color background_color = sf::Color(0x000000FF); 
std::vector<std::vector<sf::Color>> game_matrix(ROWS, std::vector<sf::Color>(COLS, background_color)); 
sf::Music background_music; 

void update_game_matrix() {
    std::vector<std::vector<sf::Color>> l_game_matrix(ROWS, std::vector<sf::Color>(COLS, background_color)); 
    int curr_row = ROWS - 1; 

    for (int i = ROWS - 1; i >= 0; i--) {
        int cnt = 0; 
        for (int j = 0; j < COLS; j++) {
            if (game_matrix[i][j] != background_color) cnt++; 
        }

        if (cnt != COLS) {
            for (int j = 0; j < COLS; j++) {
                l_game_matrix[curr_row][j] = game_matrix[i][j]; 
            }
            curr_row--;  
       }
    }

    game_matrix = l_game_matrix; 
    return; 
}

void create_grid(sf::RenderWindow & window) {
    sf::RectangleShape cell; 
	cell.setSize({CELL_SIDE, CELL_SIDE}); 

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (game_matrix[i][j] != background_color) {
                cell.setOutlineThickness(-2.f); 
                cell.setOutlineColor(sf::Color::Black); 
            }
            else {
                cell.setOutlineColor(background_color); 
            }
            cell.setFillColor(game_matrix[i][j]); 
            cell.setPosition(j * CELL_SIDE , i * CELL_SIDE); 
            window.draw(cell); 
        }
    }
}

int main() {
    Tetromino tetromino(ROWS, COLS, game_matrix, background_color);
    sf::RenderWindow window(sf::VideoMode(COLS * CELL_SIDE, ROWS * CELL_SIDE), "Terrace"); 

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
                    tetromino.moveright(game_matrix); 
                }
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left) {
                    tetromino.moveleft(game_matrix); 
                }
                if (code == sf::Keyboard::Space || code == sf::Keyboard::W || code == sf::Keyboard::Up) {
                    gunshot_sound.play(); 
                    tetromino.moveup(game_matrix); 
                }
            }
		}

        window.clear();  

        tetromino.movedown(game_matrix);  
        if (tetromino.getcontact()) {
            tetromino = Tetromino(ROWS, COLS, game_matrix, background_color); 
        }
        
        update_game_matrix(); 
        create_grid(window); 

        window.display(); 
    }

    return 0;
}
