#ifndef CONTIGUE_H
#define CONTIGUE_H

/*Les defines*/

#define MAX_TAILLE_CONTIGUE 16
#define TAILLE_DATE_ACTION 10
//10 car contient jour + heure + annee + semaine + \0


/*Variable globale*/

char CONTIGUE[MAX_TAILLE_CONTIGUE][TAILLE_DATE_ACTION];

/*Fonction*/

void InitContigue(char contigue[MAX_TAILLE_CONTIGUE][TAILLE_DATE_ACTION], char ** debut_contigue, char ** fin_contigue);
void RemplisContigue(tete_t * agenda, char * motif, char ** debut_contigue, char ** fin_contigue);
void AfficheContigue(char * debut_contigue, char * fin_contigue);


#endif
