#include "Content.h"

Content::Content()
{
        loadTextures();
        loadSounds();
        loadMusic();
        loadFonts();
}

void Content::loadTextures()
{
	m_startScreen.loadFromFile("Textures/StartScreen.png");

	m_background1.loadFromFile("Textures/Background1.png");
	m_background2.loadFromFile("Textures/Background2.png");

	m_playerBase.loadFromFile("Textures/PlayerBase.png");
	m_playerArms.loadFromFile("Textures/PlayerArms.png");
	m_playerLegs.loadFromFile("Textures/PlayerLegs.png");

	//.setSmooth(true);

}

void Content::loadSounds()
{
	//.loadFromFile("../Sounds/.wav");
}

void Content::loadMusic()
{
	//.openFromFile("../Music/.wav");
}

void Content::loadFonts()
{
	m_standardFont.loadFromFile("Fonts/LucidaTypewriterRegular.ttf");
}
