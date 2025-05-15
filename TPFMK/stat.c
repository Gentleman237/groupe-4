#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "produits.h"
#include "commandes.h"


// Définition de la structure produit
typedef struct {
    int id;
    char nom[50];
    char marque[50];
    int quantite;
    float prix_u;
} produit;
// Définition de la structure produit

//Definition de lastructure marque pour les statistique
typedef struct {
    char marque[50];
    int quantite_t;
    float prix_t;
    int num_model;
} marques;



void stat(){
    int count=0, somme_q=0;
    float  somme_p=0, prix_m, prix_m_marq;
    produit voiture, voiture_min, voiture_max;
    marques tab[6];

    //initialisation du tableau de marque
    for(int j=0; j<6;j++){
        tab[j].num_model=0;
        tab[j].prix_t=0;
        tab[j].quantite_t=0;
    }
    strcpy(tab[5].marque,"AUTRE");
    FILE *fichier = fopen("produit.csv", "r");
    if (verif_fichier(fichier)) {
        char ligne[1024];
        int initial=1;
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            if (sscanf(ligne, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
                //verification du model le moins cher et le plus cher
                   //j'initialise au premier produit
                if(initial==1){
                    voiture_max=voiture;
                    voiture_min=voiture;
                    initial=0;
                }
                if(voiture_max.prix_u<voiture.prix_u){
                    voiture_max=voiture;
                }

                if(voiture_min.prix_u>voiture.prix_u){
                    voiture_min=voiture;
                }



                //recuperation des donnee par marque
                if (!strcmp(voiture.marque,"TOYOTA")) {
                    strcpy(tab[0].marque,"TOYOTA");
                    tab[0].num_model++;
                    tab[0].prix_t+=voiture.prix_u;
                    tab[0].quantite_t+=voiture.quantite;

                }else if(!strcmp(voiture.marque,"MERCEDES")){
                    strcpy(tab[1].marque,"MERCEDES");
                    tab[1].num_model++;
                    tab[1].prix_t+=voiture.prix_u;
                    tab[1].quantite_t+=voiture.quantite;

                }else if(!strcmp(voiture.marque,"FERRARI")){
                    strcpy(tab[2].marque,"FERRARI");
                    tab[2].num_model++;
                    tab[2].prix_t+=voiture.prix_u;
                    tab[2].quantite_t+=voiture.quantite;

                }else if(!strcmp(voiture.marque,"TESLA")){
                    strcpy(tab[3].marque,"TESLA");
                    tab[3].num_model++;
                    tab[3].prix_t+=voiture.prix_u;
                    tab[3].quantite_t+=voiture.quantite;

                }else if(!strcmp(voiture.marque,"DODGE")){
                    strcpy(tab[4].marque,"DODGE");
                    tab[4].num_model++;
                    tab[4].prix_t+=voiture.prix_u;
                    tab[4].quantite_t+=voiture.quantite;

                }else{
                    strcpy(tab[5].marque,"AUTRE");
                    tab[5].num_model++;
                    tab[5].prix_t+=voiture.prix_u;
                    tab[5].quantite_t+=voiture.quantite;
                }

                //recuperation des donne pour les statistique generales
                somme_p+=voiture.prix_u;
                somme_q+=voiture.quantite;
                count++;
            }
        }
    }

fclose(fichier);

prix_m=somme_p/count;


    printf("                  ______________________________________________________________________________________________\n");
    printf("                 |                                                                                              |\n");
    printf("                 |                                STATISTIQUES GENERALES                                        |\n");
    printf("                 |                  ___________________________________________________                         |\n");
    printf("                 |                                                                                              |\n");
    printf("                 |                                 VOITURE LA PLUS CHERE                                        |\n");
    printf("                 | id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %.2f $\n",
            voiture_max.id, voiture_max.nom, voiture_max.marque, voiture_max.quantite, voiture_max.prix_u);
    printf("                 |                  ___________________________________________________                         |\n");
    printf("                 |                                                                                              |\n");
    printf("                 |                                  VOITURE MOINS CHERE                                         |\n");
    printf("                 | id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %.2f $\n",
            voiture_min.id, voiture_min.nom, voiture_min.marque, voiture_min.quantite, voiture_min.prix_u);
    printf("                 |                  ___________________________________________________                         |\n");
    printf("                 |                                                                                              |\n");
    printf("                 |  Nom de la marque            nombre de model             Quantite totale            prix moyen|\n");

   for(int i=0;i<6;i++){
    prix_m_marq= tab[i].prix_t/ tab[i].num_model;

    printf("                 |%s                             %d                                %d                    %2.f $$$\n",tab[i].marque, tab[i].num_model, tab[i].quantite_t, prix_m_marq);
    }
    printf("                 |______________________________________________________________________________________________|\n");
    printf("\n                        prix moyen: %2.f $$$                                 quantite total=%d\n",prix_m, somme_q);

}


void credit(){
        printf("\033[33m");
        printf("                  _______________________________________________________________\n");
        printf("                 |                                                               |\n");
        printf("                 |                          DEEP INFORMATIONS                    |\n");
        printf("                 |                                                               |\n");
        printf("                 | Application developpe sous la direction de M. FOMEKONG, par : |\n");
        printf("                 |      -HAIBONWA RIBEGA                                         |\n");
        printf("                 |      -KEDIS LOIC                                              |\n");
        printf("                 |      -GOMSU ERIC                                              |\n");
        printf("                 |      -AYOWA FRIDA                                             |\n");
        printf("                 |      -MBY SAMMUEL                                             |\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |[par default]:designe l'option lance si le choix n'est pas valide|\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      Interface inspirer de CracksHash.com                     |\n");
        printf("                 |                                                               |\n");
        printf("                 |       Avec l'aide de: ChatGPT, Copilot,Meta IA,               |\n");
        printf("                 |       fondamentaux-programation[pdf]: AUTEUR M. Fomekong      |\n");
        printf("                 |        Le_langage_C[PDF] : www.zestedesavoir.com              |\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      NOM DE CODE DU PROJET :   concession CAMER MOTORS SPORT  |\n");
        printf("                 |_______________________________________________________________|\n");
        printf("\033[36m\n");

}
