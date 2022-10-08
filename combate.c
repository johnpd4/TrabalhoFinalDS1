#include "combate.h"
#include "setup_inicio.h"
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

inimigo sorteiaInimigo(){
    inimigo aux;
    // Sortei um numero de 1 a 100
    int sorteio = 0;

    srand(time(NULL));

    sorteio = rand() % 100;

    //printf ("sorteio: %i", sorteio);
    // E seleciona um inimigo baseado no numero sorteado
    if (sorteio > 90){
        aux.dano = 10;
        aux.vida = 100;
        aux.tipo = INSETO;
        strcpy(aux.nome, "inseto generico");
        aux.chancePontoFraco = 35;
    }
    else if (sorteio > 80){
        aux.dano = 10;
        aux.vida = 100;
        aux.tipo = ROBO;
        strcpy(aux.nome, "robo generico");
        aux.chancePontoFraco = 35;
    }
    else {
        aux.dano = 10;
        aux.vida = 100;
        aux.tipo = HUMANO;
        strcpy(aux.nome, "humano generico");
        aux.chancePontoFraco = 35;
    }
    return aux;
}

void combate(playerCombate* player, inimigo inimigo){
    int fimCombate = 0,
    multiplicador = 1,
    selecaoArma = 0,
    cancelaTurnoInimigo = 0,
    ataqueCarregadoInimigo = 0,
    i = 0;

    printf ("\nInimigo: %s\n", inimigo.nome);

    do {
        // Imprime op��es de arma
        printf ("\nEscolha a arma para atacar: \n");

        // Mostra para o jogador as suas armas
        for (i = 0; i < 4; i++){
            printf ("%d: Dano %d, Tipo %d, Desc: %s\n", i+1, player->arma[i].dano, player->arma[i].tipoDano, player->arma[i].desc);
        }

        // Reseta a sele��o de arma e o multiplicador de dano
        selecaoArma = 0;
        multiplicador = 1;

        // Seleciona uma arma valida
        do {
            if (selecaoArma != 0)
                printf ("\nFalha ao selecionar arma, tente novamente\n");

            scanf("%i", &selecaoArma);
        } while (selecaoArma <= 0 || selecaoArma >= 5);

        // Multiplicador do item secreto pra debug
        if(strcmp(player->itemEspecial, "DELETE KEY") == 0){
            printf ("Multiplicador 999, DELETE KEY");
            multiplicador += 999;
        }

        // Agora com a arma selecionada podemos aplicar o multiplicador
        if(player->arma[selecaoArma-1].tipoDano == inimigo.tipo || strcmp(player->itemEspecial, "MIRA A LASER") == 0)
            multiplicador += 2;
        // Texto de feedback da mira
        if (strcmp(player->itemEspecial, "MIRA A LASER") == 0)
            printf("\nSua MIRA A LASER garante um tiro certeiro...\n");

        // A propiedade do ataque desarmado � pular o turno do inimigo se ele ta carregando um ataque especial
        // Tamb�m tem 10% de chance de pular 2 turnos pq achei legal colocar
        if(player->arma[selecaoArma-1].tipoDano == DESARMADO && ataqueCarregadoInimigo > 0){
            cancelaTurnoInimigo++;
            // LUVAS DE BOXE garante que o atordoamento dura 2 turnos
            if (90 < rand() % 100 || strcmp(player->itemEspecial, "LUVAS DE BOXE") == 0){
                cancelaTurnoInimigo++;
                // E da a chance de durar 3
                if (80 < rand() % 100 && strcmp(player->itemEspecial, "LUVAS DE BOXE") == 0){
                    printf ("\nSuas LUVAS DE BOXE atordoaram o inimigo por um turno extra!\n");
                    cancelaTurnoInimigo++;
                }
            }
        }
        // Multiplicador extra do item especial "FACA"
        if(player->arma[selecaoArma-1].tipoDano == DESARMADO && strcmp(player->itemEspecial, "FACA") == 0)
            multiplicador += 2;

        // Tira vida do inimigo
        inimigo.vida -= player->arma[selecaoArma-1].dano * multiplicador;

        printf ("Ataque deu %d de dano, inimigo esta com %d de vida", player->arma[selecaoArma-1].dano * multiplicador, inimigo.vida);

        sleep(1);

        // Checa se o inimigo n�o est� morto
        if (inimigo.vida <= 0){

        // Inimigo agora ataca, mas se checa primeiro se seu turno n�o foi cancelado.
        if (cancelaTurnoInimigo > 0){

            printf("\nO inimigo esta atordoado e nao conseguiu atacar!\n");
            // O turno s� pode ser cancelado quando o inimigo carrega o ataque, se ele ja teve o turno cancelado, se reseta o ataque carregado
            cancelaTurnoInimigo--;
            ataqueCarregadoInimigo = 0;
        } else if (ataqueCarregadoInimigo == 2){

            // Se o inimigo conseguiu carregar o ataque especial at� o final ele da 200% de dano
            player->vidaAtual -= inimigo.dano * 2;
            printf("\nO inimigo conseguiu completar seu ataque carregado!\nVoce levou %i de dano e esta com %i de vida\n", inimigo.dano * 2, player->vidaAtual);
            // E se reseta o ataque especial
            ataqueCarregadoInimigo = 0;
        } else if (ataqueCarregadoInimigo == 1){

            // Se o inimigo est� come�ando seu ataque especial, se da um aviso ao jogador e se incrementa a vari�vel do ataque especial
            printf("\nO inimigo esta carregando um ataque especial, expondo seu ponto fraco.\n");
            ataqueCarregadoInimigo++;
        } else {

            // Se o inimigo n�o est� atordoado nem fazendo ataque especial se faz um ataque normal
            player->vidaAtual -= inimigo.dano;
            printf("\nO inimigo conseguiu acertar seu ataque.\nVoce levou %i de dano e esta com %i de vida\n", inimigo.dano, player->vidaAtual);

            // E, por ultimo, se sorteia se o prox ataque do inimigo ser� especial. Decidi sortear no final para ele n�o poder fazer esse ataque no primeiro turno
            if (inimigo.chancePontoFraco > rand() % 100 && ataqueCarregadoInimigo == 0)
            ataqueCarregadoInimigo = 1;
        }
        }
        sleep(1);

        // Detecta o fim do combate
        if (inimigo.vida <= 0 || player->vidaAtual <= 0)
            fimCombate = 1;

    } while (fimCombate == 0);
    // Cura especial do item especial SUQUINHO
    if (strcmp(player->itemEspecial, "SUQUINHO") == 0){
        printf("\nVoce toma seu SUQUINHO refrescante... hmmmmmmmm...\n");
        player->vidaAtual = player->vidaAtual + 7;
    }
    // Ao fim do combate se restaura um pouco de vida do jogador
    if (player->vidaAtual > 0)
        player->vidaAtual = player->vidaAtual + 25;
}
