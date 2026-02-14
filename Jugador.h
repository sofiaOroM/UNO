//
// Created by sofia on 10/02/2026.
//

#ifndef JUEGOUNO_JUGADOR_H
#define JUEGOUNO_JUGADOR_H
#include <string>
#include "Mano/ListaManoCartas.h"
#include "Pila/PilaCartas.h"
#include "Cartas/Carta.h"
using namespace std;


class Jugador
{

private:
    string nombre;
    ListaManoCartas* mano;
    bool dijoUNO;

public:
    // Constructor y destructor
    Jugador(string nombre);
    ~Jugador();

    string obtenerNombre();
    int obtenerCantidadCartas();

    void robarCarta(PilaCartas* mazo);
    Carta* jugarCarta(int indice);

    bool tieneCartaJugable(Carta* cartaSuperior);
    bool haGanado();

    void gritarUNO();
    bool olvidoUNO();
    void reiniciarUNO();

    void mostrarMano();
};

#endif //JUEGOUNO_JUGADOR_H