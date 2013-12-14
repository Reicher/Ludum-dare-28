#pragma once

#include <SFML/Graphics.hpp>

class Content;

class InfoBox
{
public:
	InfoBox(Content* content, unsigned short level);
	void reset(unsigned short level, int score);

	void draw(sf::RenderWindow* window);
	void update();

	bool isActive() const;

private:
	void drawStartInfo(sf::RenderWindow* window);
	void drawLevelEndInfo(sf::RenderWindow* window);

	Content* m_pContent;
	sf::Sprite m_startScreen;
	sf::Sprite 	m_infoScreen;
	unsigned short m_level;
	int m_score;
	int m_totalScore;
	bool m_active;
};
