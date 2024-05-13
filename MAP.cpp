#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "MAPfonction.h"

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL : %s", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL_ttf : %s", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("MAP",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280, 900,SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Erreur lors de la création du renderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("img/background.jpg");
    if (backgroundSurface == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image de fond : %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (backgroundTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de fond : %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargez une police TTF
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Utilisez le chemin approprié vers votre fichier de police

    if (font == nullptr) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Créez une surface noire pour le rendu du texte
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Welcome dans la partie !", {255, 255, 255}); // Couleur blanche
    if (textSurface == nullptr) {
        SDL_Log("Erreur lors de la création de la surface de texte : %s", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Créez une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Positionnez le texte au centre de la fenêtre "MAP"
    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = (1280 - textRect.w) / 2;
    textRect.y = (900 - textRect.h) / 2;



    //------------------------------------------------------------------------------------------------------------


    /// Insertion VILLAGE NIVEAU 1 
    SDL_Surface* imageSurface = IMG_Load("img/village/village1.jpg");
    if (imageSurface == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (imageTexture == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image de fond
    int backgroundWidth, backgroundHeight;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundWidth, &backgroundHeight);

    // Récupérer les dimensions de l'image à insérer
    int imageWidth, imageHeight;
    SDL_QueryTexture(imageTexture, NULL, NULL, &imageWidth, &imageHeight);

    // Déterminer la position où insérer l'image
    int x = 15; 
    int y = 320;

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthV = imageWidth/3;
    int heightV = imageHeight/3;




    /// Insertion FORTERESSE NIVEAU 1
    SDL_Surface* imageSurfacef = IMG_Load("img/forteresse/forteresse1.jpg");
    if (imageSurfacef == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTexturef = SDL_CreateTextureFromSurface(renderer, imageSurfacef);
    SDL_FreeSurface(imageSurfacef);
    if (imageTexturef == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image à insérer
    SDL_QueryTexture(imageTexturef, NULL, NULL, &imageWidth, &imageHeight);

    // Déterminer la position où insérer l'image
    int xf = 50; 
    int yf = 100;

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthF = imageWidth/6;
    int heightF = imageHeight/6;




    /// Insertion ECOLE DE MAGIE NIVEAU 1
    SDL_Surface* imageSurfacem = IMG_Load("img/ecole de magie/1.jpg");
    if (imageSurfacem == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTexturem = SDL_CreateTextureFromSurface(renderer, imageSurfacem);
    SDL_FreeSurface(imageSurfacem);
    if (imageTexturem == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image à insérer
    SDL_QueryTexture(imageTexturem, NULL, NULL, &imageWidth, &imageHeight);

    // Déterminer la position où insérer l'image
    int xm = 60; 
    int ym = 520;

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthM = imageWidth/5;
    int heightM = imageHeight/5;



    /// Insertion TROUPE DE GUERRE NIVEAU 1
    SDL_Surface* imageSurfaceg = IMG_Load("img/troupe de guerre/1.jpg");
    if (imageSurfaceg == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTextureg = SDL_CreateTextureFromSurface(renderer, imageSurfaceg);
    SDL_FreeSurface(imageSurfaceg);
    if (imageTextureg == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image à insérer
    SDL_QueryTexture(imageTextureg, NULL, NULL, &imageWidth, &imageHeight);

    // Déterminer la position où insérer l'image
    int xg = 300; 
    int yg = 250;

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthG = imageWidth/7;
    int heightG = imageHeight/7;




    /// Insertion MAGICIEN NIVEAU 1
    SDL_Surface* imageSurfacema = IMG_Load("img/magicien/1.jpg");
    if (imageSurfacema == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTexturema = SDL_CreateTextureFromSurface(renderer, imageSurfacema);
    SDL_FreeSurface(imageSurfacema);
    if (imageTexturema == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image à insérer
    SDL_QueryTexture(imageTexturema, NULL, NULL, &imageWidth, &imageHeight);

    // Déterminer la position où insérer l'image
    int xma = 320; 
    int yma = 450;

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthMA = imageWidth/5;
    int heightMA = imageHeight/5;



    //---------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------


    Element highlightedElement = NONE;

    int nb_travailleur1 = 2;
    int nb_travailleur2 = 2;
    int nb_troupe_geurre1 = 0;
    int nb_troupe_geurre2 = 0;
    int nb_magicien1 = 0;
    int nb_magicien2 = 0;

    int level_village1 = 1;
    int level_village2 = 1;
    int level_forteresse1 = 1;
    int level_forteresse2 = 1;
    int level_ecole_magie1 = 1;
    int level_ecole_magie2 = 1;
    int level_troupe_guerre1 = 1;
    int level_troupe_guerre2 = 1;
    int level_magicien1 = 1;
    int level_magicien2 = 1;



    // Boucle principale
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Si un clic de souris est détecté, obtenir les coordonnées du clic
                int clickX = event.button.x;
                int clickY = event.button.y;


                // Vérifier si les coordonnées du clic sont à l'intérieur de l'image
                if (isClickInsideImage(clickX, clickY, x, y, widthV, heightV)) {
                    SDL_Log("Village !");
                    highlightedElement = VILLAGE;
                } else if (isClickInsideImage(clickX, clickY, xf, yf, widthF, heightF)){
                    SDL_Log("Forteresse !");
                    highlightedElement = FORTERESSE;
                } else if (isClickInsideImage(clickX, clickY, xm, ym, widthM, heightM)){
                    SDL_Log("Ecole de magie !");
                    highlightedElement = ECOLE_DE_MAGIE;
                } else if (isClickInsideImage(clickX, clickY, xg, yg, widthG, heightG)){
                    SDL_Log("Troupe de guerre !");
                    highlightedElement = TROUPE_DE_GUERRE;
                } else if (isClickInsideImage(clickX, clickY, xma, yma, widthMA, heightMA)){
                    SDL_Log("Magicien !");
                    highlightedElement = MAGICIEN;
                }
            }
        }

        // Effacer l'écran
        SDL_RenderClear(renderer);

        // Dessiner l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Afficher le texte
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);


        // Afficher les choix en fonction de l'élément mis en surbrillance
        switch (highlightedElement) {
            case VILLAGE:
                // Afficher les choix pour le village
                SDL_Log("Choix pour le village :");
                SDL_Log("1. Améliorer la défense");
                SDL_Log("2. Recruter des habitants");
                SDL_Log("3. Construire une ferme");
                break;
            case FORTERESSE:
                // Afficher les choix pour la forteresse
                SDL_Log("Choix pour la forteresse :");
                SDL_Log("1. Améliorer les remparts");
                SDL_Log("2. Former des soldats");
                SDL_Log("3. Construire une tour de guet");
                break;
            case ECOLE_DE_MAGIE:
                // Afficher les choix pour l'école de magie
                SDL_Log("Choix pour l'école de magie :");
                SDL_Log("1. Rechercher de nouveaux sorts");
                SDL_Log("2. Recruter des apprentis");
                SDL_Log("3. Améliorer les installations");
                break;
            case TROUPE_DE_GUERRE:
                // Afficher les choix pour la troupe de guerre
                SDL_Log("Choix pour la troupe de guerre :");
                SDL_Log("1. Entraîner les soldats");
                SDL_Log("2. Recruter des mercenaires");
                SDL_Log("3. Améliorer l'équipement");
                break;
            case MAGICIEN:
                // Afficher les choix pour le magicien
                SDL_Log("Choix pour le magicien :");
                SDL_Log("1. Étudier de nouveaux sorts");
                SDL_Log("2. Entraîner ses pouvoirs");
                SDL_Log("3. Chercher des artefacts magiques");
                break;
            default:
                // Aucun élément mis en surbrillance, aucun choix à afficher
                break;
        }


        // Dessiner les 2 villages niveau 1
        SDL_Rect dstRect = {x, y, widthV, heightV};
        if (highlightedElement == VILLAGE){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, x + y / 2 - 25, y + heightV / 2, widthV / 2 - 5); // Cercle autour de l'image
        }
        drawHealthBar(renderer, x, y, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        number(renderer, x, y, nb_travailleur1); // Afficher le nombre de travaileurs
        level(renderer, x, y+35, level_village1);
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);

        SDL_Rect dstRect2 = {1000, y, widthV, heightV};
        drawHealthBar(renderer, 1000, y, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        number(renderer, 1000, y, nb_travailleur2); // Afficher le nombre de travaileurs
        level(renderer, 1000, y+35, level_village2);
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect2);


        // Dessiner les 2 forteresses niveau 1
        SDL_Rect dstRectf = {xf, yf, widthF, heightF};
        if (highlightedElement == FORTERESSE){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, xf + yf / 2 + 50, yf + heightF / 2, widthF / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xf, yf, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        level(renderer, xf, yf, level_forteresse1);
        SDL_RenderCopy(renderer, imageTexturef, NULL, &dstRectf);

        SDL_Rect dstRectf2 = {1030, yf, widthF, heightF};
        drawHealthBar(renderer, 1030, yf, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        level(renderer, 1030, yf, level_forteresse2);
        SDL_RenderCopy(renderer, imageTexturef, NULL, &dstRectf2);


        // Dessiner les 2 ecoles de magie niveau 1
        SDL_Rect dstRectm = {xm, ym, widthM, heightM};
        if (highlightedElement == ECOLE_DE_MAGIE){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, xf + yf / 2 + 40, ym + heightM / 2 + 5, widthF / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xm, ym, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        level(renderer, xm, ym, level_ecole_magie1);
        SDL_RenderCopy(renderer, imageTexturem, NULL, &dstRectm);

        SDL_Rect dstRectm2 = {1050, ym, widthM, heightM};
        drawHealthBar(renderer, 1050, ym, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        level(renderer, 1050, ym, level_ecole_magie2);
        SDL_RenderCopy(renderer, imageTexturem, NULL, &dstRectm2);


        // Dessiner les 2 troupes de guerre niveau 1
        SDL_Rect dstRectg = {xg, yg, widthG, heightG};
        if (highlightedElement == TROUPE_DE_GUERRE){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, xg + yg / 2 - 35, yg + heightG / 2 + 5, widthG / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xg, yg, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        number(renderer, xg + 130, yg - 25, nb_troupe_geurre1); // Afficher le nombre de troupe de guerre
        level(renderer, xg +130, yg+10, level_troupe_guerre1);
        SDL_RenderCopy(renderer, imageTextureg, NULL, &dstRectg);

        SDL_Rect dstRectg2 = {810, yg, widthG, heightG};
        drawHealthBar(renderer, 810, yg, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        number(renderer, 810 + 130, yg -25, nb_troupe_geurre2); // Afficher le nombre de troupe de guerre
        level(renderer, 810 +130, yg+10, level_troupe_guerre2);
        SDL_RenderCopy(renderer, imageTextureg, NULL, &dstRectg2);


        // Dessiner les 2 magiciens niveau 1
        SDL_Rect dstRectma = {xma , yma, widthMA, heightMA};
        if (highlightedElement == MAGICIEN){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, (xma + yma) / 2 , yma + heightMA / 2 + 5, widthG / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xma, yma, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        number(renderer, xma + 120, yma -25, nb_magicien2); // Afficher le nombre de magicien
        level(renderer, xma +120, yma+10, level_magicien1);
        SDL_RenderCopy(renderer, imageTexturema, NULL, &dstRectma);

        SDL_Rect dstRectma2 = {820, yma, widthMA, heightMA};
        drawHealthBar(renderer, 820, yma, 200, heightV, 0.75); // Exemple: barre de vie à 75%
        number(renderer, 820 + 120, yma -25, nb_magicien2); // Afficher le nombre de magicien
        level(renderer, 820+120, yma+10, level_magicien2);
        SDL_RenderCopy(renderer, imageTexturema, NULL, &dstRectma2);


        // Afficher ce qui a été dessiné
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
        highlightedElement = NONE;
    }



    // Libération des ressources et fermeture de SDL
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(imageTexturef);
    SDL_DestroyTexture(imageTexturem);
    SDL_DestroyTexture(imageTextureg);
    SDL_DestroyTexture(imageTexturema);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
