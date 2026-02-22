//
// Created by sofia on 20/02/2026.
//

#include "CartaRoboAleatorio.h"
#include "../Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

CartaRoboAleatorio::CartaRoboAleatorio()
    : CartaComodin(CAMBIO_COLOR)
{
}

void CartaRoboAleatorio::aplicarEfecto(Juego* juego)
{
    cout << "¡Carta Caos Aleatorio!" << endl;

    NodoJugador* actual = juego->obtenerListCDJugadores()->obtenerCabeza();
    NodoJugador* inicio = actual;

    do
    {
        int cantidad = (rand() % 5) + 1;

        cout << actual->jugador->obtenerNombre()
             << " roba " << cantidad << " cartas." << endl;

        for (int i = 0; i < cantidad; i++)
        {
            actual->jugador->robarCarta(
                juego->obtenerMazo(),
                juego->obtenerDescarte()
            );
        }

        actual = juego->obtenerListCDJugadores()->jugadorSiguiente(actual);

    } while (actual != inicio);

    //Se elige tambien un color aleatorio
    string colores[4] = {"Rojo", "Azul", "Verde", "Amarillo"};
    int indice = rand() % 4;
    string nuevoColor = colores[indice];

    juego->obtenerCartaSuperior()->cambiarColor(nuevoColor);

    cout << "Nuevo color aleatorio: " << nuevoColor << endl;
}

std::string CartaRoboAleatorio::mostrar()
{
    return "[COMODIN] Caos Aleatorio";
}