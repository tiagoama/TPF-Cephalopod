
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tablero.h"

//funcion que limpia la pantalla
void limpiarPantalla(){
    printf("\033[H\033[J");
}

//funcion que lee y valida la coordenada
int verifCoord(int x){
	while (x<1||x>5){
		printf("La coordenada debe valer entre 1 y 5: ");
		scanf("%d",&x);
	}
	return x;
}

//funcion que inicializa el tablero lleno de ceros
void cargarTablero(){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			tablero[i][j].jugador=0;
			tablero[i][j].num=0;
		}
	}
}

//funcion que hace libera una casilla
void liberarCasilla(int f, int c){
	tablero[f][c].jugador=0;
	tablero[f][c].num=0;
}

//funcion que imprime el tablero
void printTablero(){
	for(int i=0;i<5;i++){
		if(!i){
			printf("\x1b[32m" "  1 2 3 4 5\n" "\x1b[0m");
		}
		for(int j=0;j<5;j++){
			if(j==0){
				printf("\x1b[32m" "%d" "\x1b[0m",i+1);
			}
			if(j<4){
				if(tablero[i][j].jugador==1){
					//jugador 1 color rojo
					printf("\x1b[31m" " %d" "\x1b[0m",tablero[i][j].num);
				}
				else{
					if(tablero[i][j].jugador==2){
						//jugador 2-pc color azul
						printf("\x1b[34m" " %d" "\x1b[0m",tablero[i][j].num);
					}
					else{
						//casilla vacia color negro
						printf(" %d" "\x1b[0m",tablero[i][j].num);
					}
				}
			}
			else{
				if(tablero[i][j].jugador==1){
					printf("\x1b[31m" " %d\n" "\x1b[0m",tablero[i][j].num);
				}
				else{
					if(tablero[i][j].jugador==2){
						printf("\x1b[34m" " %d\n" "\x1b[0m",tablero[i][j].num);
					}
					else{
						printf(" %d\n" "\x1b[0m",tablero[i][j].num);
					}
				}
			}
		}
	}
	printf("\n");
}

