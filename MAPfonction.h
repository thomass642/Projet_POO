#ifndef MAP_FUNC
#define MAP_FUNC
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

enum Element1 {
    VILLAGE1,
    FORTERESSE1,
    ECOLE_DE_MAGIE1,
    TROUPE_DE_GUERRE1,
    MAGICIEN1,
    NONE1
};

enum Element2 {
    VILLAGE2,
    FORTERESSE2,
    ECOLE_DE_MAGIE2,
    TROUPE_DE_GUERRE2,
    MAGICIEN2,
    NONE2
};

// Fonction pour vérifier si les coordonnées du clic sont à l'intérieur d'une image
bool isClickInsideImage(int clickX, int clickY, int imageX, int imageY, int imageWidth, int imageHeight);

// Fonction pour dessiner un cercle
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);


void highlightText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Color highlightColor, int x, int y);


void afficherTexte(SDL_Renderer* renderer, TTF_Font* font, const char* texte, int x, int y, SDL_Color couleur);

// Fonction pour dessiner une barre de vie
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int width, int height, float healthPercentage);

void number(SDL_Renderer* renderer, int x, int y, int count);


void level(SDL_Renderer* renderer, int x, int y, int level);


void shield(SDL_Renderer* renderer, int x, int y, int defensseur);




// Fonction pour changer la sélection en fonction de la flèche cliquée
void changeSelection(bool goRight);

#endif