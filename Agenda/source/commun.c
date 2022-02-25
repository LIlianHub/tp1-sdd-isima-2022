#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/tete.h"


//Ajout et Suppression

/* -------------------------------------------------------------------- */
/* AJoutStructure ajoute une action (et possiblement une semaine) dans  */
/* notre agenda                                                         */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD, 5 (char *) contenant*/
/* les champs de la semaine et de l'action à ajouter                    */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void AjoutStruct(tete_t * agenda, char * annee, char * sem, char *  jour, char * heure, char * nom){
    int testAlloc = 1;
    semaine_t * nouvSemaine = NULL;
    action_t * nouvAction = NULL;
    //On alloue l'élement à ajouter
    testAlloc += AlloueSemaine(&nouvSemaine, annee, sem);
    testAlloc += AlloueAction(&nouvAction, jour, heure, nom);
    //Si les 2 allocs ont fonctionnées, testAlloc vaut toujours 1 car si tout va bien les deux fonctions 
    //d'alloc renvoie 0 ! Au contraire si testAlloc change de valeur il y a eu un soucis !

    if(testAlloc == 1){ //si l'alloc n'a pas echoué et les valeurs sont bonnes pour la semaine ET l'action
        /*Parcours*/
        semaine_t * parcours_semaine = NULL;
        semaine_t * prec_semaine = NULL;
        action_t * parcours_action = NULL;
        action_t * prec_action = NULL;

        /*Liste Vide*/
        //tout simple on ajoute juste sur la tete fictive
        if(agenda->debut == NULL){
            nouvSemaine->liste_action = nouvAction;
            agenda->debut = nouvSemaine;
        }

        /*LIste non vide*/

        else{
            parcours_semaine = agenda->debut;
            prec_semaine = parcours_semaine;

            //On parcours jusqu'à tomber sur semaine plus veille que celle à insérer sur parcours_semaine
            while(parcours_semaine != NULL && strcmp(nouvSemaine->annee_semaine,parcours_semaine->annee_semaine) >= 0){
                prec_semaine = parcours_semaine;
                parcours_semaine = parcours_semaine->suivant;
            }

            //La semaine existe deja, la semaine pointée par précédent est la même que la nouvelle semaine
            if(strcmp(nouvSemaine->annee_semaine,prec_semaine->annee_semaine) == 0){
                //on parcourt la liste d'action de cette semaine
                parcours_action = prec_semaine->liste_action;
                prec_action = parcours_action;
                
                //on veut trouver une action plus vieille que celle à inserer
                while(parcours_action != NULL && strcmp(nouvAction->jour_heure,parcours_action->jour_heure) >= 0){
                    prec_action = parcours_action;
                    parcours_action = parcours_action->suivant;
                }

                //Cas on c'est la première action de la semaine: on change liste action
                if(prec_action == parcours_action){
                    prec_semaine->liste_action = nouvAction;
                }
                //Cas ou c'est une action banale de la semaine: l'action precedente pointe sur notre
                //nouvelle action
                else{
                    prec_action->suivant = nouvAction;
                }
                //Dans tous les cas notre nouvelle action pointe sur la suivante (peut être le pointeur null)

                nouvAction->suivant = parcours_action;

                //on a pas besoin de la case nouvsemaine car une semblable a elle existe deja dans la SDD
                //on la libere car on a juste inséré action
                free(nouvSemaine);
            }

            //Cas où le semaine existe pas

            else{
                //Cas ou la tête de la liste doit changer, on change la semaine pointé par la tête fictive
                if(prec_semaine == parcours_semaine){
                    agenda->debut = nouvSemaine;
                }
                //Sinon la semaien précédente pointe maintenant sur notre nouvelle semaine
                else{
                    prec_semaine->suivant = nouvSemaine;
                }
                
                //On relie l'action créee à la semaine créee !
                nouvSemaine->liste_action = nouvAction;
                //Dans tous les cas notre nouvelle semaien pointe sur la suivante (peut être null)
                nouvSemaine->suivant = parcours_semaine;
            }
        }
    }
    //liberation des semaines et actions si soucis dans l'allocation d'un des 2 au départ
    //valeurs mauvaises, allocation ratée ...
    else{
        //si la semaine est alloué mais on a eu un soucis sur l'action
        if(nouvSemaine)
            free(nouvSemaine);
        //si l'action est alloué mais on a eu un soucis sur la semaine
        if(nouvAction)
            free(nouvAction);
    }
}


