#include <stdio.h>
#include <stdlib.h>
#include "gameLogic.h"

GrafoLA *createMap(void){
    return criaGrafoLA(5);
}

GrafoLA *restartMap (GrafoLA* grafo){
    destroiGrafoLA(grafo);
    grafo = createMap();
    return grafo;
}