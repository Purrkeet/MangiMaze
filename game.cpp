//#define _WIN32_WINNT 0x0500//para Ocultar la consola

#include "juego.h"

using namespace std;


int main()
{
	srand(time(NULL));
	juego Juego = juego();
	Juego.run();
	return 0;

}
