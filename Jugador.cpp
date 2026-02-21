//
// Created by sofia on 10/02/2026.
//

#include "Jugador.h"
#include "./Cartas/Carta.h"
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

void Jugador::robarCarta(PilaCartas* mazo, PilaCartas* descarte, bool esReparto) {

    if (mazo->estaVacia()) {
        mazo->recargarDesde(descarte);
    }

    Carta* carta = mazo->sacarCarta();

    if (carta != nullptr)
    {
        mano->agregarCarta(carta);
        cout << nombre << " robó una carta." << endl;
        if (!esReparto)
            mano->ordenarMano();
        cout << nombre << " robó: " << carta->mostrar() << endl;
    }
}


Carta* Jugador::jugarCarta(int indice)
{
    Carta* carta = mano->obtenerCartaEn(indice);
    if (carta == nullptr)
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

bool Jugador::tieneMasCuatro()
{
    NodoCartaMano* actual = mano->obtenerCabeza();

    while (actual)
    {
        if (actual->carta->esMasCuatro())
            return true;

        actual = actual->siguiente;
    }

    return false;
}

bool Jugador::tieneColor(string color)
{
    NodoCartaMano* actual = mano->obtenerCabeza();

    while (actual)
    {
        if (actual->carta->obtenerColor() == color)
            return true;

        actual = actual->siguiente;
    }

    return false;
}

bool Jugador::tieneNumero(int numero)
{
    NodoCartaMano* actual = mano->obtenerCabeza();

    while (actual)
    {
        if (actual->carta->getNumero() == numero)
            return true;

        actual = actual->siguiente;
    }

    return false;
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
    cout << "Cartas de " << nombre << " : " << endl;
    mano->mostrarCartas();
}

string Jugador::obtenerNombre() {
    return nombre;
}

void Jugador::ordenarMano()
{
    mano->ordenarMano();
}
