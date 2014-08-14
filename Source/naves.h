#include "sprite.h" 


#define WIDTH 640
#define HEIGHT 480
#define BBP 24
#define MAXBALAS 3

//Estados
#define INICIALIZAR 0
#define JUGAR 1
#define SALIR 2

class Naves
{

public:
	int loop();
	static Naves Naves_Static;

	Naves();
	void finalize();

private:
	SDL_Surface *screen; // Creamos nuestra superficie principal
	CFrame fnave; // Cargamos un frame para cada nave, la de nuestro jugador y la de los enemigos
	CFrame fmalo;
	CFrame flaser; // Tambien nos hará falta un frame para el laser
	CSprite *nave; // Creamos un sprite para nuestro jugador...
	CSprite *malo1, *malo2; // ...y varios para nuestros enemigos. Usaremos solo 2 en este ejemplo
	CSprite *laser;
	SDL_Rect rectangulo;
	int frametime, vel; // Nos servirá para controlar los fps y la segunda, la velocidad enemiga
	int w1, w2, dir1, dir2; // Estas variables nos ayudarán a la hora de mover las naves enemigas
	int estado;

	struct nave{
		// Esta esturctura contiene las coordenadas de cada nave
		int x;
		int y;
	};

	// Creamos una nueva estructura por cada nave que vayamos a utilizar
	struct nave jugador;
	struct nave enemigo;
	struct nave enemigo2;

	struct shot{
		// Esta estructura contendrá las coordenadas de los disparos...
		int x, y;
	} bala[MAXBALAS+1]; // ...que como podemos ver, serán un array de balas.

	void draw_scene(SDL_Surface *screen);
	void Naves::update_Scene();
	void move_shot();
	void move_enemies();
	void draw_shot();
	void initialize();
	
	int init_sprites();

};