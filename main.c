#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLogic.h"

int main(void){

    srand(time(NULL));

    GrafoLA* test = createMap();
    imprimeGrafoLA(test);
    destroiGrafoLA(test);

    return 0;
}