#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLogic.h"

GrafoLA *createMap(void){
    int size = (rand() % 13) + 2;

    GrafoLA* map = criaGrafoLA(size);

    aplicaTipos(map);
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
void aplicaTipos(GrafoLA* grafo){
    int key = rand() % grafo->numVertices;
    grafo->vertices[key].tipo = START;
    if(key >= grafo->numVertices){
        key--;
    }else{
        key++;
    }
    grafo->vertices[key].tipo = END;

    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->vertices[i].tipo == -1){
            grafo->vertices[i].tipo = (rand() % 2) + 2;
        }
    }
}

GrafoLA *restartMap (GrafoLA* grafo){
    destroiGrafoLA(grafo);
    return createMap();
}