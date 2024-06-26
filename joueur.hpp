#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "batiment.hpp"
#include "troupe.hpp"
#include "data.hpp"
#include "testmap.hpp"

class Batiment;
class Base;
class Forteresse;
class EcoleDeMagie;
class Troupe;

class Joueur{
    protected:
        Base* _base;
        Forteresse* _forteresse;
        EcoleDeMagie* _ecole_magie;
        std::vector<Troupe*> _troupes;
        std::string _nom_joueur;
        int _ressources;

    public:
        Joueur(std::string nom);
        std::string get_name() { return _nom_joueur;}
        void jouer(Joueur& deuxieme_joueur); // Le joueur joue
        void former_troupes(int batiment_index); // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
        void recuperer_ressources(int ressources);
        Batiment* get_batiment(int index);
        Troupe& get_troupe(int index){ return *(_troupes[index]); }
        int get_size_troupes(){ return _troupes.size(); }
        void show_troupes(); // Affiche toutes les troupes avec index
        int get_action(int inf, int max); // Fait le choix 
        int get_ressources(){ return _ressources;}
        bool est_vivant(); // Regarde si le joueur peut continuer a jouer
        int cout_amelioration(int index);
};

class IA : public Joueur{
    public:
        IA() : Joueur("IA") {}
        int get_action(int inf, int max); // Choisit une troupe au hasard
};

std :: ostream& operator<<(std::ostream& os, Joueur& joueur); // Operator de flux Joueur


#endif