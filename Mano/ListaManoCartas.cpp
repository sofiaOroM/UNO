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


string obtenerColorANSI1(const string& texto)
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

ListaManoCartas::ListaManoCartas()
{
    cabeza = nullptr;
    cola = nullptr;
    cantidad = 0;
}

ListaManoCartas::~ListaManoCartas()
{
    vaciarLista();
}

bool ListaManoCartas::estaVacia()
{
    return cabeza == nullptr;
}

int ListaManoCartas::obtenerCantidad()
{
    return cantidad;
}

NodoCartaMano* ListaManoCartas::obtenerCabeza()
{
    return cabeza;
}

void ListaManoCartas::agregarCarta(Carta* carta)
{
    NodoCartaMano* nuevo = new NodoCartaMano(carta);

    if (estaVacia())
    {
        cabeza = nuevo;
        cola = nuevo;
    }
    else
    {
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
        if (actual == nullptr) return nullptr;
        actual = actual->siguiente;
    }
    if (actual == nullptr) return nullptr;

    return actual->carta;
}


void ListaManoCartas::eliminarCarta(int indice)
{
    if (indice < 0 || indice >= cantidad)
        return;

    NodoCartaMano* actual = cabeza;

    for (int i = 0; i < indice; i++)
    {
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

bool ListaManoCartas::tieneCartaJugable(Carta* cartaSuperior)
{
    NodoCartaMano* actual = cabeza;

    while (actual != nullptr)
    {
        if (actual->carta->puedeJugarseSobre(cartaSuperior))
            return true;

        actual = actual->siguiente;
    }

    return false;
}

int ListaManoCartas::buscarPrimeraJugable(Carta* cartaSuperior)
{
    NodoCartaMano* actual = cabeza;
    int indice = 0;

    while (actual != nullptr)
    {
        if (actual->carta->puedeJugarseSobre(cartaSuperior))
            return indice;

        actual = actual->siguiente;
        indice++;
    }

    return -1;
}

void ListaManoCartas::mostrarCartas()
{
    if (estaVacia())
    {
        cout << "Mano vacía."<<endl;
        return;
    }

    const int CARTAS_POR_FILA = 5;
    const int ANCHO = 18; // ancho interno real visible

    NodoCartaMano* inicioFila = cabeza;
    int indiceGlobal = 0;

    while (inicioFila != nullptr)
    {
        NodoCartaMano* cartas[CARTAS_POR_FILA];
        int cantidad = 0;

        NodoCartaMano* actual = inicioFila;

        for (int i = 0; i < CARTAS_POR_FILA && actual != nullptr; i++)
        {
            cartas[i] = actual;
            actual = actual->siguiente;
            cantidad++;
        }

        // ----- Línea superior -----
        for (int i = 0; i < cantidad; i++)
        {
            string color = obtenerColorANSI1(cartas[i]->carta->mostrar());
            cout << color << "+------------------+" << RESET << "   ";
        }
        cout << ""<<endl;

        // ----- Línea central (centrado manual real) -----
        for (int i = 0; i < cantidad; i++)
        {
            string texto = cartas[i]->carta->mostrar();
            string color = obtenerColorANSI1(texto);

            int len = texto.length();
            if (len > ANCHO) len = ANCHO;

            int totalEspacios = ANCHO - len;
            int izq = totalEspacios / 2;
            int der = totalEspacios - izq;

            cout << color
                 << "|"
                 << string(izq, ' ')
                 << texto.substr(0, ANCHO)
                 << string(der, ' ')
                 << "|"
                 << RESET << "   ";
        }
        cout << ""<<endl;

        // ----- Línea inferior -----
        for (int i = 0; i < cantidad; i++)
        {
            string color = obtenerColorANSI1(cartas[i]->carta->mostrar());
            cout << color << "+------------------+" << RESET << "   ";
        }
        cout << ""<<endl;

        // ----- Índices abajo perfectamente centrados -----
        for (int i = 0; i < cantidad; i++)
        {
            string indice = "(" + to_string(indiceGlobal++) + ")";
            int espacios = 20 - indice.length();  // 20 = ancho visible total carta

            int izq = espacios / 2;
            int der = espacios - izq;

            cout << string(izq, ' ')
                 << indice
                 << string(der, ' ')
                 << "   ";
        }
        cout << ""<<endl<<""<<endl;

        inicioFila = actual;
    }
}

void ListaManoCartas::vaciarLista()
{
    while (!estaVacia())
    {
        eliminarCarta(0);
    }
}
void ListaManoCartas::ordenarMano()
{
    if (!cabeza || !cabeza->siguiente)
        return;

    NodoCartaMano* ordenada = nullptr;
    NodoCartaMano* actual = cabeza;

    while (actual != nullptr)
    {
        NodoCartaMano* siguiente = actual->siguiente;

        // Desconectar completamente el nodo
        actual->siguiente = nullptr;
        actual->anterior = nullptr;

        if (!ordenada || debeIrAntes(actual->carta, ordenada->carta))
        {
            actual->siguiente = ordenada;
            if (ordenada)
                ordenada->anterior = actual;

            ordenada = actual;
        }
        else
        {
            NodoCartaMano* temp = ordenada;

            while (temp->siguiente &&
                   !debeIrAntes(actual->carta, temp->siguiente->carta))
            {
                temp = temp->siguiente;
            }

            actual->siguiente = temp->siguiente;

            if (temp->siguiente)
                temp->siguiente->anterior = actual;

            temp->siguiente = actual;
            actual->anterior = temp;
        }

        actual = siguiente;
    }

    cabeza = ordenada;

    // Reconstruir cola correctamente
    NodoCartaMano* recorrer = cabeza;
    cola = nullptr;

    while (recorrer != nullptr)
    {
        if (recorrer->siguiente == nullptr)
            cola = recorrer;

        recorrer = recorrer->siguiente;
    }
}

int prioridadColor(const string& color)
{
    if (color == "Rojo") return 0;
    if (color == "Amarillo") return 1;
    if (color == "Verde") return 2;
    if (color == "Azul") return 3;
    return 4; // Negro u otros
}

bool ListaManoCartas::debeIrAntes(Carta* a, Carta* b)
{
    int colorA = prioridadColor(a->obtenerColor());
    int colorB = prioridadColor(b->obtenerColor());

    if (colorA != colorB)
        return colorA < colorB;

    // mismo color

    int tipoA = a->obtenerPrioridadTipo();
    int tipoB = b->obtenerPrioridadTipo();

    if (tipoA != tipoB)
        return tipoA < tipoB;

    // mismo tipo

    if (tipoA == 0) // números
        return a->getNumero() < b->getNumero();

    return false;
}