#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "produits.h"

// Définition de la structure produit
typedef struct {
    int id;
    char nom[50];
    char marque[50];
    int quantite;
    float prix_u;
} produit;

void acheter_produit() {
    int id, i=0;
    int continu=1;
    produit tab[10];
    do {
        printf("Entrez l'ID du produit a acheter : ");
        id = verif_entier();

        if (!id_existe(id)) {
            printf("\033[31mCet ID n'existe pas.\033[36m\n");
            return;
        }

        FILE *fichier = fopen("produit.csv", "r");
        FILE *fichier_temp = fopen("temp.csv", "w");

        if (!verif_fichier(fichier) || !verif_fichier(fichier_temp)) return;

        produit voiture;
        char ligne[1024];
        int quantite_acheter;
        int trouve = 0;

        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            if (sscanf(ligne, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
                if (voiture.id == id) {
                    trouve = 1;
                    printf("VEHICULE: %s %s. Quantite disponible : %d\n",voiture.marque, voiture.nom, voiture.quantite);
                    printf("Entrez la quantite a acheter : ");
                    quantite_acheter = verif_entier();

                    if (quantite_acheter > voiture.quantite) {
                        printf("\033[31mQuantite insuffisante. Poduit retire du panier\033[36m\n");
                    } else {
                        voiture.quantite -= quantite_acheter;

                        tab[i].id = voiture.id;
                        strcpy(tab[i].nom, voiture.nom);
                        strcpy(tab[i].marque, voiture.marque);
                        tab[i].quantite = quantite_acheter;
                        tab[i].prix_u= voiture.prix_u;
                        i++;

                        printf("\033[32mProduit ajoute au panier avec succes.\033[36m\n");
                        printf("voulez vous ajouter un autre produit ?  [1]: non (par default), [2] oui  :\n");
                        continu=verif_entier();
                    }
                }

                fprintf(fichier_temp, "%d,%s,%s,%d,%.2f\n", voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
            }
        }

        if (!trouve) {
            printf("\033[31mProduit non trouve.\033[36m\n");
        }

        fclose(fichier);
        fclose(fichier_temp);

        remove("produit.csv");
        rename("temp.csv", "produit.csv");

    }while(continu==2);
    generer_facture(tab,i);
}

// Fonction pour generer une facture
void generer_facture(produit tab[10], int taille) {
    if (taille == 0) {
        printf("\033[31mAucun produit dans le panier.\033[36m\n");
        return;
    }
    float prix_total;
    FILE *facture = fopen("facture.txt", "w");
    if (!verif_fichier(facture)){
            return;
    }

    float total = 0;
    time_t now;
    struct tm *heureActuelle;

    // Récupérer l'heure actuelle
    now = time(NULL);

    // Convertir l'heure actuelle en struct tm
    heureActuelle = localtime(&now);

    // Afficher l'heure et la date actuelles
    printf("Date : %04d-%02d-%02d\n", heureActuelle->tm_year + 1900, heureActuelle->tm_mon + 1, heureActuelle->tm_mday);
    printf("Heure : %02d:%02d:%02d\n", heureActuelle->tm_hour, heureActuelle->tm_min, heureActuelle->tm_sec);

    fprintf(facture,"                  ______________________________________________________________________________________________\n");
    fprintf(facture,"                 |       Date : %04d-%02d-%02d                                     Heure : %02d:%02d:%02d                 |\n",
            heureActuelle->tm_year + 1900, heureActuelle->tm_mon + 1, heureActuelle->tm_mday, heureActuelle->tm_hour, heureActuelle->tm_min, heureActuelle->tm_sec);
    fprintf(facture,"                 |                                       Facture d'achat                                        |\n");
    fprintf(facture,"                 |                  ___________________________________________________                         |\n");
    fprintf(facture,"                 |                                                                                              |\n");
    fprintf(facture,"                 |ID |         Nom              Marque          Quantite         prix unitaire             Total|\n");

    for (int i = 0; i < taille; i++) {
                prix_total=tab[i].quantite * tab[i].prix_u;
    fprintf(facture,"                 |%d          %s      %s               %d              %2.f $             %2.f $\n",
            tab[i].id,tab[i].nom, tab[i].marque, tab[i].quantite, tab[i].prix_u, prix_total);
                total += prix_total;
    }

    fprintf(facture,"                 |______________________________________________________________________________________________|\n");
    fprintf(facture,"\n                                                           Total a payer : %.2f $      \n", total);
    fclose(facture);

    FILE *fichier = fopen("facture.txt", "r");
    FILE *historique = fopen("commande.csv", "a");
    if(historique==NULL){
        historique = fopen("commande.csv", "r");
    }
    char ligne[1024];
    printf("\033[32mFacture generee avec succes. (facture.txt)\033[36m\n");
    fprintf(historique,"\n     _      _______________ _______________ ___________________ _____________________ ______________________ ____________________\n");

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
        fprintf(historique,"%s", ligne);

    }
    fclose(fichier);
    fclose(historique);
}

void histo_commande(){
     FILE *historique = fopen("commande.csv", "r");
     char ligne[1024];
     while (fgets(ligne, sizeof(ligne), historique) != NULL) {
        printf("%s", ligne);
     }
}

