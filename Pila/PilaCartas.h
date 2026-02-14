//
// Created by sofia on 11/02/2026.
//

#ifndef JUEGOUNO_PILACARTAS_H
#define JUEGOUNO_PILACARTAS_H

#include "NodoPilaCarta.h"

class PilaCartas {
private:
    NodoPilaCarta* cima;
    int cantidad;

public:
    PilaCartas();
    ~PilaCartas();
    bool estaVacia();
    int obtenerCantidad();
    void apilarCarta(Carta* carta);
    Carta* sacarCarta();
    Carta* verCartaSuperior();
    void vaciarPila();
};

#endif //JUEGOUNO_PILACARTAS_H