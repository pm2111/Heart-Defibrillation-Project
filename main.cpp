#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
//#include <CImg.h>
using namespace std;
//using namespace cimg_library;
//#include <SFML/OpenGL.hpp>




int main()
{	
	int vertical =500, horizontal = 500;
    sf::RenderWindow window(sf::VideoMode (500,500), "Squares Test");
	
	sf::VertexArray myarray[10][10];
	sf::VertexArray::VertexArray(sf::PrimitiveType::Points);

	sf::Sprite get[10][10];
	get[1][2].setPosition(3,3);
	get[1][2].scale(sf::Vector2f(100.f,100.f));
	get[1][2].setColor(sf::Color::Red);
	
		sf::Texture texture;
	/*if (!texture.create(5,5))
	 return -1;

	get[1][2].setTexture(texture);*/

	
	sf::RectangleShape rect[50][50];
	

	for(int j =0; j<50 ; j++)
	{
		
		
	for (int i = 0; i < 50; i++) 
	{
		if (i > vertical)
		{
			i = i -vertical ;
		}
		

	sf::Vertex vertex;
	vertex.position = sf::Vector2f(j,i);

	rect[i][j].setSize(sf::Vector2f(20, 20));
	rect[i][j].setFillColor(sf::Color::Red);
	rect[i][j].setPosition(i*10,j*10);
	rect[i][j].setFillColor(sf::Color::Red);

	//rect[5].setScale(100,100);
	//window.clear();
	
	}
	}
	//window.draw(rect[6]);
	for (int i = 0; i<50; i++)
	{
		for (int j = 0; j<50; j++)
		{
			
	
			
			window.draw(rect[i][j]);
		
			
		}
		window.display();
			Sleep(100);
			window.clear();
	}
	
	int points[50];
	//points[i] = rand() %2 ;
	/*if (points[i] ==1)
	{
		myarray[1][2].append(vertex);
		
	}
	//sf::ContextSettings contextSettings = {8, 0, 0, 2, 0}; //8 depth bits, rest is default

	myarray[1][2].setPrimitiveType(sf::Triangles);
	 
	
		//window.clear();
		//window.draw(myarray[1][2]);
		//window.display();
		
		Sleep(80); // make cpu wait for x milliseconds within loop in order to visualize result as movie
		
		*/

return 0;
}