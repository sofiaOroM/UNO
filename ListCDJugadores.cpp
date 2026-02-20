//
// Created by sofia on 09/02/2026.
//

#include "ListCDJugadores.h"
#include <iostream>
using namespace std;

ListCDJugadores::ListCDJugadores()
{
    cabeza = nullptr;
    cantidad = 0;
}

bool ListCDJugadores::estaVacia()
{
    if (cabeza == nullptr)
    {
        return true;
    }
    return false;
}

int ListCDJugadores::obtenerCantidad()
{
    return cantidad;
}

NodoJugador* ListCDJugadores::obtenerCabeza()
{
    return cabeza;
}

void ListCDJugadores::insertarJugador(Jugador* jugador)
{
    NodoJugador* nuevo = new NodoJugador(jugador);

    if (estaVacia())
    {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
        cantidad++;
        return;
    }

    NodoJugador* ultimo = cabeza->anterior;

    ultimo->siguiente = nuevo;
    nuevo->anterior = ultimo;

    nuevo->siguiente = cabeza;
    cabeza->anterior = nuevo;
    cantidad++;
}

void ListCDJugadores::eliminarJugador(Jugador* jugador)
{
    if (estaVacia()) return;
    NodoJugador* actual = cabeza;

    for (int i = 0; i < cantidad; i++)
    {
        if (actual->jugador == jugador)
        {
            if (cantidad == 1)
            {
                delete actual;
                cabeza = nullptr;
            }
            else
            {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;

                if (actual == cabeza)
                    cabeza = actual->siguiente;

                delete actual;
            }
            cantidad--;
            return;
        }
        actual = actual->siguiente;
    }
}

NodoJugador* ListCDJugadores::jugadorSiguiente(NodoJugador* actual)
{
    return actual->siguiente;
}

NodoJugador* ListCDJugadores::jugadorAnterior(NodoJugador* actual)
{
    if (actual == nullptr) return nullptr;
    return actual->anterior;
}

void ListCDJugadores::mostrarJugadores()
{
    if (estaVacia())
    {
        cout << "No hay jugadores registrados"<< endl;
        return;
    }

    NodoJugador* actual = cabeza;
    cout <<"Jugadores en la partida:" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        cout <<" - " << actual->jugador->obtenerNombre()<< endl;
        actual = actual->siguiente;
    }
}

void ListCDJugadores::vaciarLista()
{
    while (!estaVacia())
    {
        eliminarJugador(cabeza->jugador);
    }
}

