#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Content
{
public:
        Content();
        void loadTextures();
        void loadSounds();
        void loadMusic();
        void loadFonts();

        sf::Texture m_startScreen;
        sf::Texture m_infoScreen;
        sf::Texture m_gameOverScreen;

        sf::Texture m_background1;
        sf::Texture m_background2;

        sf::Texture m_playerBase;

        sf::Texture m_money;
        sf::Texture m_rock;

        sf::SoundBuffer m_killed;
        sf::SoundBuffer m_gotCash;

        sf::Music m_music;

        sf::Font m_standardFont;
};
