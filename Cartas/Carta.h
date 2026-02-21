//
// Created by sofia on 13/02/2026.
//

#ifndef JUEGOUNO_CARTA_H
#define JUEGOUNO_CARTA_H
#include "../Juego.h"
#include <string>
using namespace std;
class Juego;

class Carta {
protected:
    string color;

public:
    Carta(string color);
    virtual ~Carta();

    string obtenerColor();
    void cambiarColor(string nuevoColor);
    virtual bool puedeJugarseSobre(Carta* cartaSuperior) = 0;
    virtual void aplicarEfecto(Juego* juego) = 0;
    virtual string mostrar() = 0;
    virtual bool esComodin();
    virtual bool esMasDos();
    virtual bool esMasCuatro();
    virtual bool esCambioColor();
    virtual int obtenerPrioridadTipo() const = 0;
    virtual int getNumero() const { return -1; }
};

#endif //JUEGOUNO_CARTA_H