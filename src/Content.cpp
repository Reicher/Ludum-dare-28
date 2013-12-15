#include "Content.h"
#include <string>

//std::string path = "../"; // from debug folder
std::string path = ""; // from eclipse


Content::Content()
{
        loadTextures();
        loadSounds();
        loadMusic();
        loadFonts();
}

void Content::loadTextures()
{
	m_startScreen.loadFromFile(path + "Textures/StartScreen.png");
	m_infoScreen.loadFromFile(path + "Textures/InfoScreen.png");
	m_gameOverScreen.loadFromFile(path + "Textures/GameOverScreen.png");

	m_background1.loadFromFile(path + "Textures/Background1.png");
	m_background2.loadFromFile(path + "Textures/Background2.png");
	m_background3.loadFromFile(path + "Textures/Background3.png");

	m_playerBase.loadFromFile(path + "Textures/Player.png");

	m_money.loadFromFile(path + "Textures/Money.png");
	m_rock.loadFromFile(path + "Textures/Rock.png");

	m_playerBase.setSmooth(true);
	m_money.setSmooth(true);
	m_rock.setSmooth(true);
}

void Content::loadSounds()
{
    m_killed.loadFromFile(path + "Sounds/Stone1.wav");
    m_gotCash.loadFromFile(path + "Sounds/Money1.wav");
}

void Content::loadMusic()
{
	m_music.openFromFile(path + "Music/Music.wav");
    m_music.setLoop(true);
    m_music.setVolume(40);


}

void Content::loadFonts()
{
	m_standardFont.loadFromFile(path + "Fonts/LucidaTypewriterRegular.ttf");
}
