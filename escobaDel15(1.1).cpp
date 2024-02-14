#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
typedef char str10[11];

/*
Pendiente:
-Word
-Indicar quien gano la partida
-Las cartas de la mesa que quedan cuando se termina una ronda vayan para el ultimo que junto 15
*/

struct Carta{
    int num;
    str10 palo; 
    char ubi;// T: Table, H: Hand p1, h: Hand p2, A: acumuladoP1, a: acumuladoP2,D: Deck, S: Score
};

struct Jugador{
    
    short puntos=0;
    int id;
    char mano;
    char acum;
    short cantCartas=0;
    bool  sieteOro;
    short cantOro=0;
    short cantSiete=0;
    short escobas=0;
};

void repartir(Carta[],int,char); //Reparte las cartas
void mostrarCartas(Carta[],char); //Muestra las cartas
int cartaAleatoria(); //Genera un numero aleatorio del 0 al 39
short cantCartasT(Carta[]); //Cuenta las cartas que hay en la mesa
void ronda(Jugador&,Carta[]); //Cada turno
void jugada(Jugador&, Carta[],short); //Cada jugada
void calcularPuntaje(Jugador&,Jugador&,Jugador&); //Calcula el puntaje de cada jugador

int main(){

    srand(time(nullptr)); // Inicializar la semilla del generador de números pseudoaleatorios

    Carta mazo[40] = {{1,"Basto",'D'},{1,"Copa",'D'},{1,"Espada",'D'},{1,"Oro",'D'},
                      {2,"Basto",'D'},{2,"Copa",'D'},{2,"Espada",'D'},{2,"Oro",'D'},
                      {3,"Basto",'D'},{3,"Copa",'D'},{3,"Espada",'D'},{3,"Oro",'D'},
                      {4,"Basto",'D'},{4,"Copa",'D'},{4,"Espada",'D'},{4,"Oro",'D'},
                      {5,"Basto",'D'},{5,"Copa",'D'},{5,"Espada",'D'},{5,"Oro",'D'},
                      {6,"Basto",'D'},{6,"Copa",'D'},{6,"Espada",'D'},{6,"Oro",'D'},
                      {7,"Basto",'D'},{7,"Copa",'D'},{7,"Espada",'D'},{7,"Oro",'D'},
                      {8,"Basto",'D'},{8,"Copa",'D'},{8,"Espada",'D'},{8,"Oro",'D'},
                      {9,"Basto",'D'},{9,"Copa",'D'},{9,"Espada",'D'},{9,"Oro",'D'},
                      {10,"Basto",'D'},{10,"Copa",'D'},{10,"Espada",'D'},{10,"Oro",'D'}
                    };

    Jugador jug1={0,1,'H','A',0,false,0,0,0};
    Jugador jug2={0,2,'h','a',0,false,0,0,0};
    Jugador jug3={0,3,'X','x',0,false,0,0,0};


    int cantJug;
    cout<<"[-] Ingrese la cantidad de jugadores (2 o 3): ";cin>>cantJug;
    while(cantJug != 2 && cantJug != 3){
        cout<<"[-] Error, ingrese un numero valido."<<endl;
        cout<<"[-] Ingrese la cantidad de jugadores (2 o 3): ";cin>>cantJug;
    }

    if(cantJug == 2){ // PARTIDA 2 Jugadores

        while(jug1.puntos < 15 && jug2.puntos < 15){

            repartir(mazo,4,'T'); // Se le reparte a la mesa.
            int cantCartasRepartidas = 4;

            while (cantCartasRepartidas < 40){

                repartir(mazo,3,jug1.mano); // Se le reparte al j1
                repartir(mazo,3,jug2.mano); // Se le reparte al j2
                cout<<"=============================="<<endl;
                ronda(jug1,mazo);
                cout<<"=============================="<<endl;
                ronda(jug2,mazo);
                cout<<"=============================="<<endl;
                ronda(jug1,mazo);
                cout<<"=============================="<<endl;
                ronda(jug2,mazo);
                cout<<"=============================="<<endl;
                ronda(jug1,mazo);
                cout<<"=============================="<<endl;
                ronda(jug2,mazo);

                cantCartasRepartidas += 6;

            }
            // Muestran las cartas acumuladas por cada jugador.
            cout<<"====== Acumulado J1 ======:"<<endl;
            mostrarCartas(mazo,jug1.acum);
            cout<<"====== Acumulado J2 ======"<<endl;
            mostrarCartas(mazo,jug2.acum);

            // Calculamos puntaje
            calcularPuntaje(jug1,jug2,jug3);

            cout<<"====== Jugador 1 ======"<<endl;
            cout<<"-puntos: "<<jug1.puntos<<endl;
            cout<<"-Cantidad de cartas: "<<jug1.cantCartas<<endl;
            cout<<"-Cantidad de Oros: "<<jug1.cantOro<<endl;
            cout<<"-Cantidad de 7: "<<jug1.cantSiete<<endl;
            cout<<"-Escobas: "<<jug1.escobas<<endl;
            if(jug1.sieteOro){
                cout<<"-Siete oro"<<endl;
            }

            cout<<"====== Jugador 2 ======"<<endl;
            cout<<"-puntos: "<<jug2.puntos<<endl;
            cout<<"-Cantidad de cartas: "<<jug2.cantCartas<<endl;
            cout<<"-Cantidad de Oros: "<<jug2.cantOro<<endl;
            cout<<"-Cantidad de 7: "<<jug2.cantSiete<<endl;
            cout<<"-Escobas: "<<jug2.escobas<<endl;
            if(jug2.sieteOro){
                cout<<"-Siete oro"<<endl;
            }

            // Devolvemos las cartas al mazo
            for(int i=0;i<40;i++){
                mazo[i].ubi = 'D';
            }

            jug1={jug1.puntos,1,'H','A',0,false,0,0,0};
            jug2={jug2.puntos,2,'h','a',0,false,0,0,0};
        }
    }

    else{ // PARTIDA 3 JUGADORES

        while(jug1.puntos < 15 && jug2.puntos < 15){

                        
            repartir(mazo,4,'T'); // Se le reparte a la mesa.
            int cantCartasRepartidas = 4;

            while (cantCartasRepartidas < 40){

                repartir(mazo,3,jug1.mano); // Se le reparte al j1
                repartir(mazo,3,jug2.mano); // Se le reparte al j2
                repartir(mazo,3,jug3.mano); // Se le reparte al j3

                cout<<"=============================="<<endl;
                ronda(jug1,mazo);
                cout<<"=============================="<<endl;
                ronda(jug2,mazo);
                cout<<"=============================="<<endl;
                ronda(jug3,mazo);
                cout<<"=============================="<<endl;
                ronda(jug1,mazo);
                cout<<"=============================="<<endl;
                ronda(jug2,mazo);
                cout<<"=============================="<<endl;
                ronda(jug3,mazo);
                cout<<"=============================="<<endl;
                ronda(jug1,mazo);
                cout<<"=============================="<<endl;
                ronda(jug2,mazo);
                cout<<"=============================="<<endl;
                ronda(jug3,mazo);

                cantCartasRepartidas += 9;

            }

            // Muestran las cartas acumuladas por cada jugador.
            cout<<"[-] Acumulado j1:"<<endl;
            mostrarCartas(mazo,jug1.acum);
            cout<<"[-] Acumulado j2:"<<endl;
            mostrarCartas(mazo,jug2.acum);
            cout<<"[-] Acumulado j3:"<<endl;
            mostrarCartas(mazo,jug3.acum);

            // Calculamos puntaje
            calcularPuntaje(jug1,jug2,jug3);

            // Devolvemos las cartas al mazo
            for(int i=0;i<40;i++){
                mazo[i].ubi = 'D';
            }
        }
    }

    getch(); 
    return 0;
};

