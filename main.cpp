#include "Juego.h"
#include <iostream>

void menu()
{
    std::cout << "Bienvenido al juego UNO" << std::endl;
    std::cout <<"Seleccione el modo de juego" << std::endl;
    std::cout << "1. Uno Basico" << std::endl;
    std::cout << "2. Uno Flip" << std::endl;
}

void reglas()
{
    std::cout <<"Elija las opciones de juego"<< std::endl;
    std::cout <<"1. Clasico: No permitir sumar cartas +2" << std::endl;
    std::cout <<"2. Divertido: Permitir sumar cartas +2 y +4" << std::endl;

}
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    Juego juego;
    int modoJuego;
    int reglasJuego;
    menu();
    std::cin >> modoJuego;
    reglas();
    std::cin >> reglasJuego;
    juego.iniciarJuego();


    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}