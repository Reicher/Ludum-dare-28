#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

#include "Money.h"

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
	void drawInfoScreen(sf::RenderWindow* window);

	std::list<sf::Sprite> m_scrollingBackground;


	sf::Sprite m_background1;
	sf::Sprite m_background2;

	Content* m_pContent;
	unsigned short m_levelNr;
	double m_levelSpeed;
	bool m_started, m_ended;

	sf::Clock m_levelClock;
	sf::Time m_levelTime;

	//Money
	std::list<Money*> m_money;
	sf::Clock m_timeSinceLastMoney;
	sf::Time m_nextMoney;

	Player* m_pPlayer;

};
