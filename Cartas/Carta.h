//
// Created by sofia on 13/02/2026.
//

#ifndef JUEGOUNO_CARTA_H
#define JUEGOUNO_CARTA_H
#include "../Juego.h"
#include <string>
using namespace std;

class Carta {
protected:
    string color;

public:
    Carta(string color);
    virtual ~Carta();

    string obtenerColor();

    virtual bool puedeJugarseSobre(Carta* cartaSuperior) = 0;
    virtual void aplicarEfecto(Juego* juego) = 0;
    virtual string mostrar() = 0;
};

#endif //JUEGOUNO_CARTA_H