/*#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "la ventana de christian");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}*/

#include "raylib.h"
#include "settings.h"
#include <stdio.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    Color BAGE;
    BAGE.r = 207;
    BAGE.g = 185;
    BAGE.b = 151;

    InitWindow(screenWidth, screenHeight, "Damas Chinas");

    SetTargetFPS(20);
    int ** Tablero = CrearTablero();
    Ficha * Negras = Crear_fichas(1);
    Ficha * Blancas = Crear_fichas(2);
    int turno = 1;
    int* ptrTurno = &turno;

    int wasMousePressed = 0;
    Ficha *selected = NULL;


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BAGE);
        TableroDisplay(screenWidth,screenHeight);
        DibujarFichas(Negras, BLACK);
        DibujarFichas(Blancas, WHITE);

        /*if(turno == 0)
        {
            if(selected)
            {
                // aqui ya tenemos una ficha seleccionada, que queremos hacer con ella
                CirculosR(selected);
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    // aqui posiblemente queremos revisar si el siguiente click del usuario es
                    // en un movimiento legal? si lo es, realizarlo, si no lo es, "limpiar" la seleccion con selected=null
                    PosDiagonalNegras(GetMouseX(), GetMouseY(), selected);
                    selected = NULL;
                }
                    //else
                    //selected = NULL;
                    //cambioDeTurno(&turno);
            }

            if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                selected = DetectF(GetMouseX(), GetMouseY(), Negras);
                if(selected == NULL)
                    DrawText("eres un burro", 200,400,36,RED);
            }
        }*/

        if(turno == 1)
        {
            if(selected)
            {
                // aqui ya tenemos una ficha seleccionada, que queremos hacer con ella
                CirculosR(selected);
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    // aqui posiblemente queremos revisar si el siguiente click del usuario es
                    // en un movimiento legal? si lo es, realizarlo, si no lo es, "limpiar" la seleccion con selected=null
                    PosDiagonalBlancas(GetMouseX(), GetMouseY(), selected);
                    selected = NULL;

                    //else
                        //selected = NULL;
                    //cambioDeTurno(&turno);
                }

            }

            if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                selected = DetectF(GetMouseX(), GetMouseY(), Blancas);
                if(selected == NULL)
                    DrawText("eres un burro", 200,400,36,RED);
            }

        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}