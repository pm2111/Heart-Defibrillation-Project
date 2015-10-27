#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int horizontal = 100;
const int vertical = 100;
const int rest = 25;

class Calculations{
public:
	static vector< vector<int> > states(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
	static vector<vector<int>> bonds();
	static vector<vector<int>> pacemaker(std::vector<std::vector<int>>);

private:
};

vector< vector<int> > Calculations::states(std::vector<std::vector<int>> statep, std::vector<std::vector<int>> bond)
{
	std::vector<std::vector<int>> staten(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> newe(vertical,std::vector<int>(horizontal)); // keep track of newly excited cells
	for( int i = 0 ; i< horizontal; i++)
		{
			for( int j = 0 ; j< vertical; j++)
			{
		
			if( j>0)
			{
				if(( bond[i][j-1] == 1)&& (statep[i][j-1] == 1) && (statep[i][j] == 0)) 
				{
					staten[i][j]=1; //vertical excitement is ensured from above
					newe[i][j] = 1;
				}
			}
			
			if( j<vertical-1)
			{
				if(( bond[i][j] == 1) && (statep[i][j+1] == 1)&&(statep[i][j] == 0)) 
				{
					staten[i][j] = 1; //vertical excitement is ensured from below
					newe[i][j] = 1;
				}
			}
		
			if( i >= 1)
			{
				if( (statep[i][j] == 0) && (statep[i-1][j] == 1))
				{
					staten[i][j] = 1;  //horizontal excitement from the left
					newe[i][j] = 1;
				}
			}
			
			if(i == 0)
			{
				if( (statep[i+1][j] == 0) && (statep[i][j] == 1))
				{
					staten[i+1][j] = 1;  //horizontal excitement from the left, special case of i = 0.
					newe[i+1][j] = 1;
				}
			}

			
			if( i < horizontal-1)
			{
				if( ((statep[i][j] == 0) && (statep[i+1][j] == 1)))
				{
					staten[i][j] = 1;  //horizontal excitement from the right
					newe[i][j] = 1;
				}
			}
			
			
			if ( (statep[i][j] >= 1 ) && (newe[i][j] == 0 ) )
			{
				staten[i][j] = statep[i][j] + 1; //increment resting time for refractory cells

				
			}
			
			if ( statep[i][j] == rest) // make cells excitable after  rest time has elapsed
			{
				staten[i][j] = 0;
			}
			
		}
	}
	staten[50][50] = 1;
	
return staten;	
}


vector<vector<int>> Calculations::bonds()
{
	std::vector<std::vector<int>> bonds(vertical,std::vector<int>(horizontal));
	for(int j = 0; j<vertical ; j++)
	{
		for(int i = 0; i < horizontal ; i++)
		{
			bonds[i][j] = rand() % 2; // 50% chance of a vertical bond (only zeros and ones)
		}
	}
	return bonds;
}

vector<vector<int>> Calculations::pacemaker(std::vector<std::vector<int>> states)
{
	for(int j = 0; j < vertical; j++)
	{
		int i= 0;
		states[i][j] = 1; //setup pacemaker line of excitation
	}
	return states;
}



