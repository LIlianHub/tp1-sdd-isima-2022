#ifndef ACTION_H
#define ACTION_H

/*Structure*/

typedef struct action{
    char jour_heure[4];
    char nom[11];
    struct action * suivant;
} action_t;

/*Fonction*/

int AlloueAction(action_t ** nouvelleAction, char * jour, char * heure, char * nom);

#endif
