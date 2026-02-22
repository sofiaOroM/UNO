//
// Created by sofia on 13/02/2026.
//
#include <cstdlib>
#include <ctime>
#include "PilaCartas.h"
#include "../Cartas/Carta.h"
#include "../Cartas/CartaNumero.h"
#include "../Cartas/CartaAccion.h"
#include "../Cartas/CartaComodin.h"
#include <iostream>

#include "../Cartas/CartaRoboAleatorio.h"
#include "../Cartas/CartaTransferenciaColor.h"
using namespace std;

PilaCartas::PilaCartas()
{
    cima = nullptr;
    cantidad = 0;
}

PilaCartas::~PilaCartas()
{
    vaciarPila();
}

bool PilaCartas::estaVacia()
{
    return cima == nullptr;
}

int PilaCartas::obtenerCantidad()
{
    return cantidad;
}

void PilaCartas::apilarCarta(Carta* carta)
{
    NodoPilaCarta* nuevo = new NodoPilaCarta(carta);

    nuevo->siguiente = cima;
    cima = nuevo;

    cantidad++;
}

Carta* PilaCartas::sacarCarta()
{
    if (estaVacia())
    {
        cout << "La pila está vacía." << endl;
        return nullptr;
    }

    NodoPilaCarta* temp = cima;
    Carta* cartaExtraida = temp->carta;

    cima = cima->siguiente;

    delete temp;
    cantidad--;

    return cartaExtraida;
}

Carta* PilaCartas::verCartaSuperior()
{
    if (estaVacia())
        return nullptr;

    return cima->carta;
}

void PilaCartas::vaciarPila()
{
    while (!estaVacia())
    {
        sacarCarta();
    }
}

void PilaCartas::crearMazoCompleto(int nJugadores)
{
    int cantidadMazos = ((nJugadores - 1) / 6) + 1;

    cout << "Generando " << cantidadMazos << " mazo(s)..." << endl;

    for (int i = 0; i < cantidadMazos; i++)
    {
        generarUnMazoUNO();
    }

    barajar();
}

void PilaCartas::generarUnMazoUNO()
{
    string colores[4] = {"Rojo", "Azul", "Verde", "Amarillo"};

    for (int c = 0; c < 4; c++)
    {
        apilarCarta(new CartaNumero(colores[c], 0));

        for (int n = 1; n <= 9; n++)
        {
            apilarCarta(new CartaNumero(colores[c], n));
            apilarCarta(new CartaNumero(colores[c], n));
        }
    }

    for (int c = 0; c < 4; c++)
    {
        for (int i = 0; i < 2; i++)
        {
            apilarCarta(new CartaAccion(colores[c], SALTO));
            apilarCarta(new CartaAccion(colores[c], REVERSA));
            apilarCarta(new CartaAccion(colores[c], MAS_DOS));
        }
    }

    for (int i = 0; i < 4; i++)
    {
        apilarCarta(new CartaComodin(CAMBIO_COLOR));
        apilarCarta(new CartaComodin(MAS_CUATRO));
    }

    apilarCarta(new CartaTransferenciaColor());
    apilarCarta(new CartaRoboAleatorio());
}

void PilaCartas::barajar()
{
    if (cantidad <= 1) return;

    Carta** cartas = new Carta*[cantidad];
    int total = cantidad;

    // Sacar cartas
    for (int i = 0; i < total; i++)
    {
        cartas[i] = sacarCarta();
    }

    // Fisher-Yates shuffle
    for (int i = total - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        Carta* temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }

    // Volver a apilar
    for (int i = 0; i < total; i++)
    {
        apilarCarta(cartas[i]);
    }

    delete[] cartas;

    cout << "Mazo barajado correctamente." << endl;
}

void PilaCartas::recargarDesde(PilaCartas* descarte)
{
    if (descarte == nullptr || descarte->cantidad <= 1)
    {
        cout << "No hay suficientes cartas en descarte para recargar." << endl;
        return;
    }

    cout << "Recargando mazo desde descarte..." << endl;

    Carta* cartaSuperior = descarte->sacarCarta();

    while (!descarte->estaVacia())
    {
        Carta* carta = descarte->sacarCarta();
        apilarCarta(carta);
    }

    descarte->apilarCarta(cartaSuperior);
    barajar();

    cout << "Mazo recargado y barajado correctamente." << endl;
}

void PilaCartas::agregarCartasFlip(int n)
{
    // futuro
}
