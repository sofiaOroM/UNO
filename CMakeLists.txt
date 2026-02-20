cmake_minimum_required(VERSION 4.1)
project(JuegoUno)

set(CMAKE_CXX_STANDARD 20)

add_executable(JuegoUno main.cpp
        juego.cpp
        juego.h
        Jugador.cpp
        Jugador.h
        NodoJugador.cpp
        NodoJugador.h
        ListCDJugadores.cpp
        ListCDJugadores.h
        Mano/NodoCartaMano.cpp
        Mano/NodoCartaMano.h
        Mano/ListaManoCartas.cpp
        Mano/ListaManoCartas.h
        Pila/NodoPilaCarta.cpp
        Pila/NodoPilaCarta.h
        Pila/PilaCartas.cpp
        Pila/PilaCartas.h
        Cartas/Carta.cpp
        Cartas/Carta.h
        Cartas/CartaNumero.cpp
        Cartas/CartaNumero.h
        Cartas/CartaAccion.cpp
        Cartas/CartaAccion.h
        Cartas/CartaComodin.cpp
        Cartas/CartaComodin.h
        Reglas/ReglasUno.cpp
        Reglas/ReglasUno.h
        Reglas/ConfiguracionPartida.h
        Reglas/TipoAcumulacion.h

)
