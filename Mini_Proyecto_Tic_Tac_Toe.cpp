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

// DEVUELVE TRUE SI YA NO QUEDAN CASILLAS LIBRES (POSIBLE EMPATE)
bool tableroLleno(char tablero[TAMANO][TAMANO])
{
    for (int fila = 0; fila < TAMANO; fila++)
    {
        for (int col = 0; col < TAMANO; col++)
        {
            if (tablero[fila][col] == VACIO)
            return false;
        }
    }
    return false;
}

// ENTRADA DE DATOS
int leerEntero(const string& mensaje, int minimo, int maximo)
{
    int valor;
    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
        {
            cin.ignore(numeric_limits<streamsize>::max(), "\n");
            if (valor >= minimo && valor <= maximo)
            {
                return valor;
            }
            cout << " Valor fuera de rango. Debe estar entre "
                 << minimo << " y " << maximo << ".\n";
        }else
        {
            if (cin.eof())
            {
                cout << "\nEntrada finalizada. Saliendo....\n";
                exit(0);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), "\n");
            cout << " Entrada invalida. Escriba solo numeros.\n";
        }
    }
}
// PIDE UN NOMBRE AL USUARIO; SI LO DEJA VACÍO USA EL NOMBRE POR DEFECTO
string leerNombre(const string& mensaje, const string& porDefecto)
{
    string nombre; 
    cout << mensaje;
    getline(cin, nombre);
    if (nombre.empty()) return porDefecto;
    return nombre;
}

// PREGUNTA SI/NO Y DEVUELVE TRUE PARA "SÍ"
bool preguntarSiNo(const string& mensaje)
{
    while (true)
    {
        cout << mensaje << " (s/n): ";
        string respuesta;
        if (!getline(cin, respuesta)) exit(0);
        if (respuesta == "s" || respuesta == "S") return true;
        if (respuesta == "n" || respuesta == "N") return false;
        cout << " Responde con 's' o 'n'.\n";
    }
}

// TURNOS DE JUEGO
void turnoHumano(char tablero[TAMANO][TAMANO], const string& nombre, char simbolo)
{
    while (true)
    {
        int casilla = leerEntero(nombre + " (" + simbolo +"), elige una casilla (1-9): ", 1, 9);
        int fila = (casilla - 1) / TAMANO; 
        int col = (casilla - 1) % TAMANO;

        if (casillaLibre(tablero, fila, col))
        {
            tablero[fila][col] = simbolo;
            return;
        }
        cout << " Esa casilla ya esta ocupada. Intenta de nuevo.\n";
    }
}

// BUSCAR UNA CASILLA DONDE "SIMBOLO" GANARÍA EN EL SIGUIENTE MOVIMIENTO
bool buscarGanadora(char tablero[TAMANO][TAMANO], char simbolo, int& filaGanadora, int& colGanadora)
{
    for (int fila = 0; fila < TAMANO; fila++)
    {
        for (int col = 0; col < TAMANO; col++)
        {
            if (tablero [fila][col] == VACIO)
            {
                tablero[fila][col] = simbolo;
                bool gana = hayGanador(tablero, simbolo);
                tablero[fila][col] = VACIO;
                if (gana)
                {
                    filaGanadora = fila;
                    colGanadora = col;
                    return true;
                }
            }
        }
    }
    return false;
}

// TURNO DE LA CPU:
void turnoCPU(char tablero[TAMANO][TAMANO], char simboloCPU, char simboloRival)
{
    int fila col;
    if (buscarJugadaGanadora(tablero, simboloCPU, fila, col)) {} 
    else if (buscarJugadaGanadora(tablero, simboloRival, fila, col)) {} 
    else if (tablero[1][1] == VACIO)
    {
        fila = 1;
        col = 1;
    } else 
    {
        do 
        {
            fila = rand() % TAMANO;
            col = rand() %TAMANO;
        } while (!casillaLibre(tablero, fila, col));
    }
    tablero[fila][col] = simboloCPU;
    cout << "La CPU (" << simboloCPU << ") juega en la casilla"
         << (fila * TAMANO + col + 1) << ".\n";
}

// PARTIDA COMPLETA
// JUEGA UNA PARTIDA. SI CPU ES TRUE, EL JUGADOR 2 ES CONTROLADO POR LA CPU
void jugarPartida(const string& nombre1, const string& nombre2, bool contraCPU)
{
    char tablero[TAMANO][TAMANO];
    limpiarTablero(tablero);
    int turno = 1;
    bool terminado = false;

    while (!terminado)
    {
        mostrarTablero(tablero);

        // EJECUTA EL TURNO SEGÚN QUIÉN JUEGA
        if (turno == 1)
        {
            turnoHumano(tablero, nombre1, SIMBOLO_X);
            if (hayGanador(tablero, SIMBOLO_X))
            {
                mostrarTablero(tablero);
                cout << "***" << nombre1 << " gana la partida! ***\n";
                victoriasJugador1++;
                terminado = true;
            }
        } else
        {
            if (contraCPU)
            {
                turnoCPU(tablero, SIMBOLO_O, SIMBOLO_X);
            } else 
            {
                turnoHumano(tablero, nombre2, SIMBOLO_O);
            }
            if (hayGanador(tablero, SIMBOLO_O))
            {
                mostrarTablero(tablero);
                cout << "***" << nombre2 << " gana la partida! ***\n";
                victoriasJugador2++;
                terminado = true;
            }
        }
        if (!terminado && tableroLleno(tablero))
        {
            mostrarTablero(tablero);
            cout << "*** Empate! ***\n";
            empates++;
            terminado = true;
        }
        turno = (turno == 1) ? 2 : 1;
    }
}

// MENÚS Y EXTRAS
void mostrarInstrucciones()
{
    cout << "\n=========== INSTRUCCIONES ===========\n"
         << "- El tablero tiene casillas numeradas del 1 al 9:\n"
         << "     1 | 2 | 3\n"
         << "     ---------\n"
         << "     4 | 5 | 6\n"
         << "     ---------\n"
         << "     7 | 8 | 9\n"
         << "- Los jugadores se turnan para colocar su simbolo (X u O).\n"
         << "- Gana quien logre 3 simbolos en linea (fila, columna o diagonal).\n"
         << "- Si el tablero se llena sin ganador, es empate.\n"
         << "=====================================\n";
}

void mostrarMarcador(const string& nombre1, const string& nombre2)
{
    cout << "\n------------- MARCADOR -------------\n"
         << nombre1 << ": " << victoriasJugador1 << "\n"
         << nombre2 << ": " << victoriasJugador2 << "\n"
         << "Empates: " << empates << "\n"
         << "------------------------------------\n";
}

void mostrarMenu() 
{
    cout << "\n========== TIC TAC TOE ==========\n"
         << "1. Jugar contra otro jugador\n"
         << "2. Jugar contra la CPU\n"
         << "3. Ver instrucciones\n"
         << "4. Salir\n"
         << "=================================\n";
}
