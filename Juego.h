//
// Created by sofia on 11/02/2026.
//

#ifndef JUEGOUNO_JUEGO_H
#define JUEGOUNO_JUEGO_H

#include "ListCDJugadores.h"
#include "Pila/PilaCartas.h"
#include "Cartas/Carta.h"

#include "Reglas/ConfiguracionPartida.h"
#include  "Reglas/TipoAcumulacion.h"
class ReglasUno;

class Juego {

private:
    PilaCartas* mazo;
    PilaCartas* descarte;

    ListCDJugadores* jugadores;
    NodoJugador* jugadorActual;

    bool sentidoHorario;
    string colorAntesDelMasCuatro;
    Carta* cartaAntesDelMasCuatro;
    Carta* cartaSuperior;
    ConfiguracionPartida config;
    ReglasUno* reglas;
    int roboAcumulado;
    TipoAcumulacion tipoAcumulacionActual;


public:
    Juego(ConfiguracionPartida config);
    ~Juego();
    ConfiguracionPartida getConfig();

    void agregarJugador(Jugador* jugador);
    void iniciarJuego();
    void repartirCartasIniciales();
    void jugarPartida();
    void siguienteTurno();
    void cambiarDireccion();
    void saltarJugador();
    void forzarRobo(int cantidad);
    void elegirNuevoColor();
    void hacerRobar(Jugador* jugador, int cantidad);

    PilaCartas* obtenerMazo();
    PilaCartas* obtenerDescarte();
    Carta* obtenerCartaSuperior();

    void colocarEnDescarte(Carta* carta);
    bool terminoJuego();
    void mostrarEstado();
    void mostrarCartaSuperior();
    void agregarCartasFlip();

    void agregarAcumulacion(int cantidad, TipoAcumulacion tipoAcumulacion);
    bool hayAcumulacionPendiente();
    void ejecutarAcumulacionPendiente(Jugador* jugador);
    TipoAcumulacion obtenerTipoAcumulacion();
    void resolverRetoMasCuatro(Carta* cartaAntesDelMasCuatro);
    ListCDJugadores* obtenerListCDJugadores();
    Jugador* obtenerJugadorActual();
    Jugador* obtenerJugadorSiguiente();
};

#endif //JUEGOUNO_JUEGO_H