/* -------------------------------------------------------------------- */
/* SupprStruct supprime une action (et possiblement une semaine) dans   */
/* notre agenda                                                         */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD, et param un élement */
/* de type semaine relié à une action. Ce bout de structure contient les*/
/* infos à supprimer afin de faire des comparaison dans la fonction     */    
/*                                                                      */
/* En sortie: Rien, un entier qui vaut 1 si la valeur a bien été        */
/* supprimé, 0 si la semaine cherchée n'existe pas et -1 si l'action    */
/* cherchée n'existe pas                                                   */
/* -------------------------------------------------------------------- */

int SupprStruct(tete_t * agenda, semaine_t * param){
    int sortie = 1; //valeur de sortie de la fonction
    
    //Si il y a au moins une valeur à supprimer !
    if(agenda->debut != NULL){

        /*Pointeur de parcours*/
        semaine_t * parcours_semaine = agenda->debut;
        semaine_t * prec_semaine = parcours_semaine;
        action_t * parcours_action = NULL;
        action_t * prec_action = NULL;

        //Tant qu'on a pas trouvé sur notre pointeur parcours une semaine plus vielle ou identique à
        //celle à supprimer
        while (parcours_semaine->suivant != NULL && strcmp (param->annee_semaine , parcours_semaine->annee_semaine) > 0){

            prec_semaine = parcours_semaine;
            parcours_semaine = parcours_semaine->suivant;
        
        }

        //La semaine pointée par parcours n'est pas la même que celle à supprimer
        if(strcmp (param->annee_semaine , parcours_semaine->annee_semaine) != 0){
        /*Cas où la semaine n'existe pas, on supprime rien*/
            sortie = 0;
        }

        //La semaine pointée par parcours est la même que celle à supprimer !
        else{

            parcours_action = parcours_semaine->liste_action;
            prec_action = parcours_action;

            //Tant qu'on a pas parcours qui pointe sur une action plus vieille ou identique à celle à
            //supprimer

            //On cherche un jour et une heure identique
            while (parcours_action != NULL && strcmp (param->liste_action->jour_heure, parcours_action->jour_heure) > 0){

                prec_action = parcours_action;
                parcours_action = parcours_action->suivant;
            
            }

            //ON cherche le nom identique
            while(strcmp (param->liste_action->nom , parcours_action->nom) > 0){
                //ON cherche nom
                prec_action = parcours_action;
                parcours_action = parcours_action->suivant;
            }

            //Si le nom et le jour et l'heure sont identiques on supprime !
            if(strcmp (param->liste_action->jour_heure , parcours_action->jour_heure) == 0 && strcmp(param->liste_action->nom , parcours_action->nom) == 0){
            
                /*Différents cas de suppression*/
                    
                if(prec_action == parcours_action){
                    //on supprime la première ation de la semaine donc
                    //on change l'action pointée par la semaine en mettant la suivante
                    //de l'actuelle première
                    parcours_semaine->liste_action = parcours_action->suivant;
                }
            
                else{
                    //On supprime une action "classique" de la semaine, la précédente
                    //pointe sur la suivante de celle a supprimer
                    prec_action->suivant = parcours_action->suivant;
                }

                //On libère la mémoire de l'action supprimée
                free(parcours_action);

                /*ON vérifier maintenant que la semaine n'est pas vide*/
                if(parcours_semaine->liste_action == NULL){
                    //La semaine est maintenant vide on la supprime !

                    //Si c'est la premiere semaine on change la semaine pointée
                    //par la tête fictive !

                    if(agenda->debut == parcours_semaine){
                        agenda->debut = parcours_semaine->suivant;
                    }

                    //Sinon suppression classique ! 
                    else{
                        prec_semaine->suivant = parcours_semaine->suivant;
                    }

                    //On libère la semaine ainsi supprimée
                    free(parcours_semaine);
                }
            }

            else{
                //action existe pas on supprime rien
                sortie = -1;
            }
        }
    }   
    return sortie;
}


//Allocation

