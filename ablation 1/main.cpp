#include "heart.h"
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>
#include "gsl_rng.h"
#include "gsl_randist.h"
int length = 5;
int tfinal = 10000;
const int size = 200;
//std::ofstream outfile("H:/fourth year/atrium/atrium/atrium/200.txt");

std::stringstream sstm;
std::string health = "healthy_pacemaker_";
std::string restitution = "restitution";
std::ofstream outfile;

int main()
{

	int nu_steps = 5;
	
	//rescaled time and length scales
	double b = 1000 / size;
	int tau = floor(250 / b);
	int T = floor(1100 / b);
	//heart rainbow(size,size,25,0.1,0,0);
	//heart rainbow(size,100, 5,0.5,0.05,0.5);//may have been that nu and delta where actually 1 or one of them  1 one 0
	//heart rainbow(size, T, tau, 0.1, 0.05,0.05);
	//rainbow.set_state(20,100,1);


	int time_steps = 100000;
	double nu = .18;

	
		sf::RenderWindow window(sf::VideoMode (size*5,size*5), "Squares Test");
		
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
	
		std::vector<std::vector<int>> state1(size,std::vector<int>(size)); // Defaults to zero initial value
		heart rainbow(size, T, tau, nu, 0.05, 0.05);

		int state;
			for (int time = 0; time < time_steps; time++)
			{

				rainbow.operate();
				
				rainbow.interact(window, length);
				
					for(int j =0; j<size ; j++)
					{
			
		
						for (int i = 0; i < size; i++) 
						{
							state = rainbow.get_state(j,i);
							
							
							//cout << state[i][j] << endl;
							if (state  == 1 )
							{
								excited.setPosition(length*i,length*j);
								window.draw(excited);
							}
	
							/*if (state == 0 )
							{
								dexcited.setPosition(length*i,length*j);
								window.draw(dexcited);
							}
							*/
							if((state > 1))
							{
								
								refractory.setPosition(length*i,length*j);
								refractory.setFillColor(sf::Color::Color(200-3*state,200-3*state,200-3*state)); //make refractory states slightly darker as time passes
					
								window.draw(refractory);
							}
		
					}
				}

						
						window.display();
						//Sleep(500);
						window.clear();
				}
	
	return 0;
}

