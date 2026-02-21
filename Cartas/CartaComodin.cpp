//
// Created by sofia on 14/02/2026.
//

#include "CartaComodin.h"
#include "../Juego.h"

CartaComodin::CartaComodin(TipoComodin tipo)
    : Carta("NEGRO") {
    this->tipo = tipo;
}

bool CartaComodin::puedeJugarseSobre(Carta* cartaSuperior) {
    // Siempre se puede jugar
    return true;
}

void CartaComodin::aplicarEfecto(Juego* juego) {

    juego->elegirNuevoColor();

    if (tipo == MAS_CUATRO) {
        if (juego->getConfig().permitirAcumulacion)
        {
            juego->agregarAcumulacion(4, ACUM_MAS_CUATRO);
        }
        else
        {
            juego->forzarRobo(4);
        }
    }
}

string CartaComodin::mostrar() {

    if (tipo == CAMBIO_COLOR)
        return "[COMODIN] Cambiar Color" ;

    return "[COMODIN] +4";
}
bool CartaComodin::esComodin() {
    return true;
}

bool CartaComodin::esMasCuatro()
{
    return tipo == MAS_CUATRO;
}
bool CartaComodin::esCambioColor()
{
    return tipo == CAMBIO_COLOR;
}
int CartaComodin::obtenerPrioridadTipo() const
{
    return 2;
}