#include "raylib.h"
#include "settings.h"
#include <stdio.h>


int main(void)
{
//   Caracteristicas de la ventana de juego
    const int screenWidth = 800;
    const int screenHeight = 800;
    int inicio = 0;
    int nuevo = 0;
    int cargar = 0;
    int cargado =0;
    Color BAGE;
    BAGE.r = 207;
    BAGE.g = 185;
    BAGE.b = 151;
//  Creacion de fichas y tablero e inicializacion de variables importantes
    Ficha * Negras = Crear_fichas(1);
    Ficha * Blancas = Crear_fichas(2);
    Tablero* tab = Crear_tab();
    Llenar_tab(tab);
    Llenar_disponibles(tab, Negras);
    Llenar_disponibles(tab, Blancas);
    int winner = getWinner(Blancas, Negras, tab);
    int turno = 0;
    Ficha *selected = NULL;

//  Caracteristicas de ventana y especificacion de FPS
    InitWindow(screenWidth, screenHeight, "Damas Chinas");
    SetTargetFPS(20);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
//      Se muestra el menu mientras no se haya elegido una opcion
        if(inicio == 0)
        {
            ClearBackground(BAGE);
            TableroDisplay(screenWidth,screenHeight);
            menu();
//          Si presiona la letra N se inicia un nuevo juego
            if(IsKeyPressed(KEY_N))
            {
                inicio = 1;
                nuevo = 1;
            }
//           Si presiona la letra R se carga un nuevo juego
            if(IsKeyPressed(KEY_R))
            {
                inicio = 1;
                cargar = 1;
            }
        }
//      Se inicia un nuevo juego
        if(nuevo == 1)
        {
//            Al presionar la letra S se guarda el juego
            if(IsKeyPressed(KEY_S))
            {
                DrawText("EL JUEGO SE GUARDO",200,400, 36, GREEN);
                saveGame(Blancas, Negras, turno, tab);
            }
//           Se dibuja el fondo, tablero y fichas
            ClearBackground(BAGE);
            TableroDisplay(screenWidth,screenHeight);
            DibujarFichas(Negras, BLACK, tab);
            DibujarFichas(Blancas, WHITE, tab);
//           Ganaron las blancas
            if(winner == 2)
            {
                DrawText("GANARON LAS BLANCAS", 200, 400, 36 , WHITE);
            }
//           Ganaron las negras
            if(winner == 1)
            {
                DrawText("GANARON LAS NEGRAS", 200, 400, 36 , BLACK);
            }
//          Si el turno es 0 las fichas negras se mueven
            if(turno == 0)
            {
//              Se eligio una ficha valida
                if(selected)
                {
//                  Se dibujan circulos rojos para las opciones de movimiento
                    CirculosR(selected,tab);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
//                      Si el movimiento es invalido no cambia de turno
                        if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Blancas, tab) != 1)
                        {
                            winner = getWinner(Blancas, Negras, tab);
//                           Si las negras ganan ya se cambia el turno
                            if(winner == 1)
                            {
                                turno = 1;
                            }
                            else
                            {
                                turno = 0;
                            }
                        }
                        else  //El movimiento ya fue valido y se cambia de turno
                            turno = 1;
                        selected = NULL;
                    }
                }
//                No se ha elegido a una ficha valida
                if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    selected = DetectF(GetMouseX(), GetMouseY(), Negras);
                }
            }
//           Si el turno es igual a 1 entonces se mueven las blancas y pasa lo mismo que con las negras
            if(turno == 1)
            {
                if(selected)
                {
                    CirculosR(selected, tab);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Negras, tab) != 1)
                        {
                            winner = getWinner(Blancas, Negras, tab);
                            if(winner == 2)
                            {
                                DrawText("GANARON LAS BLANCAS", 200, 400, 36 , WHITE);
                            }
                            else
                            {
                                turno = 1;
                            }
                        }
                        else
                            turno = 0;
                        selected = NULL;
                    }

                }

                if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    selected = DetectF(GetMouseX(), GetMouseY(), Blancas);
                }

            }
        }
//       Se desea cargar una partida guardada
        if(cargar == 1)
        {
//          Se carga el juego solo 1 vez
            if(cargado == 0)
            {
                loadGame(Blancas, Negras, &turno, tab);
                cargado = 1;
            }
//           Se repite lo mismo como en un juego nuevo
            ClearBackground(BAGE);
            TableroDisplay(screenWidth,screenHeight);
            DibujarFichas(Negras, BLACK, tab);
            DibujarFichas(Blancas, WHITE, tab);
            if(winner == 2)
            {
                DrawText("GANARON LAS BLANCAS", 200, 400, 36 , WHITE);
            }
            if(winner == 1)
            {
                DrawText("GANARON LAS NEGRAS", 200, 400, 36 , BLACK);
            }
            if(IsKeyPressed(KEY_S))
            {
                DrawText("EL JUEGO SE GUARDO",200,400, 36, GREEN);
                saveGame(Blancas, Negras, turno, tab);
            }
            if(turno == 0)
            {
                if(selected)
                {
                    CirculosR(selected,tab);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Blancas, tab) != 1)
                        {
                            winner = getWinner(Blancas, Negras, tab);
                            if(winner == 1)
                            {
                                DrawText("GANARON LAS NEGRAS", 200, 400, 36 , BLACK);
                            }
                            else
                            {
                                turno = 0;
                            }

                        }
                        else
                            turno = 1;
                        selected = NULL;
                    }
                }
                if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    selected = DetectF(GetMouseX(), GetMouseY(), Negras);
                }
            }
            if(turno == 1)
            {
                if(selected)
                {
                    CirculosR(selected, tab);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {

                        if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Negras, tab) != 1)
                        {
                            winner = getWinner(Blancas, Negras, tab);
                            if(winner == 2)
                            {
                                DrawText("GANARON LAS BLANCAS", 200, 400, 36 , WHITE);
                            }
                            else
                            {
                                turno = 1;
                            }

                        }
                        else
                            turno = 0;
                        selected = NULL;
                    }

                }

                if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    selected = DetectF(GetMouseX(), GetMouseY(), Blancas);
                }

            }

        }


        EndDrawing();
    }
    CloseWindow();
    return 0;
}