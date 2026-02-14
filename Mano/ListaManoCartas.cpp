//
// Created by sofia on 08/02/2026.
//

#include "ListaManoCartas.h"
#include <iostream>

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

Carta* ListaManoCartas::obtenerCartaEn(int indice) {

    if (indice < 0 || indice >= cantidad)
        return nullptr;

    NodoCartaMano* actual = cabeza;

    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }

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

void ListaManoCartas::mostrarCartas() {

    if (estaVacia()) {
        std::cout << "Mano vacía.\n";
        return;
    }

    NodoCartaMano* actual = cabeza;
    int i = 0;

    while (actual != nullptr) {
        std::cout << i << ") " << actual->carta->mostrar() << "\n";
        actual = actual->siguiente;
        i++;
    }
}

void ListaManoCartas::vaciarLista() {

    while (!estaVacia()) {
        eliminarCarta(0);
    }
}