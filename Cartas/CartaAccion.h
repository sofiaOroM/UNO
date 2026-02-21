//
// Created by sofia on 14/02/2026.
//

#ifndef JUEGOUNO_CARTAACCION_H
#define JUEGOUNO_CARTAACCION_H

#include "Carta.h"

enum TipoAccion {
    SALTO,
    REVERSA,
    MAS_DOS
};

class CartaAccion : public Carta {
private:
    TipoAccion tipo;

public:
    CartaAccion(string color, TipoAccion tipo);

    bool puedeJugarseSobre(Carta* cartaSuperior);
    void aplicarEfecto(Juego* juego);
    string mostrar();
    bool esMasDos();
    int obtenerPrioridadTipo() const override;;
};

#endif //JUEGOUNO_CARTAACCION_H