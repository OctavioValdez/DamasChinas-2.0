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
    Ficha * Negras = Crear_fichas(1);
    Ficha * Blancas = Crear_fichas(2);
    int turno = 0;

    Ficha *selected = NULL;




    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BAGE);
        TableroDisplay(screenWidth,screenHeight);
        DibujarFichas(Negras, BLACK);
        DibujarFichas(Blancas, WHITE);
        if(turno == 0)
        {
            if(selected)
            {
                CirculosR(selected, Blancas, Negras);
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Negras, Blancas) == 1)
                    {
                        turno = 1;
                    }
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
                CirculosR(selected, Negras, Blancas);
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    // aqui posiblemente queremos revisar si el siguiente click del usuario es
                    // en un movimiento legal? si lo es, realizarlo, si no lo es, "limpiar" la seleccion con selected=null
                    if(MovimientoValido(GetMouseX(),GetMouseY(),selected, Blancas, Negras) == 1)
                    {
                        turno = 0;
                    }

                    selected = NULL;
                }

            }

            if( selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                selected = DetectF(GetMouseX(), GetMouseY(), Blancas);
            }

        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}