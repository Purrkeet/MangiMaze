#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip> 
#include <functional>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<vi> Gi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef queue<ii> qii;
typedef stack<ii> sii;
typedef pair<ii, char> iic;
typedef stack<iic> siic;
typedef vector<iii> viii;
typedef priority_queue < iii, viii, greater<iii> > pq;
#define muro '#'
#define noMuro 'O'
#define offset 1
#define offsetC 50
#define anchoBloque 20
#define MAXMATRIX 77
#define INF 99999
class Enemigo
{
public:
	int dx, dy;
	int ancho, alto;
	sf::CircleShape sEnemigo;
	int matPadres[MAXMATRIX][MAXMATRIX];
	int matVisitados[MAXMATRIX][MAXMATRIX];
	siic pile;
	Enemigo();
	~Enemigo();
	void setPosEnemigo(int px, int py);
	void mover();
	void dibujar(sf::RenderWindow &pmWindow);
	sf::CircleShape getEnemigoShape();
	void initDj();
	ii BuscaPortalMan(ii posPortalInicial, char ColorActual, vii portales, vvi GPortales);
	bool hayPortal(ii pos, int ** maze);
	viii GeneraListaAdyDj(ii nodo, int colM, vii posPortales, vvi GPortales, int **maze);
	bool posValidaDJ(ii pos, int col, int fil);
	bool hayParedBFS(ii pos, int** maze);
	void Dijkstra(ii nodoI, int ** maze, int col, int fil, int colM, vii Portales, vvi GPortales, vii Puertas);
	siic PilaHaciaSalidaDJColor(ii pexit, int ** maze, int colM);
	void CaminoJugadorDJ(ii posJugaodr, int ** maze, int colM, vii Portales, int fil, int col, vvi GPortales, vii Puertas);
};

