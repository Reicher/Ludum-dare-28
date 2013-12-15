#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

#include "Money.h"
#include "Rock.h"

class Content;
class Player;

class Level
{
public:
	Level(Content* content, unsigned short levelNr, Player* player);
	~Level();

	void draw(sf::RenderWindow* window);
	void update(sf::Time dt);

	void start();
	bool isStarted() const;
	bool isEnded() const;

private:
	void updateBackground(sf::Time dt);
	void updateMoney(sf::Time dt);
	void updateRocks(sf::Time dt);

	std::list<sf::Sprite> m_scrollingBackground;

	sf::Sprite m_background1;
	sf::Sprite m_background2;

	Content* m_pContent;
	unsigned short m_levelNr;
	double m_levelSpeed;
	double m_moneyRatio;
	bool m_started, m_ended;

	sf::Clock m_levelClock;
	sf::Time m_levelTime;

	// upper lane
	sf::Clock m_upperTimeSinceLastElement;
	sf::Time m_upperTimeUntilNextElement;

	//middle lane
	sf::Clock m_middleTimeSinceLastElement;
	sf::Time m_middleTimeUntilNextElement;

	//lower lane
	sf::Clock m_lowerTimeSinceLastElement;
	sf::Time m_lowerTimeUntilNextElement;

	//Money
	std::list<Money*> m_money;

	//Rocks
	std::list<Rock*> m_rocks;

	Player* m_pPlayer;

};
