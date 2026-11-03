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

void mostrarTablero(char tablero[TAMANO][TAMANO]) // DIBUJA EL TABLERO.
{
    cout << "\n";
    for (int fila = 0; fila < TAMANO; fila ++)
    {
        cout << "    ";
        for (int col = 0; col < TAMANO; col++)
        {
            if (tablero[fila][col] == VACIO)
            {
                cout << (fila * TAMANO + col + 1); // MUESTRA EL NÚMERO DE CASILLA
            }
            else
            {
                cout << tablero[fila][col];
            }
            if (col < TAMANO - 1) cout << " | "; 
        }
        cout << "\n";
        if (fila < TAMANO - 1) cout << "     ---------\n";
    }
    cout << "\n";
}

// INDICA SI UNA CASILLA ESTÁ DENTRO DEL TABLERO Y LIBRE
bool casillalibre(char tablero[TAMANO][TAMANO], int fila, int col)
{
    return fila >= 0 && fila < TAMANO && col >= 0 && col < TAMANO
            && tablero[fila][col] == VACIO;
}

// REVISA SI EL SIMBOLO DADO COMPLETÓ ALGUNA FILA, COLUMNA O DIAGONAL
bool hayGanador(char tablero[TAMANO][TAMANO], char simbolo)
//FILAS Y COLUMNAS
{
    for (int i = 0; < TAMANO; i++)
    {
        if (tablero[i][0] == simbolo && tablero[i][1] == simbolo && tablero [i][2] == simbolo)
            return true;
        if (tablero[0][i] == simbolo && tablero[1][i] == simbolo && tablero [2][i] == simbolo)
            return true;
    } 
    // DIAGONALES
    if (tablero[0][0] == simbolo && tablero[1][1] == simbolo && tablero [2][2] == simbolo)
        return true;
    if (tablero[0][2] == simbolo && tablero[1][1] == simbolo && tablero [2][0] == simbolo)
        return true;
    return false;
}