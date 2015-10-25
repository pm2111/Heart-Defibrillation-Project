#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include "model.h"
using namespace std;
int tfinal = 50; //duration of simulation
int length = 5; //length of squares

int main()
{	
    sf::RenderWindow window(sf::VideoMode (500,500), "Squares Test");
	
	// define 3 objects, one  for excited, one for refractory and one for the ones who will be deexcited from refractory

	sf::RectangleShape excited;
	excited.setFillColor(sf::Color::Red);
	excited.setSize(sf::Vector2f(length,length));

	sf::RectangleShape refractory;
	refractory.setSize(sf::Vector2f(length,length));
	refractory.setFillColor(sf::Color::Yellow);
	sf::RectangleShape dexcited;
	dexcited.setFillColor(sf::Color::Black);
	dexcited.setSize(sf::Vector2f(length,length));
	
	std::vector<std::vector<int>> state(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> statepr(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> state1(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	statepr = Calculations::pacemaker(statepr);
	//state1 = Calculations::states(statepr, Calculations::bonds());// calculate next states from previous ones, by supplying exising bonds
	
	for(int time = 0; time <tfinal; time ++)
	{
		
		state = Calculations::states(statepr, Calculations::bonds()); // calculate next states from previous ones, by supplying exising bonds
		statepr = state;
	for(int j =0; j<horizontal ; j++)
	{
			
		
	for (int i = 0; i < vertical; i++) 
	{
		//cout << state[i][j] << endl;
		if (state[i][j]  ==1 )
		{
			excited.setPosition(length*i,length*j);
			window.draw(excited);
		}
		if (state[i][j] == 2 )
		{
			refractory.setPosition(length*i,length*j);
			window.draw(refractory);
		}
		if (state[i][j]  == rest )
		{
			dexcited.setPosition(length*i,length*j);
			window.draw(dexcited);
		}
		
	}

	}
			window.display();
			Sleep(5000);
			window.clear();
	}

return 0;
}