void ronda(Jugador& jug, Carta m[]){
    
    
    int card = 0;
    cout<<"============ MESA ============"<<endl;
    mostrarCartas(m,'T');
    cout<<"========= Jugador "<<jug.id<<" =========="<<endl;
    mostrarCartas(m,jug.mano);

    cout<<"[-] Seleccione una carta de su mano (por id): ";cin>>card; //Selecciona la carta de la mano que desea jugar.
    while(!(m[card].ubi == jug.mano)){
        cout<<"[-] Ingresar una carta valida que este en su mano: ";cin>>card;
    }
    m[card].ubi = 'T';
    
    cout<<"[-] Carta jugada: "<<m[card].num<<" de "<<m[card].palo<<endl;
    jugada(jug,m,card);
}

void jugada(Jugador &jug, Carta m[],short card){ //id de carta elegida
    
    int var=0;

    cout<<"[-] Pasar (0) / Hacer jugada (1): ";cin>>var; //Se pregunta si la desea descartar o realizar una jugada.
    
    short cantT = cantCartasT(m);
    while(var != 0 && var != 1){
        cout<<"[-] Ingrese una opcion valida."<<endl;
        cout<<"[-] pasar (0) / Hacer jugada (1): ";cin>>var;
    }
    

    if(var == 1){

        int n;
        cout<<"[-] Elija cantidad de cartas para hacer combinacion con la suya: ";cin>>n;

        while(n>cantT){
            cout<<"[-] No hay tantas cartas en la mesa."<<endl;
            cout<<"[-] Cuantas cartas de la mesa desea seleccionar (sin contar la suya): ";cin>>n;
        }

        
        int quince = m[card].num;
        int ids[n]; //Vector de ids
        m[card].ubi=jug.acum;
        for(int i=0;i<n;i++){

            int indice=0;

            cout<<"[-] Seleccione una carta de la mesa (por id): ";cin>>indice;
            while(!(m[indice].ubi == 'T')){
                cout<<"[-] Error, Ingresar una carta que este en la mesa: ";cin>>indice;
            }

            quince += m[indice].num;
            ids[i] = indice;
            m[indice].ubi = jug.acum;
        }

        if(quince == 15){
            if(n == cantT-1){
                jug.escobas++;
                cout<<"[-] Usted hizo escoba!"<<endl;
            }
            //Puntaje
            jug.cantCartas += n+1;
            for(int i=0;i<n;i++){
                
                if(strcmp(m[ids[i]].palo,"Oro")==0){ // Acumula oros
                    jug.cantOro++;
                }

                if(m[ids[i]].num == 7){ // Acumula 7
                    jug.cantSiete++;
                }

                if(ids[i] == 27){ // Siete de oro
                    jug.sieteOro = true;
                }
            }
        }

        if(quince != 15){

            for(int i=0;i<n;i++){
                m[ids[i]].ubi ='T';
            }
            cout<<"[-] Las cartas no suman 15."<<endl;
            m[card].ubi = 'T';
            jugada(jug,m,card);
        }   
    }
};

