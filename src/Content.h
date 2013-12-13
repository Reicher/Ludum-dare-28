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

        //sf::Texture

        //sf::SoundBuffer

        //sf::Music

        sf::Font m_standardFont;
};
