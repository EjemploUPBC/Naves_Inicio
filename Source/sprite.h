#ifndef CSPRITE_H_
#define CSPRITE_H_
#include "SDL.h"
#include <stdexcept>
#define TRUE 1
#define FALSE 0
// CFrame representa un frame independiente de un sprite.
class CFrame {
public:
   SDL_Surface *img; // img contendrá la imagen del frame
   void load(char *path); // La ruta hasta la imagen a cargar
   void CFrame::load_OptimizedImage(std::string ruta); // cargado optimizado de imagen 
   void unload(); // Liberará la superficie img
};
// La clase CSprite está formada por un array de frames;
class CSprite {
private:
   int posx,posy; // Coordenadas del sprite
   int state; // Esta variable marcará al frame activo
   int nframes; // Indica el número de cuadros máximos del sprite
   int cont; // Indica el número de cuadros ocupados del sprite
public:
   CFrame *sprite; // El array de frames que compondrá el sprite
   CSprite(int nf); // Este y el siguiente son los constructores
   CSprite();
   void finalize(); // Llamará a la función unload() de la clase CFrame por cada cuadro ocupado
   void addframe(CFrame frame); // Agregará un cuadro nuevo al sprite
   void selframe(int nf); // Marcará como activo el frame indicado
   int frames() {return cont;} // Devuelve el número de frames ocupados en el sprite
   void setx(int x) {posx=x;} // Este y los 7 siguientes nos devuelven valores referentes a las coordenadas del sprite
   void sety(int y) {posy=y;}
   void addx(int c) {posx+=c;}
   void addy(int c) {posy+=c;}
   int getx() {return posx;}
   int gety() {return posy;}
   int getw() {return sprite[state].img->w;} // Estos dos nos devuelven el ancho y el alto de la imagen del cuadro activo
   int geth() {return sprite[state].img->h;}
   void draw(SDL_Surface *superficie); // Dibuja el sprite sobre la superficie pasada como parámetro
   int colision(CSprite sp); // Detecta una colisión entre el sprite que lo llama y el sprite que es pasado como parámetro
};
#endif /* CSPRITE_H_ */

