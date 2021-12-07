#include "raylib.h"
#include "settings.h"
#include <stdio.h>


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    int inicio = 0;
    int nuevo = 0;
    int cargar = 0;
    Color BAGE;
    BAGE.r = 207;
    BAGE.g = 185;
    BAGE.b = 151;
    Ficha * Negras = Crear_fichas(1);
    Ficha * Blancas = Crear_fichas(2);
    Tablero* tab = Crear_tab();
    Llenar_tab(tab);
    Llenar_disponibles(tab, Negras);
    Llenar_disponibles(tab, Blancas);
    int winner = getWinner(Blancas, Negras, tab);
    int turno = 0;

    InitWindow(screenWidth, screenHeight, "Damas Chinas");
    SetTargetFPS(20);

    Ficha *selected = NULL;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        if(inicio == 0)
        {
            ClearBackground(BAGE);
            TableroDisplay(screenWidth,screenHeight);
            menu();
            if(IsKeyPressed(KEY_N))
            {
                inicio = 1;
                nuevo = 1;
            }
            if(IsKeyPressed(KEY_R))
            {
                inicio = 1;
                cargar = 1;
            }
        }

        if(nuevo == 1)
        {
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
                                turno = 0;
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
            if(turno == 1 && winner == 0)
            {
                if(selected)
                {
                    // aqui ya tenemos una ficha seleccionada, que queremos hacer con ella
                    CirculosR(selected, tab);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        // aqui posiblemente queremos revisar si el siguiente click del usuario es
                        // en un movimiento legal? si lo es, realizarlo, si no lo es, "limpiar" la seleccion con selected=null
                        if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Negras, tab) != 1)
                        {
                            winner = getWinner(Blancas, Negras, tab);
                            if(winner == 2)
                            {
                                DrawText("GANARON LAS BLANCAS", 200, 400, 36 , WHITE);
                            }
                            else
                                turno = 1;
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
        if(cargar == 1)
        {

            loadGame(Blancas, Negras, &turno, tab);
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
                                turno = 0;
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
                    // aqui ya tenemos una ficha seleccionada, que queremos hacer con ella
                    CirculosR(selected, tab);
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        // aqui posiblemente queremos revisar si el siguiente click del usuario es
                        // en un movimiento legal? si lo es, realizarlo, si no lo es, "limpiar" la seleccion con selected=null
                        if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Negras, tab) != 1)
                        {
                            winner = getWinner(Blancas, Negras, tab);
                            if(winner == 2)
                            {
                                DrawText("GANARON LAS BLANCAS", 200, 400, 36 , WHITE);
                            }
                            else
                                turno = 1;
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