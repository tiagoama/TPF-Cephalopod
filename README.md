# TPF-Cephalopod
-para el tablero utilicé una matriz 5x5 de un dato struct "dado" que contiene dos enteros "jugador" 1 o 2 y "num" 1 al 6
pense que al hacerlo con struct seria mas facil de trabajar, entendible para el que lee y facil de pasar al gtk

-limpiarPantalla(): limpia la pantalla en la terminal
-verifCoord(): recibe un entero coordenada y verifica que este entre 1 y 5
-cargarTablero(): inicializa el tablero llenandolo de ceros
-liberarCasilla(): pone ceros en "jugador" y "num" de la casilla, vaciandola
-printTablero(): imprime el tablero con la forma correcta, tambien añade indices para las coordenadas y utiliza los colores respectivos de los jugadores segun tablero.jugador
-
