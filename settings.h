#ifndef PROYECTOPROGRA_SETTINGS_H
#define PROYECTOPROGRA_SETTINGS_H

typedef struct Color color;
typedef struct ficha Ficha;

void TableroDisplay(int width,int height);
Ficha *Crear_fichas(int C);
void DibujarFichas(Ficha * fichas, color C);
void Display(Ficha * fichas);
void addF(Ficha * ficha,int x, int y, int id);
Ficha* DetectF(int x, int y,Ficha* ficha);
void CirculosR(Ficha *player, Ficha* oponentes, Ficha* amigas);
int PosDiagonalB(int x, int y, Ficha* selected, Ficha* amigas, Ficha* oponentes);
int PosDiagonalN(int x, int y, Ficha* selected, Ficha* amigas, Ficha* oponentes);
int comerf(Ficha* player, Ficha* fichas, int x, int y);
int colision(Ficha* player, Ficha* fichas);
void add(Ficha* stack, Ficha* fichas);
void MovimientoValido(int x, int y, Ficha *player, Ficha* oponentes, Ficha* amigas);
#endif //PROYECTOPROGRA_SETTINGS_H
