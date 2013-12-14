#include "MovingStuff.h"

#include <iostream>

MovingStuff::MovingStuff(Position position,
		Player* player,
		int speed)
: m_position(position)
, m_pPlayer(player)
, m_speed(speed)
, m_dead(false)
{
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

void MovingStuff::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void MovingStuff::update(sf::Time dt)
{
	m_sprite.move(-m_speed * dt.asSeconds(), 0.0f);

	//check for player
	if (m_pPlayer->getPosition() == m_position
			&& m_sprite.getPosition().x < 120
			&& m_sprite.getPosition().x > -100 )
	{
		onContact();
		m_dead = true;
	}
}

bool MovingStuff::isDead() const
{
	return m_dead;
}

