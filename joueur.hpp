#include <vector>
#include "batiment.hpp"
#include "troupe.hpp"

#ifndef JOUEUR_HPP
#define JOUEUR_HPP

class Joueur{
    private:
        std::vector<Batiment> _village;
        std::vector<Troupe> _troupes;
        int _ressources = 10;

    public:
        void former_troupes(int batiment_index); // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
        void mobiliser_troupes(); // Mobilise chaque troupe dans _troupes
        void ameliorer_batiment(int index); // On améliore ou construit un batiment
};

class IA : Joueur{}; // IA a definir

#endif