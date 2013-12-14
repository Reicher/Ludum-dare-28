#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Content;

enum Position
{
	Up = 0,
	Middle,
	Down

};

class Player
{
public:
	Player(Content* content);

	void draw(sf::RenderWindow* window);
	void update();
	Position getPosition() const;

private:
	void setPosition(sf::Vector2<int> pos);

	sf::Sprite m_spriteBase;
	sf::Sprite m_spriteArms;
	sf::Sprite m_spriteLegs;

	Content* m_pContent;
	Position m_position;
};
