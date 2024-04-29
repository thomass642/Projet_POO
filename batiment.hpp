#ifndef BATIMENT_HPP
#define BATIMENT_HPP

#include <string>
#include <vector>
#include <iostream>
#include "troupe.hpp"

class Troupe;
class Travailleur;
class TroupeDeGuerre;
class Soldat;
class Magicien;

class Batiment{
    protected: 
        int _vie;
        int _niveau;
        std::string _type_batiment;
        std::vector<TroupeDeGuerre> _defenseurs;
    public:
        Troupe former_troupes(); // On forme une troupe à partir des ressources du joueur
        void se_fait_attaquer(int degats); // Le batiment perd de la vie, a moins qu'il soit défendu. Dans ce cas c'est un défenseur qui prend les dégats
        void se_fait_defendre(Soldat troupe); // Le batiment se fait défendre par un défenseur
        void setvie(int vie){ _vie = vie;}
        int getvie(){ return _vie; }        
        int getniveau(){return _niveau;}
        void setniveau(int niveau){_niveau = niveau;}
        std::string getbatiment(){return _type_batiment;}
};

class Base : public Batiment{
    public:
        Base();
        Travailleur former_troupes(); // Renvoie un travailleur 
};

class Forteresse : public Batiment{
    public:
        Forteresse();
        Soldat former_troupes(); // Renvoie un soldat
};

class EcoleDeMagie : public Batiment{
    public:
        EcoleDeMagie();
        Magicien former_troupes(); // Renvoie un magicien 
};

#endif