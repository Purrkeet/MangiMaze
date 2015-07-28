#pragma once
#include "Enemigo.h"
#include "Bala.h"
using namespace std;

//typedef vector<int> vi;
//typedef vector<vi> vvi;
typedef vector<Enemigo> vE;
//typedef vector<bool> vb;
//typedef pair<int, int> ii;
//typedef pair<int, ii> iii;
//typedef vector<vi> Gi;
//typedef vector<ii> vii;
//typedef vector<vii> vvii;
//typedef queue<ii> qii;
//typedef stack<ii> sii;
//typedef pair<ii, char> iic;
//typedef stack<iic> siic;
//typedef vector<iii> viii;
//typedef priority_queue < iii, viii, greater<iii> > pq;
/*
#define MAXMATRIX 77
#define INF 99999

#define muro '#'
#define noMuro 'O'
#define offset 1
#define offsetC 50
#define anchoBloque 20
*/
class juego
{
private:
	int filM, colM; // seria filM y colM
	char maze[MAXMATRIX][MAXMATRIX];
	int fil, col;
	vb visitado;
	//
	vii puertasEnemigos;
	vE Venemigos;
	//
	int matPadres[MAXMATRIX][MAXMATRIX];
	int matVisitados[MAXMATRIX][MAXMATRIX];
	int JugadorX, JugadorY;
	int direccionBala;
	char color;
	float conEnemigosT;
	vi portalesActivos;
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::Image iStuffMapa;
	sf::Texture tStuffmapa;

	int contador;
	sf::Image iHero;
	sf::Texture tHero;
	vector<sf::IntRect> vHeroAdelante;
	vector<sf::IntRect> vHeroAtras;
	vector<sf::IntRect> vHeroDerecha;
	vector<sf::IntRect> vHeroIzquierda;
	vector<sf::RectangleShape> vecMunicion;
	sf::RenderWindow *mWindow;
	 
	int mapaRandom;
	vector<sf::RectangleShape> vecr;
	vector <Enemigo> enemigos;
	vector <sf::CircleShape> puertas;

	vector<sf::RectangleShape> vecrSol;
	vector<sf::CircleShape> vecPort;
	sf::CircleShape Jugador;
	vii posPortales;
	CBala *bala;
	bool	mIsMovingUp;
	bool	mIsMovingDown;
	bool	mIsMovingRight;
	bool	mIsMovingLeft;

	//cambios Steve lunes 26-06
	int ColiBalaX;
	int ColiBalaY;

	//DAMBERT
	int CANTIDADBALAS;
	int NIVEL;
	int PUNTAJE_ACUMULADO;
	//ERIK
	float TiempoG;

public:
	juego() ://mWindow(sf::VideoMode(900, 700), "Mangimaze", sf::Style::Close), 
                    Jugador(8)
		, iStuffMapa(), tStuffmapa(), mIsMovingUp(false)
		, mIsMovingDown(false)
		, mIsMovingRight(false)
		, mIsMovingLeft(false)
	{
                mWindow = new sf::RenderWindow(sf::VideoMode(900, 700), "Mangimaze", sf::Style::Close);
		mWindow->setVerticalSyncEnabled(true);

		vecr = vector<sf::RectangleShape>();
		vecrSol = vector<sf::RectangleShape>();
		vecPort = vector<sf::CircleShape>();
		vecMunicion = vector<sf::RectangleShape>();
		conEnemigosT = 0;

		iStuffMapa.loadFromFile("images/mapaStuff - Copy.bmp");
		iStuffMapa.createMaskFromColor(iStuffMapa.getPixel(0, 153));
		tStuffmapa.loadFromImage(iStuffMapa);
		tStuffmapa.setSmooth(true);

		iHero.loadFromFile("images/Hero.png");
		iHero.createMaskFromColor(iHero.getPixel(0, 0));
		tHero.loadFromImage(iHero);
		tHero.setSmooth(true);
		Jugador.setTexture(&tHero);

		vHeroAdelante = vector<sf::IntRect>();
		vHeroAtras = vector<sf::IntRect>();
		vHeroDerecha = vector<sf::IntRect>();
		vHeroIzquierda = vector<sf::IntRect>();
		//adelante caminando
		vHeroAdelante.push_back(sf::IntRect(1, 3, 17, 23));
		vHeroAdelante.push_back(sf::IntRect(19, 1, 17, 25));
		vHeroAdelante.push_back(sf::IntRect(37, 1, 17, 25));
		vHeroAdelante.push_back(sf::IntRect(1, 3, 17, 23));
		vHeroAdelante.push_back(sf::IntRect(19, 1, 17, 25));
		vHeroAdelante.push_back(sf::IntRect(37, 1, 17, 25));
		////derecha caminando
		vHeroDerecha.push_back(sf::IntRect(1, 29, 17, 23));
		vHeroDerecha.push_back(sf::IntRect(19, 28, 17, 24));
		vHeroDerecha.push_back(sf::IntRect(37, 29, 17, 23));
		vHeroDerecha.push_back(sf::IntRect(1, 29, 17, 23));
		vHeroDerecha.push_back(sf::IntRect(19, 28, 17, 24));
		vHeroDerecha.push_back(sf::IntRect(37, 29, 17, 23));
		////izquierda caminando
		vHeroIzquierda.push_back(sf::IntRect(1, 55, 17, 23));
		vHeroIzquierda.push_back(sf::IntRect(19, 54, 17, 24));
		vHeroIzquierda.push_back(sf::IntRect(37, 55, 17, 23));
		vHeroIzquierda.push_back(sf::IntRect(1, 55, 17, 23));
		vHeroIzquierda.push_back(sf::IntRect(19, 54, 17, 24));
		vHeroIzquierda.push_back(sf::IntRect(37, 55, 17, 23));
		////atras caminando
		vHeroAtras.push_back(sf::IntRect(1, 82, 17, 23));
		vHeroAtras.push_back(sf::IntRect(19, 80, 17, 25));
		vHeroAtras.push_back(sf::IntRect(37, 80, 17, 25));
		vHeroAtras.push_back(sf::IntRect(1, 82, 17, 23));
		vHeroAtras.push_back(sf::IntRect(19, 80, 17, 25));
		vHeroAtras.push_back(sf::IntRect(37, 80, 17, 25));
		
		Jugador.setTextureRect(vHeroAdelante[0]);
		Jugador.setOrigin(2 + Jugador.getGlobalBounds().width / 2, 2 + Jugador.getGlobalBounds().height / 2);
		//Jugador.setRotation(180);

		bala= nullptr;
		direccionBala = 0;
		contador = 0;
		
		fil = 25, col = 25;
		if (fil % 2 == 0)fil--;
		if (col % 2 == 0)col--;
		init();
		
		//tipo de mapa
		mapaRandom = rand() % 7;
		//Genera una pos aleatoria las columnas deben ser mayor a 1
		//int posfI=rand()%(fil-1), poscI=rand()%(col-1);
		//se marca aleatoriamente alguna pared de primera columna
		int posfI = rand() % (fil)+offset, poscI = offset;
		//if(poscI%2!=0)poscI+=1;
		if (posfI % 2 == 0)posfI += 1;
		//llama a DFS
		DFS(make_pair(posfI, poscI));
		//imprime lo generado
		GeneraEntradaYSalida();
		generarPortales(vecPort, posPortales);
		print2();
		iniciarSpritesCabrilla();
		ponerPersonaje(Jugador);
		color = 'B';
		//DAMBERT
		CANTIDADBALAS = 5;
		NIVEL = 1;
		PUNTAJE_ACUMULADO = 0;
		//ERIK
		TiempoG = 0.f;
	}
	~juego(){}

