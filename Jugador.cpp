//
// Created by sofia on 10/02/2026.
//

#include "Jugador.h"
#include "Carta.h"
#include "Pila/PilaCartas.h"
#include "Mano/ListaManoCartas.h"

#include <iostream>

Jugador::Jugador(string nombre)
{
    this->nombre = nombre;
    this->mano = new ListaManoCartas();
    this->dijoUNO = false;
}

Jugador::~Jugador()
{
    delete mano;
}

void Jugador::robarCarta(PilaCartas* mazo)
{
    if (mano->estaVacia())
    {
        cout << "El mazo está vacio" << endl;
        return;
    }

    Carta* cartaRobada = mazo->sacarCarta();
    mano->agregarCarta(cartaRobada);

    cout << nombre<< "robó una carta"<< endl;
}

Carta* Jugador::jugarCarta(int indice)
{
    Carta* carta = mano->obtenerCartaEn(indice);
    if (carta = nullptr)
    {
        cout<<"indice invalido"<< endl;
        return nullptr;
    }

    mano->eliminarCarta(indice);
    return carta;
}

bool Jugador::tieneCartaJugable(Carta* cartaSuperior)
{
    return mano->tieneCartaJugable(cartaSuperior);
}

bool Jugador::haGanado()
{
    return mano->obtenerCantidad() == 0;
}

void Jugador::gritarUNO()
{
    dijoUNO = true;
}

bool Jugador::olvidoUNO()
{
    return (mano->obtenerCantidad() == 1 && !dijoUNO);
}

void Jugador::reiniciarUNO()
{
    dijoUNO = false;
}

void Jugador::mostrarMano()
{
    cout << "Cartas de " << nombre << " : ";
    mano->mostrarCartas();
}
