#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Content.h"
#include "Player.h"



class Money
{
public:
	Money(  Content* content,
			unsigned int value,
			Position position,
			Player* player,
			int speed);

	unsigned int getValue() const ;
	Position getPosition() const;
	void draw(sf::RenderWindow* window);
	void update(sf::Time dt);

	bool isDead() const;

private:
	Content* m_pContent;

	sf::Sprite m_sprite;

	unsigned int m_value;

	Position m_position;
	Player* m_pPlayer;
	double m_speed;
	bool m_dead;
};
