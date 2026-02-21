//
// Created by sofia on 13/02/2026.
//

#include "CartaNumero.h"
#include <iostream>

CartaNumero::CartaNumero(string color, int numero)
    : Carta(color) {
    this->numero = numero;
}

int CartaNumero::obtenerNumero() {
    return numero;
}

bool CartaNumero::puedeJugarseSobre(Carta* cartaSuperior) {

    // Mismo color
    if (this->color == cartaSuperior->obtenerColor())
        return true;

    // Si la superior también es número y coincide
    CartaNumero* superior = dynamic_cast<CartaNumero*>(cartaSuperior);
    if (superior != nullptr && superior->numero == this->numero)
        return true;

    return false;
}

void CartaNumero::aplicarEfecto(Juego* juego) {
    // No hace nada ya que es solo de numeros
}

string CartaNumero::mostrar() {
    return color + " " + to_string(numero);
}

int CartaNumero::obtenerPrioridadTipo() const
{
    return 0; // números primero
}

int CartaNumero::getNumero() const
{
    return numero;
}