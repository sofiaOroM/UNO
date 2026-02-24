//
// Created by sofia on 11/02/2026.
//

#include "Juego.h"

#include "Jugador.h"
#include "Cartas/CartaNumero.h"
#include "Reglas/ReglasUno.h"
#include "Cartas/CartaAccion.h"
#include "Cartas/CartaComodin.h"
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <string>

#include <iostream>

#include "Cartas/CartaTransferenciaColor.h"
using namespace std;

#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define BLANCO  "\033[97m"


string obtenerColorANSI(const string& texto)
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

Juego::Juego(ConfiguracionPartida configRecibida)
{
    config = configRecibida;
    reglas = new ReglasUno(config);

    mazo = new PilaCartas();
    descarte = new PilaCartas();

    jugadores = new ListCDJugadores();
    jugadorActual = nullptr;

    sentidoHorario = true;
    cartaSuperior = nullptr;

    roboAcumulado = 0;
    tipoAcumulacionActual = SIN_ACUMULACION;
    time(nullptr);
}

Juego::~Juego()
{
    delete mazo;
    delete descarte;
    delete jugadores;
    delete reglas;
}

ConfiguracionPartida Juego::getConfig()
{
    return config;
}

void Juego::agregarJugador(Jugador* jugador)
{
    jugadores->insertarJugador(jugador);

    if (jugadorActual == nullptr)
    {
        jugadorActual = jugadores->obtenerCabeza();
    }
}

void Juego::iniciarJuego()
{
    int n = jugadores->obtenerCantidad();

    cout << endl << "=== INICIANDO JUEGO UNO ===" << endl;

    mazo->crearMazoCompleto(n);

    if (config.activarUnoFlip)
    {
        cout << "Modo UNO Flip activado." << endl;
        mazo->agregarCartasFlip(n);
        mazo->barajar();
    }

    // Repartir cartas
    repartirCartasIniciales();

    // Primera carta de mesa
    do
    {
        cartaSuperior = mazo->sacarCarta();
    }
    while (cartaSuperior->esComodin());

    descarte->apilarCarta(cartaSuperior);

    cout << "Carta inicial: " << cartaSuperior->mostrar() << endl;
}

void Juego::repartirCartasIniciales()
{
    NodoJugador* aux = jugadores->obtenerCabeza();

    do
    {
        for (int i = 0; i < 7; i++)
        {
            aux->jugador->robarCarta(mazo, descarte, true);
        }

        aux = jugadores->jugadorSiguiente(aux);
    }
    while (aux != jugadores->obtenerCabeza());
    do
    {
        aux->jugador->ordenarMano();
        aux = jugadores->jugadorSiguiente(aux);
    }
    while (aux != jugadores->obtenerCabeza());
}

