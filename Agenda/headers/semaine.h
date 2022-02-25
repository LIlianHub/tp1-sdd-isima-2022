#ifndef SEMAINE_H
#define SEMAINE_H

#include "action.h"

/*Structure*/

typedef struct semaine{
    char annee_semaine[7];
    struct action * liste_action;
    struct semaine * suivant;
} semaine_t;

/*Fonction*/

int AlloueSemaine(semaine_t ** nouvelleSemaine, char * annee, char * num_semaine);

#endif
