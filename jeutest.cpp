#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "MAPfonction.h"



void jeuTest(SDL_Renderer* renderer) {
    // Afficher le texte d'introduction
    afficherTexte(renderer, "Bienvenue dans le jeu !", 24, 1280 / 2, 900 / 2);

    // Attendre 2 secondes
    SDL_Delay(2000);

    // Afficher le premier tour
    afficherTexte(renderer, "Tour 1 : Vous commencez avec un village.", 24, 1280 / 2, 900 / 2);

    // Attendre 2 secondes
    SDL_Delay(2000);

    // Afficher les choix pour le joueur
    afficherTexte(renderer, "Que voulez-vous faire ?", 24, 1280 / 2, 900 / 2 + 50);
    afficherTexte(renderer, "1. Recolter des ressources", 24, 1280 / 2, 900 / 2 + 100);
    afficherTexte(renderer, "2. Construire un batiment", 24, 1280 / 2, 900 / 2 + 150);

    // Attendre la réponse du joueur
    // Ici vous pouvez attendre que le joueur appuie sur une touche par exemple
    // ou utilisez la souris pour sélectionner une option

    // Simulation du choix du joueur
    int choix = 1; // Supposons que le joueur a choisi de récolter des ressources

    // Traiter la réponse du joueur
    switch (choix) {
        case 1:
            // Récolter des ressources
            afficherTexte(renderer, "Vous avez choisi de recolter des ressources.", 24, 1280 / 2, 900 / 2 + 200);
            // Autres actions à effectuer pour la récolte de ressources
            break;
        case 2:
            // Construire un bâtiment
            afficherTexte(renderer, "Vous avez choisi de construire un batiment.", 24, 1280 / 2, 900 / 2 + 200);
            // Autres actions à effectuer pour la construction d'un bâtiment
            break;
        default:
            // Gérer les cas invalides
            break;
    }

    // Attendre 2 secondes avant de passer à l'étape suivante
    SDL_Delay(2000);

    // Et ainsi de suite...
}
