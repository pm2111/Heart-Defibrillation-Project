#include "heartrecovery.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "gsl_rng.h"
#include "gsl_randist.h"
#include "omp.h" //needed for parallel processing using OpenMP


//std::ofstream outfile("H:/fourth year/atrium/atrium/atrium/200.txt");

std::stringstream sstm;
std::string health = "healthy_pacemaker_";
std::string restitution = "restitution";
std::string no = "no";
std::string ablate = "ablate";
std::string extreme = "extreme";
std::string refractory = "refractory";
std::string excited = "excited";
std::string long_sim = "long_sim";
std::string light = "light";
std::string fixed = "fixed";
std::string structure = "structure";
// The MAIN function, from here we start our application and run the Game loop
int main()
{

	int nu_steps = 11;
	const unsigned int size = 200;
	//rescaled time and length scales
	double b = 1000 / size;
	int tau = floor(250 / b);
	int T = floor(1100 / b);
	//heart rainbow(size,size,25,0.1,0,0);
	//heart rainbow(size,100, 5,0.5,0.05,0.5);//may have been that nu and delta where actually 1 or one of them  1 one 0
	//heart rainbow(size, T, tau, 0.1, 0.05,0.05);
	//rainbow.set_state(20,100,1);


	int time_steps = 100000;
	omp_lock_t writelock;

	omp_init_lock(&writelock);

	#pragma omp parallel for
	for (int nu1 = 15; nu1 < 25; nu1 += 1)
	{
		
		std::ofstream outfile;
		double nu = nu1/100.;
		

		// heart rainbow(size,size, size, 0,0.1,0);
		//heart rainbow(size,size, 25,0.1,0.05,0.05);
		//	heart rainbow(size,size,size/3.0, nu, 0.05, 0.05);
		heart rainbow(size, T, tau, nu, 0.05, 0.05);

		//for (int n = 0; n < 50; n++)
		//{

		//rainbow.ablate(120,10,56,64,24,40, 120, 170); //remove cells of high excitability
		for (int t = 0; t < time_steps; t++)
		{

			rainbow.operate();
			//std::cout << rainbow.get_refractory(50,50)<< " " << rainbow.get_excited() << std::endl;
			//std::cout << t << " "  << rainbow.get_excited() << std::endl;


			//std::cout << rainbow.get_last_excited(10,10)<< '\t' << rainbow.get_refractory(10,10) << std::endl;

			if ( (t % 10000 < 1))
			{
				
				double time = t;
				omp_set_lock(&writelock);

				sstm.str("");
				sstm << nu << "_" << time  << "_" <<  no << "_" << restitution  << "_" << excited  << "_" << size << "_" << health << "_" << time_steps << ".txt";
				outfile.open(sstm.str());
				omp_unset_lock(&writelock);

				std::cout << t << std::endl;
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
							rainbow.set_total_rest(i, j); // update cells that havent been excited at this point before saving 
							outfile << rainbow.get_total_rest(i,j) << std::endl;
							rainbow.reset_total_rest(i,j);
							
						
					}
				}
				outfile.close();
			}
		}
		
		omp_set_lock(&writelock);
		sstm.str("");
		sstm  << nu  << "_" << long_sim <<  "_" << structure << "_" <<  no << "_" << restitution  << "_" << excited  << "_" << size << "_" << health << "_" << time_steps << ".txt";
		outfile.open(sstm.str());
		omp_unset_lock(&writelock);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				//outfile << rainbow.get_bond(i,j) << "  " << rainbow.get_total_rest(i,j) << "  " << rainbow.get_function(i,j) << std::endl;
			}
		}
		outfile.close();

	
	}
	return 0;
}
