#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "model.h"
using namespace std;
int tfinal = 1000; //duration of simulation


int main()
{	
	
    sf::RenderWindow window(sf::VideoMode (500,500), "Squares Test");
	
	// define 3 objects, one  for excited, one for refractory and one for the ones who will be deexcited from refractory

	sf::RectangleShape excited;
	excited.setFillColor(sf::Color::Color(255,255,255));
	excited.setSize(sf::Vector2f(length,length));

	sf::RectangleShape refractory;
	refractory.setSize(sf::Vector2f(length,length));
	refractory.setFillColor(sf::Color::Color(200,200,200));
	sf::RectangleShape dexcited;
	dexcited.setFillColor(sf::Color::Black);
	dexcited.setSize(sf::Vector2f(length,length));
	
	std::vector<std::vector<int>> state(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> statepr(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> state1(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> dys(vertical,std::vector<int>(horizontal)); // initiate dysfunctional array
	std::vector<std::vector<int>> bonds(vertical,std::vector<int>(horizontal)); // initiate dysfunctional array
	statepr = Calculations::pacemaker(statepr);
	
	dys = Calculations::dysfun(); //the dysfunctional cells and the vertical bonds do not change in time (initially defined)
	bonds = Calculations::bonds();
	for(int time = 0; time <tfinal; time ++)
	{
		if(  time % tpace == 0)
		{
			statepr = Calculations::pacemaker(state); // set pacemaker at desired interval
			
		}
		
		state = Calculations::states(statepr,bonds,dys); // calculate next states from previous ones, by supplying exising bonds
		statepr = state;
		
	for( int k = 2; k< rest ; k++)
	{
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
				if (state[i][j] == k )
				{
					refractory.setPosition(length*i,length*j);
					refractory.setFillColor(sf::Color::Color(200-5*k,200-5*k,200-5*k)); //make refractory states slightly darker as time passes
					
					window.draw(refractory);
				}
				if (state[i][j]  == rest )
				{
					dexcited.setPosition(length*i,length*j);
					window.draw(dexcited);
				}
		
		}
	}

	}
			window.display();
			//Sleep(500);
			window.clear();
	}

return 0;
}