//funcion de suma de dados
int sumarDados(int f, int c){
	int suma;
	int arriba=0, abajo=0, izquierda=0, derecha=0;
	int x;

	if(f-1>=0&&tablero[f-1][c].num&&tablero[f-1][c].num!=6){
		arriba=tablero[f-1][c].num;
	}
	if(f+1<5&&tablero[f+1][c].num&&tablero[f+1][c].num!=6){
		abajo=tablero[f+1][c].num;
	}
	if(c-1>=0&&tablero[f][c-1].num&&tablero[f][c-1].num!=6){
		izquierda=tablero[f][c-1].num;
	}
	if(c+1<5&&tablero[f][c+1].num&&tablero[f][c+1].num!=6){
		derecha=tablero[f][c+1].num;
	}

	//sumas automaticas de 2 dados
	if((arriba&&abajo)&&(arriba+abajo<=6)&&!izquierda&&!derecha){
		liberarCasilla(f-1,c);
		liberarCasilla(f+1,c);
		return arriba+abajo;
	}
	else{
		if((arriba&&izquierda)&&arriba+izquierda<=6&&!abajo&&!derecha){
			liberarCasilla(f-1,c);
			liberarCasilla(f,c-1);
			return arriba+izquierda;
		}
		else{
			if((arriba&&derecha)&&arriba+derecha<=6&&!abajo&&!izquierda){
				liberarCasilla(f-1,c);
				liberarCasilla(f,c+1);
				return arriba+derecha;
			}
			else{
				if((izquierda&&derecha)&&izquierda+derecha<=6&&!arriba&&!abajo){
					liberarCasilla(f,c-1);
					liberarCasilla(f,c+1);
					return izquierda+derecha;
				}
				else{
					if((izquierda&&abajo)&&izquierda+abajo<=6&&!arriba&&!derecha){
						liberarCasilla(f,c-1);
						liberarCasilla(f+1,c);
						return izquierda+abajo;
					}
					else{
						if((derecha&&abajo)&&derecha+abajo<=6&&!arriba&&!izquierda){
							liberarCasilla(f,c+1);
							liberarCasilla(f+1,c);
							return derecha+abajo;
						}
					}
				}
			}
		}
	}

	//sumas manuales de 4 dados
	if((arriba&&abajo&&izquierda&&derecha)&&(arriba+abajo<=6||arriba+izquierda<=6||arriba+derecha<=6||izquierda+derecha<=6||
		izquierda+abajo<=6||derecha+abajo<=6)){
		printf("Sumar arriba/abajo(1) arriba/izquierda(2) arriba/derecha(3) izquierda/derecha(4) izquierda/abajo(5) derecha/abajo(6) ");
		if(arriba+izquierda+derecha<=6){
			printf("arriba+izquierda+derecha(7) ");
		}
		if(arriba+izquierda+abajo<=6){
			printf("arriba+izquierda+abajo(8) ");
		}
		if(arriba+derecha+abajo<=6){
			printf("arriba+derecha+abajo(9) ");
		}
		if(derecha+izquierda+abajo<=6){
			printf("derecha+izquierda+abajo(10) ");
		}
		if(arriba+abajo+izquierda+derecha<=6){
			printf("sumar todo(11) : ");
		}
		do{
			if (suma>6){
				printf("Suma mayor a 6, pruebe otra suma");
			}
			scanf("%d",&x);
			while(x<1||x>11){
				scanf("%d",&x);
			}
			switch (x){
			case 1:
				liberarCasilla(f-1,c);
				liberarCasilla(f+1,c);
				suma=arriba+abajo;
				break;
			case 2:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c-1);
				suma=arriba+izquierda;
				break;
			case 3:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c+1);
				suma=arriba+derecha;
				break;
			case 4:
				liberarCasilla(f,c-1);
				liberarCasilla(f,c+1);
				suma=izquierda+derecha;
				break;
			case 5:
				liberarCasilla(f,c-1);
				liberarCasilla(f+1,c);
				suma=izquierda+abajo;
				break;
			case 6:
				liberarCasilla(f,c+1);
				liberarCasilla(f+1,c);
				suma=derecha+abajo;
				break;
			case 7:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c+1);
				liberarCasilla(f,c-1);
				suma=arriba+derecha+izquierda;
				break;
			case 8:
				liberarCasilla(f-1,c);
				liberarCasilla(f+1,c);
				liberarCasilla(f,c-1);
				suma=arriba+abajo+izquierda;
				break;
			case 9:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c+1);
				liberarCasilla(f+1,c);
				suma=arriba+derecha+abajo;
				break;
			case 10:
				liberarCasilla(f,c+1);
				liberarCasilla(f+1,c);
				liberarCasilla(f,c-1);
				suma=derecha+abajo+izquierda;
				break;
			case 11:
				liberarCasilla(f,c+1);
				liberarCasilla(f,c-1);
				liberarCasilla(f+1,c);
				liberarCasilla(f-1,c);
				suma=arriba+abajo+izquierda+derecha;
			}
		}while(suma>6);
		return suma;

	}

	//sumas manuales de 3 dados
	if((arriba&&izquierda&&derecha)&&(arriba+izquierda<=6||arriba+derecha<=6||izquierda+derecha<=6)){
		printf("Sumar arriba/izquierda(1) arriba/derecha(2) izquierda/derecha(3) ");
		if(arriba+izquierda+derecha<=6){
			printf("sumar todo(4) : ");
		}
		do{
			if (suma>6){
				printf("Suma mayor a 6, pruebe otra suma");
			}
			scanf("%d",&x);
			while(x<1||x>4){
				scanf("%d",&x);
			}
			switch (x){
			case 1:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c-1);
				suma=arriba+izquierda;
				break;
			case 2:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c+1);
				suma=arriba+derecha;
				break;
			case 3:
				liberarCasilla(f,c-1);
				liberarCasilla(f,c+1);
				suma=izquierda+derecha;
				break;
			case 4:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c+1);
				liberarCasilla(f,c-1);
				suma=arriba+derecha+izquierda;
				break;
			}
		}while(suma>6);
		return suma;
	}

	if((arriba&&izquierda&&abajo)&&(arriba+izquierda<=6||arriba+abajo<=6||izquierda+abajo<=6)){
		printf("Sumar arriba/izquierda(1) arriba/abajo(2) izquierda/abajo(3) ");
		if(arriba+izquierda+abajo<=6){
			printf("sumar todo(4) : ");
		}
		do{
			if (suma>6){
				printf("Suma mayor a 6, pruebe otra suma");
			}
			scanf("%d",&x);
			while(x<1||x>4){
				scanf("%d",&x);
			}
			switch (x){
			case 1:
				liberarCasilla(f-1,c);
				liberarCasilla(f,c-1);
				suma=arriba+izquierda;
				break;
			case 2:
				liberarCasilla(f-1,c);
				liberarCasilla(f+1,c);
				suma=arriba+abajo;
				break;
			case 3:
				liberarCasilla(f,c-1);
				liberarCasilla(f+1,c);
				suma=izquierda+abajo;
				break;
			case 4:
				liberarCasilla(f-1,c);
				liberarCasilla(f+1,c);
				liberarCasilla(f,c-1);
				suma=arriba+abajo+izquierda;
				break;
			}
			}while(suma>6);
			return suma;
	}
	if((arriba&&derecha&&abajo)&&(arriba+derecha<=6||arriba+abajo<=6||derecha+abajo<=6)){
			printf("Sumar arriba/derecha(1) arriba/abajo(2) derecha/abajo(3) ");
			if(arriba+derecha+abajo<=6){
				printf("sumar todo(4) : ");
			}
			do{
				if (suma>6){
					printf("Suma mayor a 6, pruebe otra suma");
				}
				scanf("%d",&x);
				while(x<1||x>4){
					scanf("%d",&x);
				}
				switch (x){
				case 1:
					liberarCasilla(f-1,c);
					liberarCasilla(f,c+1);
					suma=arriba+derecha;
					break;
				case 2:
					liberarCasilla(f-1,c);
					liberarCasilla(f+1,c);
					suma=arriba+abajo;
					break;
				case 3:
					liberarCasilla(f,c+1);
					liberarCasilla(f+1,c);
					suma=derecha+abajo;
					break;
				case 4:
					liberarCasilla(f-1,c);
					liberarCasilla(f,c+1);
					liberarCasilla(f+1,c);
					suma=arriba+derecha+abajo;
					break;
				}
				}while(suma>6);
				return suma;
		}
	if((derecha&&izquierda&&abajo)&&(derecha+izquierda<=6||derecha+abajo<=6||izquierda+abajo<=6)){
			printf("Sumar derecha/izquierda(1) derecha/abajo(2) izquierda/abajo(3) ");
			if(derecha+izquierda+abajo<=6){
				printf("sumar todo(4) : ");
			}
			do{
				if (suma>6){
					printf("Suma mayor a 6, pruebe otra suma");
				}
				scanf("%d",&x);
				while(x<1||x>4){
					scanf("%d",&x);
				}
				switch (x){
				case 1:
					liberarCasilla(f,c+1);
					liberarCasilla(f,c-1);
					suma=derecha+izquierda;
					break;
				case 2:
					liberarCasilla(f,c+1);
					liberarCasilla(f+1,c);
					suma=derecha+abajo;
					break;
				case 3:
					liberarCasilla(f,c-1);
					liberarCasilla(f+1,c);
					suma=izquierda+abajo;
					break;
				case 4:
					liberarCasilla(f,c+1);
					liberarCasilla(f+1,c);
					liberarCasilla(f,c-1);
					suma=derecha+abajo+izquierda;
					break;
				}
				}while(suma>6);
				return suma;
		}

	return 1;
}

