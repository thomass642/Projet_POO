#include <SDL2/SDL.h>
#include <string>


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

// Fonction pour dessiner une barre de vie
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int width, int height, float healthPercentage) {
    // Couleur de la barre de vie
    SDL_Color healthColor = { 0, 255, 0 }; // Vert

    // Déterminer la position et les dimensions de la barre de vie
    int barWidth = width / 2;
    int barHeight = 5;
    int barX = x + 5 ; // Position à côté de l'image
    int barY = y - 15;

    // Dessiner le contour de la barre de vie
    SDL_Rect outlineRect = { barX, barY, barWidth, barHeight };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
    SDL_RenderDrawRect(renderer, &outlineRect);

    // Dessiner la barre de vie intérieure (en fonction du pourcentage de vie restante)
    int healthWidth = (int)(barWidth * healthPercentage);
    SDL_Rect healthRect = { barX + 1, barY + 1, healthWidth - 1, barHeight - 1 };
    SDL_SetRenderDrawColor(renderer, healthColor.r, healthColor.g, healthColor.b, 255);
    SDL_RenderFillRect(renderer, &healthRect);
}

void number(SDL_Renderer* renderer, int x, int y, int count) {
    // Charger l'image 
    SDL_Surface* manSurface = IMG_Load("img/man.png");
    if (manSurface == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        return;
    }

    SDL_Texture* manTexture = SDL_CreateTextureFromSurface(renderer, manSurface);
    SDL_FreeSurface(manSurface);
    if (manTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image : %s", SDL_GetError());
        return;
    }

    // Dessiner le nombre de vies restantes à côté de l'image
    std::string lifeText = std::to_string(count);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 16); // Charger une police de taille 16 
    if (font == nullptr) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        return;
    }

    SDL_Color textColor = {255, 255, 255}; // Couleur du texte 
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, lifeText.c_str(), textColor);
    if (textSurface == nullptr) {
        SDL_Log("Erreur lors de la création de la surface de texte : %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Positionner le texte à côté de l'image
    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = x + 30; 
    textRect.y = y;

    // Dessiner l'image
    SDL_Rect heartRect = {x, y, 30, 30};
    SDL_RenderCopy(renderer, manTexture, nullptr, &heartRect);

    // Dessiner le texte du nombre
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Libérer
    SDL_DestroyTexture(manTexture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}



void level(SDL_Renderer* renderer, int x, int y, int level) {
    // Charger l'image 
    SDL_Surface* levelSurface = IMG_Load("img/level.png");
    if (levelSurface == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image du level : %s", IMG_GetError());
        return;
    }

    SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
    SDL_FreeSurface(levelSurface);
    if (levelTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image du level : %s", SDL_GetError());
        return;
    }

    // Dessiner le niveau à côté de l'image 
    std::string levelText = std::to_string(level);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 16); // Charger une police de taille 16 
    if (font == nullptr) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        return;
    }

    SDL_Color textColor = {255, 255, 255}; // Couleur du texte 
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, levelText.c_str(), textColor);
    if (textSurface == nullptr) {
        SDL_Log("Erreur lors de la création de la surface de texte : %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Positionner le texte à côté de l'image
    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = x + 30; 
    textRect.y = y;

    // Dessiner l'image 
    SDL_Rect levelRect = {x, y, 30, 30}; 
    SDL_RenderCopy(renderer, levelTexture, nullptr, &levelRect);

    // Dessiner le texte du niveau
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Libérer 
    SDL_DestroyTexture(levelTexture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}
