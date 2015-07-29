//#define _WIN32_WINNT 0x0500//para Ocultar la consola
//Stevie Wonder estuvo aqui
#include "juego.h"

using namespace std;
using namespace sf;

int main()
{
	srand(time(NULL));
	juego Juego = juego();
	Juego.run();
	return 0;

}
