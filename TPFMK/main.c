#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "produits.h"
#include "commandes.h"
#include "stat.h"


int main() {
    int choix;
    printf("\033[036m Hello world!\n");
    do {
        printf("                  _______________________________________________________________\n");
        printf("                 |                                                               |\n");
        printf("                 |                          Bienvenue                            |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [1] Afficher le catalogue de voiture                     |\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [2] Enregistrer un nouveau vehicule                      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [3] Supprimer un vehicule                                |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [4] Modifier les information d'un vehicule               |\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [5] Rechercher                                           |\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [6] Acheter une voiture                                  |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [7] Historique d'achat                                   |\n");
        printf("                 |      ___________________________________________________      |\n");
        printf("                 |                                                               |\n");
        printf("                 |      [8] Credits         [9] Statistique        [10] sortir   |\n");
        printf("                 |                                                               |\n");
        printf("                 |               concession CAMER MOTORS SPORT                   |\n");
        printf("                 |_______________________________________________________________|\n");
        printf("\n");
        printf("entrer votre choix a partir du clavier [1,2,3,4,5,6,7,8,9,10] : ");
        choix = verif_entier();
        switch (choix) {
            case 1:
                afficher();
                break;
            case 2:
                enregistrer();
                break;
            case 3:
                afficher();

                supprimer();

                printf("\033[32m                       Catalogue mis a jour! \033[36m\n");
                afficher();
                break;
            case 4:
                afficher();
                modifier();
                break;
            case 5:
                rechercher_voiture();
                break;
            case 6:
                afficher();
                acheter_produit();
                break;
            case 7:
                histo_commande();
                break;
            case 8:
                credit();
                break;
            case 9:
                stat();
                break;
            case 10:
                printf("        \033[32mAu revoir !\033[36m\n");
                break;
            default:
                printf("        \033[31mchoix invalide\033[36m\n");
        }
    } while (choix > 0 && choix!=10);
    return 0;
}



