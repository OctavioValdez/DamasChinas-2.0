#include "settings.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

//Estructuras implmentadas

struct ficha
{
    int x;
    int y;
    int id;
    int vida;
    int dir;
    char col;
    struct ficha* sig;
};

struct Cuadro
{
    int Disponible;
    int x;
    int y;
    int Reina;

}typedef cuadro;

struct tablero
{
    cuadro** Tablero;
    int size;
}typedef Tablero;


//Funciones de tablero y fichas
int get_pos_arr(Ficha* player, Tablero* tab)
{
    int pos;
    for (int i = 0; i < 64; i++)
    {
        if(tab -> Tablero[i] -> x == player -> x && tab -> Tablero[i] -> y == player -> y)
        {
            pos = i;
            return pos;
        }
    }
}

void menu()
{
    DrawText("BIENVENIDO", 250, 300, 45, BLACK);
    DrawText("Nuevo juego picale a N", 50, 450, 28, BLACK);
    DrawText("Reanudar juego a R", 500, 450, 28, BLACK);
}

void isReina(Ficha* player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player == NULL)
        return;
    if(player -> dir == 0)
    {
        if(player -> y == 750)
        {
            player -> dir = 1;
            tab -> Tablero[pos_arr] -> Reina = 1;
        }

    }
    if(player -> dir == 1)
    {
        if(player -> y == 50)
        {
            player -> dir = 0;
            tab -> Tablero[pos_arr] -> Reina = 1;
        }

    }

}

void TableroDisplay(int width,int height)
{
    int y;
    int x;

    for (y = 0; y <= 700; y = y + 200)
    {
        for(x = 100; x <= 700; x = x + 200)
        {
            DrawRectangle(x,y,100,100,BROWN);
        }
    }

    for(y = 100; y <= 700;y = y+ 200)
    {
        for(x = 0; x <= 700; x = x + 200)
        {
            DrawRectangle(x,y,100,100,BROWN);
        }
    }

    for (int i = 0; i < width; i = i + width /8)
        DrawLine(i + width/8, 0, i + width/8, height, BLACK);
    for (int i = 0; i < height; i = i + height/8)
        DrawLine(0, i + height/8, width, i + height/8, BLACK);

}

void addF(Ficha * ficha,int x, int y, int id, int dir, char col)
{
    Ficha* Current = ficha;

    while(Current -> sig != NULL)
        Current = Current -> sig;

    Current -> sig = malloc(sizeof(Ficha));
    Current -> sig -> x = x;
    Current -> sig -> y = y;
    Current -> sig -> vida = 1;
    Current -> sig -> id = id;
    Current -> sig -> dir = dir;
    Current -> sig -> col = col;
    Current -> sig -> sig = NULL;

}

Tablero *Crear_tab()
{
    Tablero* tab = malloc(sizeof(Tablero));

    tab -> size = 64;
    tab -> Tablero = calloc(64, sizeof (cuadro));

    return tab;
}

cuadro* new_cuadro(int x, int y)
{
    cuadro* n = malloc(sizeof (cuadro));
    n -> x = x;
    n -> y = y;
    n -> Disponible = 0;
    n -> Reina = 0;
    return n;
}

void Llenar_tab(Tablero* tab)
{
    int y = 50;
    int x = 50;
    int i = 0;
    while (i < 64)
    {
        x = 50;
        for(int j = 0; j < 8; j++)
        {
            tab -> Tablero[i] = new_cuadro(x, y);
            i++;
            x+= 100;
        }
        y+= 100;
    }
}

void Llenar_disponibles(Tablero* tab, Ficha* fichas)
{
    Ficha* current = fichas;
    current = current -> sig;
    while(current != NULL)
    {
        for(int i = 0; i < 64; i++)
        {
            if(tab -> Tablero[i] -> x == current -> x && tab -> Tablero[i] -> y == current -> y)
            {
                if(current -> id < 12)
                {
                    tab -> Tablero[i] -> Disponible = 1;
                }

                if(current -> id >= 12)
                {
                    tab -> Tablero[i] -> Disponible = 2;
                }

            }
        }
        current = current -> sig;
    }
}

void display_tab(Tablero* tab)
{
    for(int i = 0; i < 64; i++)
    {
        printf("%d %d %d %d\n", tab -> Tablero[i] -> x, tab -> Tablero[i] -> y, tab -> Tablero[i] -> Disponible, tab -> Tablero[i] -> Reina);
    }
}

Ficha *Crear_fichas(int C) {
    if (C == 1) {
        Ficha *N1 = malloc(sizeof(Ficha));
        N1->sig = NULL;
        int pos_x = 150;
        int pos_y = 50;
        int cont_id = 0;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id, 0, 'N');
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 50;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id, 0, 'N');
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 150;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id, 0,'N');
            pos_x = pos_x + 200;
            cont_id++;
        }
        return N1;
    } else {
        Ficha *N1 = malloc(sizeof(Ficha));
        N1->sig = NULL;
        int pos_x = 50;
        int pos_y = 550;
        int cont_id = 12;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id, 1,'B');
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 150;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id, 1,'B');
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 50;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id, 1,'B');
            pos_x = pos_x + 200;
            cont_id++;
        }

        return N1;
    }

}

