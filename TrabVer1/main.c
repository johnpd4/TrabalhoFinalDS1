#include <stdio.h>
#include "grafo_la.h"
#include "setup_inicio.h"
#include "combate.h"

int main(void){

    playerCombate jogador;

    inicioJogoCombate(&jogador);

    inimigo aux;

    aux = sorteiaInimigo();

    statusInimigo(aux);

    combate(&jogador, aux);

    statusPlayer(jogador);

    return 0;
}
