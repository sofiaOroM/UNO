#include "ReglasUno.h"
#include "../Juego.h"
#include "../Jugador.h"

#include <iostream>

using namespace std;

ReglasUno::ReglasUno(ConfiguracionPartida config)
{
    this->config = config;
}

bool ReglasUno::puedeAcumular(Carta* carta, TipoAcumulacion tipoActual)
{
    if(!config.permitirAcumulacion)
        return false;

    if(tipoActual == ACUM_MAS_DOS && carta->esMasDos())
        return true;

    if(tipoActual == ACUM_MAS_CUATRO && carta->esMasCuatro())
        return true;

    return false;
}

void ReglasUno::aplicarModoRobo(Juego* juego, Jugador* jugador)
{
    // Por ahora siempre roba solo 1 carta
    jugador->robarCarta(juego->obtenerMazo(),
                        juego->obtenerDescarte());
}

void ReglasUno::verificarGritoUno(Juego* juego, Jugador* jugador)
{
    if (!config.permitirGritoUno)
        return;

    if (jugador->obtenerCantidadCartas() == 1)
    {
        string respuesta;
        cout << "¡Te queda 1 carta! Escribe UNO: ";
        cin >> respuesta;

        if (respuesta != "UNO")
        {
            cout << "No gritaste UNO. Robas 2 cartas." << endl;
            jugador->robarCarta(juego->obtenerMazo(), juego->obtenerDescarte());
            jugador->robarCarta(juego->obtenerMazo(), juego->obtenerDescarte());
        }
        else
        {
            cout << "UNO!" <<endl;
        }
    }
}

bool ReglasUno::puedeGanarConCartaNegra(Carta* carta)
{
    if (config.permitirGanarConNegra)
        return true;

    if (carta->esComodin())
        return false;

    return true;
}

int Jugador::obtenerCantidadCartas()
{
    return mano->obtenerCantidad();
}