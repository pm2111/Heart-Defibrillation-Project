#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
using namespace std;
int main()
{	
	int vertical =200, horizontal = 200;
    sf::RenderWindow window(sf::VideoMode (horizontal,vertical), "A planar wave visualised at 300ms intervals.");
	// create an array of 3 vertices that define a triangle primitive
	sf::VertexArray lines(sf::LinesStrip, 10);
	for (int i = 1;i < 500; i ++)
	{
		if (i>horizontal-50)
		{
			i = 1;
		}
		lines[0].position = sf::Vector2f(50+i,0 );
		lines[1].position = sf::Vector2f(50+i,10);
		lines[2].position = sf::Vector2f(50+i, 20);
		lines[3].position = sf::Vector2f(50+i,30);
		lines[4].position = sf::Vector2f(50+i,50);
		lines[5].position = sf::Vector2f(50+i,60);
		lines[6].position = sf::Vector2f(50+i, 70);
		lines[7].position = sf::Vector2f(50+i,80);
		lines[8].position = sf::Vector2f(50+i, 90);
		lines[9].position = sf::Vector2f(50+i,100);
		window.clear();
		window.draw(lines);
		window.display();
		Sleep(100); // make cpu wait for x milliseconds within loop in order to visualize result as movie
		/*while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(lines);
			window.display();

		}*/

	}
	return 0;
}