#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<vector>
#include "model.h"
using namespace std;
int tfinal = 100; //duration of simulation
class Visualisation: public Calculations
{

public:
/*
const int vertical = 200; // the number of cells in the vertical direction
const int horizontal = 200; // " " horizontal "" 
*/

 
int main()
{	
    sf::RenderWindow window(sf::VideoMode (1000,1000), "Squares Test");
	
	// define 3 objects, one  for excited, one for refractory and one for the ones who will be deexcited from refractory

	sf::RectangleShape excited;
	excited.setFillColor(sf::Color::Red);
	excited.setSize(sf::Vector2f(10,10));

	sf::RectangleShape refractory;
	refractory.setSize(sf::Vector2f(10,10));
	refractory.setFillColor(sf::Color::Yellow);
	sf::RectangleShape dexcited;
	dexcited.setFillColor(sf::Color::Black);
	dexcited.setSize(sf::Vector2f(10,10));
	
	std::vector<std::vector<int>> states(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> statep(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	
	states = Calculations.states(statep, Calculations.bonds()); // calculate next states from previous ones, by supplying exising bonds
	for(int time = 0; time <tfinal; time ++)
	{

	for(int j =0; j<horizontal ; j++)
	{
		
		
	for (int i = 0; i < vertical; i++) 
	{
		

		
		if (states[i][j]  ==1 )
		{
			excited.setPosition(10*i,10*j);
			window.draw(excited);
		}
		if (states[i][j]  == 2 )
		{
			refractory.setPosition(10*i,10*j);
			window.draw(refractory);
		}
		if (states[i][j]  ==3  )
		{
			dexcited.setPosition(10*i,10*j);
			window.draw(dexcited);
		}
		
	}

	}
			window.display();
			Sleep(100);
			window.clear();
	}

return 0;
}
};