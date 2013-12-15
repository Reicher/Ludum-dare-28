#include <SFML/Graphics.hpp>

#include "Content.h"

#include "Player.h"
#include "Level.h"
#include "InfoBox.h"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Frenzy forest finances");
    Content content;

    sf::Time dt;
    sf::Clock clock;

    Player player(&content);
    unsigned short levelNr = 1;
    Level *level = new Level(&content, levelNr, &player);
    InfoBox infoBox = InfoBox(&content, levelNr);

    // background music
    content.m_music.play();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if ( event.type == sf::Event::Closed
                 || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
            	window.close();
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        if(player.isDead())
        {
        	infoBox.gameOverMan();
        	levelNr = 1;
        	delete level;
        	level = new Level(&content, levelNr, &player);
        	player.resurect();
        }

        // if infobox is gone and game have not started
        if(!infoBox.isActive() && !level->isStarted() )
        {
          	level->start();

        }
        else if( level->isEnded() )
        {
        	delete level;
        	levelNr++;
        	level = new Level(&content, levelNr, &player);
        	infoBox.reset(levelNr, player.takeAllMoney());
        }


        // update all here
        dt = clock.restart();

        if( !level->isStarted() )
        	infoBox.update();
        else if(level->isStarted())
        {
            level->update(dt);
            player.update();
        }

        // draw everything here...
        level->draw(&window);
        player.draw(&window);
    	infoBox.draw(&window);

        // end the current frame
        window.display();
    }

    return 0;
}
