//
// Created by sofia on 20/02/2026.
//

#ifndef JUEGOUNO_CARTAROBOALEATORIO_H
#define JUEGOUNO_CARTAROBOALEATORIO_H

#include "CartaComodin.h"
#include <string>
using namespace std;

class Juego;

class CartaRoboAleatorio : public CartaComodin
{
    public:
    CartaRoboAleatorio();
    void aplicarEfecto(Juego* juego) override;
    string mostrar() override;
};


#endif //JUEGOUNO_CARTAROBOALEATORIO_H