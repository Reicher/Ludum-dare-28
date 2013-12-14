#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

class Content;

class Level
{
public:
	Level(Content* content, unsigned short level);

	void draw(sf::RenderWindow* window);
	void update(sf::Time dt);
	bool started() const;

private:
	void updateBackground(sf::Time dt);

	std::list<sf::Sprite> m_scrollingBackground;

	sf::Sprite m_startScreen;

	sf::Sprite m_background1;
	sf::Sprite m_background2;

	Content* m_pContent;
	unsigned short m_level;
	double m_levelSpeed;
	bool m_started;
};
