#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <vector>
#include <string>
#include "batiment.hpp"
#include "troupe.hpp"

class Joueur{
    private:
        std::vector<Batiment> _village;
        std::vector<Troupe> _troupes;
        int _ressources;
        std::string _nom_joueur;

    public:
        Joueur(std::string nom);
        void jouer(Joueur& deuxieme_joueur); // Le joueur joue
        void former_troupes(int batiment_index); // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
        void mobiliser_troupes(); // Mobilise chaque troupe dans _troupes
        int get_action(); // Fait le choix 
        void recuperer_ressources(int ressources){ _ressources += ressources;}
        Batiment& get_batiment(int index){ return _village[index]; }
        Troupe& get_troupe(int index){ return _troupes[index]; }
        int get_size_troupes(){ return _troupes.size(); }
        void show_troupes(); // Affiche toutes les troupes avec index
};

class IA : public Joueur{}; // IA a definir

#endif