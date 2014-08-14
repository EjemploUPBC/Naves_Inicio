#include "naves.h"

// La función principal del juego
int main(int argc, char *argv[]){
	Naves *Naves_Obj = new Naves();

	if(Naves_Obj->loop())   
		Naves_Obj->finalize(); // Liberamos los recursos utilizados.
    
    return 0;
}
