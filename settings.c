#include "settings.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

struct ficha
{
    int x;
    int y;
    int id;
    int vida;
    struct ficha* sig;
};

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

void addF(Ficha * ficha,int x, int y, int id)
{
    Ficha* Current = ficha;

    while(Current -> sig != NULL)
        Current = Current -> sig;

    Current -> sig = malloc(sizeof(Ficha));
    Current -> sig -> x = x;
    Current -> sig -> y = y;
    Current -> sig -> vida = 1;
    Current -> sig -> id = id;
    Current -> sig -> sig = NULL;

}


Ficha *Crear_fichas(int C)
{
    if(C == 1) {
        Ficha *N1 = malloc(sizeof(Ficha));
        N1->sig = NULL;
        int pos_x = 150;
        int pos_y = 50;
        int cont_id = 0;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id);
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 50;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id);
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 150;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id);
            pos_x = pos_x + 200;
            cont_id++;
        }

        return N1;
    }
    else
    {
        Ficha *N1 = malloc(sizeof(Ficha));
        N1->sig = NULL;
        int pos_x = 50;
        int pos_y = 550;
        int cont_id = 12;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id);
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 150;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id);
            pos_x = pos_x + 200;
            cont_id++;
        }

        pos_x = 50;
        pos_y = pos_y + 100;

        for (int i = 0; i < 4; i++) {
            addF(N1, pos_x, pos_y, cont_id);
            pos_x = pos_x + 200;
            cont_id++;
        }

        return N1;
    }

}

void DibujarFichas(Ficha * fichas, color C)
{
    Ficha* Current = fichas -> sig;
    while(Current != NULL)
    {
        if(Current -> vida == 0)
        {
            Current -> x = 1000;
            Current -> y = 1000;
            Current = Current -> sig;
        }
        DrawCircle(Current->x,Current->y, 45, C);
        Current = Current -> sig;
    }
}