void DibujarFichas(Ficha * fichas, color C, Tablero* tab)
{
    Ficha* Current = fichas -> sig;
    while(Current != NULL)
    {
        if(Current -> vida == 0)
        {
            Current -> x = 100000;
            Current -> y = 100000;
            Current = Current -> sig;
            continue;
        }
        isReina(Current, tab);
        if(Current == NULL)
            return;
        DrawCircle(Current->x,Current->y, 45, C);
        Current = Current -> sig;
    }
}


void Display(Ficha * fichas)
{
    Ficha* Current = fichas;
    while (Current != NULL)
    {
        printf("%d, %d, %d, %d\n",Current -> x, Current -> y, Current -> id, Current -> dir);
        Current = Current -> sig;
    }

}

Ficha* DetectF(int x, int y,Ficha* ficha)
{
    Ficha* current = ficha -> sig;

    while(current != NULL)
    {
        if(current -> x -45 < x && current -> x + 45 > x)
        {
            if(current -> y - 45 < y && current -> y + 45 > y)
                break;
        }
        current = current -> sig;
    }

    return current;

}


// Movimiento

void MovBlancasSinComida(Ficha *player, int dir, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if (dir == 1)
    {
        player -> y -= 100;
        player -> x += 100;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 7] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr - 7] -> Disponible = 2;

    }
    if (dir == 0)
    {
        player -> y -= 100;
        player -> x -= 100;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 9] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr - 9] -> Disponible = 2;
    }

}

void MovBlancasConComida(Ficha *player, int dir, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if (dir == 1)
    {
        player -> y -= 200;
        player -> x += 200;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 14] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr - 14] -> Disponible = 2;
    }
    if (dir == 0)
    {
        player -> y -= 200;
        player -> x -= 200;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 18] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr - 18] -> Disponible = 2;
    }

}

void MovNegrasSinComida(Ficha *player, int dir, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if (dir == 1)
    {
        player -> y += 100;
        player -> x += 100;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr + 9] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr + 9] -> Disponible = 1;
    }
    if (dir == 0)
    {
        player -> y += 100;
        player -> x -= 100;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr + 7] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr + 7] -> Disponible = 1;
    }
}

void MovNegrasConComida(Ficha *player, int dir, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if (dir == 1)
    {
        player -> y += 200;
        player -> x += 200;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr + 18] -> Reina = 1;
        }

        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr + 18] -> Disponible = 1;
    }
    if (dir == 0)
    {
        player -> y += 200;
        player -> x -= 200;
        if(tab -> Tablero[pos_arr] -> Reina == 1)
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr + 14] -> Reina = 1;
        }
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr + 14] -> Disponible = 1;
    }
}

void eliminarf(Ficha* ficha, Tablero* tab)
{
    int arr_poss = get_pos_arr(ficha, tab);
    tab -> Tablero[arr_poss] -> Disponible = 0;
    ficha -> vida = 0;
}


int comerFNegraDerecha(Ficha* player, Ficha* oponente, Tablero* tab)
{
    Ficha* ficha = oponente -> sig;
    int x = player -> x - 100;
    int y = player -> y + 100;
    while(ficha != NULL)
    {
        if(ficha -> x == x && ficha -> y == y)
            break;
        ficha = ficha -> sig;
    }
    if(ficha != NULL)
    {
        int pos_arr = get_pos_arr(ficha, tab);
        eliminarf(ficha, tab);
        return 1;
    }
    else
        return 0;
}

int comerFNegraIzquierda(Ficha* player, Ficha* oponente, Tablero* tab)
{
    Ficha* ficha = oponente -> sig;
    int x = player -> x + 100;
    int y = player -> y + 100;
    while(ficha != NULL)
    {
        if(ficha -> x == x && ficha -> y == y)
            break;
        ficha = ficha -> sig;
    }
    if(ficha != NULL)
    {
        int pos_arr = get_pos_arr(ficha, tab);
        eliminarf(ficha, tab);
        return 1;
    }
    else
        return 0;
}

int comerFBlancaDerecha(Ficha* player, Ficha* oponente, Tablero* tab)
{
    Ficha* ficha = oponente -> sig;
    int x = player -> x - 100;
    int y = player -> y - 100;
    while(ficha != NULL)
    {
        if(ficha -> x == x && ficha -> y == y)
            break;
        ficha = ficha -> sig;
    }
    if(ficha != NULL)
    {
        int pos_arr = get_pos_arr(ficha, tab);
        eliminarf(ficha, tab);
        return 1;
    }
    else
        return 0;
}

int comerFBlancaIzquierda(Ficha* player, Ficha* oponente, Tablero* tab)
{

    Ficha* ficha = oponente -> sig;
    int x = player -> x + 100;
    int y = player -> y - 100;
    while(ficha != NULL)
    {
        if(ficha -> x == x && ficha -> y == y)
            break;
        ficha = ficha -> sig;
    }
    if(ficha != NULL)
    {
        int pos_arr = get_pos_arr(ficha, tab);
        eliminarf(ficha, tab);
        return 1;
    }
    else
        return 0;
}

