#include "Level.h"
#include "Content.h"
#include <cstdlib>
#include <string>
#include "Player.h"
#include <iostream>

Level::Level(Content* content, unsigned short levelNr, Player* player)
: m_pContent(content)
, m_levelNr(levelNr)
, m_levelSpeed(100.0 + (double)(levelNr * 50))
, m_started(false)
, m_ended(false)
, m_levelTime(sf::seconds(10.f))
, m_nextMoney(sf::seconds(rand() % 5))
, m_pPlayer(player)
{
	m_timeSinceLastMoney.restart();

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

	for(Money* cash : m_money)
	{
		cash->draw(window);
	}
}

void Level::update(sf::Time dt)
{
	// before level is started
	if(!m_started)
	{
		return;
	}

	if (m_levelClock.getElapsedTime() >= m_levelTime)
		m_ended = true;

	// Adding enemies, money and stuff
	if(m_timeSinceLastMoney.getElapsedTime() > m_nextMoney)
	{
		Position pos = static_cast<Position>(rand() % 2 + 0);
		unsigned int value = rand() % 1000 + 100;
		m_money.push_back(new Money( m_pContent, value, pos, m_pPlayer, m_levelSpeed));
		m_timeSinceLastMoney.restart();
		m_nextMoney = sf::seconds(rand() % 5);
	}

	for(Money* cash : m_money)
	{
		cash->update(dt);
	}

	updateBackground(dt);
}

bool Level::isStarted() const
{
	return m_started;
}

void Level::start()
{
	m_levelClock.restart();
	m_started = true;
}

bool Level::isEnded() const
{
	return m_ended;
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

Level::~Level()
{
	m_money.clear();
	m_scrollingBackground.clear();
}

