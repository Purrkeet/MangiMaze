#include "Bala.h"

CBala::CBala(int pDireccion){
	dx = 2.5f;
	dy = 2.5f;
	vImages = vector<sf::IntRect>();
	direccion = pDireccion; // 1->arriba , 2->abajo , 3-> izquierda, 4->derecha
	sbala = sf::CircleShape(5);
	tPokeballs.loadFromFile("images/pokeballs.png");
	tPokeballs.setSmooth(true);
	sbala.setTexture(&tPokeballs);
	vImages.push_back(sf::IntRect(10, 10, 22, 22));
	vImages.push_back(sf::IntRect(10, 50, 22, 22));
	vImages.push_back(sf::IntRect(10, 90, 22, 22));
	vImages.push_back(sf::IntRect(10, 130, 22, 22));
	vImages.push_back(sf::IntRect(10, 170, 22, 23));
	vImages.push_back(sf::IntRect(10, 210, 22, 22));
	vImages.push_back(sf::IntRect(10, 250, 22, 22));
	vImages.push_back(sf::IntRect(10, 290, 22, 22));
	vImages.push_back(sf::IntRect(10, 332, 22, 22));
	vImages.push_back(sf::IntRect(10, 372, 22, 22));
	vImages.push_back(sf::IntRect(9, 405, 23, 29));
	vImages.push_back(sf::IntRect(9, 449, 22, 23));
	vImages.push_back(sf::IntRect(7, 489, 23, 23));
	vImages.push_back(sf::IntRect(6, 529, 23, 23));
	vImages.push_back(sf::IntRect(11, 569, 22, 23));
	vImages.push_back(sf::IntRect(12, 609, 23, 23));
	vImages.push_back(sf::IntRect(13, 649, 23, 23));
	numSprites = vImages.size();
	contador = 0;
}
CBala::~CBala(){}
void CBala::setPosBala(int pX, int pY){
	sbala.setPosition(pX, pY);
}
void CBala::moverBala(sf::Time elapsedTime, const float S){
	switch (direccion)
	{
	case 1: sbala.move(0, -S*elapsedTime.asSeconds()); break;
	case 2: sbala.move(0, +S*elapsedTime.asSeconds()); break;
	case 3: sbala.move(-S*elapsedTime.asSeconds(), 0); break;
	case 4: sbala.move(+S*elapsedTime.asSeconds(), 0); break;
	}
}
void CBala::dibujarBala(sf::RenderWindow &pmWindow){
	pmWindow.draw(sbala);
}
sf::CircleShape CBala::getBalaShape(){
	return sbala;
}
void CBala::moverSpriteBala(){
	contador++;
	if (contador == numSprites) contador = 0;
	sbala.setTextureRect(vImages[contador]);
}
