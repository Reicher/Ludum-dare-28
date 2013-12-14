#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Content.h"
#include "Player.h"

class MovingStuff
{
public:
	MovingStuff(Position position,
				Player* player,
				int speed);

	void draw(sf::RenderWindow* window);
	void update(sf::Time dt);
	bool isDead() const;

	virtual void onContact() = 0;

protected:
	Content* m_pContent;

	sf::Sprite m_sprite;
	Position m_position;
	Player* m_pPlayer;
	double m_speed;
	bool m_dead;
};
