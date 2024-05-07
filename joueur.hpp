#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <vector>
#include <string>
#include "batiment.hpp"
#include "troupe.hpp"

class Batiment;
class Troupe;

class Joueur{
    private:
        std::vector<Batiment> _village;
        std::vector<Troupe> _troupes;
        int _ressources;
        std::string _nom_joueur;

    public:
        Joueur(std::string nom);
        std::string get_name() { return _nom_joueur;}
        void jouer(Joueur& deuxieme_joueur); // Le joueur joue
        void former_troupes(int batiment_index); // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
        void recuperer_ressources(int ressources){ _ressources += ressources;}
        Batiment& get_batiment(int index){ return _village[index]; }
        Troupe& get_troupe(int index){ return _troupes[index]; }
        int get_size_troupes(){ return _troupes.size(); }
        void show_troupes(); // Affiche toutes les troupes avec index
        int get_action(int inf, int max); // Fait le choix 
        int get_ressources(){ return _ressources;}
};

class IA : public Joueur{
    int get_action(int inf, int max); // Choisit une troupe au hasard
};

std :: ostream& operator<<(std::ostream& os, Joueur& joueur); // Operator de flux Joueur


#endif