#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "model.h"
using namespace std;
int tfinal = 100000; //duration of simulation


int main()
{	
	
	 ofstream myfile;
	
	 for( double mu = 0.23; mu< 0.26 ; mu += 0.05)
	{
		 std::ostringstream strs;
		 strs << mu;
		 std::string str = strs.str();
		 string filename = "counter" + str;

		 myfile.open (filename + ".txt");
	// define 3 objects, one  for excited, one for refractory and one for the ones who will be deexcited from refractory
	std::vector<std::vector<int>> state(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> statepr(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> state1(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> dys(vertical,std::vector<int>(horizontal)); // initiate dysfunctional array
	std::vector<std::vector<int>> bonds(vertical,std::vector<int>(horizontal)); // initiate dysfunctional array
	
	statepr = Calculations::pacemaker(statepr);
	
	dys = Calculations::dysfun(); //the dysfunctional cells and the vertical bonds do not change in time (initially defined)
	bonds = Calculations::bonds(mu);
	for(int time = 0; time <tfinal; time ++)
	{
	
		if(  time % tpace == 0)
		{
			statepr = Calculations::pacemaker(state); // set pacemaker at desired interval
			
		
		}
		
		state = Calculations::states(statepr,bonds,dys); // calculate next states from previous ones, by supplying exising bonds
		statepr = state;
		if(time % tpace == 0)
		{
			myfile << Calculations::counter << endl;
			
		}
	}
		myfile.close();
	}
	 	
return 0;
}