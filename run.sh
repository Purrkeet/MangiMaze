 g++ -c ./game.cpp ./Bala.cpp ./Enemigo.cpp
 g++ game.o Bala.o Enemigo.o -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./app