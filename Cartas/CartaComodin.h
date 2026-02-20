//
// Created by sofia on 14/02/2026.
//

#ifndef JUEGOUNO_CARTACOMODIN_H
#define JUEGOUNO_CARTACOMODIN_H

#include "Carta.h"

enum TipoComodin {
    CAMBIO_COLOR,
    MAS_CUATRO
};

class CartaComodin : public Carta {
private:
    TipoComodin tipo;

public:
    CartaComodin(TipoComodin tipo);

    bool puedeJugarseSobre(Carta* cartaSuperior);
    void aplicarEfecto(Juego* juego);
    string mostrar();
    bool esComodin();
    bool esMasCuatro();
};

#endif //JUEGOUNO_CARTACOMODIN_H