//
// Created by sofia on 21/02/2026.
//

#ifndef JUEGOUNO_CARTATRANSFERENCIACOLOR_H
#define JUEGOUNO_CARTATRANSFERENCIACOLOR_H

#include "CartaComodin.h"
#include <string>

class Juego;
class CartaTransferenciaColor: public CartaComodin
{
public:
    CartaTransferenciaColor();
    void aplicarEfecto(Juego* juego) override;
    string mostrar() override;
};

#endif //JUEGOUNO_CARTATRANSFERENCIACOLOR_H