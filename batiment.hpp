#include <string>
#include <vector>
#include "troupe.hpp"

#ifndef BATIMENT_HPP
#define BATIMENT_HPP

class Batiment{
    protected: 
        int _vie;
        int _niveau = 0;
        std::string _type_batiment;
        std::vector<Troupe> _defenseurs;
    public:
        Troupe former_troupes(); // On forme une troupe à partir des ressources du joueur
        void se_fait_reparer(int vie_recup){ _vie += vie_recup;} // Le batiment se fait réparer et récupère la quantité donnée
        void se_fait_attaquer(int degats); // Le batiment perd de la vie, a moins qu'il soit défendu. Dans ce cas c'est un défenseur qui prend les dégats
};

class Base : public Batiment{
    public:
        Travailleur former_troupes(); // Renvoie un travailleur 
};

class Forteresse : public Batiment{
    public:
        Soldat former_troupes(); // Renvoie un soldat
};

class EcoleDeMagie : public Batiment{
    public:
        Magicien former_troupes(); // Renvoie un magicien 
};

#endif