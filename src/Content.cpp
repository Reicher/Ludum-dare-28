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
	m_gameOverScreen.loadFromFile(DEBUG + "Textures/GameOverScreen.png");

	m_background1.loadFromFile(DEBUG + "Textures/Background1.png");
	m_background2.loadFromFile(DEBUG + "Textures/Background2.png");

	m_playerBase.loadFromFile(DEBUG + "Textures/PlayerBase.png");
	m_playerArms.loadFromFile(DEBUG + "Textures/PlayerArms.png");
	m_playerLegs.loadFromFile(DEBUG + "Textures/PlayerLegs.png");

	m_money.loadFromFile(DEBUG + "Textures/Money.png");
	m_rock.loadFromFile(DEBUG + "Textures/Rock.png");

	//.setSmooth(true);

}

void Content::loadSounds()
{
    m_killed.loadFromFile(DEBUG + "Sounds/Stone1.wav");
    m_gotCash.loadFromFile(DEBUG + "Sounds/Money1.wav");
}

void Content::loadMusic()
{
	m_music.openFromFile(DEBUG + "Music/Music.wav");
    m_music.setLoop(true);
    m_music.setVolume(50);


}

void Content::loadFonts()
{
	m_standardFont.loadFromFile(DEBUG + "Fonts/LucidaTypewriterRegular.ttf");
}
