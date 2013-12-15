#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Enums.h"

class Content;

class Player
{
public:
	Player(Content* content);

	void draw(sf::RenderWindow* window);
	void update();
	Position getPosition() const;
	bool isDead();
	void kill();
	void resurect();

	void giveMoney(unsigned int value);
	unsigned int takeAllMoney();

private:
	void setPosition(sf::Vector2<int> pos);

	sf::Sprite m_spriteBase;
	sf::Sprite m_spriteArms;
	sf::Sprite m_spriteLegs;

	sf::Sprite m_moneyBag;

	Content* m_pContent;
	Position m_position;

	unsigned int m_money;
	bool m_dead;

	//sounds
	sf::Sound m_killed;
	sf::Sound m_gotCash;
};