void Juego::jugarPartida()
{
    cout << endl << "=== COMIENZA LA PARTIDA ===" << endl;

    while (!terminoJuego())
    {
        Jugador* jugador = jugadorActual->jugador;

        cout << endl << "---------------------------------" << endl;
        cout << "Turno de: " << jugador->obtenerNombre() << endl;
        mostrarCartaSuperior();
        if (cartaSuperior->esMasCuatro() || cartaSuperior->esCambioColor())
        {
            cout << "     Color en juego:" << cartaSuperior->obtenerColor() << endl;
        }

        jugador->mostrarMano();

        if (hayAcumulacionPendiente())
        {
            cout << "Tienes un robo acumulado de " << roboAcumulado << " cartas." << endl;

            if (!config.permitirAcumulacion)
            {
                ejecutarAcumulacionPendiente(jugador);
                siguienteTurno();
                continue;
            }

            int opcion;
            cout << "Seleccione índice para intentar acumular (-1 para robar): ";
            cin >> opcion;

            if (opcion == -1)
            {
                // Si es +4 y el reto está activado
                if (config.permitirRetoMasCuatro &&
                    tipoAcumulacionActual == ACUM_MAS_CUATRO)
                {
                    resolverRetoMasCuatro(cartaAntesDelMasCuatro);
                }
                else
                {
                    ejecutarAcumulacionPendiente(jugador);
                }

                siguienteTurno();
                continue;
            }

            Carta* cartaElegida = jugador->jugarCarta(opcion);

            if (!cartaElegida)
            {
                cout << "Carta inválida." << endl;
                continue;
            }

            if (reglas->puedeAcumular(cartaElegida, tipoAcumulacionActual))
            {
                if (cartaElegida->esMasDos())
                    agregarAcumulacion(2, ACUM_MAS_DOS);

                if (cartaElegida->esMasCuatro())
                {
                    colorAntesDelMasCuatro = cartaSuperior->obtenerColor();
                    agregarAcumulacion(4, ACUM_MAS_CUATRO);
                }

                colocarEnDescarte(cartaElegida);

                cout << "¡Robo acumulado ahora es "
                    << roboAcumulado << "!" << endl;

                siguienteTurno();
            }
            else
            {
                cout << "No puedes acumular. Robas todo." << endl;
                ejecutarAcumulacionPendiente(jugador);
                siguienteTurno();
            }

            continue;
        }

        if (!jugador->tieneCartaJugable(cartaSuperior))
        {
            reglas->aplicarModoRobo(this, jugador);

            if (config.tipoRobo == ROBO_UNA_Y_PASA)
            {
                siguienteTurno();
                continue;
            }
        }
        int opcion;
        cout << "Seleccione índice (-1 para pasar, -2 salir): ";
        cin >> opcion;

        if (opcion == -1)
        {
            cout << "Turno pasado." << endl;
            siguienteTurno();
            continue;
        }

        if (opcion == -2)
        {
            cout << "Terminó el juego." << endl;
            return;
        }

        Carta* cartaJugada = jugador->jugarCarta(opcion);
        if (!cartaJugada)
        {
            cout << "Carta inválida." << endl;
            continue;
        }

        if (!cartaJugada->puedeJugarseSobre(cartaSuperior))
        {
            cout << "No puedes jugar esa carta sobre " << cartaSuperior->mostrar() << endl;
            jugador->robarCarta(mazo, descarte);
            continue;
        }

        if (cartaJugada->esMasCuatro())
        {
            cartaAntesDelMasCuatro = cartaSuperior;
            colorAntesDelMasCuatro = cartaSuperior->obtenerColor();
            cout << colorAntesDelMasCuatro << endl;
        }
        colocarEnDescarte(cartaJugada);

        cout << jugador->obtenerNombre() << " jugó: " << cartaJugada->mostrar() << endl;

        cartaJugada->aplicarEfecto(this);

        reglas->verificarGritoUno(this, jugador);

        if (jugador->haGanado())
        {
            if (reglas->puedeGanarConCartaNegra(cartaJugada))
            {
                cout << endl << "GANADOR: " << jugador->obtenerNombre() << endl;
                return;
            }
        }
        siguienteTurno();
    }
}

void Juego::siguienteTurno()
{
    if (sentidoHorario)
    {
        jugadorActual = jugadores->jugadorSiguiente(jugadorActual);
    }
    else
    {
        jugadorActual = jugadores->jugadorAnterior(jugadorActual);
    }
}

void Juego::cambiarDireccion()
{
    sentidoHorario = !sentidoHorario;
    cout << "Dirección invertida!" << endl;
}

void Juego::saltarJugador()
{
    cout << "Jugador saltado!" << endl;
    siguienteTurno();
}

void Juego::forzarRobo(int cantidad)
{
    cout << "El siguiente jugador roba " << cantidad << " cartas!" << endl;

    NodoJugador* siguiente;

    if (sentidoHorario)
        siguiente = jugadores->jugadorSiguiente(jugadorActual);
    else
        siguiente = jugadores->jugadorAnterior(jugadorActual);

    hacerRobar(siguiente->jugador, cantidad);
}

void Juego::elegirNuevoColor()
{
    cout << "Elige un color (Rojo, Azul, Verde, Amarillo): ";
    string nuevo;
    cin >> nuevo;
    if (!nuevo.empty())
    {
        // Convierte el primer carácter a mayúscula y el resto en minuscula
        nuevo[0] = toupper(nuevo[0]);
        transform(nuevo.begin() + 1, nuevo.end(), nuevo.begin() + 1,
                  [](unsigned char c) { return std::tolower(c); });
    }
    cartaSuperior->cambiarColor(nuevo);
    cout << "Nuevo color elegido: " << nuevo << endl;
}

