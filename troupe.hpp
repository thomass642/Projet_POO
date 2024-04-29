#include <string>
#include "batiment.hpp"

#ifndef TROUPE_HPP
#define TROUPE_HPP

class Troupe{
    protected:
        int _niveau;
        std::string _type_troupe;
    public : 
        Troupe(int niv);
};

class Travailleur : public Troupe{
    public:
        Travailleur(int niveau) : Troupe(niveau){} // Constructeur de travailleur (on affecte le niveau)
        int chercher_ressources(); // Renvoie le nombre de ressources collectées (en fonction de son niveau)
        void reparer_batiment(int ressources); // Répare un batiment en fonction des ressources du joueur
};

class TroupeDeGuerre : public Troupe{
    protected:
        int _vie;
    public:
        void attaquer_troupe(Troupe &troupe); // On attaque une troupe (dépend du niveau de la troupe)
        void attaquer_batiment(Batiment &batiment); // On attaque un batiment (dépend du niveau de la troupe)
        void se_fait_soigner(int qtt_soin){ _vie += qtt_soin;} // La troupe se fait soigner d'une quantité définie
        int se_fait_attaquer(int degats); // Renvoie le nombre de vie qu'il lui reste (possible négatif -> surplus de dégats)
};

class Soldat : public TroupeDeGuerre{
    public:
        Soldat(int niveau);
        void defendre_batiment(Batiment batiment); // La troupe défend un batiment
};

class Magicien : public TroupeDeGuerre{
    public:
        void soigner(Troupe &troupe); // On soigne la troupe en parametre (dépend du niveau du magicien)
};

std :: ostream& operator<<(std::ostream&, const Travailleur& trav); // Operator de flux Travailleur
std :: ostream& operator<<(std::ostream&, const Soldat& sold); // Operator de flux Soldat
std :: ostream& operator<<(std::ostream&, const Magicien& mag); // Operator de flux Magicien


#endif