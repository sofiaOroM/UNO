//
// Created by sofia on 17/02/2026.
//

#ifndef JUEGOUNO_REGLASUNO_H
#define JUEGOUNO_REGLASUNO_H

#include "ConfiguracionPartida.h"
#include "TipoAcumulacion.h"
class Jugador;
class Carta;
class Juego;

class ReglasUno {
private:
    ConfiguracionPartida config;

public:
    ReglasUno(ConfiguracionPartida config);

    bool cartaEsJugable(Carta* carta, Carta* superior);
    bool puedeAcumular(Carta* carta, TipoAcumulacion tipoActual);
    void resolverRetoMasCuatro(Juego* juego,
                              Jugador* lanzador,
                              Jugador* afectado);
    void aplicarModoRobo(Juego* juego, Jugador* jugador);

    void verificarGritoUno(Juego* juego, Jugador* jugador);
    bool puedeGanarConCartaNegra(Carta* cartaFinal);

    // Flip
    bool estaActivadoFlip();
};


#endif //JUEGOUNO_REGLASUNO_H