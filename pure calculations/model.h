#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
const int horizontal = 100;
const int vertical = 100;
const int length = 5;
const double b = 1000/horizontal;; // coarsegraining param
const double v = 0.15; //m/s conduction vel NEEDS TO BE CONSTANT
const int rest = 250/b;; // check with quantities above
const double epsilon = 0.05; // 5% dysfunctional cells
const double delta = 0.05; //prob. that each dysfunctional cell misfires
const int tpace = 1100/b;

class Calculations{

	 
public:
	static vector< vector<int> > states(std::vector<std::vector<int>>, std::vector<std::vector<int>>,std::vector<std::vector<int>>);
	static vector<vector<int>> bonds(double);
	static vector<vector<int>> pacemaker(std::vector<std::vector<int>>);
	static vector<vector<int>>dysfun();
	static int counter;
	static int fibrillation;
	
private:
	
};

vector< vector<int> > Calculations::states(std::vector<std::vector<int>> statep, std::vector<std::vector<int>> bond, std::vector<std::vector<int>> dys)
{
	 
	std::vector<std::vector<int>> staten(vertical,std::vector<int>(horizontal)); // Defaults to zero initial value
	std::vector<std::vector<int>> newe(vertical,std::vector<int>(horizontal)); // keep track of newly excited cells
	counter = 0;
	srand(time(NULL)); //unseed random num gen
	for( int i = 0 ; i< horizontal; i++)
		{
			for( int j = 0 ; j< vertical; j++)
			{
				
				
			
				if( j>0)
				{
					 if(( bond[i][j-1] == 1)&& (statep[i][j-1] == 1) && (statep[i][j] == 0)) 
					{
						if( (dys[i][j] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i][j] = 0;
						}
						else
						{
						staten[i][j]=1; //vertical excitement is ensured from above
						newe[i][j] = 1;
						}
					}
				}
				if( j == vertical -1)
				{
						 if(( bond[i][j] == 1)&& (statep[i][j] == 1) && (statep[i][0] == 0)) 
					{
						if( (dys[i][0] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i][0] = 0;
						}
						else
						{
						staten[i][0]=1; //vertical boundary condition is ensured from below
						newe[i][0] = 1;
						}
					}
				}
			if( j == 0)
				{
						 if(( bond[i][vertical-1] == 1)&& (statep[i][j] == 1) && (statep[i][vertical-1] == 0)) 
					{
						if( (dys[i][vertical-1] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i][vertical-1] = 0;
						}
						else
						{
						staten[i][vertical-1]=1; //vertical boundary cond is ensured from above
						newe[i][vertical-1] = 1;
						}
					}
				}
			
			
				if( j<vertical-1)
				{
					if(( bond[i][j] == 1) && (statep[i][j+1] == 1)&&(statep[i][j] == 0)) 
					{
						if( (dys[i][j] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i][j] = 0;
						}
						else
						{
						staten[i][j] = 1; //vertical excitement is ensured from below
						newe[i][j] = 1;
						}
					}
				}
		
				if( i >= 1)
				{
					if( (statep[i][j] == 0) && (statep[i-1][j] == 1))
					{
						if( (dys[i][j] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i][j] = 0;
						}
						else
						{
						staten[i][j] = 1;  //horizontal excitement from the left
						newe[i][j] = 1;
						}
					}
				}
			
				if(i == 0)
				{
					if( (statep[i+1][j] == 0) && (statep[i][j] == 1))
					{
						if( (dys[i+1][j] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i+1][j] = 0;
						}
						else
						{
						staten[i+1][j] = 1;  //horizontal excitement from the left, special case of i = 0.
						newe[i+1][j] = 1;
						}
					}
				}

			
				if( i < horizontal-1)
				{
					if( ((statep[i][j] == 0) && (statep[i+1][j] == 1)))
					{
						if( (dys[i][j] == 1) && (rand() % 19 == 1)) // 1 in 20 probability that a dysfunctional cell will not file)
						{
							staten[i][j] = 0;
						}
						else
						{

						staten[i][j] = 1;  //horizontal excitement from the right
						newe[i][j] = 1;
						}
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
	for( int i = 0 ; i< horizontal; i++)
		{
			for( int j = 0 ; j< vertical; j++)
			{
				if(newe[i][j] ==1)
						{
							counter +=1;
						}
			}
		}
	//cout << counter << endl;
	int threshold = 1.5*vertical;
	if(counter > threshold)
	{
		fibrillation +=1;
	}
	
return staten;	
}


vector<vector<int>> Calculations::bonds(double mu)
{
	std::vector<std::vector<int>> bonds(vertical,std::vector<int>(horizontal));
	int percent_fill = mu*1000;
	srand(time(NULL)); //unseed random num gen
	for(int j = 0; j<vertical ; j++)
	{
		for(int i = 0; i < horizontal ; i++)
		{
				
				if(rand() %1000 < percent_fill )
				{
				bonds[i][j] = 1; // 
				
				}
			
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


vector<vector<int>> Calculations::dysfun()
{
	std::vector<std::vector<int>> dys(vertical,std::vector<int>(horizontal)); // initiate array of dysfunctional states
	int percentage = epsilon * 1000;

	srand(time(NULL)); //unseed random num gen
	
	for(int j = 0; j<vertical ; j++)
	{
		for(int i = 0; i < horizontal ; i++)
		{
				
				if(rand() % 1000  < percentage )
				{
				dys[i][j] = 1; // 
				}
			
		}
		
	}
	
	return dys;
}

int Calculations::counter=0;

int Calculations::fibrillation=0;