void Display(Ficha * fichas)
{
    Ficha* Current = fichas;

    while(Current != NULL)
    {
        printf("%d, %d, %d\n",Current -> x, Current -> y, Current -> id);
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

int isAmiga(Ficha* player, Ficha* fichas)
{
    if(player -> id < 12) //Significa que estamos en las negras
    {
        int BanDer = 0;
        int BanIzq = 0;
        int x_der = player -> x + 100;
        int y_der = player -> y + 100;
        int x_izq = player -> x - 100;
        int y_izq = player -> y + 100;
        Ficha* yo = fichas;
        while(yo != NULL)
        {
            if(yo -> x == x_der && yo -> y == y_der)
                BanDer = 1;
            if(yo -> x == x_izq && yo -> y == y_izq)
                BanIzq = 1;
            yo = yo -> sig;
        }

        if(BanIzq == 1 && BanDer == 1)
            return 3;
        else if(BanDer == 1)
            return 1;
        else if(BanIzq == 1)
            return 2;
        else if(BanIzq == 0 && BanDer == 0)
            return 0;

    }
    else
    {
        int BanDer = 0;
        int BanIzq = 0;
        int x_der = player -> x + 100;
        int y_der = player -> y - 100;
        int x_izq = player -> x - 100;
        int y_izq = player -> y - 100;
        Ficha* yo = fichas;
        while(yo != NULL)
        {
            if(yo -> x  == x_der && yo -> y == y_der)
                BanDer = 1;
            if(yo -> x  == x_izq && yo -> y == y_izq)
                BanIzq = 1;
            yo = yo -> sig;
        }

        if(BanIzq == 1 && BanDer == 1)
            return 3;
        else if(BanDer == 1)
            return 1;
        else if(BanIzq == 1)
            return 2;
        else if(BanIzq == 0 && BanDer == 0)
            return 0;
    }


}

int isAmigaLejana(Ficha* player, Ficha* fichas) //Util para saber si hay una ficha amiga en lugares donde se puede comer, y no realizar movimientos ilegales
{
    if(player -> id < 12) //Significa que estamos en las negras
    {
        int BanDer = 0;
        int BanIzq = 0;
        int x_der = player -> x + 200;
        int y_der = player -> y + 200;
        int x_izq = player -> x - 200;
        int y_izq = player -> y + 200;
        Ficha* yo = fichas;
        while(yo != NULL)
        {
            if(yo -> x == x_der && yo -> y == y_der)
                BanDer = 1;
            if(yo -> x == x_izq && yo -> y == y_izq)
                BanIzq = 1;
            yo = yo -> sig;
        }

        if(BanIzq == 1 && BanDer == 1)
            return 3;
        else if(BanDer == 1)
            return 1;
        else if(BanIzq == 1)
            return 2;
        else if(BanIzq == 0 && BanDer == 0)
            return 0;

    }
    else
    {
        int BanDer = 0;
        int BanIzq = 0;
        int x_der = player -> x + 200;
        int y_der = player -> y - 200;
        int x_izq = player -> x - 200;
        int y_izq = player -> y - 200;
        Ficha* yo = fichas;
        while(yo != NULL)
        {
            if(yo -> x  == x_der && yo -> y == y_der)
                BanDer = 1;
            if(yo -> x  == x_izq && yo -> y == y_izq)
                BanIzq = 1;
            yo = yo -> sig;
        }

        if(BanIzq == 1 && BanDer == 1)
            return 3;
        else if(BanDer == 1)
            return 1;
        else if(BanIzq == 1)
            return 2;
        else if(BanIzq == 0 && BanDer == 0)
            return 0;
    }


}

int ComidaDisponible(Ficha* player, Ficha* fichas)
{
    if(player -> id < 12) //Nos encontramos jugando con las fichas negras.
    {
        int x_derecha = player -> x + 200;
        int y_derecha = player -> y + 200;
        int x_izquierda = player -> x - 200;
        int y_izquierda = player -> y + 200;
        int BandIzq = 0;
        int BanDer = 0;

        Ficha* current = fichas;

        while(current != NULL)
        {
            if(current -> x == x_derecha && current -> y == y_derecha) //&& (currentp->x != x_derecha && currentp->y != y_derecha))
                BanDer = 1;
            if(current -> x == x_izquierda && current -> y == y_izquierda) //&& (currentp->x != x_izquierda && currentp->y != y_izquierda))
                BandIzq = 1;
            current = current -> sig;
        }

        if(BandIzq == 1 && BanDer == 1)
            return 3;
        else if(BanDer == 1)
            return 1;
        else if(BandIzq == 1)
            return 2;

        return 0;
    }
    else //Turno de las fichas blancas :)
    {
        int x_derecha = player -> x + 200;
        int y_derecha = player -> y - 200;
        int x_izquierda = player -> x - 200;
        int y_izquierda = player -> y - 200;
        int BandIzq = 0;
        int BanDer = 0;

        Ficha* current = fichas;

        while(current != NULL)
        {
            if(current -> x == x_derecha && current -> y == y_derecha) //&& (currentp->x != x_derecha && currentp->y != y_derecha))
                BanDer = 1;
            if(current -> x == x_izquierda && current -> y == y_izquierda) //&& (currentp->x != x_izquierda && currentp->y != y_izquierda))
                BandIzq = 1;
            current = current -> sig;
        }

        if(BandIzq == 1 && BanDer == 1)
            return 3;
        else if(BanDer == 1)
            return 1;
        else if(BandIzq == 1)
            return 2;

        return 0;
    }
}

int colision(Ficha* player, Ficha* fichas) //FunciOn para saber si hay una ficha del oponente a nuestra izquierda o derecha
{
    if(player -> id < 12) //Es el turno de las fichas negras
    {
        int x_derecha = player -> x + 100;
        int y_derecha = player -> y + 100;
        int x_izquierda = player -> x -100;
        int y_izquierda = player -> y +100;
        int BandIzq = 0;
        int BanDer = 0;

        Ficha* current = fichas;

        while(current != NULL)
        {
            if(current -> x == x_derecha && current -> y == y_derecha)
                BanDer = 1;
            if(current -> x == x_izquierda && current -> y == y_izquierda)
                BandIzq = 1;
            current = current -> sig;
        }

        if(BandIzq == 1 && BanDer == 1) //Hay fichas en ambos lados de nuestra ficha seleccionada
            return 3;
        else if(BanDer == 1) //Hay una ficha a la derecha
            return 1;
        else if(BandIzq == 1) //Hay una ficha a la izquierda
            return 2;

        return 0;
    }
    else //Turno de las blancas
    {
        int x_derecha = player -> x + 100;
        int y_derecha = player -> y - 100;
        int x_izquierda = player -> x - 100;
        int y_izquierda = player -> y - 100;
        int BandIzq = 0;
        int BanDer = 0;

        Ficha* current = fichas;

        while(current != NULL)
        {
            if(current -> x == x_derecha && current -> y == y_derecha)
                BanDer = 1;
            if(current -> x == x_izquierda && current -> y == y_izquierda)
                BandIzq = 1;
            current = current -> sig;
        }

        if(BandIzq == 1 && BanDer == 1) //Hay fichas a ambos lados de la seleccionada
            return 3;
        else if(BanDer == 1) //Hay una ficha a la derecha
            return 1;
        else if(BandIzq == 1) //Hay una ficha a la izquierda
            return 2;

        return 0;
    }

}

void CirculosR(Ficha *player, Ficha* oponentes, Ficha* amigas)
{
    if(player -> id < 12) //Si estamos con las fichas negras
    {
        if(colision(player, oponentes) == 3) //Si hay fichas del oponente a la izquierda y derecha
        {
            if(ComidaDisponible(player, oponentes) == 1 && isAmigaLejana(player, amigas) == 2)
                return;
            if(ComidaDisponible(player, oponentes) == 1 && isAmigaLejana(player, amigas) != 2) //Si la del lado derecho no se puede comer, y no hay una amiga estorbando a la izquierda
                DrawCircle(player->x - 200, player->y + 200, 45, RED);
            if(ComidaDisponible(player, oponentes) == 2 && isAmigaLejana(player, amigas) == 1)
                return;
            if(ComidaDisponible(player, oponentes) == 2 && isAmigaLejana(player, amigas) != 1) //Si la del lado izquierdo no se puede comer
                DrawCircle(player->x + 200, player->y + 200, 45, RED);
            if(ComidaDisponible(player, oponentes) == 3) //Si ninguna se puede comer
                return; //Salimos de la funciOn
            if(ComidaDisponible(player, oponentes) == 0) //Si ambas fichas se pueden comer :)
            {
                if(isAmigaLejana(player, amigas) == 0)
                {
                    DrawCircle(player->x - 200, player->y + 200, 45, RED);
                    DrawCircle(player->x + 200, player->y + 200, 45, RED);
                }
                else if(isAmigaLejana(player, amigas) == 3)
                    return;
                else if(isAmigaLejana(player, amigas) == 2)
                    DrawCircle(player->x + 200, player->y + 200, 45, RED);
                else if(isAmigaLejana(player, amigas) == 1)
                    DrawCircle(player->x - 200, player->y + 200, 45, RED);
            }
        }
        if(colision(player, oponentes) == 1) //Si hay una ficha del oponente a la derecha
        {
            if(ComidaDisponible(player, oponentes) == 1 || ComidaDisponible(player, oponentes) == 3) //Si no se puede comer :(
            {
                if(isAmiga(player, amigas) == 2) //Si tenemos una ficha amiga a la izquierda no hacemos nada
                    return;
                else // Si no, dibujamos un cIrculo a la izquierda :)
                    DrawCircle(player->x - 100, player->y + 100, 45, RED);
            }
            else if(ComidaDisponible(player, oponentes) != 1 && isAmiga(player, amigas) == 2 && isAmigaLejana(player, amigas) == 1)
                return;
            else if(ComidaDisponible(player, oponentes) != 1 && (isAmigaLejana(player, amigas) == 1 || isAmigaLejana(player, amigas) == 3))
                DrawCircle(player->x - 100, player->y + 100, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 1 && isAmiga(player, amigas) == 2)
                DrawCircle(player->x + 200, player->y + 200, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 1)
            {
                DrawCircle(player->x + 200, player->y + 200, 45, RED);
                DrawCircle(player->x - 100, player->y + 100, 45, RED);
            }
        }
        if(colision(player, oponentes) == 2) //Cuando hay una ficha oponente a nuestra izquierda
        {
            if(ComidaDisponible(player, oponentes) == 2 || ComidaDisponible(player, oponentes) == 3) //Si no se puede comer :(
            {
                if(isAmiga(player, amigas) == 1) //Si la que estA a la derecha es una ficha amiga
                    return;
                else
                    DrawCircle(player->x + 100, player->y + 100, 45, RED);
            }
            else if(ComidaDisponible(player, oponentes) != 2 && isAmiga(player, amigas) == 1 && isAmigaLejana(player, amigas) == 2)
                return;
            else if(ComidaDisponible(player, oponentes) != 2 && (isAmigaLejana(player, amigas) == 2 || isAmigaLejana(player, amigas) == 3))
                DrawCircle(player->x + 100, player->y + 100, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 2 && isAmiga(player, amigas) == 1) //Si es posible comer esa ficha a la izquierda y tenemos una amiga a la derecha
            {
                DrawCircle(player->x - 200, player->y + 200, 45, RED);
            }
            else if(ComidaDisponible(player, oponentes) != 2)
            {
                DrawCircle(player->x + 100, player->y + 100, 45, RED);
                DrawCircle(player->x - 200, player->y + 200, 45, RED);
            }

        }
        if(colision(player, oponentes) == 0)
        {
            if(isAmiga(player, amigas) == 3)
                return;
            else if(isAmiga(player, amigas) == 2)
                DrawCircle(player->x + 100, player->y + 100, 45, RED);
            else if(isAmiga(player, amigas) == 1)
                DrawCircle(player->x - 100, player->y + 100, 45, RED);
            else if(isAmiga(player, amigas) == 0)
            {
                DrawCircle(player->x - 100, player->y + 100, 45, RED);
                DrawCircle(player->x + 100, player->y + 100, 45, RED);
            }

        }
    }

    else //Si player pertenece a las fichas blancas.
    {
        if(colision(player, oponentes) == 3)
        {
            if(ComidaDisponible(player, oponentes) == 1 && isAmigaLejana(player, amigas) == 2) //Si la del lado derecho no se puede comer
                return;
            if(ComidaDisponible(player, oponentes) == 1 && isAmigaLejana(player, amigas) != 2)
                DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
            if(ComidaDisponible(player, oponentes) == 2 && isAmigaLejana(player, amigas) == 1) //Si la izquierda no se puede comer y a la derecha nos estorban
                return;
            if(ComidaDisponible(player, oponentes) == 2 && isAmigaLejana(player, amigas) != 1)
                DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
            if(ComidaDisponible(player, oponentes) == 3) //Si ninguna se puede comer
                return;
            if(ComidaDisponible(player, oponentes) == 0) //Si las dos estAn disfrutables :)
            {
                if(isAmigaLejana(player, amigas) == 0)
                {
                    DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                    DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
                }
                else if(isAmigaLejana(player, amigas) == 3)
                    return;
                else if(isAmigaLejana(player, amigas) == 2)
                    DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
                else if(isAmigaLejana(player, amigas) == 1)
                    DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
            }

        }
        if(colision(player, oponentes) == 1) //Si hay una ficha oponente a la derecha
        {
            if(ComidaDisponible(player, oponentes) == 1 || ComidaDisponible(player, oponentes) == 3) //No se puede comer?
            {
                if(isAmiga(player, amigas) == 2)
                    return;
                else
                    DrawCircle(player -> x - 100, player -> y - 100, 45, RED);
            }
            else if(ComidaDisponible(player, oponentes) != 1 && isAmiga(player, amigas) == 2 && isAmigaLejana(player, amigas) == 1)
                return;
            else if(ComidaDisponible(player, oponentes) != 1 && (isAmigaLejana(player, amigas) == 1 || isAmigaLejana(player, amigas) == 3))
                DrawCircle(player -> x - 100, player -> y - 100, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 1 && isAmiga(player, amigas) == 2)
                DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 1)
            {
                DrawCircle(player -> x - 100, player -> y - 100, 45, RED);
                DrawCircle(player -> x + 200, player -> y - 200, 45, RED);
            }
        }
        if(colision(player, oponentes) == 2) //Si hay ficha oponente a la izquierda
        {
            if(ComidaDisponible(player, oponentes) == 2 || ComidaDisponible(player, oponentes) == 3) //Si no se puede comer
            {
                if(isAmiga(player, amigas) == 1)
                    return;
                else
                    DrawCircle(player -> x + 100, player -> y - 100, 45, RED);
            }
            else if(ComidaDisponible(player, oponentes) != 2 && isAmiga(player, amigas) == 1 && isAmigaLejana(player, amigas) == 2)
                return;
            else if(ComidaDisponible(player, oponentes) != 2 && (isAmigaLejana(player, amigas) == 2 || isAmigaLejana(player, amigas) == 3))
                DrawCircle(player -> x + 100, player -> y - 100, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 2 && isAmiga(player, amigas) == 1)
                DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
            else if(ComidaDisponible(player, oponentes) != 2)
            {
                DrawCircle(player -> x - 200, player -> y - 200, 45, RED);
                DrawCircle(player -> x + 100, player -> y - 100, 45, RED);
            }
        }
        if(colision(player, oponentes) == 0)
        {
            if(isAmiga(player, amigas) == 3)
                return;
            else if(isAmiga(player, amigas) == 2)
                DrawCircle(player->x + 100, player->y - 100, 45, RED);
            else if(isAmiga(player, amigas) == 1)
                DrawCircle(player->x - 100, player->y - 100, 45, RED);
            else if(isAmiga(player, amigas) == 0)
            {
                DrawCircle(player->x - 100, player->y - 100, 45, RED);
                DrawCircle(player->x + 100, player->y - 100, 45, RED);
            }
        }


    }

}

void MovBlancasSinComida(Ficha *ficha, int dir)
{
    if (dir == 1)
    {
        ficha -> y -= 100;
        ficha -> x += 100;
    }
    if (dir == 0)
    {
        ficha -> y -= 100;
        ficha -> x -= 100;
    }

}

void MovBlancasConComida(Ficha *ficha, int dir)
{
    if (dir == 1)
    {
        ficha -> y -= 200;
        ficha -> x += 200;
    }
    if (dir == 0)
    {
        ficha -> y -= 200;
        ficha -> x -= 200;
    }

}

void MovNegrasSinComida(Ficha *ficha, int dir)
{
    if (dir == 1)
    {
        ficha -> y += 100;
        ficha -> x += 100;
    }
    if (dir == 0)
    {
        ficha -> y += 100;
        ficha -> x -= 100;
    }
}

void MovNegrasConComida(Ficha *ficha, int dir)
{
    if (dir == 1)
    {
        ficha -> y += 200;
        ficha -> x += 200;
    }
    if (dir == 0)
    {
        ficha -> y += 200;
        ficha -> x -= 200;
    }
}

void eliminarf(Ficha* ficha)
{
    ficha -> vida = 0;
}

int comerFNegraDerecha(Ficha* player, Ficha* oponente)
{
    Ficha* ficha = DetectF(player -> x - 100, player -> y + 100, oponente);
    if(ficha != NULL)
    {
        eliminarf(ficha);
        return 1;
    }
    else
        return 0;
}

int comerFNegraIzquierda(Ficha* player, Ficha* oponente)
{
    Ficha* ficha = DetectF(player -> x + 100, player -> y + 100, oponente);
    if(ficha != NULL)
    {
        eliminarf(ficha);
        return 1;
    }
    else
        return 0;
}

int comerFBlancaDerecha(Ficha* player, Ficha* oponente)
{
    Ficha* ficha = DetectF(player -> x - 100, player -> y - 100, oponente);
    if(ficha != NULL)
    {
        eliminarf(ficha);
        return 1;
    }
    else
        return 0;
}

int comerFBlancaIzquierda(Ficha* player, Ficha* oponente)
{
    Ficha* ficha = DetectF(player -> x + 100, player-> y - 100, oponente);
    if(ficha != NULL)
    {
        eliminarf(ficha);
        return 1;
    }
    else
        return 0;
}

int MovimientoValido(int x, int y, Ficha *selected, Ficha* amigas, Ficha* oponentes)
{
    if(selected -> id < 12) //Fichas Negras
    {
        if(colision(selected, oponentes) == 3) //Si hay fichas del oponente a la izquierda y derecha
        {
            if(ComidaDisponible(selected, oponentes) == 1 && isAmigaLejana(selected, amigas) == 2)
                return 0;
            if(ComidaDisponible(selected, oponentes) == 1 && isAmigaLejana(selected, amigas) != 2) //Si la del lado derecho no se puede comer, y no hay una amiga estorbando a la izquierda
            {
                if(x > selected->x - 245 && selected->x - 155 > x && y < selected->y + 245 && selected->y + 155 < y)
                {
                    MovNegrasConComida(selected, 0);
                    comerFBlancaIzquierda(selected, oponentes);
                    return 1;
                }
            }

            if(ComidaDisponible(selected, oponentes) == 2 && isAmigaLejana(selected, amigas) == 1)
                return 0;
            if(ComidaDisponible(selected, oponentes) == 2 && isAmigaLejana(selected, amigas) != 1) //Si la del lado izquierdo no se puede comer
            {
                if(x < selected->x + 245 && selected->x + 155 < x && y < selected->y + 245 && selected->y + 155 < y)
                {
                    MovNegrasConComida(selected, 1);
                    comerFBlancaDerecha(selected, oponentes);
                    return 1;
                }
            }
            if(ComidaDisponible(selected, oponentes) == 3) //Si ninguna se puede comer
                return 0; //Salimos de la funciOn
            if(ComidaDisponible(selected, oponentes) == 0) //Si ambas fichas se pueden comer :)
            {
                if(x > selected->x - 245 && selected->x - 155 > x && y < selected->y + 245 && selected->y + 155 < y && isAmigaLejana(selected, amigas) != 2)
                {
                    MovNegrasConComida(selected, 0);
                    comerFBlancaIzquierda(selected, oponentes);
                    return 1;
                }
                if(x < selected->x + 245 && selected->x + 155 < x && y < selected->y + 245 && selected->y + 155 < y && isAmigaLejana(selected, amigas) != 1)
                {
                    MovNegrasConComida(selected, 1);
                    comerFBlancaDerecha(selected, oponentes);
                    return 1;
                }
            }
        }
        if(colision(selected, oponentes) == 0)
        {
            if(isAmiga(selected, amigas) == 3)
                return 0;
            else if(isAmiga(selected, amigas) == 2)
            {
                if(x < selected->x + 145 && selected->x + 55 < x && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 1);
                    return 1;
                }
            }

            else if(isAmiga(selected, amigas) == 1)
            {
                if(x > selected->x - 145 && selected->x - 55 > x && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 0);
                    return 1;
                }
            }
            else if(isAmiga(selected, amigas) == 0)
            {
                if(x < selected->x + 145 && selected->x + 55 < x && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 1);
                    return 1;
                }
                if(x > selected->x - 145 && selected->x - 55 > x && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 0);
                    return 1;
                }
            }
        }
        if(colision(selected, oponentes) == 1) //Si hay una ficha del oponente a la derecha
        {
            if(ComidaDisponible(selected, oponentes) == 1 || ComidaDisponible(selected, oponentes) == 3) //Si no se puede comer :(
            {
                if(isAmiga(selected, amigas) == 2) //Si tenemos una ficha amiga a la izquierda no hacemos nada
                    return 0;
                else // Si no
                {
                    if(x > selected -> x - 145 && x < selected -> x - 55 && y < selected->y + 145 && selected->y + 55 < y)
                    {
                        MovNegrasSinComida(selected, 0);
                        return 1;
                    }
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 1 && isAmiga(selected, amigas) == 2 && isAmigaLejana(selected, amigas) == 1)
                return 0;
            else if(ComidaDisponible(selected, oponentes) != 1 && (isAmigaLejana(selected, amigas) == 1 || isAmigaLejana(selected, amigas) == 3))
            {
                if(x > selected -> x - 145 && x < selected -> x - 55 && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 0);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 1 && isAmiga(selected, amigas) == 2)
            {
                if(x < selected -> x + 245 && x > selected -> x + 155 && y < selected->y + 245 && selected->y + 155 < y)
                {
                    MovNegrasConComida(selected, 1);
                    comerFBlancaDerecha(selected, oponentes);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 1)
            {
                if(x > selected -> x - 145 && x < selected -> x - 55 && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 0);
                    return 1;
                }
                if(x < selected -> x + 245 && x < selected -> x + 155 && y < selected->y + 245 && selected->y + 155 < y)
                {
                    MovNegrasConComida(selected, 1);
                    comerFBlancaDerecha(selected, oponentes);
                    return 1;
                }
            }
        }
        if(colision(selected, oponentes) == 2) //Cuando hay una ficha oponente a nuestra izquierda
        {
            if(ComidaDisponible(selected, oponentes) == 2 || ComidaDisponible(selected, oponentes) == 3) //Si no se puede comer :(
            {
                if(isAmiga(selected, amigas) == 1) //Si la que estA a la derecha es una ficha amiga
                    return 0;
                else
                {
                    if(x < selected -> x + 145 && x > selected -> x + 55 && y < selected->y + 145 && selected->y + 55 < y)
                    {
                        MovNegrasSinComida(selected, 1);
                        return 1;
                    }
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 2 && isAmiga(selected, amigas) == 1 && isAmigaLejana(selected, amigas) == 2)
                return 0;
            else if(ComidaDisponible(selected, oponentes) != 2 && (isAmigaLejana(selected, amigas) == 2 || isAmigaLejana(selected, amigas) == 3))
            {
                if(x < selected -> x + 145 && x > selected -> x + 55 && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 1);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 2 && isAmiga(selected, amigas) == 1) //Si es posible comer esa ficha a la izquierda y tenemos una amiga a la derecha
            {
                if(x > selected -> x - 245 && x < selected -> x - 155 && y < selected->y + 245 && selected->y + 155 < y)
                {
                    MovNegrasConComida(selected, 0);
                    comerFBlancaIzquierda(selected, oponentes);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 2)
            {
                if(x < selected -> x + 145 && x > selected -> x + 55 && y < selected->y + 145 && selected->y + 55 < y)
                {
                    MovNegrasSinComida(selected, 1);
                    return 1;
                }
                if(x > selected -> x - 245 && x < selected -> x - 155 && y < selected->y + 245 && selected->y + 155 < y)
                {
                    MovNegrasConComida(selected, 0);
                    comerFBlancaIzquierda(selected, oponentes);
                    return 1;
                }
            }

        }
    }
    else //Fichas blancas
    {
        if(colision(selected, oponentes) == 3) //Si hay fichas del oponente a la izquierda y derecha
        {
            if(ComidaDisponible(selected, oponentes) == 1 && isAmigaLejana(selected, amigas) == 2)
                return 0;
            if(ComidaDisponible(selected, oponentes) == 1 && isAmigaLejana(selected, amigas) != 2) //Si la del lado derecho no se puede comer, y no hay una amiga estorbando a la izquierda
            {
                if(x > selected->x - 245 && selected->x - 155 > x && y > selected->y - 245 && selected->y - 155 > y)
                {
                    MovBlancasConComida(selected, 0);
                    comerFNegraIzquierda(selected, oponentes);
                    return 1;
                }
            }

            if(ComidaDisponible(selected, oponentes) == 2 && isAmigaLejana(selected, amigas) == 1)
                return 0;
            if(ComidaDisponible(selected, oponentes) == 2 && isAmigaLejana(selected, amigas) != 1) //Si la del lado izquierdo no se puede comer
            {
                if(x < selected->x + 245 && selected->x + 155 < x && y > selected->y - 245 && selected->y - 155 > y)
                {
                    MovBlancasConComida(selected, 1);
                    comerFNegraDerecha(selected, oponentes);
                    return 1;
                }
            }
            if(ComidaDisponible(selected, oponentes) == 3) //Si ninguna se puede comer
                return 0; //Salimos de la funciOn
            if(ComidaDisponible(selected, oponentes) == 0) //Si ambas fichas se pueden comer :)
            {
                if(x > selected->x - 245 && selected->x - 155 > x && y > selected->y - 245 && selected->y - 155 > y && isAmigaLejana(selected, amigas) != 2)
                {
                    MovBlancasConComida(selected, 0);
                    comerFNegraIzquierda(selected, oponentes);
                    return 1;
                }
                if(x < selected->x + 245 && selected->x + 155 < x && y > selected->y - 245 && selected->y - 155 > y && isAmigaLejana(selected, amigas) != 1)
                {
                    MovBlancasConComida(selected, 1);
                    comerFNegraDerecha(selected, oponentes);
                    return 1;
                }
            }
        }

        if(colision(selected, oponentes) == 0)
        {
            if(isAmiga(selected, amigas) == 3)
                return 0;
            else if(isAmiga(selected, amigas) == 2)
            {
                if(x < selected->x + 145 && selected->x + 55 < x && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 1);
                    return 1;
                }
            }
            else if(isAmiga(selected, amigas) == 1)
            {
                if(x > selected->x - 145 && selected->x - 55 > x && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 0);
                    return 1;
                }
            }
            else if(isAmiga(selected, amigas) == 0)
            {
                if(x < selected->x + 145 && selected->x + 55 < x && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 1);
                    return 1;
                }
                if(x > selected->x - 145 && selected->x - 55 > x && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 0);
                    return 1;
                }
            }
        }
        if(colision(selected, oponentes) == 1) //Si hay una ficha del oponente a la derecha
        {
            if(ComidaDisponible(selected, oponentes) == 1 || ComidaDisponible(selected, oponentes) == 3) //Si no se puede comer :(
            {
                if(isAmiga(selected, amigas) == 2) //Si tenemos una ficha amiga a la izquierda no hacemos nada
                    return 0;
                else // Si no
                {
                    if(x < selected -> x + 145 && x > selected -> x + 55 && y > selected->y - 145 && selected->y - 55 > y)
                    {
                        MovBlancasSinComida(selected, 0);
                        return 1;
                    }
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 1 && isAmiga(selected, amigas) == 2 && isAmigaLejana(selected, amigas) == 1)
                return 0;
            else if(ComidaDisponible(selected, oponentes) != 1 && (isAmigaLejana(selected, amigas) == 1 || isAmigaLejana(selected, amigas) == 3))
            {
                if(x > selected -> x - 145 && x < selected -> x - 55 && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 0);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 1 && isAmiga(selected, amigas) == 2)
            {
                if(x < selected -> x + 245 && x > selected -> x + 155 && y > selected->y - 245 && selected->y - 155 > y)
                {
                    MovBlancasConComida(selected, 1);
                    comerFNegraDerecha(selected, oponentes);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 1)
            {
                if(x > selected -> x - 145 && x < selected -> x - 55 && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 0);
                    return 1;
                }
                if(x < selected -> x + 245 && x > selected -> x + 155 && y > selected->y - 245 && selected->y - 155 > y)
                {
                    MovBlancasConComida(selected, 1);
                    comerFNegraDerecha(selected, oponentes);
                    return 1;
                }
            }
        }
        if(colision(selected, oponentes) == 2) //Cuando hay una ficha oponente a nuestra izquierda
        {
            if(ComidaDisponible(selected, oponentes) == 2 || ComidaDisponible(selected, oponentes) == 3) //Si no se puede comer :(
            {
                if(isAmiga(selected, amigas) == 1) //Si la que estA a la derecha es una ficha amiga
                    return 0;
                else
                {
                    if(x < selected -> x + 145 && x > selected -> x + 55 && y > selected->y - 145 && selected->y - 55 > y)
                    {
                        MovBlancasSinComida(selected, 1);
                        return 1;
                    }
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 2 && isAmiga(selected, amigas) == 1 && isAmigaLejana(selected, amigas) == 2)
                return 0;
            else if(ComidaDisponible(selected, oponentes) != 2 && (isAmigaLejana(selected, amigas) == 2 || isAmigaLejana(selected, amigas) == 3))
            {
                if(x < selected -> x + 145 && x > selected -> x + 55 && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 1);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 2 && isAmiga(selected, amigas) == 1) //Si es posible comer esa ficha a la izquierda y tenemos una amiga a la derecha
            {
                if(x > selected -> x - 245 && x < selected -> x - 155 && y > selected->y - 245 && selected->y - 155 > y)
                {
                    MovBlancasConComida(selected, 0);
                    comerFNegraIzquierda(selected, oponentes);
                    return 1;
                }
            }
            else if(ComidaDisponible(selected, oponentes) != 2)
            {
                if(x < selected -> x + 145 && x > selected -> x + 55 && y > selected->y - 145 && selected->y - 55 > y)
                {
                    MovBlancasSinComida(selected, 1);
                    return 1;
                }
                if(x > selected -> x - 245 && x < selected -> x - 155 && y > selected->y - 245 && selected->y - 155 > y)
                {
                    MovBlancasConComida(selected, 0);
                    comerFNegraIzquierda(selected, oponentes);
                    return 1;
                }
            }

        }
    }
}