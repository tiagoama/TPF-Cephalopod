# TPF-Cephalopod
-para el tablero utilicé una matriz 5x5 de un dato struct "dado" que contiene dos enteros "jugador" 1 o 2 y "num" 1 al 6
pense que al hacerlo con struct seria mas facil de trabajar, entendible para el que lee y facil de pasar al gtk

-limpiarPantalla(): limpia la pantalla en la terminal
-verifCoord(): recibe un entero coordenada y verifica que este entre 1 y 5
-cargarTablero(): inicializa el tablero llenandolo de ceros
-liberarCasilla(): pone ceros en "jugador" y "num" de la casilla, vaciandola
-printTablero(): imprime el tablero con la forma correcta, tambien añade indices para las coordenadas y utiliza los colores respectivos de los jugadores segun tablero.jugador

-sumarDados(): funcion que realiza las combinaciones de dados, ejecuta automaticamente las sumas de 2 dados rodeados de casillas vacias.
 a partir de 3 dados solicita al usuario las sumas a realizar hasta que elija una válida.
 guarda las casillas adyacentes en los enteros: arriba, abajo, izquierda y derecha; y los utiliza en las operaciones para una mejor comprensión del programa.
 tambien llama a liberarCasilla() segun las sumas hechas.
 retorna la suma automatica o elegida de la casilla seleccionada.

-jugarUsuario(): funcion de juego del usuario, pide las coordenadas, las verifica con verifCoords y las utiliza en sumarDados; al final actualiza los valores de la casilla elegida.

-jugarPC(): funcion de juego de la PC, utiliza rand() y srand() para elegir coordenadas validas, luego llama a sumarDados() y al final actualiza los datos de la casilla.

-verifGanar(): solo verifica si el tablero está lleno.

-ganador(): cuenta los dados de cada jugador e imprime en pantalla quien es el ganador! :)
 
- en el main() se dan las opciones de inicio del juego, se puede elegir quien empieza pero el color es el mismo siempre para el que empieza como en otros juegos.
