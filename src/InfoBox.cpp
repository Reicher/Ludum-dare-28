#include "InfoBox.h"

#include "Level.h"
#include "Content.h"
#include <cstdlib>
#include <string>

InfoBox::InfoBox(Content* content, unsigned short level)
: m_pContent(content)
, m_level(level)
, m_score(0)
, m_totalScore(0)
, m_active(true)
, m_gameOver(false)
{
	m_startScreen.setTexture(m_pContent->m_startScreen);
	m_infoScreen.setTexture(m_pContent->m_infoScreen);
	m_gameOverScreen.setTexture(m_pContent->m_gameOverScreen);
}

void InfoBox::reset(unsigned short level, int LastLevelScore)
{
	m_level = level;
	m_totalScore += LastLevelScore;
	m_score = LastLevelScore;
	m_active = true;
}

void InfoBox::draw(sf::RenderWindow* window)
{
	if(!m_active)
		return;

	if(m_gameOver)
	{
		drawGameOverInfo(window);
	}
	else if(m_level == 1)
	{
		drawStartInfo(window);
	}
	else
	{
		drawLevelEndInfo(window);
	}
}

void InfoBox::update()
{
	if(m_active)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_active = false;
			m_gameOver = false;
		}
	}
}

bool InfoBox::isActive() const
{
	return m_active;
}

void InfoBox::gameOverMan()
{
	m_active = true;
	m_gameOver = true;
}

void InfoBox::drawStartInfo(sf::RenderWindow* window)
{
	window->draw(m_startScreen);

	// Level text
	sf::Text levelText;
	levelText.setFont(m_pContent->m_standardFont);
	levelText.setString("Level: 1");
	levelText.setPosition(200, 170);
	levelText.setColor(sf::Color::Black);

	window->draw(levelText);
}

void InfoBox::drawLevelEndInfo(sf::RenderWindow* window)
{
	window->draw(m_infoScreen);

	// Level text
	sf::Text levelText;
	levelText.setFont(m_pContent->m_standardFont);
	levelText.setString("Level "
						+ std::to_string(m_level -1)
						+ " completed!\n"
						+ "\nMoney: " + std::to_string(m_score) + " $"
						+ "\nTotal: " + std::to_string(m_totalScore) + " $");

	levelText.setPosition(200, 150);
	levelText.setColor(sf::Color::Black);
	levelText.setCharacterSize(40); // in pixels, not points!

	window->draw(levelText);
}

void InfoBox::drawGameOverInfo(sf::RenderWindow* window)
{
	window->draw(m_gameOverScreen);

	// Level text
	sf::Text levelText;
	levelText.setFont(m_pContent->m_standardFont);
	levelText.setString("You died on level "
						+ std::to_string(m_level)
						+ "\nTotal useless money: " + std::to_string(m_totalScore) + " $"
						+ "\n\n(Space to restart)");

	levelText.setPosition(250, 350);
	levelText.setColor(sf::Color::Black);
	levelText.setCharacterSize(20); // in pixels, not points!

	window->draw(levelText);
}
