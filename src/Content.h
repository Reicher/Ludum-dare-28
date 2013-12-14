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

        sf::Texture m_background1;
        sf::Texture m_background2;

        sf::Texture m_playerBase;
        sf::Texture m_playerArms;
        sf::Texture m_playerLegs;

        //sf::SoundBuffer

        //sf::Music

        sf::Font m_standardFont;
};
