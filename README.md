Juego de la Escoba de 15 para el TP de Algoritmos y Estructura de datos.
Para jugar copiar el codigo y pegarlo en el compilador online https://www.programiz.com/cpp-programming/online-compiler/

Guía de juego:

Una vez ejecutado el juego, deberemos indicar la cantidad de jugadores a participar (2 o 3):

Una vez ingresado, el juego se da por iniciado, reparte las cartas en la mesa y nos muestra las cartas que posee el jugador 1, cada carta posee un ID por el cual podremos hacer uso de ella; por ejemplo, si quisiera seleccionar el 7 de Basto, deberé escribir el número de ID 15.

A partir de aquí, de forma automática, se evaluará si la misma puede formar una pareja o grupo de cartas que sumen 15, y además, en el caso de que quede la mesa vacía, se suma una escoba a las estadísticas de puntuación del jugador.

Ahora es el turno del jugador 2, como se ha mencionado anteriormente, debe elegir la carta a jugar que pueda sumar 15 con las de la mesa. En este caso no posee ninguna, por lo que la elegida, se descarta de la mano del jugador y se agrega a la mesa.

Los participantes seguirán jugando nuevas rondas, las cartas se repartirán cada vez que ambos se queden sin cartas y la partida se dará por terminada cuando se acaben las cartas del mazo.
Se le dan al último jugador que sumó 15 las cartas que quedaron en la mesa mediante la funcion limpiarMesa().
Una vez finalizado la ronda, se desplegará una lista indicando los puntos, el total de cartas acumuladas, el total de Oros, de sietes, quien posee el siete de oro y el acumulado:


Funcionamiento del código:
Estructuras utilizadas:
struct Carta{
int num;	(Valor numérico de la carta)
str10 palo;	(Palo de la carta)
char ubi;	(Carácter de ubicación) 
}
Sobre el campo de “ubi”, las ubicaciones posibles para cada carta son:
D: deck.
T: Table.
H: Mano jugador 1.
h: Mano jugador 2.
X: Mano jugador 3.
A: Acumulado jugador 1.
a: Acumulado jugador 2.
x: Acumulado jugador 3.

struct Jugador{
    	short puntos=0;	(Puntos)
    	int id;			(Que jugador es)
    	char mano;		(H,h,X)
    	char acum;		(A,a,x)
short cantCartas=0;	(Cantidad de cartas)
bool  sieteOro;		(Posee siete de oro)
short cantOro=0;	(Cantidad de oros)
short cantSiete=0;	(Cantidad de sietes)
short escobas=0;	(Escobas)
};

Los campos de puntuación se resetean al inicio de cada ronda (cuando se terminan las 40 cartas del mazo).
Se utiliza la estructura de “Nodo” para la pila de sumatoria de 15, en la función jugada, ya que allí precisamos el uso de memoria dinámica.
Notar que, todo el juego se lleva a cabo alrededor de la modificación de una única estructura que se va iterando, que es el mazo. Es un vector de 40 elementos de tipo carta, vector el cual almacena cada una de las cartas del mazo y su respectiva ubicación.
Cada carta posee un “id”, que representa la ubicación de la carta en el vector mazo, es decir, que cada vez que utilizamos una carta, lo hacemos por acceso directo.

Al finalizar cada ronda, la ubicación de todas las cartas del mazo se setean en “D” (deck), para poder iniciar una nueva ronda.
Uso de memoria dinámica:
Decidimos utilizar la estructura pila con el fin de poder administrar las cartas a la hora de hacer la sumatoria de 15. 
Los ids de las cartas se van almacenando en la pila, y en caso de sumar 15, se revisan las cartas para sumar la puntuación correspondiente a cada jugador y luego se envían a las cartas acumuladas de cada jugador. 
Creímos conveniente utilizar una pila ya que la cantidad de cartas que se pueden llegar a utilizar para sumar 15 varía.

Funciones:
void repartir(Carta[],int,char): Reparte las cartas.
void mostrarCartas(Carta[],char): Muestra las cartas (Mesa o mano).
int cartaAleatoria(): Genera un número aleatorio del 0 al 39.
short cantCartasT(Carta[]): Cuenta las cartas que hay en la mesa.
void ronda(Jugador&,Carta[]): función que se ejecuta en cada turno.
void jugada(Jugador&, Carta[],short): Algoritmo que verifica si existe alguna combinación de cartas que sume 15.
void calcularPuntaje(Jugador&,Jugador&,Jugador&): Calcula el puntaje de cada jugador
void mostrarPuntaje(Carta[],Jugador): Muestra el puntaje y cartas acumuladas de cada jugador


Función de combinatoria de cartas:

Lógica:
Las cartas vienen ordenadas de manera descendente por valor.
Verifica si la suma con la siguiente carta es menor o igual a 15 y la suma pasando a la siguiente si se pasa.
Si no hay manera de sumar 15 con la carta de valor más alto pasa a la siguiente de valor más alto, y así sucesivamente hasta encontrar la primera combinación de cartas que finalmente sume 15.
La cantidad de veces que intenta combinar cartas es el número de cartas que hay en la mesa.

