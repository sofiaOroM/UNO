//
// Created by sofia on 13/02/2026.
//

#include "Carta.h"

Carta::Carta(string color) {
    this->color = color;
}

Carta::~Carta() {}

string Carta::obtenerColor() {
    return color;
}
void Carta::cambiarColor(string nuevoColor) {
    color = nuevoColor;
}

bool Carta::esComodin() {
    return false;
}

bool Carta::esMasDos() {
    return false;
}

bool Carta::esMasCuatro() {
    return false;
}