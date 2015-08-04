#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;
typedef pair<int, int> ii;

class CBala
{
private:
	float dx;
	float dy;
	int direccion;
	sf::CircleShape sbala;
	sf::Texture tPokeballs;
	vector<sf::IntRect> vImages;
	int numSprites;
	int contador;
public:
	CBala(int pDireccion);
	~CBala();
	void setPosBala(int pX, int pY);
	void moverBala(sf::Time elapsedTime, const float S);
	void dibujarBala(sf::RenderWindow &pmWindow);
	sf::CircleShape getBalaShape();
	void moverSpriteBala();
};