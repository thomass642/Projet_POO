#include <string>
#include <vector>
#include "troupe.hpp"

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

class Base : Batiment{
    public:
        Travailleur former_troupes(); // Renvoie un travailleur 
};

class Forteresse : Batiment{
    public:
        Soldat former_troupes(); // Renvoie un soldat
};

class EcoleDeMagie : Batiment{
    public:
        Magicien former_troupes(); // Renvoie un magicien 
};