int colision(Ficha *player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_izq = pos_arr + 7;
        int pos_der = pos_arr + 9;
        int band_der = 0;
        int band_izq = 0;

        if(player -> y == 750)
            return 0;

        if(player -> x == 50)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 1 || (tab ->Tablero[pos_der] -> Disponible == 2 &&
                                                                tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            }
            else
                return 0;
        }
        if(player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 1 || (tab ->Tablero[pos_izq] -> Disponible == 2 &&
                                                              tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1 || (tab ->Tablero[pos_izq] -> Disponible == 2 &&
                                                          tab -> Tablero[pos_izq] -> Reina == 1))
        {
            band_izq = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 1 || (tab ->Tablero[pos_der] -> Disponible == 2 &&
                                                          tab -> Tablero[pos_der] -> Reina == 1))
        {
            band_der = 1;
        }

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
    if(player -> dir == 0)
    {
        int pos_izq = pos_arr + 7;
        int pos_der = pos_arr + 9;
        int band_der = 0;
        int band_izq = 0;
        if(player -> y == 750)
            return 0;
        if(player -> x == 50)
        {
            if((tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 0) ||
            (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            }
            else
                return 0;
        }
        if(player -> x == 750)
        {
            if((tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 0)||
            (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))

            {
                return 2;
            } else
                return 0;
        }

        if((tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 0 )||
        (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))

        {
            band_izq = 1;
        }
        if((tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 0) ||
        (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
        {
            band_der = 1;
        }

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
    if(player -> dir == 1 && player -> col == 'N')
    {
        int pos_izq = pos_arr - 9;
        int pos_der = pos_arr - 7;
        int band_der = 0;
        int band_izq = 0;
        if(player -> y == 50)
            return 0;
        if(player -> x == 50)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 2 || (tab ->Tablero[pos_der] -> Disponible == 1 &&
                                                              tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 2 || (tab ->Tablero[pos_izq] -> Disponible == 1 &&
                                                              tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 2 || (tab ->Tablero[pos_izq] -> Disponible == 1 &&
                                                          tab -> Tablero[pos_izq] -> Reina == 1))
        {
            band_izq = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 2 || (tab ->Tablero[pos_der] -> Disponible == 1 &&
                                                          tab -> Tablero[pos_der] -> Reina == 1))
        {
            band_der = 1;
        }

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
    if(player -> dir == 1)
    {
        int pos_izq = pos_arr - 9;
        int pos_der = pos_arr - 7;
        int band_der = 0;
        int band_izq = 0;

        if(player -> y == 50)
            return 0;

        if(player -> x == 50)
        {
            if((tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 0)||
            (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))


            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 750)
        {
            if((tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 0) ||
            (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }
        if((tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 0) ||
        (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
        {
            band_izq = 1;
        }
        if((tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 0)||
        (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))


        {
            band_der = 1;
        }

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
}

int comidaDisponible(Ficha* player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_der = pos_arr + 18;
        int pos_izq = pos_arr + 14;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 650 || player -> y == 750)
            return 0;

        if(player -> x == 50 || player -> x == 150)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 1 || (tab ->Tablero[pos_der] -> Disponible == 2 &&
                                                              tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 1 || (tab ->Tablero[pos_izq] -> Disponible == 2 &&
                                                              tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }


        if(tab -> Tablero[pos_der] -> Disponible == 1 || (tab ->Tablero[pos_der] -> Disponible == 2 &&
                                                          tab -> Tablero[pos_der] -> Reina == 1))
        {
            ban_der = 1;
        }

        if(tab -> Tablero[pos_izq] -> Disponible == 1 || (tab ->Tablero[pos_izq] -> Disponible == 2 &&
                                                          tab -> Tablero[pos_izq] -> Reina == 1))
        {
            ban_izq = 1;
        }

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
    if(player -> dir == 0)
    {
        int pos_der = pos_arr + 18;
        int pos_izq = pos_arr + 14;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 650 || player -> y == 750)
            return 0;

        if(player -> x == 50 || player -> x == 150)
        {
            if((tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 0)||
            (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))

            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if((tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 0) ||
            (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))

            {
                return 2;
            } else
                return 0;
        }


        if((tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 0) ||
        (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))

        {
            ban_der = 1;
        }

        if((tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 0)||
        (tab -> Tablero[pos_izq] -> Disponible == 1 &&  tab -> Tablero[pos_izq] -> Reina == 1))

        {
            ban_izq = 1;
        }

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
    if(player -> dir == 1 && player -> col == 'N')
    {
        int pos_der = pos_arr - 14;
        int pos_izq = pos_arr - 18;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 150 || player -> y == 50)
            return 0;
        if(player -> x == 50 || player -> x == 150)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 2 || (tab ->Tablero[pos_der] -> Disponible == 1 &&
                                                          tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 2 || (tab ->Tablero[pos_izq] -> Disponible == 1 &&
                                                              tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }


        if(tab -> Tablero[pos_der] -> Disponible == 2 || (tab ->Tablero[pos_der] -> Disponible == 1 &&
                                                          tab -> Tablero[pos_der] -> Reina == 1))
        {
            ban_der = 1;
        }

        if(tab -> Tablero[pos_izq] -> Disponible == 2 || (tab ->Tablero[pos_izq] -> Disponible == 1 &&
                                                          tab -> Tablero[pos_izq] -> Reina == 1))
        {
            ban_izq = 1;
        }

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
    if(player -> dir == 1)
    {
        int pos_der = pos_arr - 14;
        int pos_izq = pos_arr - 18;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 150 || player -> y == 50)
            return 0;
        if(player -> x == 50 || player -> x == 150)
        {
            if((tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 0)||
            (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if((tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 0)||
            (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }

        if((tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 0) ||
        (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
        {
            ban_der = 1;
        }

        if((tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 0) ||
        (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
        {
            ban_izq = 1;
        }

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
}

int isAmiga(Ficha* player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_izq = pos_arr + 7;
        int pos_der = pos_arr + 9;
        int band_der = 0;
        int band_izq = 0;
        if(player -> x == 50)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 2)
            {
                return 1;
            }
            else
                return 0;
        }
        if(player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 2)
            {
                return 2;
            } else
                return 0;
        }

        if(tab -> Tablero[pos_izq] -> Disponible == 2)
        {
            band_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
            band_izq = 0;
        if(tab -> Tablero[pos_der] -> Disponible == 2)
        {
            band_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
            band_der = 0;

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
    if(player -> dir == 0)
    {
        int pos_izq = pos_arr + 7;
        int pos_der = pos_arr + 9;
        int band_der = 0;
        int band_izq = 0;
        if(player -> y == 750)
            return 0;
        if(player -> x == 50)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 1 ||
                    (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            }
            else
                return 0;
        }
        if(player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 1 ||
                    (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1 ||
                (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
        {
            band_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
            band_izq = 0;
        if(tab -> Tablero[pos_der] -> Disponible == 1 ||
                (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
        {
            band_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
            band_der = 0;

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
    if(player -> dir == 1 && player -> col == 'N')
    {
        int pos_izq = pos_arr - 9;
        int pos_der = pos_arr - 7;
        int band_der = 0;
        int band_izq = 0;
        if(player -> y == 50)
            return 0;
        if(player -> x == 50)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 1)
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 1)
            {
                return 2;
            } else
                return 0;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1)
        {
            band_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
            band_izq = 0;
        if(tab -> Tablero[pos_der] -> Disponible == 1)
        {
            band_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
            band_der = 0;

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
    if(player -> dir == 1)
    {
        int pos_izq = pos_arr - 9;
        int pos_der = pos_arr - 7;
        int band_der = 0;
        int band_izq = 0;
        if(player -> x == 50)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;

            if(tab -> Tablero[pos_der] -> Disponible == 2 ||
                    (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 2 ||
                    (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }

        if(tab -> Tablero[pos_izq] -> Disponible == 2 ||
                (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))
        {
            band_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
            band_izq = 0;
        if(tab -> Tablero[pos_der] -> Disponible == 2 ||
                (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
        {
            band_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
            band_der = 0;

        if(band_der == 1 && band_izq == 1)
            return 3;
        if(band_izq == 1)
            return 2;
        if(band_der == 1)
            return 1;
        return 0;
    }
}

int isAmigalejana(Ficha* player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_der = pos_arr + 18;
        int pos_izq = pos_arr + 14;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 650 || player -> y == 750)
            return 0;
        if(player -> x == 50 || player -> x == 150)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 2)
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 2)
            {
                return 2;
            } else
                return 0;
        }


        if(tab -> Tablero[pos_der] -> Disponible == 2)
        {
            ban_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
            ban_der = 0;

        if(tab -> Tablero[pos_izq] -> Disponible == 2)
        {
            ban_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
            ban_izq = 0;

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
    if(player -> dir == 0)
    {
        int pos_der = pos_arr + 18;
        int pos_izq = pos_arr + 14;
        int ban_izq = 0;
        int ban_der = 0;
        if(player -> y == 750 || player -> y == 650)
            return 0;
        if(player -> x == 50 || player -> x == 150)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 1 ||
                    (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 1 ||
                    (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }

        if(tab -> Tablero[pos_der] -> Disponible == 1 ||
                (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
        {
            ban_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
            ban_der = 0;

        if(tab -> Tablero[pos_izq] -> Disponible == 1 ||
                (tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1))
        {
            ban_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
            ban_izq = 0;

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
    if(player -> dir == 1 && player -> col == 'N')
    {
        int pos_der = pos_arr - 14;
        int pos_izq = pos_arr - 18;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 150 || player -> y == 50)
            return 0;
        if(player -> x == 50 || player -> x == 150)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 1)
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 1)
            {
                return 2;
            } else
                return 0;
        }


        if(tab -> Tablero[pos_der] -> Disponible == 1)
        {
            ban_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
            ban_der = 0;

        if(tab -> Tablero[pos_izq] -> Disponible == 1)
        {
            ban_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
            ban_izq = 0;

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
    if(player -> dir == 1)
    {
        int pos_der = pos_arr - 14;
        int pos_izq = pos_arr - 18;
        int ban_izq = 0;
        int ban_der = 0;

        if(player -> y == 150 || player -> y == 50)
            return 0;

        if(player -> x == 50 || player -> x == 150)
        {
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_der] -> Disponible == 2 ||
                    (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        if(player -> x == 650 || player -> x == 750)
        {
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            if(tab -> Tablero[pos_izq] -> Disponible == 2 ||
                    (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))
            {
                return 2;
            } else
                return 0;
        }

        if(tab -> Tablero[pos_der] -> Disponible == 2 ||
                (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
        {
            ban_der = 1;
        }
        if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
            ban_der = 0;

        if(tab -> Tablero[pos_izq] -> Disponible == 2 ||
                (tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1))
        {
            ban_izq = 1;
        }
        if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
            ban_izq = 0;

        if(ban_der == 1 && ban_izq == 1)
            return 3;
        if(ban_der == 1)
            return 1;
        if(ban_izq == 1)
            return 2;
        return 0;
    }
}

int SinEnemigos(int x, int y, Ficha* player, Tablero* tab)
{
    int AmigaC = isAmiga(player, tab);
    if(player -> dir == 0)
    {
        if(AmigaC == 0)
        {
            if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 1, tab);
                return 1;
            }
            if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 0, tab);
                return 1;
            }
        }
        if(AmigaC == 1)
        {
            if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 0, tab);
                return 1;
            }
        }
        if(AmigaC == 2)
        {
            if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 1, tab);
                return 1;
            }
        }
        if(AmigaC == 3)
            return 0;
    }
    else
    {
        if(AmigaC == 0)
        {
            if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y - 145 && y < player -> y -55)
            {
                MovBlancasSinComida(player, 1, tab);
                return 1;
            }

            if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y -145 && y < player -> y - 55)
            {
                MovBlancasSinComida(player, 0, tab);
                return 1;
            }
        }

        if(AmigaC == 1)
        {
            if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y -145 && y < player -> y - 55)
            {
                MovBlancasSinComida(player, 0, tab);
                return 1;
            }
        }

        if(AmigaC == 2)
        {
            if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y - 145 && y < player -> y -55)
            {
                MovBlancasSinComida(player, 1, tab);
                return 1;
            }
        }

        if(AmigaC == 3)
            return 0;
    }
}

int EnemigoDerecha(int x, int y, Ficha* player, Tablero* tab, Ficha* oponentes)
{

    int Comida = comidaDisponible(player, tab);
    int AmigaL = isAmigalejana(player, tab);
    int AmigaC = isAmiga(player, tab);
    if(player -> dir == 0)
    {
        if((Comida == 1 || Comida == 3) || (AmigaL == 1 || AmigaL == 3))
        {
            if(AmigaC == 2)
                return 0;
            if(AmigaC == 0)
                if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    MovNegrasSinComida(player, 0, tab);
                    return 1;
                }
        }

        if((Comida == 0 || Comida == 2) && (AmigaL == 0 || AmigaL == 2))
        {
            if(AmigaC == 2)
            {

                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1,tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }
            if(AmigaC == 0)
            {
                if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    if(player -> x == 650 || (player -> y == 650))
                    {
                        MovNegrasSinComida(player, 0, tab);
                        return 1;
                    } else
                    {
                        eliminarf(player, tab);
                        return 1;
                    }
                }
                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1,tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }


        }
    }
    if(player -> dir == 1)
    {
        if((Comida == 1 || Comida == 3) || (AmigaL == 1 || AmigaL == 3))
        {
            if(AmigaC == 2)
                return 0;
            if(AmigaC == 0)
            {
                if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y - 145 && y < player -> y - 55)
                {
                    MovBlancasSinComida(player,0, tab);
                    return 1;
                }
            }
        }

        if((Comida == 0 || Comida == 2) && (AmigaL == 0 || AmigaL == 2))
        {
            if(AmigaC == 2)
            {
                if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y -155)
                {
                    MovBlancasConComida(player, 1,tab);
                    comerFNegraDerecha(player, oponentes, tab);
                    return 1;
                }
            }

            if(AmigaC == 0)
            {
                if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y -155)
                {
                    MovBlancasConComida(player, 1,tab);
                    comerFNegraDerecha(player, oponentes, tab);
                    return 1;
                }
                if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y - 145 && y < player -> y - 55)
                {
                    if(player -> x == 650 || player -> y == 150)
                    {
                        MovBlancasSinComida(player,0, tab);
                        return 1;
                    }else
                    {
                        eliminarf(player, tab);
                        return 1;
                    }
                }
            }

        }
    }
}

int EnemigoIzquierda (int x, int y, Ficha* player, Tablero* tab, Ficha* oponentes)
{
    int Comida = comidaDisponible(player, tab);
    int AmigaL = isAmigalejana(player, tab);
    int AmigaC = isAmiga(player, tab);

    if(player -> dir == 0)
    {
        if((Comida == 2 || Comida == 3) || (AmigaL == 2 || AmigaL == 3))
        {
            if(AmigaC == 1)
                return 0;
            if(AmigaC == 0)
            {
                if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    MovNegrasSinComida(player, 1, tab);
                    return 1;
                }
            }
        }

        if((Comida == 1 || Comida == 0) && (AmigaL == 1 || AmigaL == 0))
        {
            if(AmigaC == 1)
            {

                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player,0,tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 2;
                }
            }
            if(AmigaC == 0)
            {
                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player,0,tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 1;
                }
                if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    if(player -> x == 150 || player -> y == 650)
                    {
                        MovNegrasSinComida(player, 1, tab);
                        return 1;
                    } else
                    {
                        eliminarf(player, tab);
                        return 1;
                    }
                }

            }
        }
    }
    if(player -> dir == 1)
    {
        if((Comida == 2 || Comida == 3) || (AmigaL == 2 || AmigaL == 3))
        {
            if(AmigaC == 1)
                return 0;
            if(AmigaC == 0)
            {
                if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y -145 && y < player -> y - 55)
                {
                    MovBlancasSinComida(player, 1, tab);
                    return 1;
                }
            }
        }

        if((Comida == 1 || Comida == 0) && (AmigaL == 1 || AmigaL == 0))
        {
            if(AmigaC == 1)
            {

                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }
            }

            if(AmigaC == 0)
            {

                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }

                if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y -145 && y < player -> y - 55)
                {
                    if(player -> x == 150 || player -> y == 150)
                    {
                        MovBlancasSinComida(player, 1, tab);
                        return 1;
                    }else
                    {
                        eliminarf(player, tab);
                        return 1;
                    }
                }
            }
        }
    }
}

int EnemigoSupremo(int x, int y, Ficha* player, Tablero* tab, Ficha* oponentes)
{
    int Comida = comidaDisponible(player, tab);
    int AmigaL = isAmigalejana(player, tab);

    if(player -> dir == 0)
    {
        if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
            return 0;

        if(Comida == 0 && AmigaL == 0)
        {

            if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
            {
                MovNegrasConComida(player, 1, tab);
                comerFBlancaDerecha(player, oponentes, tab);
                return 1;
            }

            if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
            {
                MovNegrasConComida(player, 0, tab);
                comerFBlancaIzquierda(player, oponentes, tab);
                return 1;
            }
        }

        if(Comida == 1)
        {
            if(AmigaL == 0)
            {

                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 0, tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        if(AmigaL == 1)
        {
            if(Comida == 0)
            {

                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 0, tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        if(Comida == 2)
        {
            if(AmigaL == 0)
            {

                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1, tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }
        if(AmigaL == 2)
        {
            if(Comida == 0)
            {

                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1, tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }

    }
    if(player -> dir ==1)
    {
        if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
            return 0;

        if(Comida == 0 || AmigaL == 0)
        {

            if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y - 155)
            {
                MovBlancasConComida(player, 1, tab);
                comerFNegraDerecha(player, oponentes, tab);
                return 1;
            }

            if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
            {
                MovBlancasConComida(player, 0, tab);
                comerFNegraIzquierda(player, oponentes, tab);
                return 1;
            }
        }

        if(Comida == 1)
        {
            if(AmigaL == 0)
            {

                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        if(AmigaL == 1)
        {
            if(Comida == 0)
            {
                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        if(Comida == 2)
        {
            if(AmigaL == 0)
            {
                if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 1, tab);
                    comerFNegraDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }
        if(AmigaL == 2)
        {
            if(Comida == 0)
            {
                if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 1, tab);
                    comerFNegraDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }
    }
}

int sinMovimiento(Ficha* player, Tablero* tab, int fichas_c)
{
    int colis = colision(player, tab);
    int Comida = comidaDisponible(player, tab);
    int AmigaC = isAmiga(player, tab);
    int AmigaL = isAmigalejana(player,tab);
    if(fichas_c > 0)
    {
        if(AmigaC == 0 &&(colis == 2 && (Comida == 2 || AmigaL == 2)))
            return 1;
        if(AmigaC == 0 &&(colis == 1 && (Comida == 1 || AmigaL == 1)))
            return 1;
        if(AmigaC == 0 && colis == 0)
            return 1;
        if(AmigaC == 3)
            return 1;
        if(colis == 3 &&(AmigaL == 3 || Comida == 3))
            return 1;
        if(colis == 3 &&(AmigaL == 1 && Comida == 2))
            return 1;
        if(colis == 3 &&(AmigaL == 2 && Comida == 1))
            return 1;
        if(AmigaC == 1 && (colis == 2 && ((Comida == 2 || Comida == 3) || (AmigaL == 2 || AmigaL == 3))))
            return 1;
        if(AmigaC == 2 && (colis == 1 && ((Comida == 1 || Comida == 3) || (AmigaL == 1 || AmigaL == 3))))
            return 1;
    }

    return 0;
}

int MovimientoValido(int x, int y, Ficha *player, Ficha* oponentes, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    int Mov = 0;
    int fichas_eliminadas = 0;
    int Run = sinMovimiento(player,tab, fichas_eliminadas);
    if(player -> dir == 0)
    {
        if(colision(player, tab) == 0)
        {
            Mov = SinEnemigos(x, y, player, tab);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
        if(colision(player, tab) == 1)
        {
            Mov = EnemigoDerecha(x, y, player, tab, oponentes);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
        if(colision(player, tab) == 2)
        {
            Mov = EnemigoIzquierda(x, y, player, tab, oponentes);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
        if(colision(player, tab) == 3)
        {
            Mov = EnemigoSupremo(x, y, player, tab, oponentes);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
    }
    if(player -> dir == 1)
    {
        if(colision(player, tab) == 0)
        {
            Mov = SinEnemigos(x, y, player, tab);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
        if(colision(player, tab) == 1)
        {
            Mov = EnemigoDerecha(x, y, player, tab, oponentes);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
        if(colision(player, tab) == 2)
        {
            Mov = EnemigoIzquierda(x, y, player, tab, oponentes);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
        if(colision(player, tab) == 3)
        {
            Mov = EnemigoSupremo(x, y, player, tab, oponentes);
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
    }
}

// Circulos rojos

void CirculosR(Ficha *player, Tablero* tab)
{
    int Lados = colision(player, tab);
    int Comida = comidaDisponible(player, tab);
    int AmigaC = isAmiga(player, tab);
    int AmigaL = isAmigalejana(player, tab);
    if(player -> dir == 0)
    {
        if(Lados == 0)
        {
            if(AmigaC == 0)
            {
                DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
                DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
            }
            if(AmigaC == 1)
            {
                DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
            }
            if(AmigaC == 2)
            {
                DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
            }
            if(AmigaC == 3)
                return;
        }

        if(Lados == 1)
        {
            if((AmigaL == 0 || AmigaL == 2) && (Comida == 0 || Comida == 2))
            {
                if(AmigaC == 2)
                {
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                }
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                    DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
                }
            }
            if((AmigaL == 1 || AmigaL == 3) || (Comida == 1 || Comida == 3))
            {
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
                }
                if(AmigaC == 2)
                    return;
            }
        }

        if(Lados == 2)
        {
            if((AmigaL == 0 || AmigaL == 1) && (Comida == 0 || Comida == 1))
            {
                if(AmigaC == 1)
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                    DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
                }
            }
            if((AmigaL == 2 || AmigaL == 3) || (Comida == 2 || Comida == 3))
            {
                if(AmigaC == 0)
                    DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
                if(AmigaC == 1)
                    return;
            }
        }

        if(Lados == 3)
        {
            if(AmigaL == 0 && Comida == 0)
            {
                DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
            }
            if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
                return;

            if(Comida == 1)
            {
                if(AmigaL == 0)
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                else
                    return;
            }
            if(AmigaL == 1)
            {
                if(Comida == 0)
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                else
                    return;
            }
            if(Comida == 2)
            {
                if(AmigaL == 0)
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                else
                    return;
            }
            if(AmigaL == 2)
            {
                if(Comida == 0)
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                else
                    return;
            }
        }
    }
    if(player -> dir == 1)
    {
        if(Lados == 0)
        {
            if(AmigaC == 0)
            {
                DrawCircle(player -> x + 100, player -> y - 100 , 45, RED);
                DrawCircle(player -> x - 100, player -> y - 100 , 45, RED);
            }
            if(AmigaC == 1)
            {
                DrawCircle(player -> x - 100, player -> y - 100 , 45, RED);
            }
            if(AmigaC == 2)
            {
                DrawCircle(player -> x + 100, player -> y - 100 , 45, RED);
            }
            if(AmigaC == 3)
                return;
        }
        if(Lados == 1)
        {
            if((AmigaL == 0 || AmigaL == 2) && (Comida == 0 || Comida == 2))
            {
                if(AmigaC == 2)
                {
                    DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
                }
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
                    DrawCircle(player -> x - 100, player -> y - 100 , 45, RED);
                }
            }
            if((AmigaL == 1 || AmigaL == 3) || (Comida == 1 || Comida == 3))
            {
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x - 100, player -> y - 100 , 45, RED);
                }
                if(AmigaC == 2)
                    return;
            }
        }
        if(Lados == 2)
        {
            if((AmigaL == 0 || AmigaL == 1) && (Comida == 0 || Comida == 1))
            {
                if(AmigaC == 1)
                    DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                    DrawCircle(player -> x + 100, player -> y - 100 , 45, RED);
                }
            }
            if((AmigaL == 2 || AmigaL == 3) || (Comida == 2 || Comida == 3))
            {
                if(AmigaC == 0)
                    DrawCircle(player -> x + 100, player -> y - 100 , 45, RED);
                if(AmigaC == 1)
                    return;
            }
        }
        if(Lados == 3)
        {
            if(AmigaL == 0 && Comida == 0)
            {
                DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
            }
            if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
                return;

            if(Comida == 1)
            {
                if(AmigaL == 0)
                    DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                else
                    return;
            }
            if(AmigaL == 1)
            {
                if(Comida == 0)
                    DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                else
                    return;
            }
            if(Comida == 2)
            {
                if(AmigaL == 0)
                    DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
                else
                    return;
            }
            if(AmigaL == 2)
            {
                if(Comida == 0)
                    DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
                else
                    return;
            }
        }
    }

}

// Ganador

int movimientosDisponibles(Ficha* Blancas, Ficha* Negras, Tablero* tab)
{
    Ficha* CurrentN = Negras;
    CurrentN = CurrentN -> sig;
    Ficha* CurrentB = Blancas;
    CurrentB = CurrentB -> sig;
    int contN = 0;
    int contB = 0;
    int BloqueadaN = 0;
    int BloqueadaB = 0;

    while(CurrentN != NULL)
    {
        int Lados = colision(CurrentN, tab);
        int Comida = comidaDisponible(CurrentN, tab);
        int AmigaC = isAmiga(CurrentN, tab);
        int AmigaL = isAmigalejana(CurrentN, tab);
        if(CurrentN -> x == 50 && Lados == 1 && (Comida == 1 || AmigaL == 1))
        {
            BloqueadaN ++;
        }
        if(CurrentN -> x == 750 && Lados == 2 && (Comida == 2 || AmigaL == 2))
        {
            BloqueadaN++;
        }
        if(Lados == 3 && (Comida == 3 || AmigaL == 3))
        {
            BloqueadaN++;
        }
        if(AmigaC == 3)
        {
            BloqueadaN++;
        }
        if(Lados == 1 && Comida == 1 && AmigaC == 2)
        {
            BloqueadaN++;
        }
        if(Lados == 2 && Comida == 2 && AmigaC == 1)
        {
            BloqueadaN++;
        }
        CurrentN = CurrentN -> sig;
    }

    while (CurrentB != NULL)
    {
        int Lados = colision(CurrentN, tab);
        int Comida = comidaDisponible(CurrentN, tab);
        int AmigaC = isAmiga(CurrentN, tab);
        int AmigaL = isAmigalejana(CurrentN, tab);

        if(CurrentN -> x == 50 && Lados == 1 && (Comida == 1 || AmigaL == 1))
        {
            BloqueadaB++;
        }
        if(CurrentN -> x == 750 && Lados == 2 && (Comida == 2 || AmigaL == 2))
        {
            BloqueadaB++;
        }
        if(Lados == 3 && (Comida == 3 || AmigaL == 3))
        {
            BloqueadaB++;
        }
        if(AmigaC == 3)
        {
            BloqueadaB++;
        }
        if(Lados == 1 && Comida == 1 && AmigaC == 2)
        {
            BloqueadaB++;
        }
        if(Lados == 2 && Comida == 2 && AmigaC == 1)
        {
            BloqueadaB++;
        }
        CurrentB = CurrentB -> sig;
    }

    CurrentN = Negras -> sig;
    CurrentB = Blancas -> sig;

    while (CurrentN != NULL)
    {
        if(CurrentN -> vida == 1)
        {
            contN++;
        }
        CurrentN = CurrentN -> sig;
    }
    while (CurrentB != NULL)
    {
        if(CurrentB -> vida == 1)
        {
            contB++;
        }
        CurrentB = CurrentB -> sig;
    }

    if(contN == BloqueadaN)
        return 2;
    if(contB == BloqueadaB)
        return 1;
    return 0;
}

int getWinner(Ficha* Blancas, Ficha* Negras, Tablero* tab)
{
    Ficha* CurrentB = Blancas -> sig ? Blancas -> sig: Blancas;
    Ficha *CurrentN = Negras -> sig ? Negras -> sig: Negras;

    if(CurrentN == NULL || CurrentB == NULL)
        return 0;
    int contB = 0;
    int contN = 0;

//    if(movimientosDisponibles(Blancas, Negras, tab) == 2)
//    {
//        return 2;
//    }
//    if(movimientosDisponibles(Blancas, Negras, tab) == 1)
//    {
//        return 1;
//    }

    while (CurrentN != NULL)
    {
        if(CurrentN -> vida == 0)
            contN++;
        CurrentN = CurrentN -> sig;

    }
    while (CurrentB != NULL)
    {
        if(CurrentB -> vida == 0)
            contB++;
        CurrentB = CurrentB -> sig;
    }

    if(contB == 12)
        return 1;
    if(contN == 12)
        return 2;
    return 0;
}

// Archivos

void saveGame(Ficha* Blancas, Ficha* Negras, int turno, Tablero* tab)
{
    Ficha* currentB = Blancas -> sig ? Blancas -> sig: Blancas;
    Ficha* currentN = Negras -> sig ? Negras -> sig: Negras;

    int x[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int y[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int id[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int vida[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int col [24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int trn [1] = {0};

    FILE* save = fopen("savegame.txt", "w");
    if(save)
    {
        for(int i = 0; i < 12; i++)
        {
            if(currentN != NULL)
            {
                x[i] = currentN -> x;
                y[i] = currentN -> y;
                id[i] = currentN -> id;
                vida[i] = currentN -> vida;
                col[i] = 1;
            }
            if(currentN == NULL)
            {
                x[i] = 0;
                y[i] = 0;
                id[i] = 0;
                vida[i] = 0;
                col[i] = 0;
            }
            currentN = currentN -> sig;
        }
        for(int i = 12 ; i < 24; i++)
        {
            if(currentB != NULL)
            {
                x[i] = currentB -> x;
                y[i] = currentB -> y;
                id[i] = currentB -> id;
                vida[i] = currentB -> vida;
                col[i] = 2;
            }
            if(currentB == NULL)
            {
                x[i] = 0;
                y[i] = 0;
                id[i] = 0;
                vida[i] = 0;
                col[i] = 0;
            }
            currentB = currentB -> sig;
        }

        fwrite(x, sizeof (x), 1,save);
        fwrite(y, sizeof (y), 1,save);
        fwrite(id, sizeof (id), 1,save);
        fwrite(vida, sizeof (vida), 1,save);
        fwrite(col, sizeof (col), 1,save);
        fwrite(trn, sizeof(trn), 1, save);
        fwrite(tab, sizeof(Tablero), 1, save);
    }
    fclose(save);
    exit(0);
}
void loadGame(Ficha* Blancas, Ficha* Negras, int* turno, Tablero* tab)
{
    Ficha* currentN = Negras -> sig;
    Ficha* CurrentB = Blancas -> sig;
    FILE* save = fopen("savegame.txt", "r");

    if(save != NULL)
    {
        int x[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int y[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int id[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int vida[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int col [24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int trn [1] = {0};

        fread(x,sizeof(x), 1, save);
        fread(y, sizeof(y), 1, save);
        fread(id, sizeof (id), 1,save);
        fread(vida,sizeof(vida), 1, save);
        fread(col, sizeof(col), 1, save);
        fread(trn, sizeof(trn), 1, save);
        fread(tab, sizeof(Tablero), 1, save);
        fclose(save);

        for(int i = 0; i < 12; i++)
        {
            if(currentN != NULL)
            {
                currentN -> x = x[i];
                currentN -> y = y[i];
                currentN -> id = id[i];
                currentN -> vida = vida[i];
                currentN -> col = 'N';
            }
            currentN = currentN -> sig;
        }
        for(int i = 12; i < 24; i++)
        {
            if(CurrentB != NULL)
            {
                CurrentB -> x = x[i];
                CurrentB -> y = y[i];
                CurrentB -> id = id[i];
                CurrentB -> vida = vida[i];
                CurrentB -> col = 'N';
            }
            CurrentB = CurrentB -> sig;
        }
        turno = &trn[0];

    } else
    {
        DrawText("No se guardo nada anteriormente", 200, 400, 36, RED);
    }
}