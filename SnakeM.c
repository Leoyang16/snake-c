#include "SnakeB.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

int main () {
	Inicio();
	bool gameover=false;
	while (gameover==false){
		Dibujar();
		Entradas();
		gameover=Logica();
		Sleep(25);
	}
	printf("\nFIN DEL JUEGO\n");
	return 0;
}
