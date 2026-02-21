//
// Created by sofia on 08/02/2026.
//

#include "ListaManoCartas.h"
#include "../Cartas/Carta.h"
#include <iostream>
#include <iomanip>
#include <string>

#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define BLANCO  "\033[97m"


string obtenerColorANSI(const string& texto)
{
    if (texto.find("Rojo") != string::npos)
        return ROJO;

    if (texto.find("Verde") != string::npos)
        return VERDE;

    if (texto.find("Azul") != string::npos)
        return AZUL;

    if (texto.find("Amarillo") != string::npos)
        return AMARILLO;

    if (texto.find("COMODIN") != string::npos)
        return BLANCO;
    return RESET;
}
ListaManoCartas::ListaManoCartas() {
    cabeza = nullptr;
    cola = nullptr;
    cantidad = 0;
}

ListaManoCartas::~ListaManoCartas() {
    vaciarLista();
}

bool ListaManoCartas::estaVacia() {
    return cabeza == nullptr;
}

int ListaManoCartas::obtenerCantidad() {
    return cantidad;
}

void ListaManoCartas::agregarCarta(Carta* carta) {

    NodoCartaMano* nuevo = new NodoCartaMano(carta);

    if (estaVacia()) {
        cabeza = nuevo;
        cola = nuevo;
    }
    else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }

    cantidad++;
}

Carta* ListaManoCartas::obtenerCartaEn(int indice)
{
    if (indice < 0 || indice >= cantidad)
        return nullptr;

    NodoCartaMano* actual = cabeza;

    for (int i = 0; i < indice; i++)
    {
        if(actual == nullptr) return nullptr;
        actual = actual->siguiente;
    }
    if(actual == nullptr) return nullptr;

    return actual->carta;
}


void ListaManoCartas::eliminarCarta(int indice) {

    if (indice < 0 || indice >= cantidad)
        return;

    NodoCartaMano* actual = cabeza;

    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }

    // Reconectar nodos
    if (actual->anterior != nullptr)
        actual->anterior->siguiente = actual->siguiente;
    else
        cabeza = actual->siguiente;

    if (actual->siguiente != nullptr)
        actual->siguiente->anterior = actual->anterior;
    else
        cola = actual->anterior;

    delete actual;
    cantidad--;
}

bool ListaManoCartas::tieneCartaJugable(Carta* cartaSuperior) {

    NodoCartaMano* actual = cabeza;

    while (actual != nullptr) {

        if (actual->carta->puedeJugarseSobre(cartaSuperior))
            return true;

        actual = actual->siguiente;
    }

    return false;
}

int ListaManoCartas::buscarPrimeraJugable(Carta* cartaSuperior) {

    NodoCartaMano* actual = cabeza;
    int indice = 0;

    while (actual != nullptr) {

        if (actual->carta->puedeJugarseSobre(cartaSuperior))
            return indice;

        actual = actual->siguiente;
        indice++;
    }

    return -1;
}
void ListaManoCartas::mostrarCartas()
{
    if (estaVacia()) {
        cout << "Mano vacía." << endl;
        return;
    }

    NodoCartaMano* actual = cabeza;
    int i = 0;
    const int CARTAS_POR_FILA = 5;

    while (actual != nullptr)
    {
        string textoCarta = actual->carta->mostrar();
        string color = obtenerColorANSI(textoCarta);

        cout << setw(2) << i << ") "
             << color
             << left << setw(20)
             << ("[" + textoCarta + "]")
             << RESET;

        actual = actual->siguiente;
        i++;

        if (i % CARTAS_POR_FILA == 0)
            cout << endl;
    }

    if (i % CARTAS_POR_FILA != 0)
        cout << endl;
}

void ListaManoCartas::vaciarLista() {

    while (!estaVacia()) {
        eliminarCarta(0);
    }
}