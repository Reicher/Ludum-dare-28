#include "Rock.h"

#include <iostream>

Rock::Rock(Content* content,
		Position position,
		Player* player,
		int speed)
: MovingStuff(position, player, speed)
{
	m_sprite.setTexture(content->m_rock);
}

void Rock::onContact()
{
	m_pPlayer->kill();
}



