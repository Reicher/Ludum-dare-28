#include "Money.h"

#include <iostream>

Money::Money(Content* content,
		unsigned int value,
		Position position,
		Player* player,
		int speed)
: m_pContent(content)
, m_value(value)
, m_position(position)
, m_pPlayer(player)
, m_speed(speed)
{
	m_sprite.setTexture(m_pContent->m_money);
	m_sprite.scale(0.75, 0.75);

	switch(position)
	{
	case Up:
		m_sprite.setPosition(800, 150);
		break;
	case Middle:
		m_sprite.setPosition(800, 300);
		break;
	case Down:
	default:
		m_sprite.setPosition(800, 450);
		break;
	}
}

unsigned int Money::getValue() const
{
	return m_value;
}

Position Money::getPosition() const
{
	return m_position;
}

void Money::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void Money::update(sf::Time dt)
{
	m_sprite.move(-m_speed * dt.asSeconds(), 0.0f);
}

