//
// Created by sofia on 12/02/2026.
//

#ifndef JUEGOUNO_LISTCDJUGADORES_H
#define JUEGOUNO_LISTCDJUGADORES_H
#include "NodoJugador.h"

class ListCDJugadores
{
private:
    NodoJugador* cabeza;
    int cantidad;
public:
    ListCDJugadores();
    bool estaVacia();
    int obtenerCantidad();
    NodoJugador* obtenerCabeza();

    void insertarJugador(Jugador* jugador);
    void eliminarJugador(Jugador* jugador);
    NodoJugador* jugadorSiguiente(NodoJugador* actual);
    NodoJugador* jugadorAnterior(NodoJugador* actual);

    void mostrarJugadores();

    void vaciarLista();
};


#endif //JUEGOUNO_LISTCDJUGADORES_H