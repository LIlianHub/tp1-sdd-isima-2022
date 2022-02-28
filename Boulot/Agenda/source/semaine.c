#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/semaine.h"

/* -------------------------------------------------------------------- */
/* ALloueSemaine alloue une cellule de type semaine                     */
/*                                                                      */
/* En entrée: nouvelleSemaine, un pointeur indirect sur la semaine à    */
/* allouer, 2 char * qui contienne les infos à stocker dans la semaine  */
/*                                                                      */
/* En sortie: une valeur entière qui vaut 0 si l'allocation à réussi -1 */
/* sinon                                                                */
/* -------------------------------------------------------------------- */

int AlloueSemaine(semaine_t ** nouvelleSemaine, char * annee, char * num_semaine){
    int sortie = 0; //tout va bien

    //on verifie que le numéro de semaine est correcte
    if(atoi(num_semaine) >= 1 && atoi(num_semaine) <= 53){
        *nouvelleSemaine = (semaine_t*)malloc(sizeof(semaine_t));
    
        //on verifie que le malloc est correcte
        if(nouvelleSemaine){
            //on remplis les champs de semaine
            strcpy((*nouvelleSemaine)->annee_semaine,annee);
            strcat((*nouvelleSemaine)->annee_semaine,num_semaine);
            (*nouvelleSemaine)->liste_action = NULL;
            (*nouvelleSemaine)->suivant = NULL;
        }
        else{
            sortie = -1; //mauvaise alloc
        }
    }
    else{
        sortie = -1; //mauvaise valeur
    }

    return sortie;
}