void Juego::hacerRobar(Jugador* jugador, int cantidad)
{
    cout << jugador->obtenerNombre() << " roba " << cantidad << " cartas." << endl;

    for (int i = 0; i < cantidad; i++)
    {
        jugador->robarCarta(mazo, descarte);
    }
}

PilaCartas* Juego::obtenerMazo()
{
    return mazo;
}

PilaCartas* Juego::obtenerDescarte()
{
    return descarte;
}

Carta* Juego::obtenerCartaSuperior()
{
    return cartaSuperior;
}

void Juego::colocarEnDescarte(Carta* carta)
{
    cartaSuperior = carta;
    descarte->apilarCarta(carta);
}

bool Juego::terminoJuego()
{
    return false; // se rompe cuando alguien gana
}

void Juego::mostrarEstado()
{
    cout << "Carta superior: " << cartaSuperior->mostrar() << endl;
}

void Juego::mostrarCartaSuperior()
{
    string texto = cartaSuperior->mostrar();
    string color = obtenerColorANSI(texto);
    cout << endl << "================ CARTA SUPERIOR ================" << endl;
    cout << color;
    cout << "      +----------------------+" << endl;
    cout << "      | " << left << setw(20) << texto << " |" << endl;
    cout << "      +----------------------+" << endl;
    cout << RESET << endl;
}

void Juego::agregarAcumulacion(int cantidad, TipoAcumulacion tipoAcumulacion)
{
    roboAcumulado += cantidad;
    tipoAcumulacionActual = tipoAcumulacion;
}

bool Juego::hayAcumulacionPendiente()
{
    return roboAcumulado > 0;
}

TipoAcumulacion Juego::obtenerTipoAcumulacion()
{
    return tipoAcumulacionActual;
}

void Juego::ejecutarAcumulacionPendiente(Jugador* jugador)
{
    for (int i = 0; i < roboAcumulado; i++)
    {
        jugador->robarCarta(mazo, descarte);
    }

    cout << jugador->obtenerNombre() << " roba " << roboAcumulado << " cartas acumuladas." << endl;

    roboAcumulado = 0;
    tipoAcumulacionActual = SIN_ACUMULACION;
}

void Juego::resolverRetoMasCuatro(Carta* cartaAntesDelMasCuatro)
{
    NodoJugador* siguiente = jugadorActual;
    NodoJugador* jugadorQueJugo = jugadores->jugadorSiguiente(jugadorActual);

    cout << siguiente->jugador->obtenerNombre() << ", ¿deseas retar el +4?" << endl;;
    cout << "1) Sí       2) No" << endl;
    cout << "Opción: ";

    int opcion;
    cin >> opcion;

    string colorAnterior = colorAntesDelMasCuatro;

    if (opcion == 1)
    {
        if (jugadorQueJugo->jugador->tieneColor(colorAnterior) || jugadorQueJugo->jugador->tieneCartaJugable(
            cartaAntesDelMasCuatro))
        {
            cout << "El +4 fue ilegal." << endl;;
            cout << jugadorQueJugo->jugador->obtenerNombre() << " roba 4 cartas." << endl;

            for (int i = 0; i < 4; i++)
                jugadorQueJugo->jugador->robarCarta(mazo, descarte);
        }
        else
        {
            cout << "El +4 fue válido." << endl;
            cout << siguiente->jugador->obtenerNombre() << " roba 6 cartas." << endl;

            for (int i = 0; i < 6; i++)
                siguiente->jugador->robarCarta(mazo, descarte);
        }
    }
    else
    {
        cout << siguiente->jugador->obtenerNombre() << " roba 4 cartas." << endl;

        for (int i = 0; i < 4; i++)
            siguiente->jugador->robarCarta(mazo, descarte);
    }
    roboAcumulado = 0;
    tipoAcumulacionActual = SIN_ACUMULACION;
}

ListCDJugadores* Juego::obtenerListCDJugadores()
{
    return jugadores;
}

Jugador* Juego::obtenerJugadorActual()
{
    return jugadorActual->jugador;
}

Jugador* Juego::obtenerJugadorSiguiente()
{
    NodoJugador* siguiente;

    if (sentidoHorario)
        siguiente = jugadores->jugadorSiguiente(jugadorActual);
    else
        siguiente = jugadores->jugadorAnterior(jugadorActual);

    return siguiente->jugador;
}
