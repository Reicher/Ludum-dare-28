#include "Player.h"
#include "Content.h"

#include <iostream>

Player::Player(Content* content)
: m_pContent(content)
, m_position(Middle)
, m_money(0)
, m_dead(false)
, m_killed(content->m_killed)
, m_gotCash(content->m_gotCash)
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

    // BAG OF MONEEY
    m_moneyBag.setOrigin(75.0, 75.0);
    m_moneyBag.setTexture(m_pContent->m_money);
    m_moneyBag.setPosition(90, 350); //kinda
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(m_spriteBase);
	window->draw(m_spriteArms);
	window->draw(m_spriteLegs);

	if(m_money > 0){
		window->draw(m_moneyBag);
	}
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
    m_moneyBag.setPosition(pos.x+75.0, pos.y+75.0);
}

void Player::giveMoney(unsigned int value)
{
	m_money = value;
	m_moneyBag.setScale(m_money * 0.001, m_money * 0.001);

	// money sound
	if(m_gotCash.getStatus() == sf::SoundSource::Status::Playing)
		m_gotCash.stop();

	m_gotCash.play();
}

unsigned int Player::takeAllMoney()
{
	unsigned int money = m_money;
	m_money = 0;
	m_moneyBag.setScale(1.0, 1.0);
	return money;
}

bool Player::isDead()
{
	return m_dead;
}

void Player::kill()
{
	m_dead = true;
	m_money = 0;

	m_killed.play();
}

void Player::resurect()
{
	m_dead = false;
}