	bool hayParedBFS(ii pos) {
		if (maze[pos.second][pos.first] != muro)
			return false;
		return true;
	}
	bool posValidaBFS(ii pos) {
		if (pos.first >colM || pos.second >filM || pos.first<0 || pos.second<0) {
			return false;
		}
		return true;
	}
	vii GeneraListaAdyBFS(ii nodo) {
		vii ady = vii();
		ady.push_back(make_pair(nodo.first + 1, nodo.second));
		ady.push_back(make_pair(nodo.first - 1, nodo.second));
		ady.push_back(make_pair(nodo.first, nodo.second + 1));
		ady.push_back(make_pair(nodo.first, nodo.second - 1));
		return ady;
	}
	void initBFS() {
		memset(matVisitados, -1, sizeof(matVisitados)); // seteo con -1 al array de matVisitadoss
	}
	void BFS(ii nodoI) {
		initBFS();
		matVisitados[nodoI.first][nodoI.second] = 0;
		qii Cola = qii();
		Cola.push(nodoI);

		while (!Cola.empty()) {
			ii aux = Cola.front(); Cola.pop();
			vii ady = GeneraListaAdyBFS(aux);
			for (int i = 0; i< 4; ++i) { //-1 no matVisitados, -2 pared , otro numero es el orden
				if (matVisitados[ady[i].first][ady[i].second] > -1) continue; //si es positivo obviar
				//si encontro salida (EN BFS el primero es el m�s cercano)
				if (maze[ady[i].second][ady[i].first] == 'S') {
					matVisitados[ady[i].first][ady[i].second] = matVisitados[aux.first][aux.second] + 1;
					Cola = qii();//vacia la cola para salir del while
					break;
				}

				if (hayParedBFS(ady[i])) {
					matVisitados[ady[i].first][ady[i].second] = -2;
					continue;
				}
				matVisitados[ady[i].first][ady[i].second] = matVisitados[aux.first][aux.second] + 1;
				Cola.push(ady[i]);
			}
		}
	}


