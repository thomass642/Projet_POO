#include <SDL2/SDL.h>

enum Element {
    ACTION,
    VILLAGE,
    FORTERESSE,
    ECOLE_DE_MAGIE,
    TROUPE_DE_GUERRE,
    MAGICIEN,
    NONE
};


// Fonction pour vérifier si les coordonnées du clic sont à l'intérieur d'une image
bool isClickInsideImage(int clickX, int clickY, int imageX, int imageY, int imageWidth, int imageHeight) {
    return (clickX >= imageX && clickX <= imageX + imageWidth && clickY >= imageY && clickY <= imageY + imageHeight);
}


// Fonction pour dessiner un cercle
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < 8; ++w) {
        int x = radius - 1 - w;
        int y = 0 + w;
        int tx = 1;
        int ty = 1;
        int error = tx - (radius << 1);

        while (x >= y) {
            SDL_RenderDrawPoint(renderer, centerX + x , centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

            if (error <= 0) {
                ++y;
                error += ty;
                ty += 2;
            }
            if (error > 0) {
                --x;
                tx += 2;
                error += tx - (radius << 1);
            }
        }
    }
}

void afficherTexte(SDL_Renderer* renderer, TTF_Font* font, const char* texte, int x, int y, SDL_Color couleur) {
    // Créer une surface de texte
    SDL_Surface* surfaceTexte = TTF_RenderText_Solid(font, texte, couleur);
    if (surfaceTexte == nullptr) {
        SDL_Log("Erreur lors de la création de la surface de texte : %s", TTF_GetError());
        return;
    }

    // Créer une texture à partir de la surface de texte
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
    if (textureTexte == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(surfaceTexte);
        return;
    }

    // Obtenir les dimensions de la surface de texte
    int largeur, hauteur;
    SDL_QueryTexture(textureTexte, nullptr, nullptr, &largeur, &hauteur);

    // Créer un rectangle de destination pour le texte
    SDL_Rect destRect = { x, y, largeur, hauteur };

    // Afficher le texte
    SDL_RenderCopy(renderer, textureTexte, nullptr, &destRect);

    // Libérer la surface de texte et la texture
    SDL_DestroyTexture(textureTexte);
    SDL_FreeSurface(surfaceTexte);
}