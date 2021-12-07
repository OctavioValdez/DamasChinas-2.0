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
}; // Informacion de cada ficha en el juego

struct Cuadro
{
    int Disponible;
    int x;
    int y;
    int Reina;

}typedef cuadro; // Informacion de cada cuadro en el juego

struct tablero
{
    cuadro** Tablero;
    int size;
}typedef Tablero; // Es un arreglo de los cuadros y su informacion


//Funciones de tablero y fichas
int get_pos_arr(Ficha* player, Tablero* tab)
{
    int pos;
    for (int i = 0; i < 64; i++)
    {
//        Si las posiciones en X y en Y coinciden se regresa la posicion
        if(tab -> Tablero[i] -> x == player -> x && tab -> Tablero[i] -> y == player -> y)
        {
            pos = i;
            return pos;
        }
    }
} //Se obtiene la posicion de la ficha en el arreglo

void menu()
{
    DrawText("BIENVENIDO", 250, 300, 45, BLACK);
    DrawText("Nuevo juego picale a N", 50, 450, 28, BLACK);
    DrawText("Reanudar juego a R", 500, 450, 28, BLACK);
}// Despliega el menu principal

void isReina(Ficha* player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player == NULL)
        return;
//  Si la ficha se mueve hacia abajo y llega al limite inferior
    if(player -> dir == 0)
    {
        if(player -> y == 750)
        {
            player -> dir = 1;
            tab -> Tablero[pos_arr] -> Reina = 1;
        }

    }
//    Si la ficha se mueve hacia arriba y llegua al limite superior
    if(player -> dir == 1)
    {
        if(player -> y == 50)
        {
            player -> dir = 0;
            tab -> Tablero[pos_arr] -> Reina = 1;
        }

    }

}// Identifica si la ficha se tiene que transformar a reina

//Funcion que sirve para dibujar el tablero y las lineas separadoras de cada ficha
void TableroDisplay(int width,int height)
{
    int y;
    int x;

    //Se dibujan cuadros cafe para llegar a la forma del tablero de damas chinas
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
    //Se dibujan las lineas para separar cada cuadro de diferente color
    for (int i = 0; i < width; i = i + width /8)
        DrawLine(i + width/8, 0, i + width/8, height, BLACK);
    for (int i = 0; i < height; i = i + height/8)
        DrawLine(0, i + height/8, width, i + height/8, BLACK);

}

//Esta funcion ayuda a asiganrle sus datos a cada ficha
void addF(Ficha * ficha,int x, int y, int id, int dir, char col)
{
    Ficha* Current = ficha;

    while(Current -> sig != NULL) //Mientras existan fichas inicializamos los atributos de la estructura ficha usando memoria dinamica
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

//Funcion para inicializar un nuevo tablero donde se guardaran los datos de cada cuadro.
Tablero *Crear_tab()
{
    Tablero* tab = malloc(sizeof(Tablero)); //creamos un nuevo tablero con memoria dinamica

    tab -> size = 64;
    tab -> Tablero = calloc(64, sizeof (cuadro));

    return tab;
}

//Funcion para crear  cuadro con memoria dinamica e inicializar cada uno de sus atributos,util en la funcion Llenar_tab
cuadro* new_cuadro(int x, int y)
{
    cuadro* n = malloc(sizeof (cuadro));
    n -> x = x;
    n -> y = y;
    n -> Disponible = 0;
    n -> Reina = 0;
    return n;
}
// Se inicializan todos los datos de los cuadros de nuestro tablero
void Llenar_tab(Tablero* tab)
{
    int y = 50;
    int x = 50;
    int i = 0;
    while (i < 64)
    {
//       Dentro del for se va iterando por cuadro y se cambian las coordenadas de X y Y
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

// Se llena el apartado de Disponible con 1 o 2 dependiendo de la ficha que lo ocupe
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
//                Si la ficha es negra se le asigna 1
                if(current -> id < 12)
                {
                    tab -> Tablero[i] -> Disponible = 1;
                }
//               Si la ficha es blanca se le asigna 2
                if(current -> id >= 12)
                {
                    tab -> Tablero[i] -> Disponible = 2;
                }

            }
        }
        current = current -> sig;
    }
}

//Esta es una funcion auxiliar para imprimir los datos que hay dentro de la estructura tablero
void display_tab(Tablero* tab)
{
    for(int i = 0; i < 64; i++)
    {
        printf("%d %d %d %d\n", tab -> Tablero[i] -> x, tab -> Tablero[i] -> y, tab -> Tablero[i] -> Disponible, tab -> Tablero[i] -> Reina);
    }
}

//Se crean las fichas dependiendo el parametro
Ficha *Crear_fichas(int C)
{
//    Si C es 1 se le asigna los valores respectivos como fichas negras
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
    }
