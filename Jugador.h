//
// Created by sofia on 10/02/2026.
//

#ifndef JUEGOUNO_JUGADOR_H
#define JUEGOUNO_JUGADOR_H
#include <string>
using namespace std;

class Carta;
class PilaCartas;
class ListaManoCartas;

#include "Mano/ListaManoCartas.h"
#include "Pila/PilaCartas.h"


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

    void robarCarta(PilaCartas* mazo, PilaCartas* descarte, bool esReparto = false);
    Carta* jugarCarta(int indice);

    bool tieneCartaJugable(Carta* cartaSuperior);
    bool haGanado();

    void gritarUNO();
    bool olvidoUNO();
    void reiniciarUNO();

    void mostrarMano();
    void ordenarMano();
};

#endif //JUEGOUNO_JUGADOR_H