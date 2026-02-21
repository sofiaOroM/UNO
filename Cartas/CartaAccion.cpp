//
// Created by sofia on 14/02/2026.
//

#include "CartaAccion.h"
#include "../Juego.h"

CartaAccion::CartaAccion(string color, TipoAccion tipo)
    : Carta(color) {
    this->tipo = tipo;
}

bool CartaAccion::puedeJugarseSobre(Carta* cartaSuperior) {

    // Mismo color
    if (this->color == cartaSuperior->obtenerColor())
        return true;

    // Si la carta superior es acción del mismo tipo
    CartaAccion* sup = dynamic_cast<CartaAccion*>(cartaSuperior);

    if (sup != nullptr && sup->tipo == this->tipo)
        return true;

    return false;
}

void CartaAccion::aplicarEfecto(Juego* juego) {

    if (tipo == SALTO) {
        juego->saltarJugador();
    }
    else if (tipo == REVERSA) {
        juego->cambiarDireccion();
    }
    else if (tipo == MAS_DOS) {
        if (juego->getConfig().permitirAcumulacion)
        {
            juego->agregarAcumulacion(2, ACUM_MAS_DOS);
        }
        else
        {
            juego->forzarRobo(2);
        }
    }
}

string CartaAccion::mostrar() {

    if (tipo == SALTO)
        return color + " [SALTO]";

    if (tipo == REVERSA)
        return color + " [REVERSA]";

    return color + " [+2]";
}

bool CartaAccion::esMasDos()
{
    return tipo == MAS_DOS;
}
int CartaAccion::obtenerPrioridadTipo() const
{
    return 1;
}