	ii BuscarSalida() {
		for (int i = 0; i< filM; ++i) {
			for (int j = 0; j< colM; ++j) {
				if (maze[i][j] == 'S')
				{
					return make_pair(i, j);
				}
			}
		}
	}
	ii BuscarEntrada() {
		for (int i = 0; i< filM; ++i) {
			for (int j = 0; j< colM; ++j) {
				if (maze[i][j] == 'E')
				{
					return make_pair(i, j);
				}
			}
		}
	}
	sii PilaHaciaSalida(ii pexit) {
		int idx = matVisitados[pexit.second][pexit.first]; //menor camino
		ii pivot = pexit;
		sii caminoAcasa = sii();
		caminoAcasa.push(pivot);
		while (idx != 0)
		{
			vii ady = GeneraListaAdyBFS(pivot);
			for (int i = 0; i < 4; i++)
			{
				ii aux = ady[i];
				if (colM <= ady[i].first || filM <= ady[i].second) continue;//
				if (matVisitados[ady[i].second][ady[i].first] < 0) continue;
				if (matVisitados[ady[i].second][ady[i].first] == idx - 1) {
					idx--;
					pivot = ady[i];
					caminoAcasa.push(pivot);
					break;
				}
			}
		}
		return caminoAcasa;
	}
	sii CaminoSalida(ii posJugador) {
		//recibe X,Y o sea Col, Fil en el pair
		ii salida = BuscarSalida(); //usar solo una vez, poner despues de generar matriz
		BFS(make_pair(posJugador.first, posJugador.second));
		return PilaHaciaSalida(salida);
	}
	void print4() {
		for (int i = 0; i < filM; ++i) {
			for (int j = 0; j < colM; ++j) {
				cout << matVisitados[j][i] << " ";
			}
			cout << endl;
		}
	}
	void print3(sii pila) {
		while (!pila.empty())
		{
			cout << pila.top().first << ", " << pila.top().second << endl;
			pila.pop();
		}
	}
	viii GeneraListaAdyDj(ii nodo) {
		viii ady = viii();
		bool hayPortalB = hayPortal(ii(nodo.second, nodo.first));
		bool VieneDeOtroPortal = false;
		if (hayPortalB){
			int posFirst = matPadres[nodo.first][nodo.second] % colM; // +offset;
			int posSecond = matPadres[nodo.first][nodo.second] / colM;
			VieneDeOtroPortal = hayPortal(ii(posSecond, posFirst)); //revisar si encuentra bien el portal
		}

		if (hayPortalB && !VieneDeOtroPortal){
			//si hay portal entoncesse evalua la arista entre los portales de cada color
			ii sigPort = BuscaPortalMan(ii(nodo.second, nodo.first), 'R', posPortales); //revisar si coinciden
			ady.push_back(iii(0, sigPort));
			sigPort = BuscaPortalMan(ii(nodo.second, nodo.first), 'A', posPortales); //revisar si coinciden
			ady.push_back(iii(0, sigPort));
			sigPort = BuscaPortalMan(ii(nodo.second, nodo.first), 'V', posPortales); //revisar si coinciden
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
	bool posValidaDJ(ii pos) { //puede ir uno mas abajo para llegar a marcar la salida
		if (pos.first >col || pos.second >fil + 1 || pos.first<offset || pos.second<offset)
			return false;
		return true;
	}
	void Dijkstra(ii nodoI) {
		initDj();
		// X col               Y fil
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
			viii ady = GeneraListaAdyDj(posAct);  int sza = ady.size();
			for (int i = 0; i< sza; ++i) { //-1 no matVisitados, -2 pared , otro numero es el orden

				if (!posValidaDJ(ady[i].second)) continue;
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

				if (hayParedBFS(nodoSig)) {
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
	siic PilaHaciaSalidaDJColor(ii pexit) {
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
			bool ExistePortal = hayPortal(ii(posSecond, posFirst));
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
	siic CaminoSalidaDJ(ii posJugador) {
		//recibe X,Y o sea Col, Fil en el pair
		ii salida = BuscarSalida(); //usar solo una vez, poner despues de generar matriz

		Dijkstra(make_pair(posJugador.first, posJugador.second));

		return PilaHaciaSalidaDJColor(salida);

	}
	
	bool hayPared(ii pos) {
		if (maze[pos.first][pos.second] == muro)
			return false;
		return true;
	}
	bool posValida(ii pos) {
		if (pos.first >fil || pos.second >col || pos.first<offset || pos.second<offset) {
			return false;
		}
		return true;
	}
	ii NodoxDirec(const int &d, const ii &nodoI, ii &nodoPas) { //NodoPasadizo, llenar el hueco
		ii sigNodo = nodoI;
		nodoPas = nodoI;
		switch (d) {//0arriba 1derecha 2abajo 3izquierda
		case 0: sigNodo.first -= 2; nodoPas.first--; break;
		case 1: sigNodo.second += 2; nodoPas.second++; break;
		case 2: sigNodo.first += 2; nodoPas.first++; break;
		case 3: sigNodo.second -= 2; nodoPas.second--; break;
		}
		return sigNodo;
	}
	vi GeneraListaAdy() {
		vi ady = vi(4, -1);
		int c_ord = 0;
		while (c_ord<4) {
			int direc = rand() % 4;	//0arriba 1derecha 2abajo 3izquierda
			//cout <<"direccion elegida: "<< direc<<" elem act en esa direc: "<<ady[direc]<<endl;
			if (ady[direc] == -1) {
				ady[direc] = c_ord++;
			}
		}
		return ady;
	}
	// usado para DEbugear using namespace System;
	void print2() {
		for (int i = 0; i<filM; ++i) {
			for (int j = 0; j<colM; ++j) {
				cout << maze[i][j];
			}
			cout << endl;
		}
	}
	void DFS(ii nodo) {
		// marca
		maze[nodo.first][nodo.second] = noMuro;
		//generas aleatoriamente el orden de una lista de adyacencias
		vi Avisitar = GeneraListaAdy();
		//guardo el tama�o (aunque siempre sera 4 :/ )
		int sz = Avisitar.size();
		//cout <<endl<<sz<<endl;
		//for(int a=0; a<4;++a){cout <<Avisitar[a]<<" ";}cout<<endl;
		for (int i = offset; i<sz + offset; ++i) {
			//saco la direccion y lo transformo en la posici�n siguiente
			ii nodopasadizo;
			ii sigNodo = NodoxDirec(Avisitar.back(), nodo, nodopasadizo);
			//elimino de la lista la posicion seleccionada
			Avisitar.pop_back();
			//valida si la posion es valida
			//cout <<" es valido? "<<sigNodo.first<< " "<<sigNodo.second<<endl;
			if (posValida(sigNodo)) {
				//valido que no exista ya una pared en la posicion
				if (!hayPared(sigNodo)) {
					//al no haber se marca la pared intermedia
					maze[nodopasadizo.first][nodopasadizo.second] = noMuro;
					//se llama a DFS con la pos siguiente como muro
					//para que vuelva a marcar y busque posiciones
					DFS(sigNodo);
				}
			}
		}
	}
	void init() {
		filM = fil + 2 * offset;
		colM = col + 2 * offset;

		for (int i = 0; i<filM; ++i) {
			for (int j = 0; j<colM; ++j) {
				/*if(i==0 || i==fil-1 || j==0 || j==col-1)
				maze[i][j]=noMuro;
				else*/
				maze[i][j] = muro;
			}
		}
	}
	void CrearHuecosAleatorios() {
		//busca aleatoriamente
		int c_huecos = 0;
		//la cantidadde huecos debe ser proporcional por cada 27 bloques es 3 huecos
		int c_maxHuecos = (fil*col / 27) * 2;
		while (c_huecos<c_maxHuecos) {
			int i = rand() % fil + offset, j = rand() % col + offset;
			if (!hayPared(make_pair(i, j))) { // hay pared xd
				//para que no haga cualquier hueco, solo donde haya una pared que divida dos caminos
				if ((!hayPared(make_pair(i - 1, j)) && !hayPared(make_pair(i + 1, j)) && hayPared(make_pair(i, j - 1)) && hayPared(make_pair(i, j + 1)))
					|| (!hayPared(make_pair(i, j - 1)) && !hayPared(make_pair(i, j + 1)) && hayPared(make_pair(i - 1, j)) && hayPared(make_pair(i + 1, j)))) {
					c_huecos++; maze[i][j] = noMuro;
				}
			}
		}
	}
	bool hayPortal(ii pos) {
		if (maze[pos.first][pos.second] == 'A' || maze[pos.first][pos.second] == 'R' || maze[pos.first][pos.second] == 'V')
			return true;
		return false;
	}
	void verDestinoTeleport(vii pPosp, char Color, sf::CircleShape &pCircle, ii parp)
	{
		for (int i = 0; i < pPosp.size(); i++)
		{
			if (parp.second != pPosp[i].first&& parp.first != pPosp[i].second)
			{
				if (maze[pPosp[i].first][pPosp[i].second] == Color)
				{
					pCircle.setPosition(sf::Vector2f(offsetC + pPosp[i].second * anchoBloque, offsetC + pPosp[i].first * anchoBloque));
					break;
				}
			}

		}
	}
	bool colisionPortal(sf::CircleShape personaje)
	{
		vii posiciones = vii();
		ii posJugadorTI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top);//por jugador arriba izquierda  X Y
		ii posJugadorTD = make_pair(personaje.getGlobalBounds().left + personaje.getGlobalBounds().width, personaje.getGlobalBounds().top);
		ii posJugadorBI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top + personaje.getGlobalBounds().height);
		ii posJugadorBD = make_pair(personaje.getGlobalBounds().left + personaje.getGlobalBounds().width,
			personaje.getGlobalBounds().top + personaje.getGlobalBounds().height);

		posiciones.push_back(posJugadorBD);
		posiciones.push_back(posJugadorBI);
		posiciones.push_back(posJugadorTD);
		posiciones.push_back(posJugadorTI);
		bool chocaPortal = true;
		for (int i = 0; i < 4; ++i){
			posiciones[i].first -= offsetC;
			posiciones[i].second -= offsetC;

			posiciones[i].first /= anchoBloque;
			posiciones[i].second /= anchoBloque;

			//chocaPared |= hayParedBFS(make_pair(posiciones[i].second,posiciones[i].first));
			//chocaPared |= hayParedBFS(posiciones[i]);
			//chocaPortal |= hayPortal(posiciones[i]);
			chocaPortal &= hayPortal(make_pair(posiciones[i].second, posiciones[i].first));
		}
		return chocaPortal;
	}
	//CAMBIOSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
	int distManhattan(const ii &a, const ii &b){
		return abs(a.first - b.first) + abs(a.second - b.second);
	}
	bool cmpDistRelativaSupIzq(const ii &a, const ii &b){
		//Compara Distancias Relativas a la esquina Superior Izquierda del Maze
		//segun la rubrica, 
		//la distancia primero hacia arriba y luego derecha 
		//para cuando los portales tienen distancias manhattan iguales

		if (a.first == b.first){ //cuando comparten la primera componente
			//retorna la comparaci�n el menor de la seguna componente
			return a.second < b.second;
		}
		return a.first < b.first;

	}
	vector<char> ColorPortales;
	vvi GPortales; //Grafo portales 

	ii BuscaPortalMan(ii posPortalInicial, char ColorActual, vii portales) { //retorna en  X luego Y
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
	int _BuscaPortalMan(ii posPortalInicial, char ColorActual, vii portales) { //retorna en  X luego Y
		//primero obtiene el color del jugador
		//char color = ColorJ; //CAMBIAR ColorJ por el color del Jugador!!
		//busca en el vector de portales
		int sz = portales.size();
		vii portalesdelColor = vii();
		vi posPortColAux = vi();
		//posPortalInicial = make_pair(posPortalInicial.second, posPortalInicial.first);
		//invertir
		//posPortalInicial = make_pair(posPortalInicial.second, posPortalInicial.first);
		ii aux = posPortalInicial;
		for (int i = 0; i < sz; ++i){
			//nunca teletransporta al mismo portal

			if (posPortalInicial == portales[i]) continue;
			//primero Y luego X
			//if (maze[portales[i].second][portales[i].first] == ColorActual){
			if (ColorPortales[i] == ColorActual){
				//si es el color se guarda en un vector de portales auxiliar del color que tiene el jugador
				portalesdelColor.push_back(portales[i]);
				posPortColAux.push_back(i);
			}
		}
		//si el vector de portales del color del jugador no existe, entonces el jugador muere!!
		sz = portalesdelColor.size();
		if (sz == 0){
			//PARA HACER: JUGADOR MUERE 
			//como Flag se env�a una posici�n que no existe
			return -1;
		}

		//busca la mejor opci�n
		ii menor = portalesdelColor[0];
		int posAux = 0;
		for (int i = 1; i < sz; ++i){
			//si es estrictamente MENOR entonces se elige el anterior
			int distMenor = distManhattan(posPortalInicial, menor);
			int distAux = distManhattan(posPortalInicial, portalesdelColor[i]);
			if (distMenor> distAux){
				menor = portalesdelColor[i];
				posAux = i;
			}
			else // si las distancias manhattan son iguales
			if (distMenor == distAux){
				//elegir el que esta m�s arriba
				//NO (es la primera distancia relativa menor que la segunda?)
				if (!cmpDistRelativaSupIzq(menor, portalesdelColor[i])){
					menor = portalesdelColor[i];
					posAux = i;
				}
			}
		}

		return posPortColAux[posAux]; //devuelve el ID del portal
	}
	void generarPortales(vector<sf::CircleShape> &pvecrPort, vii &Pport)
	{
		int portales = 0;
		int portal_max = ((fil*col / 81) * 2);
		GPortales = vvi(portal_max);
		char tipoPortal = 'R';


		while (portales < portal_max)
		{
			sf::CircleShape portal(10.f);
			int i = rand() % fil + offset, j = rand() % col + offset;
			if (maze[i][j] == 'R' || maze[i][j] == 'A' || maze[i][j] == 'V'){
				continue; //si un portal se crea encima
			}
			if (hayPared(ii(i - 1, j)) && hayPared(ii(i + 1, j)) && hayPared(ii(i, j - 1)) && hayPared(ii(i, j + 1))){
				continue; //si un portal se crea en medio de 4 paredes que vuelva a generarse

			}
			portal.setPosition(sf::Vector2f(offsetC + j * anchoBloque, offsetC + i * anchoBloque));
			int a = rand() % 3 + 1;// color del portal
			if (a == 1)
			{
				tipoPortal = 'R';
				portal.setFillColor(sf::Color::Red);
				//portal.setTextureRect(sf::IntRect(469,427,16,16));
			}
			if (a == 2)
			{
				tipoPortal = 'A';
				portal.setFillColor(sf::Color::Blue);
			}

			if (a == 3)
			{
				tipoPortal = 'V';
				portal.setFillColor(sf::Color::Green);
			}
			maze[i][j] = tipoPortal;
			pvecrPort.push_back(portal);
			Pport.push_back(make_pair(j, i));
			ColorPortales.push_back(tipoPortal);////// guarda el color y ID de portales
			portales++;

		}

		//Una vez generados buscamos los caminos para todos los portales
		// distancias manhattann
		//llenamos el grafo de portales
		for (int i = 0; i < portal_max; ++i){

			//iteramos por la cantidad de colores
			for (int c = 0; c < 3; ++c){
				char colo = 'R';
				switch (c)
				{
				case 0: colo = 'R'; break;
				case 1: colo = 'A'; break;
				case 2: colo = 'V'; break;
				default:
					break;
				}
				int sigPortal = _BuscaPortalMan(Pport[i], colo, Pport);
				GPortales[i].push_back(sigPortal);
			}
		}


	}
	void CrearCajaDeBalas() {
		//busca aleatoriamente
		int c_huecos = 0;
		//la cantidadde huecos debe ser proporcional por cada 27 bloques es 3 huecos
		int c_maxHuecos = 2;
		sf::RectangleShape shape(sf::Vector2f(anchoBloque - 5, anchoBloque - 5));
		while (c_huecos<c_maxHuecos) {
			int i = rand() % fil + offset, j = rand() % col + offset;
			if (hayPared(make_pair(i, j))) { // hay pared xd
				//para que no haga cualquier hueco, solo donde haya una pared que divida dos caminos
				if ((!hayPared(make_pair(i - 1, j)) && !hayPared(make_pair(i + 1, j)) && hayPared(make_pair(i, j - 1)) && hayPared(make_pair(i, j + 1)))
					|| (!hayPared(make_pair(i, j - 1)) && !hayPared(make_pair(i, j + 1)) && hayPared(make_pair(i - 1, j)) && hayPared(make_pair(i + 1, j)))) {
					c_huecos++;
					shape.setPosition(sf::Vector2f(offsetC + j * anchoBloque + 2, offsetC + i * anchoBloque + 2));
					shape.setTexture(&tStuffmapa);
					shape.setTextureRect(sf::IntRect(0, 153, 24, 24));
					vecMunicion.push_back(shape);
				}
			}
		}
	}
	void GeneraEntradaYSalida() {
		bool Entrada_b = true, Salida_b = true;
		CrearHuecosAleatorios();
		CrearCajaDeBalas();
		int entrada, salida;
		while (Entrada_b) {
			entrada = rand() % col; //fila 0
			if (maze[offset][entrada] != muro) {
				maze[0][entrada] = 'E';
				Entrada_b = false;
			}
		}
		while (Salida_b) {
			salida = rand() % col; //fila ultima
			if (maze[fil][salida] != muro) {
				maze[filM - 1][salida] = 'S';
				Salida_b = false;
			}
		}
	}
	bool colisionaOptimizado(sf::CircleShape personaje){
		vii posiciones = vii();
		ii posJugadorTI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top);//por jugador arriba izquierda  X Y
		ii posJugadorTD = make_pair(personaje.getGlobalBounds().left + personaje.getGlobalBounds().width, personaje.getGlobalBounds().top);
		ii posJugadorBI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top + personaje.getGlobalBounds().height);
		ii posJugadorBD = make_pair(personaje.getGlobalBounds().left + personaje.getGlobalBounds().width,
			personaje.getGlobalBounds().top + personaje.getGlobalBounds().height);
		posiciones.push_back(posJugadorBD);
		posiciones.push_back(posJugadorBI);
		posiciones.push_back(posJugadorTD);
		posiciones.push_back(posJugadorTI);
		bool chocaPared = false;
		for (int i = 0; i < 4; ++i){
			posiciones[i].first -= offsetC;
			posiciones[i].second -= offsetC;
			posiciones[i].first /= anchoBloque;
			posiciones[i].second /= anchoBloque;
			chocaPared |= !hayPared(make_pair(posiciones[i].second, posiciones[i].first));
			if (chocaPared){ ColiBalaX = posiciones[i].first; ColiBalaY = posiciones[i].second; }
		}
		return chocaPared;
	}
	void pintarSolucion(siic pPila, vector<sf::RectangleShape> &pvecrSol)
	{
		while (!pPila.empty()){
			iic valorx = pPila.top();
			ii valor = valorx.first;
			pPila.pop();
			sf::RectangleShape shape(sf::Vector2f(anchoBloque, anchoBloque));
			shape.setPosition(sf::Vector2f(offsetC + valor.second * anchoBloque, offsetC + valor.first * anchoBloque));
			sf::Color colorin=sf::Color::White;
			switch (valorx.second)
			{
			case 'A': colorin = sf::Color::Blue; break;
			case 'V': colorin = sf::Color::Green; break;
			case 'R': colorin = sf::Color::Red; break;
			case 'B': colorin = sf::Color::White; break;
			default:
				break;
			}
			shape.setFillColor(colorin);
			pvecrSol.push_back(shape);
		}
	}
	inline int colisiona(sf::CircleShape ptriangle, vector<sf::RectangleShape> pVecr){
		sf::FloatRect boundbox1 = ptriangle.getGlobalBounds();
		for (int i = 0; i < pVecr.size(); i++){
			sf::FloatRect boundbox = pVecr[i].getGlobalBounds();
			bool choca = boundbox.intersects(boundbox1);
			if (choca){
				return i;
			}
		}
		return -1;
	}
	void ponerMurosRectangulo(vector<sf::RectangleShape> &pVecr)
	{
		for (int i = 0; i < filM; ++i)
		{
			for (int j = 0; j < colM; ++j)
			{
				if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
				{
					sf::RectangleShape shape(sf::Vector2f(anchoBloque, anchoBloque));
					shape.setPosition(sf::Vector2f(offsetC + j * anchoBloque, offsetC + i * anchoBloque));
					shape.setFillColor(sf::Color::White);
					pVecr.push_back(shape);
				}
			}
		}
	}
	void ponerPersonaje(sf::CircleShape &pcir)
	{
		for (int i = 0; i < filM; ++i)
		{
			for (int j = 0; j < colM; ++j)
			{
				if (maze[i][j] == 'E')
				{
					ii Entrada = BuscarEntrada();
					//pcir.setFillColor(sf::Color::White);
					pcir.setTextureRect(vHeroAdelante[0]);
					pcir.setPosition(sf::Vector2f(5+offsetC + pcir.getGlobalBounds().width / 2 + Entrada.second * anchoBloque,
						offsetC + pcir.getGlobalBounds().height / 2 + Entrada.first * anchoBloque));
				}
			}
		}
	}
	bool haySalida(ii pos) {
		if (maze[pos.first][pos.second] == 'S')
			return true;
		return false;
	}
	bool jugadorEnSalida(sf::CircleShape personaje)
	{
		vii posiciones = vii();
		ii posJugadorTI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top);//por jugador arriba izquierda  X Y
		ii posJugadorTD = make_pair(personaje.getGlobalBounds().left + personaje.getGlobalBounds().width, personaje.getGlobalBounds().top);
		ii posJugadorBI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top + personaje.getGlobalBounds().height);
		ii posJugadorBD = make_pair(personaje.getGlobalBounds().left + personaje.getGlobalBounds().width,
			personaje.getGlobalBounds().top + personaje.getGlobalBounds().height);
		posiciones.push_back(posJugadorBD);
		posiciones.push_back(posJugadorBI);
		posiciones.push_back(posJugadorTD);
		posiciones.push_back(posJugadorTI);
		bool chocaSalida = false;
		for (int i = 0; i < 4; ++i){
			posiciones[i].first -= offsetC;
			posiciones[i].second -= offsetC;
			posiciones[i].first /= anchoBloque;
			posiciones[i].second /= anchoBloque;
			chocaSalida |= haySalida(make_pair(posiciones[i].second, posiciones[i].first));
		}
		return chocaSalida;
	}

	void teletransportar(vii pPosp, sf::CircleShape &personaje)
	{
		ii posJugadorTI = make_pair(personaje.getGlobalBounds().left, personaje.getGlobalBounds().top);
		posJugadorTI.first -= offsetC;
		posJugadorTI.second -= offsetC;
		posJugadorTI.first /= anchoBloque;
		posJugadorTI.second /= anchoBloque;
		ii posi = make_pair(posJugadorTI.second, posJugadorTI.first);
		ii mangina = BuscaPortalMan(posi, color, pPosp);
		personaje.setPosition(sf::Vector2f(offsetC + mangina.first * anchoBloque + anchoBloque / 2, offsetC + mangina.second * anchoBloque + anchoBloque / 2));
	}
	void crearEntradasEnemigo()
	{
		/*int max = rand() % (10 * NIVEL / 7);
		int cont = 0;
		for (int i = 0; i < filM; i++)
		for (int j = 0; j < colM; j++)
		{
			if (i == 0 || j == 0 || i == filM - 1 || j == colM - 1)
			{
				if (cont < max)
				{*/
					puertasEnemigos.push_back(make_pair(0, 7));
					sf::CircleShape puerta = sf::CircleShape(8, 2);
					puerta.setPosition(sf::Vector2f(offsetC + 0 * anchoBloque, offsetC + 7 * anchoBloque));
					puerta.setFillColor(sf::Color::Cyan);
					puertas.push_back(puerta);

					puertasEnemigos.push_back(make_pair(fil-1, 12));
					sf::CircleShape puerta2 = sf::CircleShape(8, 2);
					puerta2.setPosition(sf::Vector2f(offsetC + (fil-1) * anchoBloque, offsetC + 12 * anchoBloque));
					puerta2.setFillColor(sf::Color::Cyan);
					puertas.push_back(puerta2);
					/*cont++;*/
				//}
		/*		else
					return;
					
			}

		}*/

	}
	void dibujarPuertas()
	{
		for (int i = 0; i < puertas.size(); i++)
			mWindow->draw(puertas[i]);
	}
	void refrescarBusqueda(sf::Time tiempo)
	{
		conEnemigosT +=tiempo.asSeconds();
		
		if ((int)conEnemigosT % 10 == 0)
		{
			int ** auxMaze = new int  *[MAXMATRIX];
			for (int i = 0; i < MAXMATRIX; i++)
				auxMaze[i] = new int[MAXMATRIX];
			for (int i = 0; i < MAXMATRIX; i++)
			for (int j = 0; j < MAXMATRIX; j++)
			{
				auxMaze[i][j] = maze[i][j];

			}
			ii posJugadorTI = make_pair(Jugador.getGlobalBounds().left, Jugador.getGlobalBounds().top);
			posJugadorTI.first -= offsetC;
			posJugadorTI.second -= offsetC;
			posJugadorTI.first /= anchoBloque;
			posJugadorTI.second /= anchoBloque;
			for (int i = 0; i < enemigos.size(); i++)
				enemigos[i].CaminoJugadorDJ(posJugadorTI, auxMaze, colM, posPortales, fil, col, GPortales,puertasEnemigos);
		}
	}	
	void iniciarEnemys(sf::Time tiempo)
	{
		if (!puertasEnemigos.empty())
		{
			if ((int)conEnemigosT % (500 / NIVEL)== 0)
			{
				int ra = rand() % puertasEnemigos.size() ;
				ii portalElegido = puertasEnemigos[ra];
				Enemigo en = Enemigo();
				//verificar
				en.setPosEnemigo(portalElegido.first, portalElegido.second);
				enemigos.push_back(en);
			}
		}
	}
	void dibujarEnemigos()
	{
		for (int i = 0; i < enemigos.size(); i++)
			enemigos[i].dibujar(*mWindow);
	}
	void moverEnemigo()
	{
		for (int i = 0; i < enemigos.size(); i++)
			enemigos[i].mover();

	}
	void iniciarSpritesCabrilla()
	{
		for (int i = 0; i < filM; ++i)
		{
			for (int j = 0; j < colM; ++j)
			{
				sf::RectangleShape shape(sf::Vector2f(anchoBloque, anchoBloque));
				shape.setPosition(sf::Vector2f(offsetC + j * anchoBloque, offsetC + i * anchoBloque));
				shape.setTexture(&tStuffmapa);
				switch (mapaRandom)
				{
				case 0: // CUEVA MARRON
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(272, 289, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(136, 255, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(187, 204, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(136, 204, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(289, 221, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(289, 204, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(340, 34, 16, 16));		//LADO INFERIOR todo
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro)	//PISO
							{
								shape.setTextureRect(sf::IntRect(187, 221, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'E')	//ENTRADA
							{
								shape.setTextureRect(sf::IntRect(221, 187, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'S')	//SALIDA
							{
								shape.setTextureRect(sf::IntRect(425, 85, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j + 1] == 'S')	//SALIDA costado derecho
							{
								shape.setTextureRect(sf::IntRect(408, 85, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j - 1] == 'S')	//SALIDA costado izquierdo
							{
								shape.setTextureRect(sf::IntRect(442, 85, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				case 1: //CUEVA GRIS
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(731, 221, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(697, 238, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(765, 187, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(697, 187, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(850, 204, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(850, 187, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(833, 306, 16, 16));	//LADO INFERIOR todo
								if (i == filM - 1 && j == 0)
									shape.setTextureRect(sf::IntRect(697, 306, 16, 16));	//ESQUINA INFERIOR IZQUIERDA sola
								if (i == filM - 1 && j == colM - 1)
									shape.setTextureRect(sf::IntRect(850, 306, 16, 16));	//ESQUINA INFERIOR DERECHA sola
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro)	//PISO
							{
								shape.setTextureRect(sf::IntRect(714, 221, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'E')	//ENTRADA
							{
								shape.setTextureRect(sf::IntRect(816, 238, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'S')	//SALIDA
							{
								shape.setTextureRect(sf::IntRect(765, 306, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j + 1] == 'S')	//SALIDA costado derecho
							{
								shape.setTextureRect(sf::IntRect(748, 306, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j - 1] == 'S')	//SALIDA costado izquierdo
							{
								shape.setTextureRect(sf::IntRect(782, 306, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				case 2: //CUEVA BLANCA
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(17, 442, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(867, 221, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(901, 187, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(867, 187, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(1020, 204, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(1020, 187, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(884, 306, 16, 16));	//LADO INFERIOR todo
								if (i == filM - 1 && j == 0)
									shape.setTextureRect(sf::IntRect(867, 306, 16, 16));	//ESQUINA INFERIOR IZQUIERDA sola
								if (i == filM - 1 && j == colM - 1)
									shape.setTextureRect(sf::IntRect(1020, 306, 16, 16));	//ESQUINA INFERIOR DERECHA sola
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro)	//PISO
							{
								shape.setTextureRect(sf::IntRect(884, 204, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'E')	//ENTRADA
							{
								shape.setTextureRect(sf::IntRect(986, 238, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'S')	//SALIDA
							{
								shape.setTextureRect(sf::IntRect(935, 306, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j + 1] == 'S')	//SALIDA costado izquierdo
							{
								shape.setTextureRect(sf::IntRect(918, 306, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j - 1] == 'S')	//SALIDA costado derecho
							{
								shape.setTextureRect(sf::IntRect(952, 306, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				case 3: //CUEVA HIELO
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(714, 408, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(697, 340, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(748, 323, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(697, 323, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(850, 340, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(850, 323, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(816, 442, 16, 16));	//LADO INFERIOR todo
								if (i == filM - 1 && j == 0)
									shape.setTextureRect(sf::IntRect(697, 442, 16, 16));	//ESQUINA INFERIOR IZQUIERDA sola
								if (i == filM - 1 && j == colM - 1)
									shape.setTextureRect(sf::IntRect(850, 442, 16, 16));	//ESQUINA INFERIOR DERECHA sola
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro)	//PISO
							{
								shape.setTextureRect(sf::IntRect(714, 391, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'E')	//ENTRADA
							{
								shape.setTextureRect(sf::IntRect(816, 374, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'S')	//SALIDA
							{
								shape.setTextureRect(sf::IntRect(765, 442, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j + 1] == 'S')	//SALIDA costado izquierdo
							{
								shape.setTextureRect(sf::IntRect(748, 442, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j - 1] == 'S')	//SALIDA costado derecho
							{
								shape.setTextureRect(sf::IntRect(782, 442, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				case 4: //CUEVA MOHO VERDE
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(884, 374, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(867, 340, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(901, 323, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(867, 323, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(1020, 340, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(1020, 323, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(1003, 442, 16, 16));	//LADO INFERIOR todo
								if (i == filM - 1 && j == 0)
									shape.setTextureRect(sf::IntRect(867, 442, 16, 16));	//ESQUINA INFERIOR IZQUIERDA sola
								if (i == filM - 1 && j == colM - 1)
									shape.setTextureRect(sf::IntRect(1020, 442, 16, 16));	//ESQUINA INFERIOR DERECHA sola
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro)	//PISO
							{
								shape.setTextureRect(sf::IntRect(935, 408, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'E')	//ENTRADA
							{
								shape.setTextureRect(sf::IntRect(969, 374, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j] == 'S')	//SALIDA
							{
								shape.setTextureRect(sf::IntRect(935, 442, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j + 1] == 'S')	//SALIDA costado izquierdo
							{
								shape.setTextureRect(sf::IntRect(918, 442, 16, 16));
								vecr.push_back(shape);
							}
							if (maze[i][j - 1] == 'S')	//SALIDA costado derecho
							{
								shape.setTextureRect(sf::IntRect(952, 442, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				case 5: //CAMPO CON CERCO
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(34, 17, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(17, 17, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(34, 0, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(17, 0, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(51, 17, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(51, 0, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(34, 34, 16, 16));	//LADO INFERIOR todo
								if (i == filM - 1 && j == 0)
									shape.setTextureRect(sf::IntRect(17, 34, 16, 16));	//ESQUINA INFERIOR IZQUIERDA sola
								if (i == filM - 1 && j == colM - 1)
									shape.setTextureRect(sf::IntRect(51, 34, 16, 16));	//ESQUINA INFERIOR DERECHA sola
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro || maze[i][j] == 'E' || maze[i][j] == 'S')	//PISO
							{
								shape.setTextureRect(sf::IntRect(51, 51, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				case 6: //CAMPO CON PALOS
				{
							if (maze[i][j] == muro && maze[i][j] != 'E' && maze[i][j] != 'S')
							{
								// PARA MUROS CON SALIDA Y ENTRADA CALATA
								shape.setTextureRect(sf::IntRect(561, 51, 16, 16));
								if (i > 0 && j == 0)
									shape.setTextureRect(sf::IntRect(374, 0, 16, 16));	//LADO IZQUIERDO SIN ESQUINAS
								if (i == 0 && j > 0)
									shape.setTextureRect(sf::IntRect(340, 0, 16, 16));	//LADO SUPERIOR SIN ESQUINAS
								if (j == 0 && i == 0)
									shape.setTextureRect(sf::IntRect(323, 0, 16, 16));	//ESQUINA SUPERIOR IZQUIERDA sola
								if (j == colM - 1)
									shape.setTextureRect(sf::IntRect(442, 0, 16, 16));	//LADO DERECHO SIN ESQUINAS
								if (j == colM - 1 && i == 0)
									shape.setTextureRect(sf::IntRect(357, 0, 16, 16));	//ESQUINA SUPERIOR DERECHA sola
								if (i == filM - 1)
									shape.setTextureRect(sf::IntRect(340, 0, 16, 16));	//LADO INFERIOR todo
								if (i == filM - 1 && j == 0)
									shape.setTextureRect(sf::IntRect(425, 0, 16, 16));	//ESQUINA INFERIOR IZQUIERDA sola
								if (i == filM - 1 && j == colM - 1)
									shape.setTextureRect(sf::IntRect(408, 0, 16, 16));	//ESQUINA INFERIOR DERECHA sola
								vecr.push_back(shape);
							}
							if (maze[i][j] == noMuro || maze[i][j] == 'E' || maze[i][j] == 'S')	//PISO
							{
								shape.setTextureRect(sf::IntRect(51, 51, 16, 16));
								vecr.push_back(shape);
							}
				}break;
				}
			}
		}
		crearEntradasEnemigo();
	}
	/////DAMBERT

	void pintarNivel(sf::Text textInformativo){

		//cambiar esta variable por la variable global que manejara los niveles
	
		//asigno un texto
		sf::Text text = textInformativo;
		text.setPosition(50, 10);
		text.setString(" Nivel :" + std::to_string(NIVEL));

		this->mWindow->draw(text);

	}
	void pintarCantidadBalas(sf::Text textInformativo)
	{
		//cambiar esta variable por la variable global que manejara la cantidad de balas
		

		//asigno un texto
		sf::Text text = textInformativo;
		text.setPosition(135, 10);
		text.setString(" Balas :" + std::to_string(CANTIDADBALAS));

		this->mWindow->draw(text);

	}
	void pintarTiempo(sf::Text textInformativo, sf::Time tiempo)
	{
		//debemos de declarar la hora como variable global y hacer una logica que vaya aumentando
		//PD. no se que como hacerlo en smfl
		
		
		//asigno un texto
		sf::Text text = textInformativo;
		text.setPosition(220, 10); 
		TiempoG += tiempo.asSeconds();
		text.setString(" Tiempo :" + std::to_string((int)TiempoG));
		this->mWindow->draw(text);

	}
	void pintarTeclaVisor(sf::Text textInformativo)
	{
		//asigno un texto
		sf::Text text = textInformativo;
		text.setPosition(340, 10);
		text.setString(" Visor : Tab");
		this->mWindow->draw(text);
	}
	void pintarColorTecla(sf::RectangleShape rectangle, sf::Color color, float posx, float posy, sf::Text textInformativo, sf::String tecla)
	{
		sf::RectangleShape r = rectangle;
		r.setOutlineColor(color);
		r.setPosition(posx, posy);

		sf::Text text = textInformativo;
		text.setColor(color);
		text.setPosition(posx + 5, posy + 2);
		text.setString(tecla);
		this->mWindow->draw(r);
		this->mWindow->draw(text);

	}
	void pintarTeclaColores(sf::Text textInformativo)
	{
		//asigno un texto
		sf::Text text = textInformativo;
		text.setPosition(465, 10);
		text.setString(" Colores :");
		this->mWindow->draw(text);


		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(20, 20));
		rectangle.setOutlineThickness(5);

		pintarColorTecla(rectangle, sf::Color::Red, 570, 10, textInformativo, sf::String("1"));
		pintarColorTecla(rectangle, sf::Color::Green, 600, 10, textInformativo, sf::String("2"));
		pintarColorTecla(rectangle, sf::Color::Blue, 630, 10, textInformativo, sf::String("3"));

		this->mWindow->draw(text);
	}

	void pintarPuntajeAcumulado(sf::Text textInformativo)
	{
		//asigno un texto
		sf::Text text = textInformativo;
		text.setPosition(670, 10);
		text.setString(" Puntaje :"+	std::to_string( this->PUNTAJE_ACUMULADO));
		this->mWindow->draw(text);
	}
	void pintarDetalles(sf::Time tiempo)
	{
		//creo una variable texto
		sf::Text textInformativo;
		//creo una variable fuente
		sf::Font font;
		//cargo la fuente a mi variable fuente // (ruta en la raiz del proyecto)
		font.loadFromFile("Orbitron-Black.ttf");
		//asigno una fuente al texto
		textInformativo.setFont(font);
		// tama�o del texto
		textInformativo.setCharacterSize(15);
		// color del texto
		textInformativo.setColor(sf::Color::White);
		// set the text style
		textInformativo.setStyle(sf::Text::Bold);

		pintarCantidadBalas(textInformativo);
		pintarNivel(textInformativo);
		pintarTiempo(textInformativo,tiempo);
		pintarTeclaVisor(textInformativo);
		pintarTeclaColores(textInformativo);
		pintarPuntajeAcumulado(textInformativo);
	}

	void render(sf::Time tiempo)
	{
		mWindow->clear();
		
		for (int i = 0; i < vecr.size(); i++)
			mWindow->draw(vecr[i]);
		for (int k = 0; k < vecrSol.size(); k++)
			mWindow->draw(vecrSol[k]);
		for (int i = 0; i < vecPort.size(); i++)
			mWindow->draw(vecPort[i]);
		mWindow->draw(Jugador);
		if (bala != nullptr){
			bala->dibujarBala(*mWindow);
		}
		for (int k = 0; k < vecMunicion.size(); k++)
			mWindow->draw(vecMunicion[k]);
		pintarDetalles(tiempo);
		
		dibujarEnemigos();
		dibujarPuertas();

		mWindow->display();
	}
	void update(sf::Time elapsedTime)
	{
		if (bala != nullptr){
			bala->moverBala(elapsedTime,PlayerSpeed);
			bala->moverSpriteBala();
			if (colisionaOptimizado(bala->getBalaShape())){
				
				if (direccionBala == 2){
					if (ColiBalaY + 1 < fil){
						maze[ColiBalaY + 1][ColiBalaX] = 'O';
						iniciarSpritesCabrilla();
					}
				}
				else if (direccionBala == 4){
					if (ColiBalaX + 1<col) {
						maze[ColiBalaY][ColiBalaX + 1] = 'O';
						iniciarSpritesCabrilla();
					}
				}
				else if (direccionBala == 1 || direccionBala == 3){
					if (ColiBalaY > 0 && ColiBalaX > 0) {
						maze[ColiBalaY][ColiBalaX] = 'O';
						iniciarSpritesCabrilla();
					}
				}
				
				bala = nullptr;
			}
		}
		refrescarBusqueda(elapsedTime);
	//	iniciarEnemys(elapsedTime);
	}
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
	{
		if (key == sf::Keyboard::W)
			mIsMovingUp = isPressed;
		else if (key == sf::Keyboard::S)
			mIsMovingDown = isPressed;
		else if (key == sf::Keyboard::A)
			mIsMovingLeft = isPressed;
		else if (key == sf::Keyboard::D)
			mIsMovingRight = isPressed;
	}
	void processEvents()
	{
		sf::Event event;

		while (mWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mWindow->close();
			if (event.type == sf::Event::KeyPressed){
				if (jugadorEnSalida(Jugador))
				{
					//CREAR NNUEVO LABERINTO
					vecr.clear();
					vecPort.clear();
					//vecrSol.clear();
					posPortales.clear();
					fil = 25, col = 25;
					if (fil % 2 == 0)fil--;
					if (col % 2 == 0)col--;
					//llenar el laberinto con O 
					init();
					//Genera una pos aleatoria las columnas deben ser mayor a 1
					//se marca aleatoriamente alguna pared de primera columna
					int posfI = rand() % (fil)+offset, poscI = offset;
					//if(poscI%2!=0)poscI+=1;
					if (posfI % 2 == 0)posfI += 1;
					//llama a DFS
					DFS(make_pair(posfI, poscI));
					//imprime lo generado
					GeneraEntradaYSalida();
					generarPortales(vecPort, posPortales);
					ponerMurosRectangulo(vecr);
					ponerPersonaje(Jugador);
					iniciarSpritesCabrilla();
					int factorTiempo;
					if (TiempoG >= 60)
						factorTiempo = 0;
					else
						factorTiempo = 60 - TiempoG;

					PUNTAJE_ACUMULADO += (75 + (this->NIVEL * 25) + (factorTiempo * 5));


					NIVEL++;
					TiempoG = 0;
				}
				if (event.key.code == sf::Keyboard::W){
					Jugador.move(0, -1);
					//Jugador.setRotation(0);
					direccionBala = 1;
					Jugador.setTextureRect(vHeroAtras[contador++]);
					if (contador == 6)contador = 0;
					//if (!colisiona(circle, vecr))
					if (!colisionaOptimizado(Jugador)){
						int i = colisiona(Jugador, vecMunicion);
						if (i != -1){ vecMunicion.erase(vecMunicion.begin() + i); CANTIDADBALAS++;}
						if (colisionPortal(Jugador)){
							teletransportar(posPortales, Jugador);
						}
						continue;
					}
					else
						Jugador.move(0, +1);
				}
				if (event.key.code == sf::Keyboard::S){
					Jugador.move(0, +1);
					//Jugador.setRotation(180);
					direccionBala = 2;
					Jugador.setTextureRect(vHeroAdelante[contador++]);
					if (contador == 6)contador = 0;
					if (!colisionaOptimizado(Jugador)){
						int i = colisiona(Jugador, vecMunicion);
						if (i != -1){ vecMunicion.erase(vecMunicion.begin() + i); CANTIDADBALAS++; }
						if (colisionPortal(Jugador)){
							teletransportar(posPortales, Jugador);
						}
						continue;
					}
					else
						Jugador.move(0, -1);
				}
				if (event.key.code == sf::Keyboard::A){
					Jugador.move(-1, 0);
					//Jugador.setRotation(270);
					direccionBala = 3;
					Jugador.setTextureRect(vHeroIzquierda[contador++]);
					if (contador == 6)contador = 0;
					if (!colisionaOptimizado(Jugador)){
						int i = colisiona(Jugador, vecMunicion);
						if (i != -1){ vecMunicion.erase(vecMunicion.begin() + i); CANTIDADBALAS++; }
						if (colisionPortal(Jugador)){
							teletransportar(posPortales, Jugador);
						}
						continue;
					}
					else
						Jugador.move(+1, 0);
				}
				if (event.key.code == sf::Keyboard::D){
					Jugador.move(+1, 0);
					//Jugador.setRotation(90);
					direccionBala = 4;
					Jugador.setTextureRect(vHeroDerecha[contador++]);
					if (contador == 6)contador = 0;
					if (!colisionaOptimizado(Jugador)){
						int i = colisiona(Jugador, vecMunicion);
						if (i != -1){ vecMunicion.erase(vecMunicion.begin() + i); CANTIDADBALAS++; }
						if (colisionPortal(Jugador)){
							teletransportar(posPortales, Jugador);
						}
						continue;
					}
					else
						Jugador.move(-1, 0);
				}
				if (event.key.code == sf::Keyboard::Tab)
				{
					vecrSol.clear();
					ii posJugadorTI = make_pair(Jugador.getGlobalBounds().left, Jugador.getGlobalBounds().top);
					posJugadorTI.first -= offsetC;
					posJugadorTI.second -= offsetC;
					posJugadorTI.first /= anchoBloque;
					posJugadorTI.second /= anchoBloque;
					/*BFS(make_pair(posJugadorTI.first, posJugadorTI.second));
					ii salida = BuscarSalida();
					sii Pilan = PilaHaciaSalida(salida);*/
					pintarSolucion(CaminoSalidaDJ(posJugadorTI), vecrSol);
				}
				if (event.key.code == sf::Keyboard::Space){
					if (bala == nullptr && CANTIDADBALAS>0){
						CANTIDADBALAS--;
						bala = new CBala(direccionBala);
						bala->setPosBala(Jugador.getGlobalBounds().left + (Jugador.getGlobalBounds().width / 2) / 2
							, Jugador.getGlobalBounds().top + (Jugador.getGlobalBounds().height / 2) / 2);
					}
				}
				if (event.key.code == sf::Keyboard::Num1)
				{
					Jugador.setFillColor(sf::Color::Red);
					color = 'R';
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					color = 'V';
					Jugador.setFillColor(sf::Color::Green);
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					color = 'A';
					Jugador.setFillColor(sf::Color::Blue);
				}
				if (event.key.code == sf::Keyboard::Num4)
				{
					color = 'B';
					Jugador.setFillColor(sf::Color::White);
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code = sf::Keyboard::Tab)
					vecrSol.clear();
			}
		}
	}
	void run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (mWindow->isOpen())
		{
			/*sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;	
			}*/
			processEvents();
			sf::Time tiempo = clock.restart();
			update(tiempo);
			render(tiempo);
		}
	}
};
const float juego::PlayerSpeed = 100.f;
const sf::Time juego::TimePerFrame = sf::seconds(1.f / 6.f);
