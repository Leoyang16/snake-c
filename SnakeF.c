#include "SnakeB.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

//Variables globales
	//tablero
int ancho=40;
int alto=20;
	//Cabeza
int x,y;
	//Fruta
int frutax,frutay;
	//Puntuaje
int puntuaje;
	//Cuerpo capacidad
int colax[100],colay[100];
	//Cantidad de cola
int ncola;
	//Entradas
enum Direction {
ALTO=0,
ARRIBA,
ABAJO,
DERECHA,
IZQUIERDA,
}; 
enum Direction mov;
bool gameover=false;

//Funciones
void Inicio() {
	srand(time(NULL));
	mov=ALTO;
	x=ancho/2;
	y=alto/2;
	frutax=rand()%(ancho-2)+1;
	frutay=rand()%alto;
	puntuaje=0;
	ncola=0;
}

void Dibujar() {
	system("cls");
    int i,j,k;
    printf("Puntuaje: %d\n",puntuaje);
    // borde superior
    for (i=0;i<ancho;i++) {
        printf("#");
    }
    printf("\n");
    for (i=0;i<alto;i++) {
        for (j=0;j<ancho;j++) {
            if (j==0 || j==ancho-1) {
                printf("#");
                continue;
            }
            if (i==y && j==x) {
                printf("O");
                continue;
            }
            if (i==frutay && j==frutax) {
                printf("a");
                continue;
            }
            bool imp=false;
            for (k=1;k<=ncola;k++) {
                if (colax[k]==j && colay[k]==i) {
                    printf("o");
                    imp=true;
                    break;
                }
            }
            if (!imp) {
                printf(" ");
            }
        }
        printf("\n");
    }
    // borde inferior
    for (i=0;i<ancho;i++) {
        printf("#");
    }
    printf("\n");
}


void Entradas() {
    if (kbhit()) {
        switch (getch()) {
            case 'a':
				mov=IZQUIERDA;
				break;
            case 'd':
				mov=DERECHA;
				break;
            case 'w':
				mov=ARRIBA;
				break;
            case 's':
				mov=ABAJO;
				break;
        }
    }
}

bool Logica() {
	bool fin=false;
	//movimiento
	switch (mov) {
		case DERECHA:
			x++;
			break;
		case IZQUIERDA:
			x--;
			break;
		case ARRIBA:
			y--;
			break;
		case ABAJO:
			y++;
			break;
		default:
			break;
	}

	//colisione pared
	if (x<=0 || x>=ancho-1 || y<0 || y>=alto) {
		fin=true;
	}
	
	//mover cola
	int temp1x=colax[0];
	int temp1y=colay[0];
	int temp2x,temp2y;
	int i;
	colax[0]=x;
	colay[0]=y;

	for (i=1;i<=ncola;i++) {
		temp2x=colax[i];
		temp2y=colay[i];
		colax[i]=temp1x;
		colay[i]=temp1y;
		temp1x=temp2x;
		temp1y=temp2y;
	}

	//colision cola
	for (i=1;i<=ncola;i++) {
		if (colax[i]==x && colay[i]==y) {
			fin=true;
			break;
		}
	}
	
	//aparecer nueva fruta
	if (x==frutax && y==frutay) {
		puntuaje++;
		frutax=rand()%(ancho-2)+1;
		frutay=rand()%alto;
		ncola++;
	}
	
	return fin;
}
