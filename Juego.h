//
// Created by sofia on 11/02/2026.
//

#ifndef JUEGOUNO_JUEGO_H
#define JUEGOUNO_JUEGO_H
#include "ListCDJugadores.h"
#include "Pila/PilaCartas.h"
#include "Cartas/Carta.h"

class Juego
{
private:
    PilaCartas<Carta*> mazo;
    PilaCartas<Carta*> descarte;
    ListCDJugadores<Jugador*> jugadores;
    Config reglas;
    bool direccion = false;
    Carta* cartaActual;

public:
    void iniciarJuego();
    void direccionJuego();
    void turno();
    void aplicarEfectoCarta(Carta* carta);
    bool finJuego();
    void verificarGanador();
    void reversarJuego();
    void saltarJugador();
    void tomarCartas(cantidad: int);
    void llamadaUno();
    void sumarCarta(atacante: Jugador*, afectado: Jugador*);
};


#endif //JUEGOUNO_JUEGO_H