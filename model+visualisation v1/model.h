#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int horizontal = 100;
const int vertical = 100;
const int rest = 10;

class Calculations{
public:
vector< vector<int> > states(std::vector<std::vector<int>> statep, std::vector<std::vector<int>> bond)
{
	std::vector<std::vector<int>> staten(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	
	
	for( int j = 1 ; j< vertical; j++)
	{
		for( int i = 1 ; i< horizontal; i++)
		{

			if(( bond[i][j-1] == 1)&& (statep[i][j-1] == 1) && (statep[i][j] = 0)) 
			{
				staten[i][j]=1; //vertical excitement is ensured from below
			}
			if(( bond[i][j] == 1) && (statep[i][j+1] == 1)&&(statep[i][j] = 0)) 
			{
				staten[i][j] = 1; //vertical excitement is ensured from above
			}


			if( (statep[i][j] == 0) && (statep[i-1][j] == 1))
			{
				staten[i][j] = 1;  //horizontal excitement from the left
			}
			if( (statep[i][j] == 0) && (statep[i+1][j] == 1))
			{
				staten[i][j] = 1;  //horizontal excitement from the right
			}
			

			if ( rest>statep[i][j] >= 1)
			{
				staten[i][j] += 1; //increment resting time for refractory cells
			}
			if ( statep[i][j] > rest) // make cells excitable after  rest time has elapsed
			{
				staten[i][j] = 0;
			}
			
		}
	}
return staten;	
}

vector<vector<int>> bonds()
{
	std::vector<std::vector<int>> bonds;
	for(int j = 1; j<vertical ; j++)
	{
		for(int i = 1; i < horizontal ; i++)
		{
			bonds[i][j] = rand() % 1; // 50% chance of a vertical bond
		}
	}
	return bonds;
}


};
