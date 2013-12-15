#pragma once

#include <SFML/Graphics.hpp>
#include "Content.h"
#include "Player.h"
#include "MovingStuff.h"


class Money : public MovingStuff
{
public:
	Money(  Content* content,
			unsigned int value,
			Position position,
			Player* player,
			int speed);

	unsigned int getValue() const ;

	void onContact();

private:
	unsigned int m_value;
};
