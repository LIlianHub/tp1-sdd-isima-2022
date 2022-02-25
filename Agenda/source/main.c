#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../headers/commun.h"
#include "../headers/contigue.h"

/*COUCOU BEBER*/

int main(int argc, char *argv[]){
        if(argc == 2){
                tete_t * agenda = NULL;
                AlloueTete(&agenda);
                int bonneLecture = LectureFichier(agenda, argv[1]);
                if(bonneLecture){
                        //Premier affichage
                        AffichageAgenda(agenda);
                        
                        //Exemple avec la liste contigue et le motif "TD"
                        char * debut_contigue = NULL;
                        char * fin_contigue = NULL;
                        InitContigue(CONTIGUE, &debut_contigue, &fin_contigue);
                        RemplisContigue(agenda,"T", &debut_contigue, &fin_contigue);
                        AfficheContigue(debut_contigue,fin_contigue);

                        //Exemple de Supression
                        //Ici on supprime L'activité "Boulot" ayant lieu le
                        //Lundi de la semaine 15 de l'année 2022 à 12h
                        semaine_t * supprExemple = NULL;
                        CreationElement(&supprExemple, "2022", "15", "1", "12", "Boulot    ");
                        SupprStruct(agenda, supprExemple);
                        LiberationElement(supprExemple);
                        
                        //Affichage de notre agenda après modification
                        AffichageAgenda(agenda);

                        //Ecriture de la SDD dans le fichier sauvegarde
                        //Dans un fichier ayant le même nom qu'en entrée
                        EcritureFichier(agenda, argv[1]);
                }
                else{
                        printf("Problème lors de la lecture du fichier !\n");
                }
                LibererStruct(agenda);
        }
        else{
                printf("Rentrer un nom de fichier en argument\n");
        }
        return 0;
}
