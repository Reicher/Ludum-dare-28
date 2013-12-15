#include "Level.h"
#include "Content.h"
#include <cstdlib>
#include <string>
#include "Player.h"
#include <iostream>

Level::Level(Content* content, unsigned short levelNr, Player* player)
: m_pContent(content)
, m_levelNr(levelNr)
, m_levelSpeed(130.0 + (double)(levelNr * 50))
, m_moneyRatio(0.9 - (levelNr *0.1))
, m_started(false)
, m_ended(false)
, m_levelTime(sf::seconds(15.f))
, m_pPlayer(player)
, m_stonesInARow(0)
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
	m_background3.setTexture(m_pContent->m_background3);

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

	for(MovingStuff* stuff : m_movingStuff)
	{
		stuff->draw(window);
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
	int rand_k = 20 / ((double)m_levelNr*0.3);

	if(m_upperTimeSinceLastElement.getElapsedTime() > m_upperTimeUntilNextElement)
	{
		m_upperTimeSinceLastElement.restart();
		m_upperTimeUntilNextElement = sf::seconds(((double)(rand() % rand_k) *0.1)+1.0);
		position = Position::Up;
	}
	else if(m_middleTimeSinceLastElement.getElapsedTime() > m_middleTimeUntilNextElement)
	{
		m_middleTimeSinceLastElement.restart();
		m_middleTimeUntilNextElement = sf::seconds(((double)(rand() % rand_k) *0.1)+1.0);
		position = Middle;
	}
	else if(m_lowerTimeSinceLastElement.getElapsedTime() > m_lowerTimeUntilNextElement)
	{
		m_lowerTimeSinceLastElement.restart();
		m_lowerTimeUntilNextElement =sf::seconds(((double)(rand() % rand_k) *0.1)+1.0);
		position = Down;
	}
	else
		addStuff = false;

	if( addStuff )
	{
		if((rand() % 100) < (m_moneyRatio * 100.0))
		{ //money!
			unsigned int value = rand() % 700 + 300;
			m_movingStuff.push_back(new Money( m_pContent, value, position, m_pPlayer, m_levelSpeed));
			m_stonesInARow = 0;
		}
		else if(m_stonesInARow <= 3)// Rocks =/
		{
			m_movingStuff.push_back(new Rock( m_pContent, position, m_pPlayer, m_levelSpeed));
			m_stonesInARow++;
		}
	}

	updateBackground(dt);
	updateMovingStuff(dt);
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
		int toAdd = rand() % 3 + 1;
		sf::Sprite newSprite;
		switch(toAdd)
		{
			case 1:
				newSprite = m_background1;
				break;
			case 2:
				newSprite = m_background2;
				break;
			case 3:
				newSprite = m_background3;
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

void Level::updateMovingStuff(sf::Time dt)
{
	std::list<MovingStuff*>::iterator mEnd;
	mEnd = std::remove_if (m_movingStuff.begin(), m_movingStuff.end(), isDead);
	m_movingStuff.assign(m_movingStuff.begin(), mEnd);

	for(MovingStuff* cash : m_movingStuff)
	{
		cash->update(dt);
	}
}

Level::~Level()
{
	m_movingStuff.clear();
	m_scrollingBackground.clear();
}