//funcion de juego del usuario
void jugarUsuario(int n){
	int f,c;
	do{
		printf("Introduzca fila: ");
		scanf("%d",&f);
		f=verifCoord(f);
		printf("Introduzca columna: ");
		scanf("%d",&c);
		c=verifCoord(c);
		if (tablero[f-1][c-1].num!=0){
			printf("Casilla ocupada, intente otra\n");
		}
	}while(tablero[f-1][c-1].num!=0);

	tablero[f-1][c-1].jugador=n;
	tablero[f-1][c-1].num=sumarDados(f-1,c-1);

}

//funcion de juego de la pc
void jugarPC(){
	int f, c;
	time_t t1;
	srand ( (unsigned) time (&t1));
	do{
		f = rand()%4;
		c = rand()%4;
	}while(tablero[f][c].jugador!=0);

	tablero[f][c].jugador=2;
	tablero[f][c].num=sumarDados(f,c);
}

//funcion que verifica si el tablero está lleno
int verifGanar(){
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if (tablero[i][j].jugador==0)
				return 1;
		}
	}
	return 0;
}

//funcion que calcula quien ganó
void ganador(){
	int cont1=0, cont2=0;

	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if (tablero[i][j].jugador==1){
				cont1++;
			}
			else{
				cont2++;
			}
		}
	}
	if (cont1>cont2){
		printf("\x1B[38;2;53;149;240m" "¡¡¡El ganador es el Jugador 1 uno con %d dados!!!" "\x1b[0m", cont1);
	}
	else{
		printf("\x1B[38;2;53;149;240m" "¡¡¡El ganador es la computadora con %d dados!!!" "\x1b[0m", cont2);
	}
}

int main(void) {

	int x;
	printf("\x1B[38;2;53;149;240m" "¡¡¡BIENVENIDO A C-PHALOPOD!!!\n\n" "\x1b[0m");

	printf("Empiezo yo(1)  Empieza la pc(2)  Todo aleatorio(3): ");
	scanf("%d", &x);
	while(x<1||x>3){
		printf("Inserte 1 para empezar usted, 2 para la pc o 3 todo aleatorio: ");
		scanf("%d", &x);
	}
	if(x==3){
		x=rand()%2+1;
	}
	if(x==1){
		while(verifGanar()){
			limpiarPantalla();
			printf("Tu turno\n");
			jugarUsuario(1);
			printTablero();
			printf("Turno de la pc\n");
			jugarPC(2);
			printTablero();
		}
	}
	else{
		if(x==2){
			while(verifGanar()){
				limpiarPantalla();
				printf("Turno de la pc\n");
				jugarPC(1);
				printTablero();
				printf("Tu turno\n");
				jugarUsuario(2);
				printTablero();
			}
		}
	}
	ganador();


	return EXIT_SUCCESS;
}
