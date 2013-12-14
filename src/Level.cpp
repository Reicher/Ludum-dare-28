#include "Level.h"
#include "Content.h"
#include <cstdlib>
#include <string>

Level::Level(Content* content, unsigned short level)
: m_pContent(content)
, m_level(level)
, m_levelSpeed(100.0 + (level * 50))
, m_started(false)
{
	m_startScreen.setTexture(m_pContent->m_startScreen);

	m_background1.setTexture(m_pContent->m_background1);
	m_background2.setTexture(m_pContent->m_background2);

	sf::Sprite newSprite = m_background1;
	newSprite.setPosition(0, 0);
	m_scrollingBackground.push_back(newSprite);
}

void Level::draw(sf::RenderWindow* window)
{
	std::list<sf::Sprite>::iterator sprite = m_scrollingBackground.begin();
	window->draw(*sprite);
	sprite++;
	window->draw(*sprite);

	//start screen
	if(!m_started)
	{
		window->draw(m_startScreen);

		// Level text
		sf::Text levelNumber;
		levelNumber.setFont(m_pContent->m_standardFont);
		levelNumber.setString("Level: " + std::to_string(m_level));
		levelNumber.setPosition(200, 170);
		levelNumber.setColor(sf::Color::Black);
		levelNumber.setCharacterSize(40); // in pixels, not points!

		window->draw(levelNumber);
	}
}

void Level::update(sf::Time dt)
{
	if(!m_started)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			m_started = true;

		return;
	}

	updateBackground(dt);


}

bool Level::started() const
{
	return m_started;
}

void Level::updateBackground(sf::Time dt)
{
	// UGLY
	while(m_scrollingBackground.size() < 2)
	{
		int toAdd = rand() % 2 + 1;
		sf::Sprite newSprite;
		switch(toAdd)
		{
			case 1:
				newSprite = m_background1;
				break;
			case 2:
				newSprite = m_background2;
				break;
		}
		newSprite.setPosition(800, 0);
		m_scrollingBackground.push_back(newSprite);
	}

	// Move background sprites
	std::list<sf::Sprite>::iterator sprite = m_scrollingBackground.begin();
	sprite->move(-m_levelSpeed * dt.asSeconds(), 0);
	sprite++;
	sprite->move(-m_levelSpeed * dt.asSeconds(), 0);

	// Remove used sprite
	if(m_scrollingBackground.begin()->getPosition().x < -800)
		m_scrollingBackground.pop_front();
}
