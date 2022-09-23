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

    //aplicaTipos(map);
    //criaCaminhos(map);

    return map;
}

// criaCaminhos : GrafoLA -> void
/* Conecta todos os nodos do grafo garantindo que o nodo do tipo END seja alcançavel a partir do nodo START
    Aplica os valores das distancias entre cada nodo no valor distancia da struct arestas
*/
void criaCaminhos(GrafoLA* grafo){

}

// aplicaTipos : GrafoLA -> void
/*
    Aplica os tipos para cada nodo do grafo respeitando a quantidade ideal para cada tipo. START & END só podem exister 1
    Usar style enum
*/
void aplicaTipos(GrafoLA* GrafoLA){

}

GrafoLA *restartMap (GrafoLA* grafo){
    destroiGrafoLA(grafo);
    grafo = createMap();
    return grafo;
}