//
// Created by sofia on 08/02/2026.
//

#include "NodoCartaMano.h"

NodoCartaMano::NodoCartaMano(Carta* carta) {
    this->carta = carta;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}