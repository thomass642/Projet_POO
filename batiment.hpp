#ifndef BATIMENT_HPP
#define BATIMENT_HPP

#include <string>
#include <vector>
#include <iostream>
#include "troupe.hpp"
#include "DefParam.hpp"
#include "data.hpp"

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
        std::vector<TroupeDeGuerre*> _defenseurs;
    public:
        Troupe* former_troupes(); // On forme une troupe à partir des ressources du joueur
        void se_fait_attaquer(int degats); // Le batiment perd de la vie, a moins qu'il soit défendu. Dans ce cas c'est un défenseur qui prend les dégats
        void se_fait_defendre(Soldat* troupe); // Le batiment se fait défendre par un défenseur
        void setvie(int vie){ _vie = vie;}
        int getvie(){ return _vie; }        
        int getniveau(){return _niveau;}
        std::vector<TroupeDeGuerre*> getdefenseurs(){return _defenseurs;}
        void setniveau(int niveau){_niveau = niveau;}
        std::string getbatiment(){return _type_batiment;}
        void se_fait_reparer(int reparation); // reparation du batiment
        int cout_formation(){ return 0;}
        int cout_amelioration(){ return 0;}
};

class Base : public Batiment{
    public:
        Base();
        Travailleur* former_troupes(); // Renvoie un travailleur 
        int cout_formation(){ return _niveau * FACTO_COUT_BASE;}
        int cout_amelioration();
};

class Forteresse : public Batiment{
    public:
        Forteresse();
        Soldat* former_troupes(); // Renvoie un soldat
        int cout_formation(){ return _niveau * FACTO_COUT_FORT;}
        int cout_amelioration();
};

class EcoleDeMagie : public Batiment{
    public:
        EcoleDeMagie();
        Magicien* former_troupes(); // Renvoie un magicien 
        int cout_formation(){ return _niveau * FACTO_COUT_ECOLE;}
        int cout_amelioration();
};


std :: ostream& operator<<(std::ostream& os, Batiment& batiment); // Operator de flux Batiment


#endif