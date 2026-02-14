//
// Created by sofia on 12/02/2026.
//

#ifndef JUEGOUNO_NODOJUGADOR_H
#define JUEGOUNO_NODOJUGADOR_H
#include "Jugador.h"


class NodoJugador
{
    public:
    NodoJugador(Jugador* jugador);
    Jugador* jugador;
    NodoJugador* siguiente;
    NodoJugador* anterior;
};


#endif //JUEGOUNO_NODOJUGADOR_H