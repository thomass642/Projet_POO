#ifndef MAP_FUNC
#define MAP_FUNC
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

enum Element {
    ACTION,
    VILLAGE,
    FORTERESSE,
    ECOLE_DE_MAGIE,
    TROUPE_DE_GUERRE,
    MAGICIEN
    // Ajoutez d'autres éléments selon vos besoins
};


// Fonction pour vérifier si les coordonnées du clic sont à l'intérieur d'une image
bool isClickInsideImage(int clickX, int clickY, int imageX, int imageY, int imageWidth, int imageHeight);

// Fonction pour dessiner un cercle
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);

#endif