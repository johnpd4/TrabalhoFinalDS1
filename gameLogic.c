#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLogic.h"

int random(void){
    srand(time(NULL));
    return rand();
}


GrafoLA *createMap(void){
    int size = (random() % 15) + 1;

    GrafoLA* map = criaGrafoLA(size);

    //criaCaminhos(map);

    return map;
}

void criaCaminhos(GrafoLA* grafo){

    

}

GrafoLA *restartMap (GrafoLA* grafo){
    destroiGrafoLA(grafo);
    grafo = createMap();
    return grafo;
}