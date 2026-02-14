//
// Created by sofia on 09/02/2026.
//

#include "NodoJugador.h"

NodoJugador::NodoJugador(Jugador* jugador)
{
    this->jugador = jugador;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}
