#ifndef COMMUN_H
#define COMMUN_H

#include "tete.h"

/*Fonction*/

//Allocation 
void LibererStruct(tete_t * agenda);
int CreationElement(semaine_t ** nouvSemaine, char * annee, char * num_semaine, char * jour, char * heure, char * nom);
void LiberationElement(semaine_t * aliberer);

//AJout et Suppression
void AjoutStruct(tete_t * agenda, char * annee, char * semaine, char *  jour, char * heure,char * nom);
int SupprStruct(tete_t * agenda, semaine_t * param);

//Affichage
void AffichageAgenda(tete_t * agenda);

//Fichier
int LectureFichier(tete_t * agenda, char * nomFichier);
void EcritureFichier(tete_t * agenda, char * nomFichier);

#endif
