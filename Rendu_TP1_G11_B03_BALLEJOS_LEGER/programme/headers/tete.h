#ifndef TETE_H
#define TETE_H

#include "semaine.h"

/*Structure*/

typedef struct tete{
    semaine_t * debut;
} tete_t;

/*Fonction*/

int AlloueTete(tete_t ** agenda);

#endif
