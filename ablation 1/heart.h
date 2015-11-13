#include <iostream>
#include <vector>
#include <stdio.h>
#include <gsl\gsl_randist.h>
#include <gsl\gsl_rng.h>
#include <time.h>
#include <SFML\Graphics.hpp>
#ifndef _HEART_H
#define _HEART_H




class heart
{
	private:
		int L;  //sytem size length for now square

		std::vector<std::vector<int>> state;  //value indicates whether in excited state refactory or resting
		std::vector<std::vector<int>> new_state;  //using new_state and state to distinguish newly excited cells from previously excited
		std::vector<std::vector<int>> functional; //1 if functional 0 if disfunctional
		std::vector<std::vector<int>> bond; //1 if bond to site above current cell, 0 if no bond above site
		std::vector<std::vector<int>> unablated; // Defaults to zero initial value
		int heart_time; //internal clock
		//model parameters 
		int tau; //refactory period
		int T; // pacemaker rate
		double nu, epsilom, delta; //probability vertical connection exists, probability of misfire given faulty and probability cell faulty 
		
		//random number generator 
		const gsl_rng_type*Type;
		gsl_rng*r; 

		int total_bonds;
		int total_functional;
		int total_excited;
		

	public:

		heart()
		{

		}
		heart(const int _L,  int _T, int _tau ,double _nu, double _epsilom, double _delta)
		{
			L=_L;
			nu= _nu;
			tau=_tau;
			T=_T;
			epsilom=_epsilom;
			delta=_delta;
			heart_time = T;
			
			state.resize(L);
			new_state.resize(L);
			functional.resize(L);
			bond.resize(L);
			unablated.resize(L);
			//pacemaker action
			for(unsigned i=0; i<L; i++)
			{
				state[i].resize(L,0);  // all cells eligible for excitation
				new_state[i].resize(L,0);
				functional[i].resize(L,0);// none disfunctional at the moment
				bond[i].resize(L, 1); // all transverse bonds present at the moment
				unablated[i].resize(L,1);
			}
		//	total_functional = L*L;
		//	total_bonds = L*L;
			total_excited =0;//could be useful avoiding calling size of some vector

			 //HAVE NOT USED gsl_rng in class before need to make sure is working correctly

			//  environment variable GSL_RNG_TYPE 
			gsl_rng_env_setup();

			Type = gsl_rng_mt19937;//random number generator using the Mersenne Twister algorithm 
			r = gsl_rng_alloc (Type);

			gsl_rng_set(r,time(NULL));//random number generator seeded with time
			//gsl_rng_set(r,0);//random number generator seeded with time

			//assigning cells as having a bond above them or not and functional or not functional
			for(int i=0; i<L; i++)
			{
				for(int j=0; j<L; j++)
				{

					bond[i][j] = (gsl_rng_uniform(r)<nu); 
					functional[i][j] = (gsl_rng_uniform(r)>delta);// inequality reversed
					//double x =  gsl_rng_uniform(r);
				//	std::cout <<x<< '\t' << (x<nu) << std::endl;

				}
			}

	
		}
		void operate()//one time step
		{
			total_excited =0;

			//Relax excited cells
				for(int i=0; i<L ;i++)
			{
				for(int j=0; j<L; j++)
				{
					if(state[i][j]==1)//searching 4 neighbours of excited cell trying to excite if resting and if don't misfire and if there is a bond
					{
						new_state[((i+1)<L)*(i+1)][j]+=(state[((i+1)<L)*(i+1)][j]<1)*bond[i][j]*(1-(1-functional[((i+1)<L)*(i+1)][j])*(gsl_rng_uniform(r)<epsilom))*unablated[((i+1)<L)*(i+1)][j];
				
						new_state[(i-1)*(i>0)+(L-1)*(i<1)][j]+=(state[(i-1)*(i>0)+(L-1)*(i<1)][j]<1)*bond[(i-1)*(i>0)+(L-1)*(i<1)][j]*(1-(1-functional[(i-1)*(i>0)+(L-1)*(i<1)][j])*(gsl_rng_uniform(r)<epsilom))*unablated[(i-1)*(i>0)+(L-1)*(i<1)][j];
					
						new_state[i][(j+1)*(j<L-1)] += (j<L-1)*(state[i][(j+1)*(j<L-1)]<1)*(1-(1-functional[i][(j+1)*(j<L-1)])*(gsl_rng_uniform(r)<epsilom))*unablated[i][(j+1)*(j<L-1)];
			
						new_state[i][(j-1)*(j>0)]+= (j>0)*(state[i][(j-1)*(j>0)]<1)*(1-(1-functional[i][(j-1)*(j>0)])*(gsl_rng_uniform(r)<epsilom))*unablated[i][(j-1)*(j>0)];
					}
				}
			}
				//end relaxing


			//evolving cells that were not excited previously or now (some subtlty to those possibly excited now)
			for(int i=0;i<L;i++)
			{
				for(int j=0; j<L; j++)
				{
					new_state[i][j] += (state[i][j]>0);
					//if state was excited or refactory before +1 states that were resting may have been newly excited or not but this ignores them
					new_state[i][j] *= (state[i][j]<tau);//promote to resting after end of refactory 
					total_excited += (new_state[i][j]<2)*new_state[i][j];
				}
			}
		
				//SAN  
			for(int i=0; i<L; i++) 
			{
				new_state[i][0] += (state[i][0]<1)*(heart_time>T-1)*(1-(1-functional[i][0])*(gsl_rng_uniform(r)<epsilom));
					//will do something every T steps should also add in misfire
			}
		
			heart_time++;
			heart_time *= (heart_time<T+1);
			//end SAN

			state=new_state;
			
		}
		int get_state(int i, int j)//perhaps have alternative for 2d array
		{

			return state[i][j];

		}
		void set_state(int i, int j, int val)
		{

			state[i][j]=val;
		}
		int get_function(int i, int j)
		{
			return functional[i][j];
		}
		void set_function(int i, int j, int val)
		{
			functional[i][j]=val;
		}
		int get_bond(int i, int j)
		{
			return bond[i][j];
		}
		void set_bond(int i, int j, int val)
		{
			bond[i][j]=val;
		}
		int get_tau()
		{
			return tau;
		}
		int get_T()
		{
			return T;
		}
		void age_nu()
		{

		}
		void set_disfunction()
		{


		}
		int get_excited()
		{
			return total_excited;
		}
		double colour(int i, int j)
		{
			return (1-state[i][j]/(1.0*tau))*(state[i][j]>1);
			//return state[i][j]/(1.0*T);
			
		}
		void interact(sf::RenderWindow & renderWindow, int length) 
		{
			sf::Event event;
			float x;
			float y;
			
			float Mx = sf::Mouse::getPosition(renderWindow).x;
			float My = sf::Mouse::getPosition(renderWindow).y;
			//std::cout << Mx << " " << My << std::endl;
			while (renderWindow.pollEvent(event))
			{
			switch(event.type)
			{
			case sf::Event::KeyPressed:
			
			
				state[My/length][Mx/length] = 0;
				new_state[My/length][Mx/length] = 0;
				unablated[My/length][Mx/length] = 0;

			}
			}
		}
};
#endif