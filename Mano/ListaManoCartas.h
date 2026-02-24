//
// Created by sofia on 08/02/2026.
//

#ifndef JUEGOUNO_LISTAMANOCARTAS_H
#define JUEGOUNO_LISTAMANOCARTAS_H
#include <string>
class Carta;
class NodoCartaMano;

#include "NodoCartaMano.h"

class ListaManoCartas {
private:
    NodoCartaMano* cabeza;
    NodoCartaMano* cola;
    int cantidad;

public:
    ListaManoCartas();
    ~ListaManoCartas();
    bool estaVacia();
    int obtenerCantidad();
    NodoCartaMano* obtenerCabeza();
    void agregarCarta(Carta* carta);
    void eliminarCarta(int indice);
    Carta* obtenerCartaEn(int indice);
    bool tieneCartaJugable(Carta* cartaSuperior);
    void mostrarCartas();
    void vaciarLista();
    bool debeIrAntes(Carta* a, Carta* b);
    void ordenarMano();
    void transferirCartasDeColor(std::string color, ListaManoCartas* destino);
};

#endif //JUEGOUNO_LISTAMANOCARTAS_H