/* -------------------------------------------------------------------- */
/* LibererStruct libère l'entiéreté de l'agenda, c'est à dire toutes les*/
/* semaines, toutes les actions et la tête fictive                      */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD                      */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void LibererStruct(tete_t * agenda){
    /*Pointeur de parcours*/
    semaine_t * parcours_semaine = agenda->debut;
    semaine_t * prec_semaine = NULL;
    action_t * parcours_action = NULL;
    action_t * prec_action = NULL;
    
    //Tant qu'on a pas parcouru toutes les semaines
    while(parcours_semaine != NULL){
        parcours_action = parcours_semaine->liste_action;
        //Tant qu'on a pas parcouru toutes les actions de la semaine actuelle
        while(parcours_action != NULL){
            //On libère toutes les actions
            prec_action = parcours_action;
            parcours_action = parcours_action->suivant;
            free(prec_action);
        }
        //On libère toutes les semaines
        prec_semaine = parcours_semaine;
        parcours_semaine = parcours_semaine->suivant;
        free(prec_semaine);
    }
    //On libère la tête fictive
    free(agenda);
}

/* -------------------------------------------------------------------- */
/* Création élement alloue un élément de type semaine, un élément de    */
/* type action, et les relie entre eux (utile pour la fonction          */
/* SupprStruct)                                                         */
/*                                                                      */
/* En entrée: nouvSemaine, un pointeur indirect sur la semaine à allouer*/
/* 5 (char *) contenant les infos à stocker dans action et semaine      */
/*                                                                      */
/* En sortie: Un entier qui vaut 1 si l'allocation c'est bien passé, 0  */
/* ou -1 si il y a eu un soucis d'allocation avec semaine et (ou) action*/
/* -------------------------------------------------------------------- */

int CreationElement(semaine_t ** nouvSemaine, char * annee, char * semaine, char * jour, char * heure, char * nom){
    int sortie = 1;
    action_t * nouvAction = NULL;
    //On Crée séparément l'élement action et semaine et on les alloue
    sortie += AlloueSemaine(nouvSemaine, annee, semaine);
    sortie += AlloueAction(&nouvAction, jour, heure, nom);
    //si pas de soucis d'alloc dans les 2 cas on les relie entre eux
    if(sortie == 1)
        (*nouvSemaine)->liste_action = nouvAction;
    return sortie;
}

/* -------------------------------------------------------------------- */
/* LibérerElement libère une semaine et son action relié, c'est la      */
/* fonction qui complète "CreationElement"                              */
/*                                                                      */
/* En entrée: un pointeur de type semaine sur la semaine à libérer      */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void LiberationElement(semaine_t * aliberer){
    //Si l'action et la semaine existe on les libère tous les deux
    if(aliberer){
        if(aliberer->liste_action)
            free(aliberer->liste_action);
        free(aliberer);
    }
}

//Affichage

/* -------------------------------------------------------------------- */
/* AffichageAgenda Affiche entièrement toute notre SDD agenda !         */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD                      */
/*                                                                      */
/* En sortie: Rien, fonction de type void                               */
/* -------------------------------------------------------------------- */

void AffichageAgenda(tete_t * agenda){
    if(agenda != NULL){

        /*Pointeur de Parcours*/
        semaine_t * parcours_semaine = agenda->debut;
        action_t * parcours_action = NULL;

        /*Tableau utile pour un affichae plus propre des jours de la semaines*/
        char tab_jour[7][10] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

        printf("\n=-=-=-=-=-= VOTRE AGENDA =-=-=-=-=-=\n\n");

        /*On parcourt toutes les semaines*/
        while(parcours_semaine != NULL){
            /*On affiche les valeurs de l'élément semaine*/
            parcours_action = parcours_semaine->liste_action;

            printf("===== Année ");
            for(int i = 0; i < 4; i++){
                printf("%c",parcours_semaine->annee_semaine[i]);
            }
            printf(" Semaine ");
            for(int i = 4; i < 7; i++){
                printf("%c",parcours_semaine->annee_semaine[i]);
            }

            printf(" =====\n");
            
            /*On parcourt toutes les actions de la semaine pointée*/
            while(parcours_action != NULL){
                //on récupère l'indice correspondant au bon jour dans le tableau plus haut
                //rAvec le codeASCII le char 1 correspondant à lundi vaudra l'int 0 par exemple ...
                int indice = (parcours_action->jour_heure[0]) - '1'; 

                //on affiche toutes les infos de l'action pointée
                printf("Le %s à %c%ch : %s\n",tab_jour[indice],parcours_action->jour_heure[1],parcours_action->jour_heure[2],parcours_action->nom);

                parcours_action = parcours_action->suivant;
            }
            parcours_semaine = parcours_semaine->suivant;
            printf("\n");
        }
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
                           
    }  
}

