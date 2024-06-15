#include "score.hpp"

ScoreManager::ScoreManager(const sf::Font& font, float windowWidth) {
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(0xF4B71DFF));
    scoreText.setPosition(10, 10);

    highestScoreText.setFont(font);
    highestScoreText.setCharacterSize(24);
    highestScoreText.setFillColor(sf::Color(0xF4B71DFF));
    highestScoreText.setPosition(windowWidth - 200, 10);
}

void ScoreManager::draw(sf::RenderWindow& window, int score, int highestScore) {
    scoreText.setString("Score: " + std::to_string(score));
    highestScoreText.setString("Highest Score: " + std::to_string(highestScore));
    
    window.draw(scoreText);
    window.draw(highestScoreText);
}
