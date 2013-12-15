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
, m_moneyRatio(1.0 - (levelNr *0.1))
, m_started(false)
, m_ended(false)
, m_levelTime(sf::seconds(10.f))
, m_pPlayer(player)
{

	m_moneyRatio = m_moneyRatio < 0.2 ? 0.2 : m_moneyRatio;

	m_upperTimeSinceLastElement.restart();
	m_middleTimeSinceLastElement.restart();
	m_lowerTimeSinceLastElement.restart();

	m_upperTimeUntilNextElement = sf::seconds(rand() % 2);
	m_middleTimeUntilNextElement = sf::seconds(rand() % 2);
	m_lowerTimeUntilNextElement = sf::seconds(rand() % 2);

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

	for(Rock* rock : m_rocks)
	{
		rock->draw(window);
	}
}

void Level::update(sf::Time dt)
{
	// before level is started
	if(!m_started || m_pPlayer->isDead())
	{
		return;
	}

	if (m_levelClock.getElapsedTime() >= m_levelTime)
		m_ended = true;

	//adding things to lanes
	bool addStuff = true;
	Position position;
	if(m_upperTimeSinceLastElement.getElapsedTime() > m_upperTimeUntilNextElement)
	{
		m_upperTimeSinceLastElement.restart();
		m_upperTimeUntilNextElement = sf::seconds(((float)(rand() % 50)*0.1f)+1.0f);
		position = Position::Up;
	}
	else if(m_middleTimeSinceLastElement.getElapsedTime() > m_middleTimeUntilNextElement)
	{
		m_middleTimeSinceLastElement.restart();
		m_middleTimeUntilNextElement = sf::seconds(((float)(rand() % 50)*0.1f)+1.0f);
		position = Middle;
	}
	else if(m_lowerTimeSinceLastElement.getElapsedTime() > m_lowerTimeUntilNextElement)
	{
		m_lowerTimeSinceLastElement.restart();
		m_lowerTimeUntilNextElement = sf::seconds(((float)(rand() % 50)*0.1f)+1.0f);
		position = Down;
	}
	else
		addStuff = false;

	if( addStuff )
	{
		if((rand() % 100) < (m_moneyRatio * 100.0))
		{ //money!
			unsigned int value = rand() % 700 + 300;
			m_money.push_back(new Money( m_pContent, value, position, m_pPlayer, m_levelSpeed));
		}
		else // Rocks =/
			m_rocks.push_back(new Rock( m_pContent, position, m_pPlayer, m_levelSpeed));
	}

	updateBackground(dt);
	updateMoney(dt);
	updateRocks(dt);
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

bool isDead (MovingStuff* m) { return m->isDead(); }

void Level::updateMoney(sf::Time dt)
{
	std::list<Money*>::iterator mEnd;
	mEnd = std::remove_if (m_money.begin(), m_money.end(), isDead);
	m_money.assign(m_money.begin(), mEnd);

	for(Money* cash : m_money)
	{
		cash->update(dt);
	}
}

void Level::updateRocks(sf::Time dt)
{
	std::list<Rock*>::iterator mEnd;
	mEnd = std::remove_if (m_rocks.begin(), m_rocks.end(), isDead);
	m_rocks.assign(m_rocks.begin(), mEnd);

	for(Rock* stone : m_rocks)
	{
		stone->update(dt);
	}
}
Level::~Level()
{
	m_money.clear();
	m_rocks.clear();
	m_scrollingBackground.clear();
}

