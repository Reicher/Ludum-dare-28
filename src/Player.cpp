#include "Player.h"
#include "Content.h"

Player::Player(Content* content)
: m_pContent(content)
, m_position(Middle)
, m_money(0)
, m_dead(false)
, m_killed(content->m_killed)
, m_gotCash(content->m_gotCash)
, m_updateFreq(sf::seconds(0.1f))
, m_animationNr(0)
{
	m_animationClock.restart();

	m_player.setTexture(m_pContent->m_playerBase);
	m_player.setPosition(0, 300);
	m_player.setTextureRect (sf::IntRect(0, 0, 150, 150));

    // BAG OF MONEEY
    m_moneyBag.setOrigin(65.0, 75.0);
    m_moneyBag.setTexture(m_pContent->m_money);
    m_moneyBag.setPosition(90, 350); //kinda
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(m_player);

	if(m_money > 0){
		window->draw(m_moneyBag);
	}
}

void Player::update()
{
	//Player animation
	if(m_animationClock.getElapsedTime() > m_updateFreq)
	{
		m_animationNr++;
		m_animationNr = m_animationNr % 4;

		sf::Vector2<int> from(m_animationNr*150, 0);
		sf::Vector2<int> to(m_animationNr+1*150, 150);

		m_player.setTextureRect(sf::IntRect(from.x, from.y, to.x, to.y));

		m_animationClock.restart();
	}

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
	m_player.setPosition(pos.x, pos.y);
    m_moneyBag.setPosition(pos.x+30.0, pos.y+85.0);
}

void Player::giveMoney(unsigned int value)
{
	m_money = value;
	m_moneyBag.setScale(m_money * 0.001, m_money * 0.001);

	// money sound
	m_gotCash.setVolume(value*0.1);
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
