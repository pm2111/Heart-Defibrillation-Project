#include <iostream>
#include <vector>
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>
#include <math.h>
//#include <C:/Program Files (x86)/Intel/Composer XE/compiler/include/cilk/cilk.h>
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
	std::vector<std::vector<int>> last_excited;
	std::vector<std::vector<int>> refractory;
	std::vector<std::vector<int>> last_excited_counter; // have a dummy counter so as to not interfere with APD dynamics
	std::vector<std::vector<int>> total_rest; //have counter for total time cells spend in rest or refractory 


	int heart_time; //internal clock
	//model parameters 
	int tau; //refactory period
	int T; // pacemaker rate
	double nu, epsilom, delta; //probability vertical connection exists, probability of misfire given faulty and probability cell faulty 
	double b; //scaling parameter 

	double A, B, C, D;  //sigmoidal parameters for APD restitution

	//random number generator 
	const gsl_rng_type*Type;
	gsl_rng*r;

	int total_bonds;
	int total_functional;
	int total_excited;
	double F;

public:

	heart()
	{

	}
	heart(int _L, int _T, int _tau, double _nu, double _epsilom, double _delta, double _F)
	{
		L = _L;
		nu = _nu;
		tau = _tau;
		T = _T;
		epsilom = _epsilom;
		delta = _delta;
		F = _F;

		heart_time = T;

		state.resize(L);
		new_state.resize(L);
		functional.resize(L);
		bond.resize(L);
		last_excited.resize(L);
		refractory.resize(L);
		last_excited_counter.resize(L);
		total_rest.resize(L);
		//pacemaker action
		for (unsigned i = 0; i<L; i++)
		{
			state[i].resize(L, 0);  // all cells eligible for excitation
			new_state[i].resize(L, 0);
			functional[i].resize(L, 1);// none disfunctional at the moment
			bond[i].resize(L, 1); 
			last_excited[i].resize(L, T);
			refractory[i].resize(L, tau);
			last_excited_counter[i].resize(L, 0);
			total_rest[i].resize(L,0);

		}
		//	total_functional = L*L;
		//	total_bonds = L*L;
		total_excited = 0;//could be useful avoiding calling size of some vector

		//HAVE NOT USED gsl_rng in class before need to make sure is working correctly

		//  environment variable GSL_RNG_TYPE 
		gsl_rng_env_setup();

		Type = gsl_rng_mt19937;//random number generator using the Mersenne Twister algorithm 
		r = gsl_rng_alloc(Type);

		gsl_rng_set(r, time(NULL));//random number generator seeded with time
		//gsl_rng_set(r, 0);//random number generator seeded with time

		//assigning cells as having a bond above them or not and functional or not functional
		int healthy = 1;

		for (int j = healthy; j<L; j++)
		{
			for (int i = 0; i<L; i++)
			{

				//bond[i][j] = (gsl_rng_uniform(r)<nu);
				functional[i][j] = (gsl_rng_uniform(r)>delta);// inequality reversed
				//double x =  gsl_rng_uniform(r);
				//	std::cout <<x<< '\t' << (x<nu) << std::endl;

			}
		}
		for (int i = 0; i < floor((1 - nu)*L*L); i++)  //breaking fraction 1-nu bonds no longer a probability
		{
			bool aged = false;
			while (aged == false)
			{
				int X = gsl_rng_uniform_int(r, L);
				int Y = gsl_rng_uniform_int(r, L);
				double W = gsl_rng_uniform(r);

				if (bond[X][Y] == 1 && W<1/F)
				{
					bond[X][Y] = 0;
					aged = true;

				}
				else
				{
					int left_right = gsl_rng_uniform_int(r, 2);
					bool end_of_fibre = false;
					if (left_right == 1)
					{
						Y++;
						while (Y < L  && end_of_fibre == false)
						{
							if (bond[X][Y] == 1 && W>1/F)
							{
								bond[X][Y] = 0;
								aged = true;
								end_of_fibre = true;
							}
							Y++;
						}
					}
					if (left_right == 0)
					{
						Y--;
						while (Y > 0  && end_of_fibre == false)
						{
							if (bond[X][Y] == 1 && W>1/F)
							{
								bond[X][Y] = 0;
								aged = true;
								end_of_fibre = true;
							}
							Y--;
						}
					}
				}
			}
		}
		//deal with bonds for pacemaker
		for (int i = 0; i < L; i++)
		{
			bond[i][0] = 0;
		}

	

	}
	void operate()//one time step
	{


		total_excited = 0;
		//Relax excited cells
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j<L; j++)
			{
				if (state[i][j] == 1)//searching 4 neighbours of excited cell trying to excite if resting and if don't misfire and if there is a bond
				{
					new_state[((i + 1)<L)*(i + 1)][j] += (new_state[((i + 1)<L)*(i + 1)][j]<1)*(state[((i + 1)<L)*(i + 1)][j]<1)*bond[i][j] * (1 - (1 - functional[((i + 1)<L)*(i + 1)][j])*(gsl_rng_uniform(r)<epsilom));

					new_state[(i - 1)*(i>0) + (L - 1)*(i<1)][j] += (new_state[(i - 1)*(i>0) + (L - 1)*(i<1)][j]<1)*(state[(i - 1)*(i>0) + (L - 1)*(i<1)][j]<1)*bond[(i - 1)*(i>0) + (L - 1)*(i<1)][j] * (1 - (1 - functional[(i - 1)*(i>0) + (L - 1)*(i<1)][j])*(gsl_rng_uniform(r)<epsilom));

					new_state[i][(j + 1)*(j<L - 1)] += (new_state[i][(j + 1)*(j<L - 1)]<1)*(j<L - 1)*(state[i][(j + 1)*(j<L - 1)]<1)*(1 - (1 - functional[i][(j + 1)*(j<L - 1)])*(gsl_rng_uniform(r)<epsilom));

					new_state[i][(j - 1)*(j>0)] += (new_state[i][(j - 1)*(j>0)]<1)*(j>0)*(state[i][(j - 1)*(j>0)]<1)*(1 - (1 - functional[i][(j - 1)*(j>0)])*(gsl_rng_uniform(r)<epsilom));

					refractory[i][j] = restitution(i, j);
					
					total_rest[i][j] += last_excited_counter[i][j];
				
				}
			}
		}
		//end relaxing
		//std::vector<std::pair<int,int>> next_excited_cells;

		//evolving cells that were not excited previously or now (some subtlty to those possibly excited now)
		for (int i = 0; i<L; i++)
		{
			for (int j = 0; j<L; j++)
			{
				new_state[i][j] += (state[i][j]>0);
				//if state was excited or refactory before +1 states that were resting may have been newly excited or not but this ignores them
				new_state[i][j] *= (state[i][j]<refractory[i][j]);//promote to resting after end of refactory which is now variable
				total_excited += (new_state[i][j]<2)*new_state[i][j];


				last_excited[i][j] += (state[i][j] < 1) + (state[i][j]>1);//counts if not excited
				last_excited[i][j] *= (state[i][j] < 1) + (state[i][j]>1); //cycles back to 0 if excited;  old states so don't put lastexcited to 0 before calculating new refractory
				last_excited_counter[i][j] += (state[i][j] < 1) + (state[i][j]>1);//dummy counter
				last_excited_counter[i][j] *= (state[i][j] < 1) + (state[i][j]>1); //dummy counter
				

			}
		}

		//SAN  
		for (int i = 0; i<L; i++)
		{
			new_state[i][0] += (state[i][0]<1)*(heart_time>T - 1)*(1 - (1 - functional[i][0])*(gsl_rng_uniform(r)<epsilom));
			//will do something every T steps 
		}

		heart_time++;
		heart_time *= (heart_time<T + 1);
		//end SAN

		state = new_state;

	}
	int get_state(int i, int j)//perhaps have alternative for 2d array
	{

		return state[i][j];

	}
	void set_state(int i, int j, int val)
	{

		state[i][j] = val;
	}
	int get_function(int i, int j)
	{
		return functional[i][j];
	}
	void set_function(int i, int j, int val)
	{
		functional[i][j] = val;
	}
	int get_bond(int i, int j)
	{
		return bond[i][j];
	}
	void set_bond(int i, int j, int val)
	{
		bond[i][j] = val;
	}
	void update_total_rest(int i, int j)
	{
		total_rest[i][j] += last_excited_counter[i][j];
	}
	double get_total_rest(int i,int j)
	{
		return total_rest[i][j];
	}
	void reset_total_rest(int i, int j)
	{
		total_rest[i][j] = 0;
		last_excited_counter[i][j] = 0;
	}
	int get_tau()
	{
		return tau;
	}
	int get_T()
	{
		return T;
	}

	int get_excited()
	{
		return total_excited;
	}
	int get_refractory(int i, int j)
	{
		return refractory[i][j];
	}
	int get_last_excited(int i, int j)
	{
		return last_excited[i][j];
	}
	double colour(int i, int j)
	{
		return (1 - state[i][j] / (1.0*tau))*(state[i][j]>1);
		//return state[i][j]/(1.0*T);

	}
	int restitution(int i, int j)
	{
		if (last_excited[i][j] < T)
		{
			return tau*(1 - 0.5*exp(-4.0 * last_excited[i][j] / T));
		}
		else
			return tau;

	}
};
#endif