//    Si C es diferente a 1 entonces se le asignan el valor de las fichas blancas
    else {
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

//Se dibujan las fichas en la ventana de juego
void DibujarFichas(Ficha * fichas, color C, Tablero* tab)
{
    Ficha* Current = fichas -> sig;
    while(Current != NULL)
    {
//        Si la ficha fue comida la posicion cambia para que se dibuje fuera de la ventana
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

//Es una funcion auxiliar para imprimir la informacion del conjunto de fichas
void Display(Ficha * fichas)
{
    Ficha* Current = fichas;
    while (Current != NULL)
    {
        printf("%d, %d, %d, %d\n",Current -> x, Current -> y, Current -> id, Current -> dir);
        Current = Current -> sig;
    }

}

//Detecta a que ficha le esta picando el usuario
Ficha* DetectF(int x, int y,Ficha* ficha)
{
    Ficha* current = ficha -> sig;
    //Recorriendo cada ficha, si alguna coincide en x y en y con la posicion del mouse del usuario reotrnamos la ficha
    while(current != NULL)
    {
        if(current -> x -45 < x && current -> x + 45 > x) //
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
    //Primero obtenemos pa posicion de la ficha seleccionada en el tablero que creamos anteriormente
    int pos_arr = get_pos_arr(player, tab);
    if (dir == 1) //Si el movimiento se realizara a la derecha
    {
        //Dibujamos el circulo en la nueva posicion
        player -> y -= 100; //Dibujamos el circulo en la nueva posicion
        player -> x += 100;
        if(tab -> Tablero[pos_arr] -> Reina == 1) //Si se trata de una reina, cambiamos el atributo de reina al lugar donde se cambio la ficha
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 7] -> Reina = 1;
        }
        //Al lugar que queda vacio al hacer el movimiento le cambiamos su disponibilidad a 0
        tab -> Tablero[pos_arr] -> Disponible = 0;
        //Cambiamos la disponibilidad del cuadro a 2 al lugar donde se cambio la ficha dentro del tablero
        tab -> Tablero[pos_arr - 7] -> Disponible = 2;

    }
    if (dir == 0) //Si el mocimiento sera a la izquierda
    {
        //Dibujamos el circulo en la nueva posicion
        player -> y -= 100;
        player -> x -= 100;
        if(tab -> Tablero[pos_arr] -> Reina == 1) //Si es una
        {
            tab -> Tablero[pos_arr] -> Reina = 0; //El lugar que quedo vacio en el movimiento cambia su atributo de reina a 0
            tab -> Tablero[pos_arr - 9] -> Reina = 1;//El lugar a donde nos movimos cambia reina a 1
        }
        tab -> Tablero[pos_arr] -> Disponible = 0; //La disponibilidad del cuadro que queda vacio cambia a 0
        tab -> Tablero[pos_arr - 9] -> Disponible = 2; //A donde nos movimos cambia a 2
    }

}

void MovBlancasConComida(Ficha *player, int dir, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab); //Obtenemos la posicion de la ficha en el tablero
    if (dir == 1)//Si el movimiento es a la derecha
    {
        //Dibujamos el circulo en la nueva posicion
        player -> y -= 200;
        player -> x += 200;
        if(tab -> Tablero[pos_arr] -> Reina == 1) //Cambiamos el atributo de reina dentro del cuadro del tablero al hacerl el movimiento
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 14] -> Reina = 1;
        }
        //El cuadro que queda vacio cambia su disponibilidad a 0
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr - 14] -> Disponible = 2; //Cambiamos la disponibilidad del cuadro pero tomanndo en cuenta que es un movimiento con comida (doble)
    }
    if (dir == 0) //Si nuestro movimiento es hacia la izquierda
    {
        //Dibujamos el circulo en la nueva posicion
        player -> y -= 200;
        player -> x -= 200;
        if(tab -> Tablero[pos_arr] -> Reina == 1)//Cambiamos atributo de reina
        {
            tab -> Tablero[pos_arr] -> Reina = 0;
            tab -> Tablero[pos_arr - 18] -> Reina = 1;
        }
        //Realizamos el cambio de disponibilidad al hacer el movimiento
        tab -> Tablero[pos_arr] -> Disponible = 0;
        tab -> Tablero[pos_arr - 18] -> Disponible = 2;
    }

}

//Funciona igual que MovBlancasSinComida, pero tratando con las fichas negras
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

//Funciona igual que MovBlancasConComida, pero tratando con las fichas negras
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

//Funcion para eliminar una ficha de nuestro tablero y de la interfaz grafica
void eliminarf(Ficha* ficha, Tablero* tab)
{
    int arr_poss = get_pos_arr(ficha, tab); //Se obtiene la posicion en el tablero para cambiar su diaposicion a 0
    tab -> Tablero[arr_poss] -> Disponible = 0;
    ficha -> vida = 0; //La vida de la ficha se hace 0, y con la funcion DIbujarFichas se dibujara en otro lado no visible
}

//Funcion para eliminar una ficha negra que se encuentra a nuestra derecha
int comerFNegraDerecha(Ficha* player, Ficha* oponente, Tablero* tab)
{
    Ficha* ficha = oponente -> sig; //siguiente para no obtener basura
    //Se obtiene la direccion en el tablero para saber luego si habia una ficha
    int x = player -> x - 100;
    int y = player -> y + 100;
    while(ficha != NULL)
    {
        if(ficha -> x == x && ficha -> y == y) //Si las direcciones coinciden se sale del ciclo
            break;
        ficha = ficha -> sig;
    }
    if(ficha != NULL)
    {
        eliminarf(ficha, tab); //Se elimina la ficha que se comio con la ficha blanca y retirnamos 1
        return 1;
    }
    else
        return 0;
}

//Funcion para comer una ficha negra a la izquierda de nuestra ficha blanca
int comerFNegraIzquierda(Ficha* player, Ficha* oponente, Tablero* tab)
{
    Ficha* ficha = oponente -> sig; //siguiente para no obtener basura
    //Se obtiene, las coordenadas en las que se encontraria la ficha a comer
    int x = player -> x + 100;
    int y = player -> y + 100;
    while(ficha != NULL)
    {
        if(ficha -> x == x && ficha -> y == y) //Si las coordenadas de alguna ficha oponente coinciden se sale del ciclo
            break;
        ficha = ficha -> sig;
    }
    if(ficha != NULL)
    {
        eliminarf(ficha, tab); //Se elimina la ficha que se comio la ficha blanca y se retorna 1
        return 1;
    }
    else
        return 0;
}

//Funciona igual que comerFNegraDerecha, pero estando en las fichas negras para comer blancas
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
        eliminarf(ficha, tab);
        return 1;
    }
    else
        return 0;
}

//Funciona igual que comerFNegraIzquierda pero estando en las negras
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
        eliminarf(ficha, tab);
        return 1;
    }
    else
        return 0;
}

//Detecta si hay fichas enemigas a los lados
int colision(Ficha *player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab); // se consigue la posicion en el arreglo de la ficha
//   Se detecta si es una reina blanca con estas condiciones
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_izq = pos_arr + 7; // Posicion derecha
        int pos_der = pos_arr + 9; // Posicion izquiera
        int band_der = 0; // las banderas se usaran para comprobar si hay fichas a ambos lados
        int band_izq = 0;

//        Si la ficha se encuentra al limite inferior no se evalua nada
        if(player -> y == 750)
            return 0;
