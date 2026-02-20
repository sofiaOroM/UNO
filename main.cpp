#include "Juego.h"
#include "Jugador.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Reglas/ConfiguracionPartida.h"
using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
void mostrarTitulo()
{
    cout << "========================================="<<endl;
    cout << "            BIENVENIDO A UNO "<<endl;
    cout << "========================================"<<endl;
}

int seleccionarModoJuego()
{
    int opcion;

    cout << endl << "Seleccione el modo de juego:"<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "1) UNO Básico"<<endl;
    cout << "2) UNO Flip (Próximamente)"<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "Opción: ";
    cin >> opcion;

    while (opcion < 1 || opcion > 2)
    {
        cout << "Opción inválida. Intente de nuevo: ";
        cin >> opcion;
    }

    return opcion;
}

bool preguntarActivacion(string texto)
{
    int opcion;

    cout << endl << texto <<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "1) Sí"<<endl;
    cout << "2) No"<<endl;
    cout << "Opción: ";
    cin >> opcion;

    while (opcion < 1 || opcion > 2)
    {
        cout << "Opción inválida. Intente de nuevo: ";
        cin >> opcion;
    }

    return (opcion == 1);
}

TipoRobo seleccionarModoRobo()
{
    int opcion;

    cout << endl << "Seleccione el modo de robo:"<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "1) Robar solo 1 carta y pasar turno"<<endl;
    cout << "2) Robar hasta poder jugar"<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "Opción: ";
    cin >> opcion;

    while (opcion < 1 || opcion > 2)
    {
        cout << "Opción inválida. Intente de nuevo: ";
        cin >> opcion;
    }

    if (opcion == 1)
        return ROBO_UNA_Y_PASA;
    else
        return ROBO_HASTA_PODER_JUGAR;
}

int pedirCantidadJugadores()
{
    int n;

    cout << "¿Cuántos jugadores participarán?"<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "(mínimo 2, máximo 12)"<<endl;
    cout << "Cantidad: ";
    cin >> n;

    while (n < 2 || n > 12)
    {
        cout << "Cantidad inválida. Ingrese entre 2 y 12: ";
        cin >> n;
    }

    return n;
}

int main()
{
    srand(time(nullptr));

    mostrarTitulo();

    int modo = seleccionarModoJuego();

    if (modo == 2)
    {
        cout << endl <<"UNO Flip aún no está implementado."<<endl;
        cout << "Se iniciará en modo UNO Básico." <<endl;
    }


    cout << endl <<"========================================="<<endl;
    cout << "        CONFIGURACIÓN DE PARTIDA "<<endl;
    cout << "========================================="<<endl;

    ConfiguracionPartida config;

    config.permitirAcumulacion =
        preguntarActivacion("¿Desea activar acumulación (+2 sobre +2 y +4 sobre +4)?");

    config.permitirRetoMasCuatro =
        preguntarActivacion("¿Desea activar el reto del +4?");

    config.tipoRobo =
        seleccionarModoRobo();

    config.permitirGritoUno =
        preguntarActivacion("¿Desea activar la regla de gritar 'UNO'?");

    config.permitirGanarConNegra =
        preguntarActivacion("¿Permitir ganar con carta negra (comodín)?");

    config.activarUnoFlip = false;

    Juego juego(config);

    cout << endl <<"========================================="<<endl;
    cout << "          REGISTRO DE JUGADORES "<<endl;
    cout << "========================================="<<endl;

    int cantidad = pedirCantidadJugadores();

    for (int i = 1; i <= cantidad; i++)
    {
        string nombre;

        cout << "Ingrese nombre del Jugador " << i << ": ";
        cin >> nombre;

        Jugador* nuevo = new Jugador(nombre);
        juego.agregarJugador(nuevo);
    }

    cout << endl <<"========================================="<<endl;
    cout << "            INICIANDO PARTIDA..."<<endl;
    cout << "========================================="<<endl;

    juego.iniciarJuego();
    juego.jugarPartida();

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}