void repartir(Carta mazo[],int n, char u){

    for (int i = 0; i < n; ++i) {
        int indice = cartaAleatoria();
        while (!(mazo[indice].ubi == 'D')) {
            indice = cartaAleatoria();
        }
        mazo[indice].ubi = u;
    }
}

// Función para generar un número aleatorio en el rango de 0 a 39
int cartaAleatoria() {
    return rand() % 40;
}

void mostrarCartas(Carta m[],char u){ //Muestra las cartas y cuenta cuantas cartas hay en la mesa
   
    cout<<"-Id- ==== CARTA ==== "<<endl;
    for(int i=0;i<40;i++){
        
        if(m[i].ubi == u){
            cout<<"["<<setw(2)<<i<<"] ----"<<setw(2)<<m[i].num<<" de "<<m[i].palo<<endl;  
        }
    }
};

short cantCartasT(Carta m[]){

    short n = 0;

    for(int i=0;i<40;i++){
        if(m[i].ubi == 'T'){
            n++;
        }
    }
    return n;
}

void calcularPuntaje(Jugador &jug1,Jugador &jug2, Jugador &jug3){

    // Suma las escobas

    jug1.puntos += jug1.escobas;
    jug2.puntos += jug2.escobas;
    jug3.puntos += jug3.escobas;

    // Consulta por el siete de oro

    if(jug1.sieteOro){
        jug1.puntos++;
    }

    if(jug2.sieteOro){
        jug2.puntos++;
    }

    if(jug3.sieteOro){
        jug3.puntos++;
    }

    // Compara cantidad de oros

    if(jug1.cantOro > jug2.cantOro && jug1.cantOro > jug3.cantOro){
        jug1.puntos++;
    }

    if(jug2.cantOro > jug1.cantOro && jug2.cantOro > jug3.cantOro){
        jug2.puntos++;
    }

    if(jug3.cantOro > jug1.cantOro && jug3.cantOro > jug2.cantOro){
        jug3.puntos++;
    }

    // Compara cantidad de cartas

    if(jug1.cantCartas > jug2.cantCartas && jug1.cantCartas > jug3.cantCartas){
        jug1.puntos++;
    }

    if(jug2.cantCartas > jug1.cantCartas && jug2.cantCartas > jug3.cantCartas){
        jug2.puntos++;
    }

    if(jug3.cantCartas > jug1.cantCartas && jug3.cantCartas > jug2.cantCartas){
        jug3.puntos++;
    }

    // Compara cantidad de 7

    if(jug1.cantSiete > jug2.cantSiete && jug1.cantSiete > jug3.cantSiete){
        jug1.puntos++;
    }

    if(jug2.cantSiete > jug1.cantSiete && jug2.cantSiete > jug3.cantSiete){
        jug2.puntos++;
    }

    if(jug3.cantSiete > jug1.cantSiete && jug3.cantSiete > jug2.cantSiete){
        jug3.puntos++;
    }
};