//       Si la ficha se encuentra en el limite de la derecha solo se evalua el lado derecho
        if(player -> x == 50)
        {
//            Se evalua si la posicion de la derecha hay algun enemigo o una reina enemiga y se retorna 1 en caso de ser cierto
            if(tab -> Tablero[pos_der] -> Disponible == 1 || (tab ->Tablero[pos_der] -> Disponible == 2 &&
                                                                tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            }
            else
                return 0;
        }
//        Si la ficha se encuentra en el limite de la izquierda solo se evalua el lado izquierdo
        if(player -> x == 750)
        {
//            Se evalua si la posicion de la izquierda hay algun enemigo o una reina enemiga y se retorna 1 en caso de ser cierto
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
//      Si hay colisiones en ambos lados se retorna 3
        if(band_der == 1 && band_izq == 1)
            return 3;
//        Si solo hay a la izquierda se retorna 2
        if(band_izq == 1)
            return 2;
//        Si solo hay a la derecha se retorna 1
        if(band_der == 1)
            return 1;
//        Si no se cumple nada se retorna 0
        return 0;
    }
//    Si la ficha se dirige hacia abajo
    if(player -> dir == 0)
    {
        int pos_izq = pos_arr + 7; // Posicion de la izquierda de la ficha
        int pos_der = pos_arr + 9; // Posicion de la derecha de la ficha
        int band_der = 0;
        int band_izq = 0;
//        Si la ficha esta en el limite inferior no se evalua nada
        if(player -> y == 750)
            return 0;
//        Si la ficha se encuentra en el limite izquierdo solo se evalua la derecha
        if(player -> x == 50)
        {
//            Si hay una ficha enemiga a la derecha o es una reina enemiga se retorna 1 de lo contrario se retorna 0
            if((tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 0) ||
            (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            }
            else
                return 0;
        }
//        Si la ficha esta en el limite derecho
        if(player -> x == 750)
        {
//            Si hay una ficha enemiga a la izquierda o es una reina enemiga se retorna 1 de lo contrario se retorna 0
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
//        Si hay de ambos lados se retorna 3
        if(band_der == 1 && band_izq == 1)
            return 3;
//        Si solo hay del lado izquierdo se retorna 2
        if(band_izq == 1)
            return 2;
//        Si solo hay del lado derecho se retorna 1
        if(band_der == 1)
            return 1;
//        Si no hay ninguna se retorna 0
        return 0;
    }
//    Se deecta si es una reina negra con estas condiciones y funciona igual que la condicion de la reina blanca
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
    //    Si la ficha se dirige hacia arriba con la misma logica que con las que se dirigen abajo
    if(player -> dir == 1)
    {
        int pos_izq = pos_arr - 9;
        int pos_der = pos_arr - 7;
        int band_der = 0;
        int band_izq = 0;
//      Si llega al limite inferior no se evalua
        if(player -> y == 50)
            return 0;
//      Si se encuentra en el limite derecho
        if(player -> x == 50)
        {
            if((tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 0)||
            (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))


            {
                return 1;
            } else
                return 0;
        }
        //      Si se encuentra en el limite izquierdo
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

//Detecta si hay fichas enemigas en los diagonales lejanos
int comidaDisponible(Ficha* player, Tablero* tab)
{
//    Se usa la misma logica que la de colision identificando su direccion y si son reinas
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_der = pos_arr + 18; // Posicion de la derecha lejana
        int pos_izq = pos_arr + 14; // Posicion de la izquierda lejana
        int ban_izq = 0; // Banderas para identificar si hay fichas
        int ban_der = 0;

        // Si la ficha se encuentra en el limite inferior o un cuadro antes no se evalua
        if(player -> y == 650 || player -> y == 750)
            return 0;
        // Si la ficha se encuentra en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
            if(tab -> Tablero[pos_der] -> Disponible == 1 || (tab ->Tablero[pos_der] -> Disponible == 2 &&
                                                              tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        // Si la ficha se encuentra en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
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
        int pos_der = pos_arr + 18; // Posicion de la derecha lejana
        int pos_izq = pos_arr + 14; // Posicion de la izquierda lejana
        int ban_izq = 0; // Banderas para identificar si hay fichas
        int ban_der = 0;
        // Si la ficha se encuentra en el limite inferior o un cuadro antes no se evalua
        if(player -> y == 650 || player -> y == 750)
            return 0;
        // Si la ficha se encuentra en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
            if((tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 0)||
            (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))

            {
                return 1;
            } else
                return 0;
        }
        // Si la ficha se encuentra en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
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
        int pos_der = pos_arr - 14; // Posicion derecha lejana
        int pos_izq = pos_arr - 18; // Posicion izquierda lejana
        int ban_izq = 0; //Banderas para identificar si hay fichas
        int ban_der = 0;

        //Si la ficha esta en el limite superior o un cuadro antes abajo no se evalua
        if(player -> y == 150 || player -> y == 50)
            return 0;
        // Si la ficha se encuentra en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
            if(tab -> Tablero[pos_der] -> Disponible == 2 || (tab ->Tablero[pos_der] -> Disponible == 1 &&
                                                          tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        // Si la ficha se encuentra en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la izquierda
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
        int pos_der = pos_arr - 14;// Posicion de la derecha lejana
        int pos_izq = pos_arr - 18;// Posicion de la izquierda lejana
        int ban_izq = 0;// Banderas para identificar si hay fichas
        int ban_der = 0;

        // Si la ficha se encuentra en el limite superior o un cuadro antes no se evalua
        if(player -> y == 150 || player -> y == 50)
            return 0;
        // Si la ficha se encuentra en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
            if((tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 0)||
            (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        // Si la ficha se encuentra en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Se evalua si hay una ficha enemiga o una reina enemiga a la derecha
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

// Detecta si hay fichas amigas a los lados
int isAmiga(Ficha* player, Tablero* tab)
{
    //Se usa la misma logica de colision analisando la direccion de la ficha y si es reina
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_izq = pos_arr + 7; // Posicion derecha
        int pos_der = pos_arr + 9; // Posicion izquierda
        int band_der = 0; //Banderas para identificar si hay fichas a los lados
        int band_izq = 0;
        //Si la ficha esta en el limite izquierdo solo se evalua la derecha
        if(player -> x == 50)
        {
            //Si hay una reina negra a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 2)
            {
                return 1;
            }
            else
                return 0;
        }
        //Si la ficha esta en el limite derecho se evlaua la izquierda
        if(player -> x == 750)
        {
            //Si hay una reina negra a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 2
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
        int pos_izq = pos_arr + 7;// Posicion izquierda
        int pos_der = pos_arr + 9;// Posicion derecha
        int band_der = 0;//Banderas para identificar si hay fichas a los lados
        int band_izq = 0;
        //Si la ficha esta en el limite inferior no se evalua
        if(player -> y == 750)
            return 0;
        //Si la ficha esta en el limite izquierdo solo se evalua la derecha
        if(player -> x == 50)
        {
            //Si hay una reina negra a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 1 ||
                    (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            }
            else
                return 0;
        }
        //Si la ficha esta en el limite derecho se evlaua la izquierda
        if(player -> x == 750)
        {
            //Si hay una reina negra a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 2
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
        int pos_izq = pos_arr - 9;// Posicion izquierda
        int pos_der = pos_arr - 7;// Posicion derecha
        int band_der = 0;//Banderas para identificar si hay fichas a los lados
        int band_izq = 0;
        //Si la ficha esta en el limite inferior no se evalua
        if(player -> y == 50)
            return 0;
        //Si la ficha esta en el limite izquierdo solo se evalua la derecha
        if(player -> x == 50)
        {
            //Si hay una reina negra a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 1)
            {
                return 1;
            } else
                return 0;
        }
        //Si la ficha esta en el limite derecho se evlaua la izquierda
        if(player -> x == 750)
        {
            //Si hay una reina negra a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 2
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
        int pos_izq = pos_arr - 9;// Posicion izquierda
        int pos_der = pos_arr - 7;// Posicion derecha
        int band_der = 0;//Banderas para identificar si hay fichas a los lados
        int band_izq = 0;
        //Si la ficha esta en el limite izquierdo solo se evalua la derecha
        if(player -> x == 50)
        {
            //Si hay una reina negra a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 2 ||
                    (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        //Si la ficha esta en el limite derecho se evlaua la izquierda
        if(player -> x == 750)
        {
            //Si hay una reina negra a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si hay una ficha contraria se retorna 2
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

// Detecta si hay amigas en las diagonales lejanas
int isAmigalejana(Ficha* player, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    if(player -> dir == 0 && player -> col == 'B')
    {
        int pos_der = pos_arr + 18; //Posicion derecha lejana
        int pos_izq = pos_arr + 14; // Posicion izquierda lejana
        int ban_izq = 0; // Bandera para identificar si hay fichas a los dos lados
        int ban_der = 0;

        // Si se encuentra en el limite inferior o un cuadro antes no se evalua
        if(player -> y == 650 || player -> y == 750)
            return 0;
        // Si esta en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Si se detecta una reina enemiga a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 2)
            {
                return 1;
            } else
                return 0;
        }
        // Si se esta en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Si se detecta una reina enemiga a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 2
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
        int pos_der = pos_arr + 18;//Posicion derecha lejana
        int pos_izq = pos_arr + 14;// Posicion izquierda lejana
        int ban_izq = 0;// Bandera para identificar si hay fichas a los dos lados
        int ban_der = 0;
        // Si se encuentra en el limite inferior o un cuadro antes no se evalua
        if(player -> y == 750 || player -> y == 650)
            return 0;
        // Si esta en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Si se detecta una reina enemiga a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 1 ||
                    (tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        // Si se esta en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Si se detecta una reina enemiga a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 2
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
        int pos_der = pos_arr - 14;//Posicion derecha lejana
        int pos_izq = pos_arr - 18;// Posicion izquierda lejana
        int ban_izq = 0;// Bandera para identificar si hay fichas a los dos lados
        int ban_der = 0;
        // Si se encuentra en el limite superior o un cuadro antes no se evalua
        if(player -> y == 150 || player -> y == 50)
            return 0;
        // Si esta en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Si se detecta una reina enemiga a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 1)
            {
                return 1;
            } else
                return 0;
        }
        // Si se esta en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Si se detecta una reina enemiga a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 1 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 2
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
        int pos_der = pos_arr - 14;//Posicion derecha lejana
        int pos_izq = pos_arr - 18;// Posicion izquierda lejana
        int ban_izq = 0;// Bandera para identificar si hay fichas a los dos lados
        int ban_der = 0;
        // Si se encuentra en el limite superior o un cuadro antes no se evalua
        if(player -> y == 150 || player -> y == 50)
            return 0;
        // Si esta en el limite izquierdo o un cuadro antes solo se evalua la derecha
        if(player -> x == 50 || player -> x == 150)
        {
            //Si se detecta una reina enemiga a la derecha se retorna 0
            if(tab -> Tablero[pos_der] -> Disponible == 2 && tab -> Tablero[pos_der] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 1
            if(tab -> Tablero[pos_der] -> Disponible == 2 ||
                    (tab -> Tablero[pos_der] -> Disponible == 1 && tab -> Tablero[pos_der] -> Reina == 1))
            {
                return 1;
            } else
                return 0;
        }
        // Si se esta en el limite derecho o un cuadro antes solo se evalua la izquierda
        if(player -> x == 650 || player -> x == 750)
        {
            //Si se detecta una reina enemiga a la izquierda se retorna 0
            if(tab -> Tablero[pos_izq] -> Disponible == 2 && tab -> Tablero[pos_izq] -> Reina == 1)
                return 0;
            //Si se detecta una ficha amiga se retorna 2
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

//Detecta si no tenemos enemigos a izquierda y derecha y hace un movimiento, retorna 1 si se hace un movimiento valido, 0 si no.
int SinEnemigos(int x, int y, Ficha* player, Tablero* tab)
{
    int AmigaC = isAmiga(player, tab); //Asignamos el valor de esta funcion a una variable para hacer mas sencilla la lectura del codigo
    if(player -> dir == 0)//Si la ficha va hacia abajo
    {
        if(AmigaC == 0)//Si no tenemos amigas a izquierda y derecha
        {
            //Si el usuario presiona en una casilla a la derecha
            if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 1, tab);//realizamos un movimiento a la derecha sin comida usando esta funcion y retornamos 1
                return 1;
            }
            //Si el usuario presiona en una casilla a la izquierda
            if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 0, tab);//Movemos la ficha a la izquierda y retornamos 1
                return 1;
            }
        }
        if(AmigaC == 1)//Si tenemos una amiga a nuestra derecha
        {
            //Si el usuario presiona a una casilla a la izquierda que no esta ocupada
            if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 0, tab);//Se realiza el movimiento a la izquierda
                return 1;
            }
        }
        if(AmigaC == 2)//Si tenemos una amiga a la izquierda
        {
            //Si el usuario presiona en una casilla a la derecha que no contiene nada
            if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
            {
                MovNegrasSinComida(player, 1, tab);//realizamos un movimiento a la derecha
                return 1;
            }
        }
        if(AmigaC == 3)//al tener amigas a los dos lados retornamos 0 pues no puede haber movimientos
            return 0;
    }
    else//si la ficha va hacia abajo
    {
        if(AmigaC == 0)//Si no tememos amigas a  los lados
        {
            //al presionar en una cadilla a la derecha
            if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y - 145 && y < player -> y -55)
            {
                MovBlancasSinComida(player, 1, tab);//nos movemos a la derecha
                return 1;
            }
            //al presionar en una casilla a la izquierda
            if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y -145 && y < player -> y - 55)
            {
                MovBlancasSinComida(player, 0, tab);//realizamos el movimiento valido a la izquierda
                return 1;
            }
        }

        if(AmigaC == 1)//si tenemos una amiga a la derecha
        {
            //si presionamos en una casilla a la izquierda
            if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y -145 && y < player -> y - 55)
            {
                MovBlancasSinComida(player, 0, tab);//realizamos movimiento a la izquierda
                return 1;
            }
        }

        if(AmigaC == 2)//lo contrario si tenemos una amiga a la izquierda
        {
            if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y - 145 && y < player -> y -55)
            {
                MovBlancasSinComida(player, 1, tab);
                return 1;
            }
        }

        if(AmigaC == 3)//con amigas a los dos lados retornamos 0
            return 0;
    }
}

//Detectamos si hay un enemigo a nuestra derecha
int EnemigoDerecha(int x, int y, Ficha* player, Tablero* tab, Ficha* oponentes)
{
    //hacemos las siguientes asignaciones para hacer mas sencilla la lectura del codigo
    int Comida = comidaDisponible(player, tab);
    int AmigaL = isAmigalejana(player, tab);
    int AmigaC = isAmiga(player, tab);
    if(player -> dir == 0)//si nuestra ficha va hacia abajo
    {
        //si tenemos una ficha oponente o una amiga lejana estorbando para poder comer
        if((Comida == 1 || Comida == 3) || (AmigaL == 1 || AmigaL == 3))
        {
            //si tenemos una amiga a la izquierda
            if(AmigaC == 2)
                return 0;
            if(AmigaC == 0)//si no hay amigas
                //si el usuario presiona una casilla al al izquierda
                if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    MovNegrasSinComida(player, 0, tab);//realizamos el movimiento de una casilla a la izquierda
                    return 1;
                }
        }
        //si no nos estorba ninguna ficha enemiga o amiga para comer a la derecha
        if((Comida == 0 || Comida == 2) && (AmigaL == 0 || AmigaL == 2))
        {
            if(AmigaC == 2)//si tenemos una amiga a la izquierda
            {
                //si el usuario presiona en una casilla valida para comer a la derecha
                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1,tab);//movemos nuestra ficha al lugar donde comio
                    comerFBlancaDerecha(player, oponentes, tab);//usamos esta funcion para eliminar la ficha que fue comida
                    return 1;
                }
            }
            if(AmigaC == 0)//si no teniamos amiga a la izquierda
            {
                //Si se selecciona una casilla valida para mover
                if(x > player -> x - 145 && x < player -> x - 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    //si no nos encontramos en posiciones que pueden obtener informacion basura
                    if(player -> x == 650 || (player -> y == 650))
                    {
                        MovNegrasSinComida(player, 0, tab);//realizamos movimiento de nuestra ficha
                        return 1;
                    } else
                    {
                        //eliminamos la ficha si habia oportunidad de comer algo y se decidio mover para otro lado (por bobo)
                        eliminarf(player, tab);
                        return 1;
                    }
                }
                //si se selecciona una casilla valida para comer
                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    //realizamos movimiento y nos comemos la ficha
                    MovNegrasConComida(player, 1,tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }


        }
    }
    if(player -> dir == 1)//si la direccion de nuestra ficha es hacia arriba
    {
        //si hay enemigas o amigas estorbando para comer
        if((Comida == 1 || Comida == 3) || (AmigaL == 1 || AmigaL == 3))
        {
            if(AmigaC == 2)//movimiento totalmente bloqueado
                return 0;
            if(AmigaC == 0)
            {
                //si no hay amiga a la izquierda y se selecciona la casilla valida
                if(x > player -> x - 145 && x < player -> x - 55 && y > player -> y - 145 && y < player -> y - 55)
                {
                    MovBlancasSinComida(player,0, tab);//realizamos movimiento
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


//detectamos si tenemos un enemigo a la izquierda
int EnemigoIzquierda (int x, int y, Ficha* player, Tablero* tab, Ficha* oponentes)
{
    //asignacion del resultado de estas funciones a estos enteros para hacer codigo mas simple
    int Comida = comidaDisponible(player, tab);
    int AmigaL = isAmigalejana(player, tab);
    int AmigaC = isAmiga(player, tab);

    if(player -> dir == 0)//ficha que va hacia abajo
    {
        //si tenemos amigas o enemigas estorbando para comer
        if((Comida == 2 || Comida == 3) || (AmigaL == 2 || AmigaL == 3))
        {
            //si tenemos el paso totalmente bloqueado
            if(AmigaC == 1)
                return 0;
            //si nos podemos mover a la derecha
            if(AmigaC == 0)
            {
                //si se selecciona una casilla correcta y disponible a la derecha
                if(x < player -> x + 145 && x > player -> x + 55 && y < player -> y + 145 && y > player -> y + 55)
                {
                    MovNegrasSinComida(player, 1, tab);//nos movemos a la derecha sin comer nada
                    return 1;
                }
            }
        }
        //si no nos estorba ninguna amiga lejana o alguna enemiga
        if((Comida == 1 || Comida == 0) && (AmigaL == 1 || AmigaL == 0))
        {
            //si a la derecha nos estorba una amiga
            if(AmigaC == 1)
            {
                //si seleccionamos una casilla valida para comer a la izquierda
                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    //nos movemos a la izquierda y eliminamos la ficha oponente
                    MovNegrasConComida(player,0,tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 2;
                }
            }
            //si no tetemos amigas estorbando a la derecha
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
                    if(player -> x == 150 || player -> y == 650)//solo si nos encontramos en lugares donde se podria tomar basura si verificamos posiciones lejanas
                    {
                        MovNegrasSinComida(player, 1, tab);
                        return 1;
                    } else
                    {
                        //se elimina la ficha del jugador en turno si tuvo oportunidad de comer y no lo hizo
                        eliminarf(player, tab);
                        return 1;
                    }
                }

            }
        }
    }
    if(player -> dir == 1)//si nuestra ficha va hacia arriba
    {
        //si nos estorba alguna amiga lejana o una enemiga para comer a la izquierda
        if((Comida == 2 || Comida == 3) || (AmigaL == 2 || AmigaL == 3))
        {
            //si tenemos el paso totalmente bloqueado
            if(AmigaC == 1)
                return 0;
            //si tenemos oportunidad de movernos a la derecha y seleccionamos la casilla correcta
            if(AmigaC == 0)
            {
                if(x < player -> x + 145 && x > player -> x + 55 && y > player -> y -145 && y < player -> y - 55)
                {
                    MovBlancasSinComida(player, 1, tab);//nos movemos a la derecha sin comer
                    return 1;
                }
            }
        }
        //si ninguna amiga lejana o enemiga nos estorba para comer a la izquierda
        if((Comida == 1 || Comida == 0) && (AmigaL == 1 || AmigaL == 0))
        {
            //si una amiga nos tapa el paso a la derecha
            if(AmigaC == 1)
            {
                //si se selecciona la casilla correcta a la izquierda para comer
                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    //nos movemos y nos comemos la ficha oponente
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
            //si no tenemos una amiga a la derecha tapando nuestro paso
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
                    if(player -> x == 150 || player -> y == 150)//solo si nos encontramos en posiciones que pueden tomar basura
                    {
                        MovBlancasSinComida(player, 1, tab);//nos movemos sin comer
                        return 1;
                    }else
                    {
                        //si hubo oportunidad de comer y no se hizo, se pierde la ficha del jugador en turno por bobo.
                        eliminarf(player, tab);
                        return 1;
                    }
                }
            }
        }
    }
}

//detecta si se puede comer a la izquierda y derecha
int EnemigoSupremo(int x, int y, Ficha* player, Tablero* tab, Ficha* oponentes)
{
    int Comida = comidaDisponible(player, tab);
    int AmigaL = isAmigalejana(player, tab);

    if(player -> dir == 0)//si la ficha va hacia abajo
    {
        //si tenemos el paso bloqueado para comer de cualquier direccion
        if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
            return 0;

        //si podemos comer de los dos lados
        if(Comida == 0 && AmigaL == 0)
        {
            //si seleccionamos una casilla valida a la derecha para comer
            if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
            {
                //movemos nuestra ficha y nos comemos la oponente
                MovNegrasConComida(player, 1, tab);
                comerFBlancaDerecha(player, oponentes, tab);
                return 1;
            }
            //movimiento para comer a la izquierda
            if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
            {
                MovNegrasConComida(player, 0, tab);
                comerFBlancaIzquierda(player, oponentes, tab);
                return 1;
            }
        }
        //si tenemos bloqueado el lado derecho para comer por una ficha oponente
        if(Comida == 1)
        {
            //si ninguna amiga nos estorba a la izquierda
            if(AmigaL == 0)
            {
                //movimiento para comer a la izquierda
                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 0, tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        //si del lado derecho no se puede comer debido a una amiga
        if(AmigaL == 1)
        {
            if(Comida == 0)
            {
                //movimiento valida para comer a la izquierda
                if(x > player -> x - 245 && x < player -> x - 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 0, tab);
                    comerFBlancaIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        //si a la izquierda nos estorba una ficha oponente para comer
        if(Comida == 2)
        {
            if(AmigaL == 0)
            {
                //movimiento valido para comer a la derecha
                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1, tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }
        //si a la izquierda nos estorba una amiga lejana para comer
        if(AmigaL == 2)
        {
            if(Comida == 0)
            {
                //movimiento valido para comer a la derecha
                if(x < player -> x + 245 && x > player -> x + 155 && y < player -> y + 245 && y > player -> y + 155)
                {
                    MovNegrasConComida(player, 1, tab);
                    comerFBlancaDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }

    }
    //si nuestra ficha va hacia arriba
    if(player -> dir ==1)
    {
        //al tener bloqueado todo para comer
        if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
            return 0;
        //al poder comer todo
        if(Comida == 0 || AmigaL == 0)
        {
            //movimiento valido para comer a la derecha si se selecciona la casilla
            if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y - 155)
            {
                MovBlancasConComida(player, 1, tab);
                comerFNegraDerecha(player, oponentes, tab);
                return 1;
            }
            //movimiento valido para comer a la izquierda si se selecciona la casilla
            if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
            {
                MovBlancasConComida(player, 0, tab);
                comerFNegraIzquierda(player, oponentes, tab);
                return 1;
            }
        }
        //si a la derecha nos estorba un oponente para comer
        if(Comida == 1)
        {
            if(AmigaL == 0)
            {
                //movimiento valido para comer a la izquierda
                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        //si nos estorba una amiga lejana para comer a la derecha
        if(AmigaL == 1)
        {
            if(Comida == 0)
            {
                //movimiento valido para comer a la izquierda
                if(x > player -> x - 245 && x < player -> x - 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 0, tab);
                    comerFNegraIzquierda(player, oponentes, tab);
                    return 1;
                }
            }
        }
        //si a la izquierda nos estorba una oponente para comer
        if(Comida == 2)
        {
            if(AmigaL == 0)
            {
                //movimiento valido para comer al a derecha
                if(x < player -> x + 245 && x > player -> x + 155 && y > player -> y - 245 && y < player -> y - 155)
                {
                    MovBlancasConComida(player, 1, tab);
                    comerFNegraDerecha(player, oponentes, tab);
                    return 1;
                }
            }
        }
        //si al al izquierda nos estorba una amiga lejana para comer
        if(AmigaL == 2)
        {
            if(Comida == 0)
            {
                //movimiento valido para comer a la derecha
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

//Se evalua si el movimiento realizado sea valido
int MovimientoValido(int x, int y, Ficha *player, Ficha* oponentes, Tablero* tab)
{
    int pos_arr = get_pos_arr(player, tab);
    int Mov = 0;
    int fichas_eliminadas = 0;
//    Si la ficha se mueve hacia abajo
    if(player -> dir == 0)
    {
//        Si np hay enemigos a los lados
        if(colision(player, tab) == 0)
        {
//            Se mueve bajo las restricciones de la funcion
            Mov = SinEnemigos(x, y, player, tab);
            //Si se hizo correctamente el movimiento se retorna 1
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
//        Hay un oponente a la derecha
        if(colision(player, tab) == 1)
        {
//            Se mueve bajo las restricciones de la funcion
            Mov = EnemigoDerecha(x, y, player, tab, oponentes);
            //Si se hizo correctamente el movimiento se retorna 1
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
//        Hay un oponente a la izquierda
        if(colision(player, tab) == 2)
        {
            //Se mueve bajo las restricciones de la funcion
            Mov = EnemigoIzquierda(x, y, player, tab, oponentes);
            //Si se hizo correctamente el movimiento se retorna 1
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
//        Hay oponentes en ambos lados
        if(colision(player, tab) == 3)
        {
            //Se mueve bajo las restricciones de la funcion
            Mov = EnemigoSupremo(x, y, player, tab, oponentes);
//            Si se hizo correctamente el movimiento se retorna 1
            if(Mov == 1)
                return 1;
            else
                return 0;
        }
    }
//    Si la ficha se mueve hacia arriba
    if(player -> dir == 1)
    {
//        Se hace lo mismo que cuando la ficha se mueve hacia abajo
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

//Funcion que dibuja los circulos rojos
void CirculosR(Ficha *player, Tablero* tab)
{
    int Lados = colision(player, tab); //Si hay fichas oponentes a los lados
    int Comida = comidaDisponible(player, tab); // Si hay fichas oponentes lejanas
    int AmigaC = isAmiga(player, tab); // Si hay fichas amigas a los lados
    int AmigaL = isAmigalejana(player, tab); // Si hay fichas amigas lejanas
    //Si la ficha se mueve hacia arriba
    if(player -> dir == 0)
    {
        //Si no hay oponentes a los lados
        if(Lados == 0)
        {
            // Si no hay amigas a los lados dibujas a ambos lados
            if(AmigaC == 0)
            {
                DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
                DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
            }
            // Si hay una amiga a la derecha dibujas a la izquierda
            if(AmigaC == 1)
            {
                DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
            }
            //Si hay una amiga a la izquierda
            if(AmigaC == 2)
            {
                DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
            }
            //Si hay amigas en ambos lados no dibujas
            if(AmigaC == 3)
                return;
        }
        // Si hay un oponente a la derecha
        if(Lados == 1)
        {
            // Si se puede comer comer la ficha
            if((AmigaL == 0 || AmigaL == 2) && (Comida == 0 || Comida == 2))
            {
                //Si hay una amiga tapando el lado izquierdo solo dibujar a la derecha
                if(AmigaC == 2)
                {
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                }
                //Si esta dispobible la izquierda dibujas en la izquierda y en la derecha
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                    DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
                }
            }
            //Si no se puede comer
            if((AmigaL == 1 || AmigaL == 3) || (Comida == 1 || Comida == 3))
            {
                //Si no tienes amigas estorbando dibujar a la izquierda
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x - 100, player -> y + 100 , 45, RED);
                }
                // Si tienes amigas estorbando a la izquierda no dibujas nada
                if(AmigaC == 2)
                    return;
            }
        }
        //Si tienes un oponente a la izquierda
        if(Lados == 2)
        {
            //Si te puedes comer la ficha
            if((AmigaL == 0 || AmigaL == 1) && (Comida == 0 || Comida == 1))
            {
                //Si tiens tapado el espacio de la derecha dibujar a la izquierda
                if(AmigaC == 1)
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                //Si tienes el espacio de la derecha dibujas a ambos lados
                if(AmigaC == 0)
                {
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                    DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
                }
            }
            //No se puede comer la ficha
            if((AmigaL == 2 || AmigaL == 3) || (Comida == 2 || Comida == 3))
            {
                //Si se tiene disponible el espacio de la derecha dibujar a la derecha
                if(AmigaC == 0)
                    DrawCircle(player -> x + 100, player -> y + 100 , 45, RED);
                //Si no se tiene disponible no dibujar
                if(AmigaC == 1)
                    return;
            }
        }
        // Si tienes oponentes a ambos lados
        if(Lados == 3)
        {
            //Si se pueden comer las dos fichas dibujar a ambos lados
            if(AmigaL == 0 && Comida == 0)
            {
                DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
            }
            //Si no se pued comer ninguna no dibujar
            if((Comida == 3 || AmigaL == 3) || (Comida == 1 && AmigaL == 2) || (Comida == 2 && AmigaL == 1))
                return;
            //Si tienes una ficha oponente tapandote a la derecha
            if(Comida == 1)
            {
                //Si no te tapa una amiga a la izquierda dibujar a la izquierda de lo contrario no dibujar
                if(AmigaL == 0)
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                else
                    return;
            }
            //Si tienes una ficha amiga tapandote a la derecha
            if(AmigaL == 1)
            {
                //Si no te tapa un oponente a la izquierda dibujar a la izquierda de lo contrario no dibujar
                if(Comida == 0)
                    DrawCircle(player -> x - 200, player -> y + 200, 45, RED);
                else
                    return;
            }
            //Si tienes una ficha oponente tapandote a la izquierda
            if(Comida == 2)
            {
                //Si no te tapa una amiga a la derecha dibujar a la derecha de lo contrario no dibujar
                if(AmigaL == 0)
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                else
                    return;
            }
            //Si tienes una ficha amiga tapandote a la izquierda
            if(AmigaL == 2)
            {
                //Si no te tapa un oponente a la derecha dibujar a la derecha de lo contrario no dibujar
                if(Comida == 0)
                    DrawCircle(player -> x + 200, player -> y + 200, 45, RED);
                else
                    return;
            }
        }
    }
    //Si la ficha se mueve hacia arriba
    if(player -> dir == 1)
    {
        //Se usa lo mismo que si una ficha se mueve haca abajo
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

// Funcion para obtener al ganador
int getWinner(Ficha* Blancas, Ficha* Negras, Tablero* tab)
{
    //Listas enlazadas de las fichas negras y blancas
    Ficha* CurrentB = Blancas -> sig ? Blancas -> sig: Blancas;
    Ficha *CurrentN = Negras -> sig ? Negras -> sig: Negras;

    //Se evitan valores NULL
    if(CurrentN == NULL || CurrentB == NULL)
        return 0;
    //Contadores para las fichas
    int contB = 0;
    int contN = 0;

    while (CurrentN != NULL) // Se recorre la lista
    {
//        Si la ficha se la copmieron se suma
        if(CurrentN -> vida == 0)
            contN++;
        CurrentN = CurrentN -> sig;

    }
    while (CurrentB != NULL)
    {
        //Si la ficha se la copmieron se suma
        if(CurrentB -> vida == 0)
            contB++;
        CurrentB = CurrentB -> sig;
    }
    //Si todas las fichas blancas han sido comidas ganan las negras y se retorna 1
    if(contB == 12)
        return 1;
    //Si todas las fichas negras han sido comidas ganan las blancas y se retorna 2
    if(contN == 12)
        return 2;
    //Si no ha ganado nadie se retorna 0
    return 0;
}

// Funcion para guardar el juego
void saveGame(Ficha* Blancas, Ficha* Negras, int turno, Tablero* tab)
{
    //Apuntadores a las listas enlazadas de las fichas
    Ficha* currentB = Blancas -> sig ? Blancas -> sig: Blancas;
    Ficha* currentN = Negras -> sig ? Negras -> sig: Negras;

    //Arreglos para guardar los datos de las estructuras
    int x[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int y[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int id[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int vida[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int col [24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int dir[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int trn [1] = {0};
    int Dis_tab[64];
    int x_tab[64];
    int y_tab[64];
    int reina[64];

    FILE* save = fopen("savegame.txt", "w");
    if(save)
    {
        for(int i = 0; i < 12; i++)
        {
            //Se guardan los datos de las negras
            if(currentN != NULL)
            {
                x[i] = currentN -> x;
                y[i] = currentN -> y;
                id[i] = currentN -> id;
                vida[i] = currentN -> vida;
                dir[i] = currentN -> dir;
                col[i] = 1;
            }
            //Si es NULL se guarda como 0
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
//            Se inicializan valores de las blancas
            if(currentB != NULL)
            {
                x[i] = currentB -> x;
                y[i] = currentB -> y;
                id[i] = currentB -> id;
                vida[i] = currentB -> vida;
                dir[i] = currentB -> dir;
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
//       Se guardan valores del tablero
        for(int i = 0; i < 64; i++)
        {
            Dis_tab[i] = tab -> Tablero[i] -> Disponible;
            x_tab[i] = tab -> Tablero[i] -> x;
            y_tab[i] = tab -> Tablero[i] -> y;
            reina[i] = tab -> Tablero[i] -> Reina;
        }
//       Se escriben en el archivo
        fwrite(x, sizeof (x), 1,save);
        fwrite(y, sizeof (y), 1,save);
        fwrite(id, sizeof (id), 1,save);
        fwrite(vida, sizeof (vida), 1,save);
        fwrite(col, sizeof (col), 1,save);
        fwrite(dir, sizeof(dir), 1, save);
        fwrite(trn, sizeof(trn), 1, save);
        fwrite(Dis_tab, sizeof(Dis_tab), 1, save);
        fwrite(x_tab, sizeof(x_tab), 1, save);
        fwrite(y_tab, sizeof(y_tab), 1, save);
        fwrite(reina, sizeof(reina), 1, save);

    }
    fclose(save);
    exit(0);
}
//Funcion para cargar juego guardado
void loadGame(Ficha* Blancas, Ficha* Negras, int* turno, Tablero* tab)
{
    //Apuntadores a las listas enlazadas de las fichas
    Ficha* currentN = Negras -> sig;
    Ficha* CurrentB = Blancas -> sig;
    FILE* save = fopen("savegame.txt", "r");

    if(save != NULL)
    {
        //Se crean arreglos para recuperar los datos de las estructuras
        int x[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int y[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int id[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int vida[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int col [24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int dir[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int trn [1] = {0};
        int Dis_tab[64];
        int x_tab[64];
        int y_tab[64];
        int reina[64];

        fread(x,sizeof(x), 1, save);
        fread(y, sizeof(y), 1, save);
        fread(id, sizeof (id), 1,save);
        fread(vida,sizeof(vida), 1, save);
        fread(col, sizeof(col), 1, save);
        fread(dir, sizeof(dir), 1, save);
        fread(trn, sizeof(trn), 1, save);
        fread(Dis_tab, sizeof(Dis_tab), 1, save);
        fread(x_tab, sizeof(x_tab), 1, save);
        fread(y_tab, sizeof(y_tab), 1, save);
        fread(reina, sizeof(reina), 1, save);
        fclose(save);

        for(int i = 0; i < 12; i++)
        {
            //Se le asignan los datos a las fichas negras
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
            //Se le asignan los datos a las fichas blancas
            if(CurrentB != NULL)
            {
                CurrentB -> x = x[i];
                CurrentB -> y = y[i];
                CurrentB -> id = id[i];
                CurrentB -> vida = vida[i];
                CurrentB -> col = 'B';
            }
            CurrentB = CurrentB -> sig;
        }
        //Se le asigna el turno
        turno = &trn[0];
        //Se le asignan los datos al tablero
        for(int i = 0; i  < 64; i++)
        {
            tab -> Tablero[i] -> Disponible = Dis_tab[i];
            tab -> Tablero[i] -> x = x_tab[i];
            tab -> Tablero[i] -> y = y_tab[i];
            tab -> Tablero[i] -> Reina = reina[i];
        }
    } else
    {
        DrawText("No se guardo nada anteriormente", 200, 400, 36, RED);
    }// Si no se guardo ningun archivo anteriormente
}