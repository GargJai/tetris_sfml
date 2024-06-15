#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include <SFML/Graphics.hpp>

class ScoreManager {
public:
    ScoreManager(const sf::Font& font, float windowWidth);
    void draw(sf::RenderWindow& window, int score, int highestScore);

private:
    sf::Text scoreText;
    sf::Text highestScoreText;
};

#endif // SCOREMANAGER_HPP

