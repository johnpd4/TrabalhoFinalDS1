#include "combate.h"
#include "setup_inicio.h"
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

inimigo sorteiaInimigo(){
    inimigo aux;

    // Eu n sei pq mas isso n ta gerando numeros aleatorios...

    float sorteio = 0;

    srand(time(NULL));

    sorteio = rand();

    sorteio = sorteio / RAND_MAX;

    printf ("sorteio: %f", sorteio);

    if (sorteio > 0.9){
        aux.dano = 10;
        aux.vida = 100;
        aux.tipo = INSETO;
        strcpy(aux.nome, "inseto generico");
    }
    else if (sorteio > 0.8){
        aux.dano = 10;
        aux.vida = 100;
        aux.tipo = ROBO;
        strcpy(aux.nome, "robo generico");
    }
    else {
        aux.dano = 10;
        aux.vida = 100;
        aux.tipo = HUMANO;
        strcpy(aux.nome, "humano generico");
    }
    return aux;
}

void combate(playerCombate* player, inimigo inimigo){
    int fimCombate = 0,
    multiplicador = 1,
    selecaoArma = 0,
    i = 0;

    printf ("\nInimigo: %s\n", inimigo.nome);

    do {
        // Imprime opções de arma
        printf ("\nEscolha a arma para atacar: \n");

        // MUDAR ISSO DPS PRA FICAR MENOR
        for (i = 0; i < 4; i++){
            printf ("%d: Dano %d, Tipo %d, Desc: %s\n", i+1, player->arma[i].dano, player->arma[i].tipoDano, player->arma[i].desc);
        }

        // Reseta a seleção de arma e o multiplicador de dano
        selecaoArma = 0;
        multiplicador = 1;

        // Seleciona uma arma valida
        do {
            if (selecaoArma != 0)
                printf ("\nFalha ao selecionar arma, tente novamente\n");

            scanf("%i", &selecaoArma);
        } while (selecaoArma <= 0 || selecaoArma >= 5);

        // Multiplicador do item secreto pra debug
        if(strcmp(player->itemEspecial, "DELETE KEY") == 0)
            multiplicador += 999;

        // Agora com a arma selecionada podemos aplicar o multiplicador
        if(player->arma[selecaoArma-1].tipoDano == inimigo.tipo)
            multiplicador += 2;

        // Tira vida do inimigo
        inimigo.vida -= player->arma[selecaoArma-1].dano * multiplicador;

        printf ("Ataque deu %d de dano, inimigo esta com %d de vida", player->arma[selecaoArma-1].dano * multiplicador, inimigo.vida);

        // Detecta o fim do combate
        if (inimigo.vida <= 0 || player->vidaAtual <= 0)
            fimCombate = 1;

    } while (fimCombate == 0);
}
