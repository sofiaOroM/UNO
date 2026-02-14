//
// Created by sofia on 11/02/2026.
//

#ifndef JUEGOUNO_NODOPILACARTA_H
#define JUEGOUNO_NODOPILACARTA_H

class NodoPilaCarta {
public:
    Carta* carta;
    NodoPilaCarta* siguiente;

    NodoPilaCarta(Carta* carta);
};

#endif //JUEGOUNO_NODOPILACARTA_H