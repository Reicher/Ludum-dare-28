#include "Money.h"

#include <iostream>

Money::Money(Content* content,
		unsigned int value,
		Position position,
		Player* player,
		int speed)
: MovingStuff(position, player, speed)
, m_value(value)
{
	m_sprite.setTexture(content->m_money);
	m_sprite.scale(value * 0.001, value * 0.001);
}

void Money::onContact()
{
	m_dead = true;
	m_pPlayer->giveMoney(m_value);
}



