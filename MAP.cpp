#include "MAP.hpp"
// g++ -o mat MAP.cpp MAPfonction.cpp  -lSDL2 -lSDL2_image -lSDL2_ttf


// int main(int argc, char* argv[]) {
int interface() {

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
    SDL_Surface* imageSurfacem = IMG_Load("img/ecole de magie/ecole.png");
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




    /// Insertion FLECHE POUR SELECTIONNER DROITE
    SDL_Surface* imageSurfacefl = IMG_Load("img/arrow.png");
    if (imageSurfacefl == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTexturefl = SDL_CreateTextureFromSurface(renderer, imageSurfacefl);
    SDL_FreeSurface(imageSurfacefl);
    if (imageTexturefl == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image à insérer
    SDL_QueryTexture(imageTexturefl, NULL, NULL, &imageWidth, &imageHeight);

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthFL = imageWidth/8;
    int heightFL = imageHeight/8;


    /// Insertion FLECHE POUR SELECTIONNER GAUCHE
    SDL_Surface* imageSurfaceflg = IMG_Load("img/arrowleft.png");
    if (imageSurfaceflg == nullptr) {
        SDL_Log("Erreur lors du chargement de l'image à insérer : %s", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTextureflg = SDL_CreateTextureFromSurface(renderer, imageSurfaceflg);
    SDL_FreeSurface(imageSurfaceflg);
    if (imageTextureflg == nullptr) {
        SDL_Log("Erreur lors de la création de la texture de l'image à insérer : %s", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Récupérer les dimensions de l'image à insérer
    SDL_QueryTexture(imageTextureflg, NULL, NULL, &imageWidth, &imageHeight);

    // Redimensionner l'image à insérer (par exemple, à la moitié de sa taille)
    int widthFLg = imageWidth/8;
    int heightFLg = imageHeight/8;


    

    //---------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------


    Element1 highlightedElement1 = NONE1;
    Element2 highlightedElement2 = NONE2; 

    int nb_travailleur1 = 2;
    int nb_travailleur2 = 2;
    int nb_troupe_geurre1 = 0;
    int nb_troupe_geurre2 = 0;
    int nb_magicien1 = 0;
    int nb_magicien2 = 0;

    int level_village1 = 1;
    int level_village2 = 1;
    int level_forteresse1 = 1;
    int level_forteresse2 ;
    int level_ecole_magie1 = 1;
    int level_ecole_magie2 = 1;
    int level_troupe_guerre1 = 1;
    int level_troupe_guerre2 = 1;
    int level_magicien1 = 1;
    int level_magicien2 = 1;


    int clickX ;
    clickX = -1;
    int clickY ;
    clickY = -1;


    // Boucle principale
    bool running = true;
    SDL_Event event;
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }else if (event.type == SDL_MOUSEBUTTONDOWN) {


                // Si un clic de souris est détecté, obtenir les coordonnées du clic
                clickX = event.button.x;
                clickY = event.button.y;



                // ELEMENT DU JOUEUR 1
                if (isClickInsideImage(clickX, clickY, x, y, widthV, heightV)) {
                    SDL_Log("Village 1!");
                    highlightedElement1 = VILLAGE1;
                } else if (isClickInsideImage(clickX, clickY, xf, yf, widthF, heightF)){
                    SDL_Log("Forteresse 1!");
                    highlightedElement1 = FORTERESSE1;
                } else if (isClickInsideImage(clickX, clickY, xm, ym, widthM, heightM)){
                    SDL_Log("Ecole de magie 1!");
                    highlightedElement1 = ECOLE_DE_MAGIE1;
                } else if (isClickInsideImage(clickX, clickY, xg, yg, widthG, heightG)){
                    SDL_Log("Troupe de guerre 1!");
                    highlightedElement1 = TROUPE_DE_GUERRE1;   
                } else if (isClickInsideImage(clickX, clickY, xma, yma, widthMA, heightMA)){
                    SDL_Log("Magicien 1!");
                    highlightedElement1 = MAGICIEN1;
                }

                // ELEMENT DU JOUEUR 2
                else if (isClickInsideImage(clickX, clickY, 1000, y, widthV, heightV)){
                    SDL_Log("Village 2!");
                    highlightedElement2 = VILLAGE2;
                    changeVillage2(&DONNEES);
                } else if (isClickInsideImage(clickX, clickY, 1030, yf, widthF, heightF)){
                    SDL_Log("Forteresse 2!");
                    highlightedElement2 = FORTERESSE2;
                } else if (isClickInsideImage(clickX, clickY, 1050, ym, widthM, heightM)){
                    SDL_Log("Ecole de magie 2!");
                    highlightedElement2 = ECOLE_DE_MAGIE2;
                } else if (isClickInsideImage(clickX, clickY, 810, yg, widthG, heightG)){
                    SDL_Log("Troupe de guerre 2!");
                    highlightedElement2 = TROUPE_DE_GUERRE2;
                } else if (isClickInsideImage(clickX, clickY, 820, yma, widthMA, heightMA)){
                    SDL_Log("Magicien 2!");
                    highlightedElement2 = MAGICIEN2;
                } 

            }
        }

        // Effacer l'écran
        SDL_RenderClear(renderer);

        // Dessiner l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Afficher le texte
        //SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);





//-----------------------------------------------------------------------------------------------------------------
        /// AFFICHER LES BAT ET PERSO -----------------------------------------------------------------------------


        // Dessiner les 2 villages niveau 1
        SDL_Rect dstRect = {x, y, widthV, heightV};
        if (highlightedElement1 == VILLAGE1){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, x + y / 2 - 25, y + heightV / 2, widthV / 2 - 5); // Cercle autour de l'image
        }
        drawHealthBar(renderer, x, y, 200, heightV, DONNEES.j1.base.vie,FACTO_VIE_BASE,DONNEES.j1.base.niveau); 
        number(renderer, x, y, DONNEES.j1.nb_travailleurs); // Afficher le nombre de travaileurs
        level(renderer, x, y+35, DONNEES.j1.base.niveau);
        shield(renderer, x+145, y-28, DONNEES.j1.base.nb_defenseurs);
        drawHealthBar(renderer, x+185, y, 100, heightV, DONNEES.j1.base.vie_premier_defenseur,FACTO_VIE_SOLDAT, DONNEES.j1.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);

        SDL_Rect dstRect2 = {1000, y, widthV, heightV};
        if (highlightedElement2 == VILLAGE2){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, 1000 + y / 2 - 25, y + heightV / 2, widthV / 2 - 5); // Cercle autour de l'image
        }
        drawHealthBar(renderer, 1000, y, 200, heightV, DONNEES.j2.base.vie,FACTO_VIE_BASE,DONNEES.j2.base.niveau); 
        number(renderer, 1000, y, DONNEES.j2.nb_travailleurs); // Afficher le nombre de travaileurs
        level(renderer, 1000, y+35, DONNEES.j2.base.niveau);
        shield(renderer, 1000+145, y-28, DONNEES.j2.base.nb_defenseurs);
        drawHealthBar(renderer, 1000+185, y, 100, heightV, DONNEES.j2.base.vie_premier_defenseur,FACTO_VIE_SOLDAT,DONNEES.j2.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect2);


        // Dessiner les 2 forteresses niveau 1
        SDL_Rect dstRectf = {xf, yf, widthF, heightF};
        if (highlightedElement1 == FORTERESSE1){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, xf + yf / 2 + 50, yf + heightF / 2, widthF / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xf, yf, 200, heightV, DONNEES.j1.forteresse.vie,FACTO_VIE_FORTERESSE,DONNEES.j1.forteresse.niveau); 
        level(renderer, xf, yf, DONNEES.j1.forteresse.niveau);
        shield(renderer, xf+145, yf-28, DONNEES.j1.forteresse.nb_defenseurs);
        drawHealthBar(renderer, xf+185, yf, 100, heightV, DONNEES.j1.forteresse.vie_premier_defenseur,FACTO_VIE_SOLDAT,DONNEES.j1.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTexturef, NULL, &dstRectf);

        SDL_Rect dstRectf2 = {1030, yf, widthF, heightF};
        if (highlightedElement2 == FORTERESSE2){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, 1030 + yf / 2 + 50, yf + heightF / 2, widthF / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, 1030, yf, 200, heightV, DONNEES.j2.forteresse.vie,FACTO_VIE_FORTERESSE,DONNEES.j2.forteresse.niveau); 
        level(renderer, 1030, yf, DONNEES.j2.forteresse.niveau);
        shield(renderer, 1030+145, yf-28, DONNEES.j2.forteresse.nb_defenseurs);
        drawHealthBar(renderer, 1030+185, yf, 100, heightV, DONNEES.j2.forteresse.vie_premier_defenseur,FACTO_VIE_SOLDAT,DONNEES.j2.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTexturef, NULL, &dstRectf2);


        // Dessiner les 2 ecoles de magie niveau 1
        SDL_Rect dstRectm = {xm, ym, widthM, heightM};
        if (highlightedElement1 == ECOLE_DE_MAGIE1){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, xf + yf / 2 + 40, ym + heightM / 2 + 5, widthF / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xm-30, ym, 200, heightV, DONNEES.j1.ecole_magie.vie,FACTO_VIE_ECOLE_MAGIE,DONNEES.j1.ecole_magie.niveau); 
        level(renderer, xm-30, ym, DONNEES.j1.ecole_magie.niveau);
        shield(renderer, xm+115, ym-28, DONNEES.j1.ecole_magie.nb_defenseurs);
        drawHealthBar(renderer, xm+155, ym, 100, heightV, DONNEES.j1.ecole_magie.vie_premier_defenseur,FACTO_VIE_SOLDAT,DONNEES.j1.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTexturem, NULL, &dstRectm);

        SDL_Rect dstRectm2 = {1050, ym, widthM, heightM};
        if (highlightedElement2 == ECOLE_DE_MAGIE2){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, 1050 + yf / 2 + 40, ym + heightM / 2 + 5, widthF / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, 1050-30, ym, 200, heightV, DONNEES.j2.ecole_magie.vie,FACTO_VIE_ECOLE_MAGIE,DONNEES.j2.ecole_magie.niveau); 
        level(renderer, 1050-30, ym, DONNEES.j2.ecole_magie.niveau);
        shield(renderer, 1050+115, ym-28, DONNEES.j2.ecole_magie.nb_defenseurs);
        drawHealthBar(renderer, 1050+155, ym, 100, heightV, DONNEES.j2.ecole_magie.vie_premier_defenseur,FACTO_VIE_SOLDAT,DONNEES.j2.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTexturem, NULL, &dstRectm2);


        // Dessiner les 2 troupes de guerre niveau 1
        SDL_Rect dstRectg = {xg, yg, widthG, heightG};
        if (highlightedElement1 == TROUPE_DE_GUERRE1){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, xg + yg / 2 - 35, yg + heightG / 2 + 5, widthG / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xg, yg, 200, heightV, DONNEES.j1.select_vie_sold,FACTO_VIE_SOLDAT,DONNEES.j1.select_niveau_sold); 
        number(renderer, xg + 130, yg - 25, DONNEES.j1.listesoldats.size()); // Afficher le nombre de troupe de guerre
        level(renderer, xg +130, yg+10, DONNEES.j1.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTextureg, NULL, &dstRectg);

        SDL_Rect dstRectg2 = {810, yg, widthG, heightG};
        if (highlightedElement2 == TROUPE_DE_GUERRE2){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, 810 + yg / 2 - 35, yg + heightG / 2 + 5, widthG / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, 810, yg, 200, heightV, DONNEES.j2.select_vie_sold,FACTO_VIE_SOLDAT,DONNEES.j2.select_niveau_sold); 
        number(renderer, 810 + 130, yg -25, DONNEES.j2.listesoldats.size()); // Afficher le nombre de troupe de guerre
        level(renderer, 810 +130, yg+10, DONNEES.j2.select_niveau_sold);
        SDL_RenderCopy(renderer, imageTextureg, NULL, &dstRectg2);


        // Dessiner les 2 magiciens niveau 1
        SDL_Rect dstRectma = {xma , yma, widthMA, heightMA};
        if (highlightedElement1 == MAGICIEN1){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, (xma + yma) / 2 , yma + heightMA / 2 + 5, widthG / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, xma, yma, 200, heightV, DONNEES.j1.select_vie_mag,FACTO_VIE_MAGICIEN,DONNEES.j1.select_niveau_mag); 
        number(renderer, xma + 120, yma -25, DONNEES.j1.listemagiciens.size()); // Afficher le nombre de magicien
        level(renderer, xma +120, yma+10, DONNEES.j1.select_niveau_mag);
        SDL_RenderCopy(renderer, imageTexturema, NULL, &dstRectma);

        SDL_Rect dstRectma2 = {820, yma, widthMA, heightMA};
        if (highlightedElement2 == MAGICIEN2){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune
            drawCircle(renderer, 660 + yma / 2 , yma + heightMA / 2 + 5, widthG / 2 ); // Cercle autour de l'image
        }
        drawHealthBar(renderer, 820, yma, 200, heightV, DONNEES.j2.select_vie_mag,FACTO_VIE_MAGICIEN,DONNEES.j2.select_niveau_mag); 
        number(renderer, 820 + 120, yma -25, DONNEES.j2.listemagiciens.size()); // Afficher le nombre de magicien
        level(renderer, 820+120, yma+10, DONNEES.j2.select_niveau_mag);
        SDL_RenderCopy(renderer, imageTexturema, NULL, &dstRectma2);


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( DONNEES.tour_joueur == 1 ) { 
            afficherTexte(renderer, font, DONNEES.j1.nomj.c_str(), 600, 100, {100,0,50,0});
            ressources(renderer,600,130,DONNEES.j1.ressources);
        } else {
            afficherTexte(renderer, font, DONNEES.j2.nomj.c_str(), 600, 100, {100,0,50,0});
            ressources(renderer,600,130,DONNEES.j2.ressources);
        }
        
        const char* info = DONNEES.texteinfo.c_str(); // convertir string en const char*
        
        afficherTexte(renderer, font, info,500,180, {255,255,255,0});




        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// JOUEUR 1 //////////////////////////////////////////////////////////////////////////////////////////////////////////
                
        if ( DONNEES.tour_joueur == 1 ){


            // DEBUT JOUEUR
            if(tourjeu == NONE && action == FORMATION_TROUPE && choice == NONE_CHOICE){
                afficherTexte(renderer, font,"Oui",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Non",650,400,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,50,30)){
                    std::cout << "Oui pour former des ressources!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                    choice = OUI;

                } else if(isClickInsideImage(clickX,clickY,650,400,50,30)){
                    std::cout << "Non pour former des ressources!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }

            }

            if (tourjeu == NONE && action == FORMATION_TROUPE && choice == OUI){

                afficherTexte(renderer, font,"Arreter la formation",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Travailleurs",550,550,{255,255,255,0});
                afficherTexte(renderer, font,"Soldats",550,600,{255,255,255,0});
                afficherTexte(renderer, font,"Magiciens",550,650,{255,255,255,0});
                
                if (isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "arret formation!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "travailleurs!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                } else if(isClickInsideImage(clickX,clickY,550,600,200,30)){
                    std::cout << "soldat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                } else if(isClickInsideImage(clickX,clickY,550,650,200,30)){
                    std::cout << "mag!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                }
            }


            /// CHOIX DU SOLDAT -----------------------------------------------------------------------------------------------------

            if (tourjeu == SOLDATS && choix ==-1){
                afficherTexte(renderer, font,"Attaquer une troupes",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Attaquer un batiment",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Defendre un batiment",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Passer son tour",550,550,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "attaque troup!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "attaque bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "defendre bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                    choix = 0;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "passe!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
            }



            // SI IL ATTAQUE

            if (choix == 1 && tourjeu == SOLDATS){

                // baisser nb ressources

                afficherTexte(renderer, font, "Qui voulez vous attaquer ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement2 == VILLAGE2) { //click une le village adverse
                    // -- vie base sinon defensseurs
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 1;
                    
                } else if (highlightedElement2 == FORTERESSE2){ //click sur la forteresse adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 2;
                    // -- vie forteresse sinon defensseurs

                } else if (highlightedElement2 == ECOLE_DE_MAGIE2){  //click sur ecole magie adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 3;
                    // -- vie ecole sinon defensseurs

                } else if (highlightedElement2 == TROUPE_DE_GUERRE2){  //click sur soldat adverse

                   
                    if (DONNEES.j2.listesoldats.size() > 1){
                        insertImages(renderer, 810, yg, widthG, heightG, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, 810-widthFLg, yg + (heightG - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j2.sold_select > 0){
                            std::cout << "soldat avant" << std::endl;
                            changesold2avant(&DONNEES);
                            std::cout << DONNEES.j2.listesoldats[DONNEES.j2.sold_select].index << std::endl;

                            // -- vie 

                        } else if (isClickInsideImage(clickX, clickY, 810+widthG, yg + (heightG - heightFL) / 2, widthFL, heightFL) && DONNEES.j2.sold_select < DONNEES.j2.listesoldats.size()-1){
                            std::cout << "soldat apres" << std::endl;
                            changesold2apres(&DONNEES);
                            std::cout << DONNEES.j2.listesoldats[DONNEES.j2.sold_select].index<< std::endl;

                            // -- vie 

                        }
                    }

                } else if (highlightedElement2 == MAGICIEN2){ //click sur magicien adverse
                    
                    // -- vie magiciens
                    if (DONNEES.j2.listemagiciens.size() > 1){
                        insertImages(renderer, 820, yma, widthMA, heightMA, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, 820-widthFLg, yma + (heightMA - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j2.mag_select > 0){
                            std::cout << "magicien avant" << std::endl;
                            changemag2avant(&DONNEES);
                            std::cout << DONNEES.j2.listemagiciens[DONNEES.j2.mag_select].index << std::endl;

                        } else if (isClickInsideImage(clickX, clickY, 820+widthMA, yma + (heightMA - heightFL) / 2, widthFL, heightFL) && DONNEES.j2.mag_select < DONNEES.j2.listemagiciens.size()-1){
                            std::cout << "magicien apres" << std::endl;
                            changemag2apres(&DONNEES);
                            std::cout << DONNEES.j2.listemagiciens[DONNEES.j2.mag_select].index << std::endl;
                        }
                    }
                }
               
            }

        
            // SI IL DEFEND 

            else if (choix == 0 && tourjeu == SOLDATS){

                afficherTexte(renderer, font, "Qui voulez vous defendre ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement1 == VILLAGE1) { // click sur sa base
                    DONNEES.action = 1;
                    // ++ nb defensseurs
                   
                } else if (highlightedElement1 == FORTERESSE1){ // click sur sa forteresse
                    DONNEES.action = 2;
                    // ++ nb defensseurs
                    
                } else if (highlightedElement1 == ECOLE_DE_MAGIE1){ // click sur son ecole magie
                    DONNEES.action = 3;
                    // ++ nb defensseurs
                    
                } 
            }

            else {
                
            }



            /// CHOIX DU MAGICIEN  -------------------------------------------------------------------------------------------------


            if (tourjeu == MAGICIENS && choix ==-1){
                afficherTexte(renderer, font,"Attaquer une troupes",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Attaquer un batiment",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Soigner une troupe",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Passer son tour",550,550,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "attaque troup!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "attaque bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "soigner troup!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "passe!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
            }


            // SI IL ATTAQUE

            if (choix == 1 && tourjeu == MAGICIENS){

                // baisser nb ressources

                afficherTexte(renderer, font, "Qui voulez vous attaquer ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement2 == VILLAGE2) { //click une le village adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 1;
                    // -- vie base sinon defensseurs
                    
                } else if (highlightedElement2 == FORTERESSE2){ //click sur la forteresse adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 2;
                    // -- vie forteresse sinon defensseurs

                } else if (highlightedElement2 == ECOLE_DE_MAGIE2){  //click sur ecole magie adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 3;
                    // -- vie ecole sinon defensseurs

                } else if (highlightedElement2 == TROUPE_DE_GUERRE2){  //click sur soldat adverse

                   
                    if (DONNEES.j2.listesoldats.size() > 1){
                        insertImages(renderer, 810, yg, widthG, heightG, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, 810-widthFLg, yg + (heightG - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j2.sold_select > 0){
                            std::cout << "soldat avant" << std::endl;
                            changesold2avant(&DONNEES);
                            std::cout << DONNEES.j2.listesoldats[DONNEES.j2.sold_select].index << std::endl;

                            // -- vie 

                        } else if (isClickInsideImage(clickX, clickY, 810+widthG, yg + (heightG - heightFL) / 2, widthFL, heightFL) && DONNEES.j2.sold_select < DONNEES.j2.listesoldats.size()-1){
                            std::cout << "soldat apres" << std::endl;
                            changesold2apres(&DONNEES);
                            std::cout << DONNEES.j2.listesoldats[DONNEES.j2.sold_select].index << std::endl;

                            // -- vie 

                        }
                    } 
                } else if (highlightedElement2 == MAGICIEN2){ //click sur magicien adverse
                    
                    // -- vie magiciens
                    if (DONNEES.j2.listemagiciens.size() > 1){
                        insertImages(renderer, 820, yma, widthMA, heightMA, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, 820-widthFLg, yma + (heightMA - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j2.mag_select > 0){
                            std::cout << "magicien avant" << std::endl;
                            changemag2avant(&DONNEES);
                            std::cout << DONNEES.j2.listemagiciens[DONNEES.j2.mag_select].index << std::endl;

                        } else if (isClickInsideImage(clickX, clickY, 820+widthMA, yma + (heightMA - heightFL) / 2, widthFL, heightFL) && DONNEES.j2.mag_select < DONNEES.j2.listemagiciens.size()-1){
                            std::cout << "magicien apres" << std::endl;
                            changemag2apres(&DONNEES);
                            std::cout << DONNEES.j2.listemagiciens[DONNEES.j2.mag_select].index << std::endl;

                        }
                    }
                }
               
            }


            // SI IL SOIGNE

            if (choix == 2 && tourjeu == MAGICIENS){
                
                afficherTexte(renderer, font, "Qui voulez vous soigner ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement1 == TROUPE_DE_GUERRE1){

                    if (DONNEES.j1.listesoldats.size() > 1){
                        insertImages(renderer, xg, yg, widthG, heightG, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, xg-widthFLg, yg + (heightG - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j1.sold_select > 0){
                            std::cout << "soldat avant" << std::endl;
                            changesold1avant(&DONNEES);

                            // ++ vie 

                        } else if (isClickInsideImage(clickX, clickY, xg+widthG, yg + (heightG - heightFL) / 2, widthFL, heightFL) && DONNEES.j1.sold_select < DONNEES.j1.listesoldats.size()-1){
                            std::cout << "soldat apres" << std::endl;
                            changesold1apres(&DONNEES);

                            // ++ vie 

                        }
                    } 
                } else if (highlightedElement1 == MAGICIEN1){

                    if (DONNEES.j1.listemagiciens.size() > 1){
                        insertImages(renderer, xma, yma, widthMA, heightMA, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, xma-widthFLg, yma + (heightMA - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j1.mag_select > 0){
                            std::cout << "magicien avant" << std::endl;
                            changemag1avant(&DONNEES);

                            // ++ vie 

                        } else if (isClickInsideImage(clickX, clickY, xma+widthMA, yma + (heightMA - heightFL) / 2, widthFL, heightFL) && DONNEES.j1.mag_select < DONNEES.j1.listemagiciens.size()-1){
                            std::cout << "magicien apres" << std::endl;
                            changemag1apres(&DONNEES);

                            // ++ vie 

                        }
                    } 
                }
            }

            


            // CHOIX TRAVAILLEUR
            // std:: cout << "je dois avoir : " << TRAVAILLEURS << " et " << NONE_ACTION << " j'ai " << tourjeu << " et " << action <<"\n";
            if (tourjeu == TRAVAILLEURS && action == NONE_ACTION){
                afficherTexte(renderer, font,"Former des ressources",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Reparer un batiment",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Construire/Ameliorer un batiment",550,500,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "former des ressources!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "Reparer bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "const bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                }
            }

            if (tourjeu == TRAVAILLEURS && action == CONST_BATIMENTS){
                afficherTexte(renderer, font,"Base",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Forteresse",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Ecole de magie",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Annuler",550,550,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "base!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "forteresse!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "ecole mag!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "annuler!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
            }

           

            

        } 
        
        /// JOUEUR 2 //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        
        else {

             if (DONNEES.tour_joueur == 2){


            // DEBUT JOUEUR

            if(tourjeu == NONE && action == FORMATION_TROUPE && choice == NONE_CHOICE){
                afficherTexte(renderer, font, "Former troupe",550,300,{255,255,255,0});

                afficherTexte(renderer, font,"Oui",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Non",650,400,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,50,30)){

                    std::cout << "Oui pour former des ressources!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                    choice = OUI;
                } else if(isClickInsideImage(clickX,clickY,650,400,50,30)){

                    std::cout << "Non pour former des ressources!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

            }

            if (tourjeu == NONE && action == FORMATION_TROUPE && choice == OUI){

                afficherTexte(renderer, font,"Arreter la formation",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Travailleurs",550,550,{255,255,255,0});
                afficherTexte(renderer, font,"Soldats",550,600,{255,255,255,0});
                afficherTexte(renderer, font,"Magiciens",550,650,{255,255,255,0});
                
                if (isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "arret formation!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "travailleurs!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                } else if(isClickInsideImage(clickX,clickY,550,600,200,30)){
                    std::cout << "soldat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                } else if(isClickInsideImage(clickX,clickY,550,650,200,30)){
                    std::cout << "mag!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                }
            }


            /// CHOIX DU SOLDAT -----------------------------------------------------------------------------------------------------


            if (tourjeu == SOLDATS && choix ==-1){
                afficherTexte(renderer, font,"Attaquer une troupes",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Attaquer un batiment",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Defendre un batiment",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Passer son tour",550,550,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "attaque troup!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "attaque bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "defendre bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "passe!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
            }



            // SI IL ATTAQUE

            if (choix == 1 && tourjeu == SOLDATS){

                // baisser nb ressources

                afficherTexte(renderer, font, "Qui voulez vous attaquer ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement1 == VILLAGE1) { //click une le village adverse
                    // -- vie base sinon defensseurs
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 1;

                    
                } else if (highlightedElement1 == FORTERESSE1){ //click sur la forteresse adverse
                    
                    // -- vie forteresse sinon defensseurs
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 2;

                } else if (highlightedElement1 == ECOLE_DE_MAGIE1){  //click sur ecole magie adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 3;
                    // -- vie ecole sinon defensseurs

                } else if (highlightedElement1 == TROUPE_DE_GUERRE1){  //click sur soldat adverse

                   
                    if (DONNEES.j1.listesoldats.size() > 1){
                        insertImages(renderer, xg, yg, widthG, heightG, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, xg-widthFLg, yg + (heightG - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j1.sold_select > 0){
                            std::cout << "soldat avant" << std::endl;
                            changesold1avant(&DONNEES);
                            std::cout << DONNEES.j1.listesoldats[DONNEES.j1.sold_select].index << std::endl;


                            // -- vie 

                        } else if (isClickInsideImage(clickX, clickY, xg+widthG, yg + (heightG - heightFL) / 2, widthFL, heightFL) && DONNEES.j1.sold_select < DONNEES.j1.listesoldats.size()-1){
                            std::cout << "soldat apres" << std::endl;
                            changesold1apres(&DONNEES);
                            std::cout << DONNEES.j1.listesoldats[DONNEES.j1.sold_select].index << std::endl;

                            // -- vie 

                        }
                    }

                } else if (highlightedElement1 == MAGICIEN1){ //click sur magicien adverse
                    
                    // -- vie magiciens
                    if (DONNEES.j1.listemagiciens.size() > 1){
                        insertImages(renderer, xma, yma, widthMA, heightMA, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, xma-widthFLg, yma + (heightMA - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j1.mag_select > 0){
                            std::cout << "magicien avant" << std::endl;
                            changemag1avant(&DONNEES);
                            std::cout << DONNEES.j1.listemagiciens[DONNEES.j1.mag_select].index << std::endl;
                        } else if (isClickInsideImage(clickX, clickY, xma+widthMA, yma + (heightMA - heightFL) / 2, widthFL, heightFL) && DONNEES.j1.mag_select < DONNEES.j1.listemagiciens.size()-1){
                            std::cout << "magicien apres" << std::endl;
                            changemag1apres(&DONNEES);
                            std::cout << DONNEES.j1.listemagiciens[DONNEES.j1.mag_select].index << std::endl;

                        }
                    }
                }
               
            }

        
            // SI IL DEFEND 

            else if (choix == 0 && tourjeu == SOLDATS){

                afficherTexte(renderer, font, "Qui voulez vous defendre ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement2 == VILLAGE2) { // click sur sa base
                    DONNEES.action = 1;    
                    // ++ nb defensseurs
                   
                } else if (highlightedElement2 == FORTERESSE2){ // click sur sa forteresse
                    DONNEES.action = 2;
                    // ++ nb defensseurs
                    
                } else if (highlightedElement2 == ECOLE_DE_MAGIE2){ // click sur son ecole magie
                    DONNEES.action = 3;
                    // ++ nb defensseurs
                    
                } 
            }

            else {
                
            }



            /// CHOIX DU MAGICIEN  -------------------------------------------------------------------------------------------------


            if (tourjeu == MAGICIENS && choix ==-1){
                afficherTexte(renderer, font,"Attaquer une troupes",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Attaquer un batiment",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Soigner une troupe",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Passer son tour",550,550,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "attaque troup!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "attaque bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                    choix = 1;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "soigner troup!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "passe!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
            }


            // SI IL ATTAQUE

            if (choix == 1 && tourjeu == MAGICIENS){

                // baisser nb ressources

                if (highlightedElement1 == VILLAGE1) { //click une le village adverse
                    // -- vie base sinon defensseurs
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 1;
                    
                } else if (highlightedElement1 == FORTERESSE1){ //click sur la forteresse adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 2;
                    // -- vie forteresse sinon defensseurs

                } else if (highlightedElement1 == ECOLE_DE_MAGIE1){  //click sur ecole magie adverse
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DONNEES.action = 3;
                    // -- vie ecole sinon defensseurs

                } else if (highlightedElement1 == TROUPE_DE_GUERRE1){  //click sur soldat adverse

                   
                    if (DONNEES.j1.listesoldats.size() > 1){
                        insertImages(renderer, xg, yg, widthG, heightG, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, xg-widthFLg, yg + (heightG - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j1.sold_select > 0){
                            std::cout << "soldat avant" << std::endl;
                            changesold1avant(&DONNEES);
                            std::cout << DONNEES.j1.listesoldats[DONNEES.j1.sold_select].index << std::endl;

                            // -- vie 

                        } else if (isClickInsideImage(clickX, clickY, xg+widthG, yg + (heightG - heightFL) / 2, widthFL, heightFL) && DONNEES.j1.sold_select < DONNEES.j1.listesoldats.size()-1){
                            std::cout << "soldat apres" << std::endl;
                            changesold1apres(&DONNEES);
                            std::cout << DONNEES.j1.listesoldats[DONNEES.j1.sold_select].index << std::endl;

                            // -- vie 

                        }
                    }

                } else if (highlightedElement1 == MAGICIEN1){ //click sur magicien adverse
                    
                    // -- vie magiciens
                    if (DONNEES.j1.listemagiciens.size() > 1){
                        insertImages(renderer, xma, yma, widthMA, heightMA, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, xma-widthFLg, yma + (heightMA - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j1.mag_select > 0){
                            std::cout << "magicien avant" << std::endl;
                            changemag1avant(&DONNEES);
                            std::cout << DONNEES.j1.listemagiciens[DONNEES.j1.mag_select].index << std::endl;

                        } else if (isClickInsideImage(clickX, clickY, xma+widthMA, yma + (heightMA - heightFL) / 2, widthFL, heightFL) && DONNEES.j1.mag_select < DONNEES.j1.listemagiciens.size()-1){
                            std::cout << "magicien apres" << std::endl;
                            changemag1apres(&DONNEES);
                            std::cout << DONNEES.j1.listemagiciens[DONNEES.j1.mag_select].index << std::endl;
                        }
                    }
                }
               
            }
        

            // SI IL SOIGNE

            if (choix == 2 && tourjeu == MAGICIENS){
                
                afficherTexte(renderer, font, "Qui voulez vous soigner ?", textRect.x,textRect.y+50,{255,255,255,0});

                if (highlightedElement2 == TROUPE_DE_GUERRE2){

                    if (DONNEES.j2.listesoldats.size() > 1){
                        insertImages(renderer, 810, yg, widthG, heightG, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, 810-widthFLg, yg + (heightG - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j2.sold_select > 0){
                            std::cout << "soldat avant" << std::endl;
                            changesold2avant(&DONNEES);

                            // ++ vie 

                        } else if (isClickInsideImage(clickX, clickY, 810+widthG, yg + (heightG - heightFL) / 2, widthFL, heightFL) && DONNEES.j2.sold_select < DONNEES.j2.listesoldats.size()-1){
                            std::cout << "soldat apres" << std::endl;
                            changesold2apres(&DONNEES);

                            // ++ vie 

                        }
                    } 
                } else if (highlightedElement2 == MAGICIEN2){

                    if (DONNEES.j2.listemagiciens.size() > 1){
                        insertImages(renderer, 820, yma, widthMA, heightMA, imageTextureflg, widthFLg, heightFLg, imageTexturefl, widthFL, heightFL);
                        if (isClickInsideImage(clickX, clickY, 820-widthFLg, yma + (heightMA - heightFLg) / 2, widthFLg, heightFLg) && DONNEES.j2.mag_select > 0){
                            std::cout << "magicien avant" << std::endl;
                            changemag2avant(&DONNEES);

                            // ++ vie 

                        } else if (isClickInsideImage(clickX, clickY, 820+widthMA, yma + (heightMA - heightFL) / 2, widthFL, heightFL) && DONNEES.j2.mag_select < DONNEES.j2.listemagiciens.size()-1){
                            std::cout << "magicien apres" << std::endl;
                            changemag2apres(&DONNEES);

                            // ++ vie 

                        }
                    } 
                }
            }

            // std:: cout << "je dois avoir : " << TRAVAILLEURS << " et " << NONE_ACTION << " j'ai " << tourjeu << " et " << action <<"\n";
                // CHOIX TRAVAILLEUR
            if (tourjeu == TRAVAILLEURS && action == NONE_ACTION){
                afficherTexte(renderer, font,"Former des ressources",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Reparer un batiment",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Construire/Ameliorer un batiment",550,500,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "former des ressources!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "Reparer bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "const bat!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                }
            }

            if (tourjeu == TRAVAILLEURS && action == CONST_BATIMENTS){
                afficherTexte(renderer, font,"Base",550,400,{255,255,255,0});
                afficherTexte(renderer, font,"Forteresse",550,450,{255,255,255,0});
                afficherTexte(renderer, font,"Ecole de magie",550,500,{255,255,255,0});
                afficherTexte(renderer, font,"Annuler",550,550,{255,255,255,0});

                if(isClickInsideImage(clickX,clickY,550,400,200,30)){
                    std::cout << "base!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 1;
                } else if(isClickInsideImage(clickX,clickY,550,450,200,30)){
                    std::cout << "forteresse!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 2;
                } else if(isClickInsideImage(clickX,clickY,550,500,200,30)){
                    std::cout << "ecole mag!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 3;
                } else if(isClickInsideImage(clickX,clickY,550,550,200,30)){
                    std::cout << "annuler!" << std::endl;
                    clickX = 0; clickY = 0;
                    DONNEES.action = 0;
                }
            }
            


            }
            // CHOIX FORMATION DE RESSOURCES
            
            
        }





        // Afficher ce qui a été dessiné
        SDL_RenderPresent(renderer);

        // Met en pause pendant 5 secondes
        sleep(0.3);
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
