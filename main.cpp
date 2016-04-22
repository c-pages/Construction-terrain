
#include <SFML/Graphics.hpp>
#include <iostream>

#include "noise/noise.h"
#include "noiseutils.h"

#include "stdio.h"
#include "terrain/Terrain.h"
#include <time.h>

using namespace noise;

sf::Vector2i tailleCarte (800,600);

sf::RenderWindow window(sf::VideoMode( tailleCarte .x , tailleCarte.y ), "Terrain" );
//sf::RectangleShape shape( { tailleCarte .x , tailleCarte.y } );

Terrain* terrain = new Terrain ( tailleCarte );

int main()
{


    // le seed du random
    srand(time(NULL));




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear( sf::Color ( 50,160,70) );
        window.draw( *terrain );
        window.display();
    }

    return 0;
}
