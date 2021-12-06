#ifndef PROYECTOPROGRA_SETTINGS_H
#define PROYECTOPROGRA_SETTINGS_H

typedef struct Color color;
typedef struct ficha Ficha;
typedef struct tablero Tablero;


void TableroDisplay(int width,int height);
Ficha *Crear_fichas(int C);
void DibujarFichas(Ficha * fichas, color C);
void Display(Ficha * fichas);
Ficha* DetectF(int x, int y,Ficha* ficha);
void CirculosR(Ficha *player, Tablero* tab);
int MovimientoValido(int x, int y, Ficha *player, Ficha* oponentes, Tablero* tab);
int getWinner(Ficha* Blancas, Ficha* Negras, Tablero* tab);
Tablero *Crear_tab();
void Llenar_tab(Tablero* tab);
void Llenar_disponibles(Tablero* tab, Ficha* fichas);
void display_tab(Tablero* tab);
#endif //PROYECTOPROGRA_SETTINGS_H