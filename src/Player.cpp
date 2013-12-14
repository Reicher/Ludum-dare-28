#include "Player.h"
#include "Content.h"

Player::Player(Content* content)
: m_pContent(content)
, m_position(Middle)
{
	// Base
    m_spriteBase.setTexture(m_pContent->m_playerBase);
    m_spriteBase.setPosition(0, 300);

    // Arms and sword
    m_spriteArms.setTexture(m_pContent->m_playerArms);
    m_spriteArms.setPosition(0, 300);

    // Running legs!
    m_spriteLegs.setTexture(m_pContent->m_playerLegs);
    m_spriteLegs.setPosition(0, 300);
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(m_spriteBase);
	window->draw(m_spriteArms);
	window->draw(m_spriteLegs);
}

void Player::update()
{
	// Player movement up/down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		setPosition(sf::Vector2<int>(0, 150));
		m_position = Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		setPosition(sf::Vector2<int>(0, 450));
		m_position = Down;
	}
	else
	{
		setPosition(sf::Vector2<int>(0, 300));
		m_position = Middle;
	}
}

Position Player::getPosition() const
{
	return m_position;
}

void Player::setPosition(sf::Vector2<int> pos)
{
	m_spriteBase.setPosition(pos.x, pos.y);
	m_spriteArms.setPosition(pos.x, pos.y);
	m_spriteLegs.setPosition(pos.x, pos.y);
}
