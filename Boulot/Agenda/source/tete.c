#include <stdlib.h>
#include <stdio.h>

#include "../headers/tete.h"

/* -------------------------------------------------------------------- */
/* AlloueTete alloue la tête fictive de notre SDD                       */
/*                                                                      */
/* En entrée: agenda, un pointeur indirect de type tete_t               */
/*                                                                      */
/* En sortie: une valeur entière qui vaut 0 si l'allocation à réussi -1 */
/* sinon                                                                */
/* -------------------------------------------------------------------- */

int AlloueTete(tete_t ** agenda){
    int sortie = 0;
    *agenda = (tete_t*)malloc(sizeof(tete_t));
    //On verifie que l'allocation soit bien faite !
    if(agenda){
        (*agenda)->debut = NULL;
    }
    else{
        sortie = -1; //probleme alloc
    }
    return sortie;
}
