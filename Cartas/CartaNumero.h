//
// Created by sofia on 13/02/2026.
//

#ifndef JUEGOUNO_CARTANUMERO_H
#define JUEGOUNO_CARTANUMERO_H
#include "Carta.h"

class CartaNumero : public Carta {
private:
    int numero;

public:
    CartaNumero(string color, int numero);

    bool puedeJugarseSobre(Carta* cartaSuperior);
    void aplicarEfecto(Juego* juego);
    string mostrar();

    int obtenerNumero();
};

#endif //JUEGOUNO_CARTANUMERO_H