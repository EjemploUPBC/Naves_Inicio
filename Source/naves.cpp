#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
//#include "./libs/csprite.h" 
#include "naves.h"

Naves::Naves(){
	nave = NULL;
	malo1 = NULL;
	laser = NULL;
	nave = new CSprite(1); // Creamos un sprite para nuestro jugador...
	malo1 = new CSprite(1);
	malo2 = new CSprite(1); // ...y varios para nuestros enemigos. Usaremos solo 2 en este ejemplo
	laser = new CSprite(1);
	estado = 0;
	vel = 5;
	w1 = w2 =0; dir1 = dir2 = 1; // Estas variables nos ayudarán a la hora de mover las naves enemigas
	// Creamos una nueva estructura por cada nave que vayamos a utilizar
	struct nave jugador;
	struct nave enemigo;
	struct nave enemigo2;
}

void Naves::update_Scene()
{
	

    // Usando las estructuras declaradas antes, establecemos coordenadas iniciales a las naves...
    nave->setx(jugador.x);
    nave->sety(jugador.y);

	 // Repetimos la operación por cada nave enemiga
    malo1->setx(enemigo.x);
    malo1->sety(enemigo.y);
	malo2->setx(enemigo2.x);
    malo2->sety(enemigo2.y);
	
	// Recorremos el array de disparos dibujando todos aquellos que esten activos
    for(int i = 0; i <= MAXBALAS; i++){
        if(bala[i].x != 0){
            laser->setx(bala[i].x);
            laser->sety(bala[i].y);            
        }
    }

	// Actualizamos enemigos y disparos, y dibujamos la escena.
	move_enemies();
	move_shot();

	// Si algún disparo colisiona con cualquiera de los dos enemigos...
    if(malo1->colision(*laser) == TRUE || malo2->colision(*laser) == TRUE){
        //done = 1; // ...salimos del juego.
    }


}

// Esta función será la encargada de dibujar toda la escena en pantalla
void Naves::draw_scene(SDL_Surface *screen){
    
    //int i;
    
    // Borramos (pintamos de negro) toda la pantalla
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen -> format, 0, 0, 0));
    

    nave->draw(screen); // dibujamos las naves en pantalla
    
    //Repetimos la operación por cada nave enemiga
    malo1->draw(screen);
    malo2->draw(screen);
    
    // Recorremos el array de disparos dibujando todos aquellos que esten activos
    for(int i = 0; i <= MAXBALAS; i++){
        if(bala[i].x != 0){
            laser->draw(screen);
        }
    }
    
    // Dibujamos la escena al completo.
    SDL_Flip(screen);
}

// Con esta función movemos las balas activas
void Naves::move_shot(){
    int i;
    
    // Recorremos el array de balas buscando las activas
    for(i=0; i <= MAXBALAS; i++){
        if(bala[i].x != 0){ // Si la coordenada X es distinta de 0, se considera una bala activa...
            bala[i].y -= 5; // ...que se mueve verticalmente.
        }
        if(bala[i].y < 0){ // Si la bala se sale de la pantalla...
            bala[i].x = 0; // ...la desactivamos
        }
    }
}

// Esta función movera automáticamente a los enemigos
void Naves::move_enemies(){
    
    w1 = malo1->getw();
    w2 = malo2->getw();
    
    enemigo.x -= vel*dir1; // Asignamos las velocidades horizontales de ambas naves. La variable dir1 o dir2 indica la dirección del movimiento
    enemigo2.x += vel*dir2*2;
    
    // Comprobamos si un enemigo toca un borde de la pantalla...
    if(enemigo.x < 0){ // ...en caso de golpear el borde izquierdo...
        enemigo.x = 0;
        dir1 *= -1; // ...cambiamos la dirección en la que se moverá.
    }else if(enemigo.x + w1 >= WIDTH){ // Seguimos la misma mecánica si chocase contra el borde derecho.
        enemigo.x = (screen->w - w1) - 1;
        dir1 *= -1;
    }
    
    // Como en el caso anterior, comprobamos los "rebotes" contra la pantalla del segundo enemigo
    if(enemigo2.x < 0){
        enemigo2.x = 0;
        dir2 *= -1;
    } else if(enemigo2.x + w2 >= WIDTH){
        enemigo2.x = (screen->w -w2) -1;
        dir2 *= -1;
    }
    
}

void Naves::draw_shot(){
    int libre = -1;
    
    // Recorremos el array en busca de una bala disponible
    for(int i = 0; i <= MAXBALAS; i++){
        if(bala[i].x == 0){ // Cuando la encontramos...
            libre = i; // ...lo indicamos con la variable "libre"
        }
    }
    
    // Si, efectivamente, encontramos una bala diponible...
    if(libre >= 0){
        bala[libre].x = nave->getx() + 32; // ...la posicionamos inicialmente frente a nuestra nave 
        bala[libre].y = nave->gety() - 64; // Sumando la mitad del ancho y restando el alto, nos aseguramos de que el disparo quede centrado y frente a la nave
    }
}

