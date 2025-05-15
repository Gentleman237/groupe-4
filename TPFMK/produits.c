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


char buffer[1024];
// Fonction qui met tous les caractères d'une chaîne en majuscule
void majuscule(char *chaine) {
    /*
    desc: cette fonction met tous les caractères d'une chaîne en majuscule
    arg: char *chaine, la chaîne à modifier
    */
    for(int i = 0; i < strlen(chaine); i++) {
        chaine[i] = toupper(chaine[i]);
    }
}

// Fonction qui vérifie que l'entier entré est supérieur à 0
int verif_entier() {
    /*
    desc: cette fonction vérifie que l'entier entré est supérieur à 0
    return: a entier
    */
    int a;
    int valide = 0;
    while (!valide) {
        if (scanf("%d", &a) == 1) {
            getchar();
            if (a > 0) {
                valide = 1;
            } else {
                printf("\033[31mIl faut entrer des valeurs correctes.\033[36m\n");
            }
        } else {
            printf("\033[31mCeci n'est pas un nombre. Veuillez ressaisir.\033[36m\n");
            scanf("%*s");
        }
    }
    return a;
}

// Fonction qui vérifie que le réel entré est supérieur à 0
float verif_decimal() {
    /*
    desc: cette fonction vérifie que le réel entré est supérieur à 0
    return: a réel
    */
    float a;
    int valide = 0;
    while (!valide) {
        if (scanf("%f", &a) == 1) {
            getchar();
            if (a > 0) {
                valide = 1;
            } else {
                printf("\033[31mIl faut entrer des valeurs correctes. Ressaisir.\033[36m\n");
            }
        } else {
            printf("\033[31mCeci n'est pas un nombre. Veuillez ressaisir.\033[36m\n");
            scanf("%*s");
        }
    }
    return a;
}

// Fonction qui vérifie l'existence du fichier
int verif_fichier(FILE *fichier) {
    /*
    desc: fonction qui vérifie l'existence du fichier et le crée s'il n'existe pas
    arg: fichier de type FILE
    return: int temp, entier qui détermine la nature de l'existence du fichier
    */
    int temp = 1;
    if (fichier == NULL) {
        printf("\033[31mErreur d'ouverture du fichier\033[36m. Nous venons de le créer.\n");
        FILE *fichiers = fopen("produit.csv", "w");
        fclose(fichiers);
        temp = 0;
    }
    return temp;
}

// Fonction qui vérifie l'existence d'un ID dans notre fichier produit.csv
int id_existe(int id) {
    /*
    desc: cette fonction vérifie l'existence d'un ID dans notre fichier produit.csv
    arg: int id, l'ID à rechercher
    return: 1 ou 0 en fonction du résultat de la recherche
    */
    FILE *fichier = fopen("produit.csv", "r");
    if (!verif_fichier(fichier)) {
        return 0;
    }
    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        produit voiture;
        if (sscanf(ligne, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
            if (voiture.id == id) {
                fclose(fichier);
                return 1;
            }
        }
    }
    fclose(fichier);
    return 0;
}

