#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/action.h"

/* -------------------------------------------------------------------- */
/* AlloueAction alloue une cellule de type action                       */
/*                                                                      */
/* En entrée: nouvelleAction, un pointeur indirect sur l'action à       */
/* allouer, 3 char * qui contienne les infos à stocker dans l'action    */
/*                                                                      */
/* En sortie: une valeur entière qui vaut 0 si l'allocation à réussi -1 */
/* sinon                                                                */
/* -------------------------------------------------------------------- */

int AlloueAction(action_t ** nouvelleAction, char * jour, char * heure, char * nom){
    int sortie = 0; //si on renvoie 0 tout va bien
    //on verifie si la valeur entrée sont valides
    if(atoi(jour) >= 1 && atoi(jour) <= 7 && atoi(heure) >= 0 && atoi(heure) <= 24){
        *nouvelleAction = (action_t*)malloc(sizeof(action_t));
        //on vérifie que l'allocation a réussi
        if(nouvelleAction){
            strcpy((*nouvelleAction)->jour_heure,jour);
            strcat((*nouvelleAction)->jour_heure,heure);
            strcpy((*nouvelleAction)->nom,nom);
            (*nouvelleAction)->suivant = NULL;
        }
        else{
            sortie = -1;//mauvaise alloc
        }
    }
    else{
        sortie = -1;//mauvaise valeur
    }
    
    return sortie;
}
