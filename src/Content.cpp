#include "Content.h"
#include <string>

//std::string DEBUG = "../";
std::string DEBUG = "";

Content::Content()
{
        loadTextures();
        loadSounds();
        loadMusic();
        loadFonts();
}

void Content::loadTextures()
{
	m_startScreen.loadFromFile(DEBUG + "Textures/StartScreen.png");
	m_infoScreen.loadFromFile(DEBUG + "Textures/InfoScreen.png");

	m_background1.loadFromFile(DEBUG + "Textures/Background1.png");
	m_background2.loadFromFile(DEBUG + "Textures/Background2.png");

	m_playerBase.loadFromFile(DEBUG + "Textures/PlayerBase.png");
	m_playerArms.loadFromFile(DEBUG + "Textures/PlayerArms.png");
	m_playerLegs.loadFromFile(DEBUG + "Textures/PlayerLegs.png");

	m_money.loadFromFile(DEBUG + "Textures/Money.png");

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
	m_standardFont.loadFromFile(DEBUG + "Fonts/LucidaTypewriterRegular.ttf");
}
