#include <SFML/Graphics.hpp>

#include "Content.h"

#include "Player.h"
#include "Level.h"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ludum dare #28");
    Content content;

    sf::Time dt;
    sf::Clock clock;

    Player player(&content);
    Level *level = new Level(&content, 1);

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

        // update all here
        dt = clock.restart();

        if(level->started())
        	player.update();

        level->update(dt);

        // draw everything here...
        level->draw(&window);
        player.draw(&window);

        // end the current frame
        window.display();
    }

    return 0;
}