// Fonction qui affiche tous les produits contenus dans le fichier produit.csv
void afficher() {
    /*
    desc: cette fonction affiche tous les produits contenus dans le fichier produit.csv
    */
    produit voiture;
    FILE *fichier = fopen("produit.csv", "r");
    if (verif_fichier(fichier)) {
        char ligne[1024];
        printf("                  ______________________________________________________________________________________________\n");
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            if (sscanf(ligne, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
                printf("                 |      ___________________________________________________                                     |\n");
                printf("                 |                                                                                              |\n");
                printf("                 | id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %.2f $\n", voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
            }
        }       printf("                 |______________________________________________________________________________________________|\n");
    }
fclose(fichier);
}


void enregistrer(){
    produit voiture;
    FILE *fichier = fopen("produit.csv", "a");
    int temp;
    temp=verif_fichier(fichier);
    if (temp==1){
        printf("entrer le id du produit : ");
        voiture.id=verif_entier();
        if(!id_existe(voiture.id)){
            printf("entrer le nom du produit : ");
            fgets(buffer, sizeof(buffer), stdin);
            strncpy(voiture.nom,buffer,50);
            voiture.nom[strcspn(voiture.nom, "\n")] = 0;
            majuscule(voiture.nom);
            printf("entrer la marque : ");
            fgets(buffer, sizeof(buffer), stdin);
            strncpy(voiture.marque,buffer,50);
            voiture.marque[strcspn(voiture.marque, "\n")] = 0;
            majuscule(voiture.marque);
            printf("entrer la quantite : ");
            voiture.quantite=verif_entier();
            printf("entrer le prix unitaire (EN DOLLARS '$'): ");
            voiture.prix_u=verif_decimal();
            fprintf(fichier,"%d,%s,%s,%d,%f\n",voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
            printf("\033[32mEnregistrer avec succes.\n");
            printf("id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %2.f $\033[36m\n",voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);

        }
    }
    fclose(fichier);
}


void supprimer() {
    int id;
    printf("Entrer l'ID du produit a supprimer : ");
    id = verif_entier();

    if (!id_existe(id)) {
        printf("\033[31mDsl mais cet ID n'est pas valide ou n'existe pas\033[36m\n");
        return;
    }

    FILE *fichier = fopen("produit.csv", "r");
    FILE *fichier_temp = fopen("temp.csv", "w");

    if (!verif_fichier(fichier)) {
        return;
    }

    char ligne_produit[1024];
    while (fgets(ligne_produit, sizeof(ligne_produit), fichier) != NULL) {
        produit voiture;
        if (sscanf(ligne_produit, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
            if (voiture.id != id) {
                fprintf(fichier_temp, "%d,%s,%s,%d,%f\n", voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
            }
        }
    }

    fclose(fichier);
    fclose(fichier_temp);

    remove("produit.csv");
    rename("temp.csv", "produit.csv");

    printf("\033[32mProduit supprime avec succes.\033[36m\n");
}



void modifier() {
    /*
    desc: cette fonction permet de modifier les information d'un produit en reecrivant le nouveau dans un fichier temporaire
    que l'on va emplacer et renomer en produit.csv
    */
    int id,choix;
    printf("Entrer l'ID du produit a modifier : ");
    id = verif_entier();

    if (!id_existe(id)) {
        printf("\033[31mDesole, cet ID n'est pas valide ou n'existe pas.\033[36m\n");//verification de l'ID du produit a modifier
        return;
    }

    FILE *fichier = fopen("produit.csv", "r");
    FILE *fichier_temp = fopen("temp.csv", "w");//creation du fichier temporaire

    if (!verif_fichier(fichier)) {
        return;
    }

    char ligne_produit[1024];
    int modifie = 0;

    while (fgets(ligne_produit, sizeof(ligne_produit), fichier) != NULL) {
        produit voiture;

        if (sscanf(ligne_produit, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
            if (voiture.id == id) {
                printf("Produit trouve: \n");
                printf("id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %2.f $\n",voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);

                choix=1;
                printf("voulez vous modifier le nom 1:non (par default), 2: oui");
                choix=verif_entier();
                if (choix==2){
                    printf("Entrer le nom du produit (actuel : %s) : ", voiture.nom);
                    fgets(buffer, sizeof(buffer), stdin);
                    strncpy(voiture.nom,buffer,50);
                    voiture.nom[strcspn(voiture.nom, "\n")] = 0;
                    majuscule(voiture.nom);
                }

                choix=1;
                printf("voulez vous modifier la marque: 1:non (par default), 2: oui");
                choix=verif_entier();
                if(choix==2){
                    printf("Entrer la marque (actuelle : %s) : ", voiture.marque);
                    fgets(buffer, sizeof(buffer), stdin);
                    strncpy(voiture.marque,buffer,50);
                    voiture.marque[strcspn(voiture.marque, "\n")] = 0;
                    majuscule(voiture.marque);
                }

                choix=1;
                printf("voulez vous modifier la quantite: 1:non (par default), 2: oui");
                choix=verif_entier();
                if(choix==2){
                    printf("Entrer la quantite (actuelle : %d) : ", voiture.quantite);
                    voiture.quantite = verif_entier();
                }

                choix=1;
                printf("voulez vous modifier la quantite: 1:non (par default), 2: oui");
                choix=verif_entier();
                if(choix==2){
                    printf("Entrer le prix unitaire (actuel : %.2f $) : ", voiture.prix_u);
                    voiture.prix_u = verif_decimal();
                }
                modifie = 1;
                printf("\033[32m Produit modifie avec succes.\033[36m\n");
            }

            fprintf(fichier_temp, "%d,%s,%s,%d,%.2f\n", voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
        }
    }

    fclose(fichier);
    fclose(fichier_temp);

    if (!modifie) {
        printf("\033[31mAucune modification effectuee.\033[36m\n");
    }

    remove("produit.csv");// suppression de l'ancien fichier
    rename("temp.csv", "produit.csv");//renomer le fichier temporaire en produit.csv

}


void rechercher_voiture() {
    int choix;
    printf("Choisissez le critere de recherche:\n");
    printf("1: Nom et marque\n");
    printf("2: Intervalle de prix\n");
    printf("Entrez votre choix: ");
    choix = verif_entier();

    if (choix == 1) {
        char recherche[50];

        printf("Entrez le nom ou la marque du produit a rechercher : ");
        fgets(recherche, sizeof(recherche), stdin);
        recherche[strcspn(recherche, "\n")] = 0;
        majuscule(recherche);
        FILE *fichier = fopen("produit.csv", "r");
        if (!verif_fichier(fichier)) {
            return;
        }

        produit voiture;
        char ligne[1024];
        int trouve = 0;

        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            if (sscanf(ligne, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
                if ( strstr(voiture.nom, recherche) != NULL || strstr(voiture.marque, recherche)!= NULL) {
                    printf("id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %2.f$\n",
                           voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
                    trouve = 1;
                }
            }
        }

        if (!trouve) {
            printf("\033[31mAucun produit trouve avec les criteres specifies.\033[36m\n");
        }
        fclose(fichier);
    } else if (choix == 2) {
        float prix_min, prix_max;

        printf("Entrez le prix minimum: ");
        prix_min = verif_decimal();

        printf("Entrez le prix maximum: ");
        prix_max = verif_decimal();

        FILE *fichier = fopen("produit.csv", "r");
        if (!verif_fichier(fichier)) {
            return;
        }

        produit voiture;
        char ligne[1024];
        int trouve = 0;
        printf("\033[32mResultat de la recherche...\033[36m\n");
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            if (sscanf(ligne, "%d,%49[^,],%49[^,],%d,%f", &voiture.id, voiture.nom, voiture.marque, &voiture.quantite, &voiture.prix_u) == 5) {
                if (voiture.prix_u >= prix_min && voiture.prix_u <= prix_max) {
                    printf("id: %d, nom: %s, marque: %s, quantite: %d, prix unitaire: %2.f $\n",
                           voiture.id, voiture.nom, voiture.marque, voiture.quantite, voiture.prix_u);
                    trouve = 1;
                }
            }
        }

        if (!trouve) {
            printf("\033[31mAucun produit trouve dans l'intervalle de prix specifie.\033[36m\n");
        }

        fclose(fichier);
    } else {
        printf("\033[31mChoix invalide.\033[36m\n");
    }
}
