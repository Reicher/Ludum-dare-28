#pragma once

#include <SFML/Graphics.hpp>
#include "Content.h"
#include "Player.h"
#include "MovingStuff.h"


class Rock : public MovingStuff
{
public:
	Rock(  Content* content,
			Position position,
			Player* player,
			int speed);

	void onContact();
};