//Fichier

/* -------------------------------------------------------------------- */
/* LectureFichier: Lit un fichier formaté avec les élements à ajouter   */
/* dans notre SDD, il y a un élément par ligne ! A chaque ligne lue,    */
/* Il essaye d'ajouter l'élement lu dans la SDD                         */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD, 1 (char *)          */
/* nomFichier qui contient le nom du fichier à ouvrir                   */
/*                                                                      */
/* En sortie: UN entier qui vaut 1 si on a réussi à ouvrir le fichier,  */
/* 0 sinon                                                              */
/* -------------------------------------------------------------------- */

int LectureFichier(tete_t * agenda, char * nomFichier){
    FILE * fichier = NULL;
    char ouverture[32];
    //Permet de chercher automatiquement dans le dossier "entree"
    //on concatène au dossier "entree" le nom du fichier à
    //ouvrir
    sprintf(ouverture,"entree/%s",nomFichier);
    fichier = fopen(ouverture,"r");
    int sortie = 1;

    //SI on a réussi à ouvrir le fichier
    if(fichier){
        char annee[5];
        char semaine[3];
        char jour[2];
        char heure[3];
        char nom[11];

        //Tant qu'on ne lit pas un élement plus loin que la fin du fichier
        while(!feof(fichier)){
            fgets(annee,5,fichier); //on recupere l'année sur 4 bits + '\0'
            fgets(semaine,3,fichier); //on recupere la semaine sur 2 bits + '\0'
            fgets(jour,2,fichier); //on recupere le jour sur 1 bits + '\0'
            fgets(heure,3,fichier); //on recupere l'heure sur 2 bits + '\0'
            fgets(nom,11,fichier); //on recupere le nom sur 10 bits + '\0'
            fgetc(fichier); //on passe le "\n"
            //On essayer d'ajouter ces informations à la SDD
            AjoutStruct(agenda,annee,semaine,jour,heure,nom);
        }
        fclose(fichier);
    }
    else{
        sortie = 0;// probleme fichier
    }
    return sortie;
}


/* -------------------------------------------------------------------- */
/* EcritureFichier Parcours toutes notre SDD et écrit ligne par ligne   */
/* dans un fichier formaté de la même forme que ceux lu par Lecture     */
/* fichier toutes les actions qu'elle rencontre !                       */
/*                                                                      */
/* En entrée: agenda, la tete fictive de notre SDD, 1 (char *)          */
/* nomFichier qui contient le nom du fichier à ouvrir                   */
/*                                                                      */
/* En sortie: UN entier qui vaut 1 si on a réussi à ouvrir le fichier,  */
/* 0 sinon                                                              */
/* -------------------------------------------------------------------- */

void EcritureFichier(tete_t * agenda, char * nomFichier){
    //SI l'agenda est alloué
    if(agenda != NULL){
        FILE * fichier;
        char ouverture[32];
        sprintf(ouverture,"sauvegarde/%s",nomFichier);
        fichier = fopen(ouverture,"w+");
        //Si l'ouverture du fichier a fonctionné
        if(fichier){
            /*Pointeurs de parcours*/
            semaine_t * parcours_semaine = agenda->debut;
            action_t * parcours_action = NULL;

            int depart = 1;
            
            //On parcourt toutes les semainnes
            while(parcours_semaine != NULL){
                parcours_action = parcours_semaine->liste_action;
                //On parcourt toutes les actions de la semaine pointée
                while(parcours_action != NULL){
                    //si c'est la première ligne qu'on écrit, on ne met pas de '\n'
                    //Mais on marque le fait que les prochaines fois on devra
                    //le faire ! 
                    if(depart)
                        depart = 0;
                    else
                        fputc('\n',fichier);
                    
                    //on ecrit les infos de la semaine pointée
                    fputs(parcours_semaine->annee_semaine,fichier);
                    //puis on ecrit les infos de le l'cation pointée
                    fputs(parcours_action->jour_heure,fichier);
                    fputs(parcours_action->nom,fichier);
                    parcours_action = parcours_action->suivant;
                }
                parcours_semaine = parcours_semaine->suivant;
            }
            fclose(fichier);
        }
    }
}