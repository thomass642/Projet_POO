#include "MAPfonction.hpp"

bool isClickInsideImage(int clickX, int clickY, int imageX, int imageY, int imageWidth, int imageHeight) {
    return (clickX >= imageX && clickX <= imageX + imageWidth && clickY >= imageY && clickY <= imageY + imageHeight);
}

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


void highlightText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Color highlightColor, int x, int y) {
    // Créer une surface de texte normale
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, textColor);
    if (textSurface == nullptr) {
        SDL_Log("Erreur lors de la création de la surface de texte : %s", TTF_GetError());
        return;
    }

    // Créer une texture à partir de la surface de texte normale
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Obtenir les dimensions de la texture de texte
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    // Dessiner le texte normalement
    SDL_Rect textRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Dessiner un rectangle autour du texte pour le surligner
    SDL_SetRenderDrawColor(renderer, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
    SDL_RenderDrawRect(renderer, &textRect);

    // Libérer la texture et la surface de texte
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
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
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int width, int height, float healthPercentage, int vie_max) {
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
    int healthWidth = (int)(barWidth * (healthPercentage/vie_max));
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


void shield(SDL_Renderer* renderer, int x, int y, int defensseur) {
    // Charger l'image 
    SDL_Surface* defensseurSurface = IMG_Load("img/shield.png");
    if (defensseurSurface == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        return;
    }

    SDL_Texture* defensseurTexture = SDL_CreateTextureFromSurface(renderer, defensseurSurface);
    SDL_FreeSurface(defensseurSurface);
    if (defensseurTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image : %s", SDL_GetError());
        return;
    }

    // Dessiner le niveau à côté de l'image 
    std::string defensseurText = std::to_string(defensseur);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 16); // Charger une police de taille 16 
    if (font == nullptr) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        return;
    }

    SDL_Color textColor = {255, 255, 255}; // Couleur du texte 
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, defensseurText.c_str(), textColor);
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
    SDL_Rect defensseurRect = {x, y, 30, 30}; 
    SDL_RenderCopy(renderer, defensseurTexture, nullptr, &defensseurRect);

    // Dessiner le texte du niveau
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Libérer 
    SDL_DestroyTexture(defensseurTexture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}


// Fonction pour insérer des images à droite et à gauche d'une image centrale
void insertImages(SDL_Renderer* renderer, int centralX, int centralY, int centralWidth, int centralHeight, SDL_Texture* leftImage, int leftWidth, int leftHeight, SDL_Texture* rightImage, int rightWidth, int rightHeight) {
    
    // Calcul des positions des images
    int leftX = centralX - leftWidth;
    int leftY = centralY + (centralHeight - leftHeight) / 2;

    int rightX = centralX + centralWidth;
    int rightY = centralY + (centralHeight - rightHeight) / 2;

    // Rendu des images
    SDL_Rect leftRect = { leftX, leftY, leftWidth, leftHeight };
    SDL_Rect rightRect = { rightX, rightY, rightWidth, rightHeight };

    SDL_RenderCopy(renderer, leftImage, NULL, &leftRect);
    SDL_RenderCopy(renderer, rightImage, NULL, &rightRect);
}


void ressources(SDL_Renderer* renderer, int x, int y, int ressources) {
    // Charger l'image 
    SDL_Surface* manSurface = IMG_Load("img/ressources.png");
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
    std::string lifeText = std::to_string(ressources);
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
    textRect.x = x + 45; 
    textRect.y = y+10;

    // Dessiner l'image
    SDL_Rect heartRect = {x, y, 40, 40};
    SDL_RenderCopy(renderer, manTexture, nullptr, &heartRect);

    // Dessiner le texte du nombre
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Libérer
    SDL_DestroyTexture(manTexture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}


/*SelectedImage selectedImage = SelectedImage::VILLAGE; // Image initialement sélectionnée

// Fonction pour changer la sélection en fonction de la flèche cliquée
void changeSelection(bool goRight) {
    switch (selectedImage) {
        case SelectedImage::VILLAGE:
            selectedImage = (goRight) ? SelectedImage::FORTERESSE : SelectedImage::MAGICIEN;
            break;
        case SelectedImage::FORTERESSE:
            selectedImage = (goRight) ? SelectedImage::ECOLE_DE_MAGIE : SelectedImage::VILLAGE;
            break;
        case SelectedImage::ECOLE_DE_MAGIE:
            selectedImage = (goRight) ? SelectedImage::TROUPE_DE_GUERRE : SelectedImage::FORTERESSE;
            break;
        case SelectedImage::TROUPE_DE_GUERRE:
            selectedImage = (goRight) ? SelectedImage::MAGICIEN : SelectedImage::ECOLE_DE_MAGIE;
            break;
        case SelectedImage::MAGICIEN:
            selectedImage = (goRight) ? SelectedImage::VILLAGE : SelectedImage::TROUPE_DE_GUERRE;
            break;
    }
}*/

