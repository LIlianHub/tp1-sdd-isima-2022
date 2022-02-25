#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/commun.h"
#include "../headers/contigue.h"

/* -------------------------------------------------------------------- */
/* InitContigue place les pointeurs de depart et de fin de la liste     */
/* contigue au départ                                                   */
/*                                                                      */
/* En entrée: contigue, notre liste contigue de taille fixe,            */
/* debut_contigue et fin_contigue les 2 pointeurs indirects de debut et */
/* de fin de notre liste                                                */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void InitContigue(char contigue[MAX_TAILLE_CONTIGUE][TAILLE_DATE_ACTION], char ** debut_contigue, char ** fin_contigue){
    //On place les pointeurs de fin et de debut sur la debut de la liste ar elle est vide !
    (*debut_contigue) = contigue[0];
    (*fin_contigue) = contigue[0];
}

/* -------------------------------------------------------------------- */
/* RemplisContigue parcours toutes la SDD agenda et cherche dans les    */
/* noms des actions si un motif est présent                             */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD, motif, le motif à   */
/* chercher, les pointeurs de debut et de fin de la liste contigue      */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void RemplisContigue(tete_t * agenda, char * motif, char ** debut_contigue, char ** fin_contigue){
    /*Pointeur de parcours de l'agenda*/
    semaine_t * parcours_semaine = agenda->debut;
    action_t * parcours_action = NULL;

    /*On place le pointeur "dernier_element" sur le dernier emplacement sur lequel on peut écrire
    c'est à dire "MAX_TAILLE_CONTIGUE - 1"*/
    char * dernier_element = (*debut_contigue) + (MAX_TAILLE_CONTIGUE - 1) * TAILLE_DATE_ACTION;

    /*Le pointeur qui va parcourir est placé au départ*/
    char * parcours_contigue = (*debut_contigue);

    //On informe l'utilisateur du motif cherché
    printf("\n---> Motif recherché: %s <---\n", motif);

    //On parcourt intégralement la SDD
    while(parcours_semaine != NULL){
        parcours_action = parcours_semaine->liste_action;
        while(parcours_action != NULL){
            //Si il reste de la place dans la liste contiguë et que le motif apparait dans le nom
            //de l'action pointée, on ajoute la date de cette action dans la liste contiguë !
            //strstr renvoie NULL si le motif n'est pas dedans et l'adresse de la premiere occurence
            //du motif si il existe !
            if(parcours_contigue <= dernier_element && strstr(parcours_action->nom, motif) != NULL){
                //on concatene les infos dans la liste contigue !
                strcpy(parcours_contigue, parcours_semaine->annee_semaine);
                strcat(parcours_contigue, parcours_action->jour_heure);
                //on déplace le pointeur de parcours sur la prochaine zone à ecrire
                //c'est à dire à "TAILLE_DATE_ACTION mots" de l'emplacement actuel !
                parcours_contigue += TAILLE_DATE_ACTION;
            }
            parcours_action = parcours_action->suivant;
        }
        parcours_semaine = parcours_semaine->suivant;
    }
    //On place le pointeur de fin de liste contiguë sur la dernière valeur entrée dans la liste !
    //Soit la valeur max possible, soit avant !
    (*fin_contigue) = parcours_contigue - TAILLE_DATE_ACTION;
}

/* -------------------------------------------------------------------- */
/* Affiche contigue parcours toutes la liste contigue et                */
/* affiche les valeurs qu'elle contient                                 */
/*                                                                      */
/* En entrée: les pointeurs de debut et de fin de la liste contigue     */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void AfficheContigue(char * debut_contigue, char * fin_contigue){
    //Tableau qui facilite l'affichage des jours de la semaine !

    char tab_jour[7][10] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    int indice;
    printf("\n\n===== Date Correspondant au motif cherché =====\n");
    //Utilisation d'une boucle for car on a connait la taille de la liste contiguë !
    for(char * parcours = debut_contigue; parcours <= fin_contigue; parcours += TAILLE_DATE_ACTION){
        //On affiche toutes les infos dans la liste contiguë proprement !
        printf("Année: ");
        for(int i = 0; i < 4; i++){
            printf("%c",*(parcours + i));
        }
        printf(" Semaine %c%c: ",*(parcours + 4), *(parcours + 5));

        indice = (*(parcours + 6)) - '1';
        printf("Le %s à %c%ch\n", tab_jour[indice], *(parcours + 7), *(parcours + 8));
    }
    printf("===============================================\n\n");
}
