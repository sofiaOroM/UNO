//
// Created by sofia on 08/02/2026.
//

#ifndef JUEGOUNO_NODOCARTAMANO_H
#define JUEGOUNO_NODOCARTAMANO_H

class Carta;

class NodoCartaMano {
public:
    Carta* carta;
    NodoCartaMano* siguiente;
    NodoCartaMano* anterior;

    NodoCartaMano(Carta* carta);
};

#endif //JUEGOUNO_NODOCARTAMANO_H