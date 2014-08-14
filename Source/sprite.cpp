#include "SDL.h"
#include "SDL_image.h"// Ahora podemos cargar BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA y PNG /*http://lazyfoo.net/SDL_tutorials/lesson03/index.php*/
#include "sprite.h"

//Antigua forma de cargar, pero no optimizada para la profundidad de colores
void CFrame::load(char *path){

    img = SDL_LoadBMP(path); // Carga la imagen indicada en path...
    SDL_SetColorKey(img, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(img -> format, 255, 0, 0)); // ...y le asigna como color transparente el rojo
    img =SDL_DisplayFormat(img); // Luego convierte la imagen al formato nativo de SDL
}

void CFrame::load_OptimizedImage(std::string ruta)
	{
		SDL_Surface* temp_img = NULL;
		SDL_Surface* optimizedImage = NULL;

		temp_img = IMG_Load( ruta.c_str() );//SDL_LoadBMP( ruta.c_str() ); Ahora podemos cargar BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA y PNG 

		if( temp_img != NULL ) { 
			//hacemos una imagen optimizada segun la profundidad de bits
			optimizedImage = SDL_DisplayFormat( temp_img );
			//Liberamos imagen temporal
			SDL_FreeSurface( temp_img ); 
		}

		if( optimizedImage != NULL ) { 
			//Damos de alta el valor del color a transparentar
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0x00, 0x00 );
			//Ahora le decimos que ese color lo transparente
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); }
				
		img = optimizedImage;

	}

void CFrame::unload(){

    SDL_FreeSurface(img); // Libera la superficie imagen
}

CSprite::CSprite(int nc){

    // El contructor crea un nuevo sprite que consiste en un array de tipo CFrame, con un número de celdas igual al parámetro que se le pase
    sprite = new CFrame[nc];
    nframes = nc; // El número total de cuadros se iguala al número de elementos del array
    cont = 0; // Así mismo, el número de cuadros ocupados en este punto es 0
	state = 0;
}

CSprite::CSprite(){

    // Es el mismo caso anterior pero aplicado al caso de que no se pase una cantidad mayor a 1 como parámetro. Es un sprite de un solo cuadro
    int nc = 1;
    sprite = new CFrame[nc];
    nframes = nc;
    cont = 0;
}

void CSprite::finalize(){

    // Utilizando un bucle for elimina todos los cuadros del sprite
    int i;
    for(i = 0; i <= nframes-1; i++){ // Al empezar por el 0, la verificación será hasta el número de cuadros menos 1, ya que si se añaden 9 cuadros, el ultimo será el número 8
        sprite[i].unload(); // Por cada elemento del array de tipo CFrame se llama a su función unload()
    }
}

void CSprite::addframe(CFrame frame){

    // Verificando que el número de cuadros ocupados no sea mayor al total...
    if(cont < nframes){
        sprite[cont] = frame; // ...se añade el cuadro al elemento correspondiente en el array...
        cont++; // ...para luego aumentar en uno el número de cuadros ocupados.
    }
}

void CSprite::selframe(int nc){

    // Si el número de cuadro que queremos marcar como activo no rebasa el número de cuadros ocupados...
    if(nc <= cont){
        state = nc; // ...dicho elemento del array se marca como activo.
    }
}

void CSprite::draw(SDL_Surface *superficie){

    SDL_Rect dest; // Creamos un rectángulo de destino...
    
    dest.x = posx; // ...y le damos coordenadas iniciales.
    dest.y = posy;
    
    SDL_BlitSurface(sprite[state].img, NULL, superficie, &dest); // Luego, dibujamos la imagen del cuadro activo sobre la superficie destino.
}

int CSprite::colision(CSprite sp){

    // Mediante esta y las siguientes 11 líneas, obtenemos la posición y tamaño de los dos sprites en colisión
    int w1, h1, w2, h2, x1, x2, y1, y2;
    
    w1 = getw();
    h1 = geth();
    x1 = getx();
    y1 = gety();
    
    w2 = sp.getw();
    h2 = sp.geth();
    x2 = sp.getx();
    y2 = sp.gety();
    
    // Verificamos si las dos figuras se solapan
    if(((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1)){
        return TRUE; // Si existe colisión se devuelve el valor TRUE
    } else {
        return FALSE; // Sino, todo lo contrario.
    }
}
