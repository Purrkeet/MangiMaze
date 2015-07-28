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
/////////
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
	Enemigo()
	{

		dx = 0.2f;
		dy = 0.2f;
		pile = siic();
		sEnemigo = sf::CircleShape(5);
		sEnemigo.setFillColor(sf::Color::Cyan);
		int tipo = rand() % 3 + 1;
		if (tipo == 1)
			sEnemigo.setFillColor(sf::Color::Red);
		if (tipo == 2)
			sEnemigo.setFillColor(sf::Color::Blue);
		if (tipo == 3)
			sEnemigo.setFillColor(sf::Color::Green);
	}
	~Enemigo(){}
	void setPosEnemigo(int px, int py)
	{
		
		sEnemigo.setPosition(offsetC + px * anchoBloque, offsetC + py * anchoBloque);
	}
	void mover()
	{
	//verificar colision optimizada 
		iic par = pile.top();
		ii pos = par.first;
		char c = par.second;
		ii posJugadorTI = make_pair(sEnemigo.getGlobalBounds().left, sEnemigo.getGlobalBounds().top);
		//recibe X,Y o sea Col, Fil en el pair
		//usar solo una vez, poner despues de generar matriz
		posJugadorTI.first -= offsetC;
		posJugadorTI.second -= offsetC;

		posJugadorTI.first /= anchoBloque;
		posJugadorTI.second /= anchoBloque;
		if (pos == posJugadorTI)
			pile.pop();
		else

			sEnemigo.move( pos.first-posJugadorTI.first, pos.second-posJugadorTI.second);
	}
	void dibujar(sf::RenderWindow &pmWindow)
	{
		pmWindow.draw(sEnemigo);
	}
	sf::CircleShape getEnemigoShape(){
		return sEnemigo;
	}
	void initDj() {

		for (int i = 0; i < MAXMATRIX; i++)
		{
			for (int j = 0; j < MAXMATRIX; j++)
			{
				matVisitados[i][j] = INF; // seteo con valores infinitos a la matriz visitados
			}

		}
		memset(matPadres, -1, sizeof(matVisitados));
	}
	ii BuscaPortalMan(ii posPortalInicial, char ColorActual, vii portales,vvi GPortales) { //retorna en  X luego Y
		int tPortal = 0;
		switch (ColorActual)
		{
		case 'R':  tPortal = 0; break;
		case 'A':  tPortal = 1; break;
		case 'V':  tPortal = 2; break;
		case 'B':
			return ii(-1, -1);
		}
		int i = 0; int posPort = -1;
		posPortalInicial = ii(posPortalInicial.second, posPortalInicial.first);
		for (; i < portales.size(); ++i){
			if (portales[i] == posPortalInicial){

				posPort = GPortales[i][tPortal];
				if (posPort == -1) return ii(-1, -1);
				break;

			}
		}
		return portales[posPort];
	}
	bool hayPortal(ii pos,int ** maze) {
		if (maze[pos.first][pos.second] == 'A' || maze[pos.first][pos.second] == 'R' || maze[pos.first][pos.second] == 'V')
			return true;
		return false;
	}
	viii GeneraListaAdyDj(ii nodo,int colM,vii posPortales,vvi GPortales,int **maze) {
		viii ady = viii();
		bool hayPortalB = hayPortal(ii(nodo.second, nodo.first),maze);
		bool VieneDeOtroPortal = false;
		if (hayPortalB){
			int posFirst = matPadres[nodo.first][nodo.second] % colM; // +offset;
			int posSecond = matPadres[nodo.first][nodo.second] / colM;
			VieneDeOtroPortal = hayPortal(ii(posSecond, posFirst),maze); //revisar si encuentra bien el portal
		}

		if (hayPortalB && !VieneDeOtroPortal){
			//si hay portal entoncesse evalua la arista entre los portales de cada color
			ii sigPort = BuscaPortalMan(ii(nodo.second, nodo.first), 'R', posPortales,GPortales); //revisar si coinciden
			ady.push_back(iii(0, sigPort));
			sigPort = BuscaPortalMan(ii(nodo.second, nodo.first), 'A', posPortales,GPortales); //revisar si coinciden
			ady.push_back(iii(0, sigPort));
			sigPort = BuscaPortalMan(ii(nodo.second, nodo.first), 'V', posPortales,GPortales); //revisar si coinciden
			ady.push_back(iii(0, sigPort));
		}
		else{
			/*ady.push_back(make_pair(nodo.second + 1,nodo.first));
			ady.push_back(make_pair(nodo.second - 1,nodo.first));
			ady.push_back(make_pair(nodo.second	  , nodo.first + 1));
			ady.push_back(make_pair(nodo.second	  , nodo.first - 1));*/
			ady.push_back(iii(1, (make_pair(nodo.first + 1, nodo.second))));
			ady.push_back(iii(1, (make_pair(nodo.first - 1, nodo.second))));
			ady.push_back(iii(1, (make_pair(nodo.first, nodo.second + 1))));
			ady.push_back(iii(1, (make_pair(nodo.first, nodo.second - 1))));

		}



		return ady;
	}
	bool posValidaDJ(ii pos,int col,int fil) { //puede ir uno mas abajo para llegar a marcar la salida
		if (pos.first >col || pos.second >fil + 1 || pos.first<offset || pos.second<offset)
			return false;
		return true;
	}
	bool hayParedBFS(ii pos,int** maze) {
		if (maze[pos.second][pos.first] != muro)
			return false;
		return true;
	}
	void Dijkstra(ii nodoI,int ** maze,int col,int fil,int colM,vii Portales,vvi GPortales,vii Puertas) {
		initDj();
		// X col               Y fil
		int nodoi = nodoI.first;
		int nodoj = nodoI.second;
		if (nodoi == 0)
			nodoI = ii(nodoi + 1, nodoj);
		if (nodoj == 0)
			nodoI = ii(nodoi, nodoj + 1);
		if (nodoi == col)
			nodoI = ii(nodoi - 1, nodoj);
		if (nodoj == fil)
			nodoI = ii(nodoi, nodoj - 1);
		matVisitados[nodoI.first][nodoI.second] = 0;
		//enumerar cada posicion de la matriz en fil*tamanio columnas + col;
		matPadres[nodoI.first][nodoI.second] = nodoI.second * colM + nodoI.first;
		//vi ady = GeneraListaAdy(nodoI);
		pq Cola = pq();
		Cola.push(iii(0, nodoI));

		while (!Cola.empty()) {
			iii nodoAct = Cola.top(); Cola.pop();
			int pesoNodo = nodoAct.first;
			ii posAct = nodoAct.second;
			viii ady = GeneraListaAdyDj(posAct,colM,Portales,GPortales,maze);  int sza = ady.size();
			for (int i = 0; i< sza; ++i) { //-1 no matVisitados, -2 pared , otro numero es el orden

				if (!posValidaDJ(ady[i].second,col,fil)) continue;
				ii nodoSig = ady[i].second;
				if (matVisitados[nodoSig.first][nodoSig.second] == -2) continue; //si es pared obviar
				//si encontro salida (EN BFS el primero es el m�s cercano)
				//if (maze[ady[i].second][ady[i].first] == 'S') {
				//	matVisitados[ady[i].first][ady[i].second] = matVisitados[aux.first][aux.second] + 1;
				//	//parche para que no busque despues de la salida
				//	matVisitados[ady[i].first][ady[i].second + 1] = -2; //seteado como pared
				//	//Cola = qii();//vacia la cola para salir del while
				//	//break;
				//}

				if (hayParedBFS(nodoSig,maze)) {
					matVisitados[nodoSig.first][nodoSig.second] = -2;
					continue;
				}
				//RELAX
				int pesoAlNodo = ady[i].first;
				if (matVisitados[nodoSig.first][nodoSig.second] >
					matVisitados[posAct.first][posAct.second] + pesoAlNodo){

					matVisitados[nodoSig.first][nodoSig.second] = matVisitados[posAct.first][posAct.second] + pesoAlNodo;
					matPadres[nodoSig.first][nodoSig.second] = posAct.second * colM + posAct.first;// +offset; //crea un hash del padre
					Cola.push(iii(matVisitados[nodoSig.first][nodoSig.second], nodoSig));
				}

			}
		}

		//termino xd

	}
	siic PilaHaciaSalidaDJColor(ii pexit,int ** maze,int colM) {
		int idx = matVisitados[pexit.second][pexit.first]; //menor camino

		siic caminoAcasa = siic();
		char color = 'B';  //blanco por defecto sin color desde la salida hacia atras
		iic pivot = iic(pexit, color);
		caminoAcasa.push(pivot);
		bool ayuda = false;
		while (idx > 0)
		{
			ii nodo = pivot.first;
			int hash = matPadres[nodo.second][nodo.first];
			int posFirst = hash % colM;
			int posSecond = hash / colM;
			idx = matVisitados[posFirst][posSecond];
			bool ExistePortal = hayPortal(ii(posSecond, posFirst),maze);
			if (ExistePortal && !ayuda){
				color = maze[posSecond][posFirst];
				ayuda = true;
			}
			else if (ayuda){
				ayuda = false;
			}
			pivot = iic(ii(posSecond, posFirst), color);
			caminoAcasa.push(pivot);
		}
		return caminoAcasa;
	}
	void CaminoJugadorDJ(ii posJugaodr,int ** maze,int colM,vii Portales,int fil,int col,vvi GPortales,vii Puertas) {
		ii posJugadorTI = make_pair(sEnemigo.getGlobalBounds().left, sEnemigo.getGlobalBounds().top);
		//recibe X,Y o sea Col, Fil en el pair
	 //usar solo una vez, poner despues de generar matriz
		posJugadorTI.first -= offsetC;
		posJugadorTI.second -= offsetC;

		posJugadorTI.first /= anchoBloque;
		posJugadorTI.second /= anchoBloque;
		Dijkstra(make_pair(posJugadorTI.first, posJugadorTI.second),maze,col,fil,colM,Portales,GPortales,Puertas);

		pile = PilaHaciaSalidaDJColor(posJugaodr,maze,colM);

	}
};

