//
// Created by sofia on 21/02/2026.
//

#include "CartaTransferenciaColor.h"

string CartaTransferenciaColor::mostrar()
{
    return "COMODIN TRANSFERENCIA";
}

CartaTransferenciaColor::CartaTransferenciaColor()
    : CartaComodin(CAMBIO_COLOR)
{
}

void CartaTransferenciaColor::aplicarEfecto(Juego* juego)
{
    juego->elegirNuevoColor();
    string color = obtenerColor();

    Jugador* actual = juego->obtenerJugadorActual();
    Jugador* siguiente = juego->obtenerJugadorSiguiente();

    actual->transferirCartasDeColor(color, siguiente);
}