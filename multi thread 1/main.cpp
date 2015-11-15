#include "heart.h"
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
	

	#pragma omp parallel for
	for (int nu1 = 19;nu1 < 30;nu1 += 1)
	{ 
		std::ofstream outfile;
		double nu = nu1/100.0;
		sstm.str("");
		sstm << nu << "_" << restitution << "_" << size << "_" << health << "_" << time_steps << ".txt";
		outfile.open(sstm.str());

		// heart rainbow(size,size, size, 0,0.1,0);
		//heart rainbow(size,size, 25,0.1,0.05,0.05);
		//	heart rainbow(size,size,size/3.0, nu, 0.05, 0.05);
		heart rainbow(size, T, tau, nu, 0.05, 0.05);

		//for (int n = 0; n < 50; n++)
		//{


			for (int i = 0; i < time_steps; i++)
			{

				rainbow.operate();

				outfile << i << '\t' << rainbow.get_excited() << std::endl;

				//std::cout << rainbow.get_last_excited(10,10)<< '\t' << rainbow.get_refractory(10,10) << std::endl;
				if (i % 10000 < 1)
					std::cout << i << std::endl;
			}
		//}

		outfile.close();

		
	}
	return 0;
}
