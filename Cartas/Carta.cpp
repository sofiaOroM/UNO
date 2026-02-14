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