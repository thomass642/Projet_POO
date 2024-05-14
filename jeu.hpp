#ifndef JEU_HPP
#define JEU_HPP

#include "joueur.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "MAPfonction.h"
#include "data.h"

class Jeu{
    private:
        Joueur* _joueur1;
        Joueur* _joueur2;
    public:
        Jeu(std::string joueur1, std::string joueur2); // Définition des joueurs (ou IA)
        void run();
};

#endif