// La función que tenemos a continuación se encarga de dar valores iniciales a todos los componentes del juego
void Naves::initialize(){

    int i;    
    
    jugador.x = 400; // Modificamos los valores de las estructuras...
    jugador.y = 400; // ...de las tres naves, dándoles un valor inicial...
    enemigo.x = 100; // ...distinto para cada una.
    enemigo.y = 100;
    enemigo2.x = 250;
    enemigo2.y = 100;
    
    // Recorremos el array de balas...
    for(i = 0; i <= MAXBALAS; i++){
        bala[i].x = 0; // ...y ponemos todas a 0, es decir, desactivadas.
        bala[i].y = 0;
    }
}

// Con esta función eliminaremos todos los elementos en pantalla
void Naves::finalize(){
    nave->finalize();
    malo1->finalize(); // Ojo aquí, finalizamos un solo enemigo, pues esto liberará el frame que hemos usado para ambos enemigos, así que no hace falta finalizar también el segundo
    laser->finalize();
}

// Cargamos los frames y los incorporamos a sus respectivos sprites
int Naves::init_sprites(){

    fnave.load("img/minave.bmp"); // Cargamos el frame de nuestra nave...
	//fnave.load_OptimizedImage("img/minave.bmp");// forma optimizada de cargar
    nave->addframe(fnave); // ...y lo añadimos a su sprite.
    
    // Repetimos la operación para los enemigos y para los disparos.
    fmalo.load("img/navemalo.bmp");
	//fnave.load_OptimizedImage("img/navemalo.bmp");//forma optimizada de cargar
    malo1->addframe(fmalo); // Si os fijais, los enemigos usan el mismo frame, por lo que solo debemos cargarlo una vez
    malo2->addframe(fmalo); // Para un control más individual cargariamos un frame por cada enemigo creado.
    
    flaser.load("img/laser.bmp");
	//fnave.load_OptimizedImage("img/laser.bmp");//forma optimizada de cargar
    laser->addframe(flaser);

    return 0;
}

int Naves::loop()
{
	int salir;
	salir = FALSE;	
	SDL_Event event; // Estas dos variables nos ayudarán para salir del juego...
    Uint8 *keys; // ...y monitorizar el teclado.
    
    // Iniciamos SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("No se pudo iniciar SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    // Activamos el modo de video
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, BBP, SDL_HWSURFACE);
    if (screen == NULL){
        printf("No se pudo establecer el modo de video: %s\n", SDL_GetError());
        return 1;
    }
    
    atexit(SDL_Quit);        

	while (salir == FALSE){
    
        // Con esta función obtenemos el tiempo actual
        frametime = SDL_GetTicks();
        
		//Maquina de estados
		switch(estado){
			case INICIALIZAR:
					// Llamamos a la función para dar valores iniciales...
					initialize();
				    
					// ...y cargamos todos los sprites.
					init_sprites();
					estado++;
			break;

			case JUGAR:			
				update_Scene();
				draw_scene(screen);
			break;
			
			case SALIR:
				salir = TRUE;
			break;
		};
        // Obtenemos el estado del teclado...
        keys = SDL_GetKeyState(NULL);
        
        // ...y verificamos si se pulsa alguna tecla de control.
        if (keys[SDLK_UP] && jugador.y > 0) {jugador.y = jugador.y-(5);}
        if (keys[SDLK_DOWN] && jugador.y < HEIGHT - nave->geth()) {jugador.y = jugador.y+(5);}
        if (keys[SDLK_LEFT] && jugador.x > 0) {jugador.x = jugador.x-(5);}
        if (keys[SDLK_RIGHT] && jugador.x < WIDTH - nave->getw()) {jugador.x = jugador.x+(5);}
        if (keys[SDLK_SPACE]) {draw_shot();} // Si se pulsa la tecla espacio se crea un disparo.
        
        // Comienza la cola de eventos
        while (SDL_PollEvent(&event)){
        
            if (event.type == SDL_QUIT) {salir = 1;} // Si se detecta un evento de salida...
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE){ // ...o se pulsa la tecla de escape...
                    estado = SALIR; // ...salimos del loop principal, y por tanto, del juego.
                }
            }
        }
       
        // Las siguientes líneas se encargan de controlar la velocidad a la que se muestra el juego
        frametime = SDL_GetTicks() - frametime;
        if(frametime < 30){ // Si el tiempo usado para dibujar un cuadro es menor a 30 ms...
            SDL_Delay(Uint32(30 - frametime)); // ...entonces vete a dormir hasta el siguiente cuadro
        }
		
    }
	return TRUE;


}
