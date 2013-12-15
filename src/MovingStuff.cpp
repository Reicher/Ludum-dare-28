#include "MovingStuff.h"

#include <iostream>

MovingStuff::MovingStuff(Position position,
		Player* player,
		int speed)
: m_position(position)
, m_pPlayer(player)
, m_speed(speed)
, m_dead(false)
, m_offset(75.0)
{
	m_sprite.setOrigin(m_offset, m_offset);

	switch(position)
	{
	case Up:
		m_sprite.setPosition(800+m_offset, 150+m_offset);
		break;
	case Middle:
		m_sprite.setPosition(800+m_offset, 300+m_offset);
		break;
	case Down:
	default:
		m_sprite.setPosition(800+m_offset, 450+m_offset);
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

	if(m_sprite.getPosition().x < -75)
		m_dead = true;

	//check for player
	if (	m_pPlayer->getPosition() == m_position
			&& m_sprite.getPosition().x < 120
			&& m_sprite.getPosition().x > 0 )
	{
		onContact();
	}
}

bool MovingStuff::isDead() const
{
	return m_dead;
}

