#include <iostream>
#include <string>
#include <limits>
#include <cstlib>
# include <ctime>

using namespace std;

//CONSTANTES
const int TAMANO = 3;          
const char VACIO = ' ';        
const char SIMBOLO_X = 'X';    
const char SIMBOLO_O = 'O';

//MARCADOR ACUMULADO ENTRE PARTIDAS 
int victoriasJugador1 = 0
int victoriasJugador2 = 0
int empateas = 0

//FUNCIONES DEL TABLERO
void limpiarTablero(char tablero[TAMANO][TAMANO]) // DEJA TODAS LAS CASILLAS DEL TABLERO VACÍAS
{
    for (int fila = 0; fila < TAMANO; fila++) 
    {
        for (int col = 0; col < TAMANO; col++) 
        {
            tablero[fila][col] = VACIO;
        }
    }
}

void mostrarTablero(char tablero[TAMANO][TAMANO])
{
    cout << "\n";
    for (int fila = 0; fila < TAMANO; fila ++)
    {
        cout << "    ";
        for (int col = 0; col < TAMANO; col++)
        {
            if (tablero[fila][col] == VACIO)
            {
                cout << (fila * TAMANO + col + 1);
            }

        }
    }
}