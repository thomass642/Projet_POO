#include <vector>
#include <string>
#include "batiment.hpp"
#include "troupe.hpp"

#ifndef JOUEUR_HPP
#define JOUEUR_HPP

class Joueur{
    private:
        std::vector<Batiment> _village;
        std::vector<Troupe> _troupes;
        int _ressources;
        std::string _nom_joueur;

    public:
        Joueur(std::string nom);
        void jouer(); // Le joueur joue
        void former_troupes(int batiment_index); // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
        void mobiliser_troupes(); // Mobilise chaque troupe dans _troupes
        void ameliorer_batiment(int index); // On améliore ou construit un batiment
};

class IA : public Joueur{}; // IA a definir

#endif