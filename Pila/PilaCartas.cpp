//
// Created by sofia on 13/02/2026.
//

#include "PilaCartas.h"
#include <iostream>

PilaCartas::PilaCartas() {
    cima = nullptr;
    cantidad = 0;
}

PilaCartas::~PilaCartas() {
    vaciarPila();
}

bool PilaCartas::estaVacia() {
    return cima == nullptr;
}

int PilaCartas::obtenerCantidad() {
    return cantidad;
}

void PilaCartas::apilarCarta(Carta* carta) {

    NodoPilaCarta* nuevo = new NodoPilaCarta(carta);

    nuevo->siguiente = cima;
    cima = nuevo;

    cantidad++;
}

Carta* PilaCartas::sacarCarta() {

    if (estaVacia()) {
        std::cout << "La pila está vacía.\n";
        return nullptr;
    }

    NodoPilaCarta* temp = cima;
    Carta* cartaExtraida = temp->carta;

    cima = cima->siguiente;

    delete temp;
    cantidad--;

    return cartaExtraida;
}

Carta* PilaCartas::verCartaSuperior() {

    if (estaVacia())
        return nullptr;

    return cima->carta;
}

void PilaCartas::vaciarPila() {

    while (!estaVacia()) {
        sacarCarta();
    }
}