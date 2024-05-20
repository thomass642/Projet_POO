#ifndef TROUPE_HPP
#define TROUPE_HPP

#include <string>
#include "batiment.hpp"
#include "joueur.hpp"
#include "DefParam.hpp"
#include "data.hpp"
#include "testmap.hpp"

class Batiment;
class Joueur;


class Troupe{
    protected:
        int _niveau;
        std::string _type_troupe;
    public : 
        Troupe(){_type_troupe="troupe";}
        Troupe(int niv);
        virtual std::string get_infos(){return "VIRTUAL TROUPE";}
        int getniveau(){return _niveau;}
        int getniveau() const {return _niveau;}
        std::string gettroupe() const {return _type_troupe;}
        void virtual agir(Joueur& joueur, Joueur& deuxieme_joueur){} // Méthode d'action. Pour l'IA ou le joueur, on recupere la méthode d'actions en parametre 
};

class Travailleur : public Troupe{
    public:
        Travailleur(int niveau) : Troupe(niveau){_type_troupe = "Travailleur";} // Constructeur de travailleur (on affecte le niveau)
        std::string get_infos() override ;
        int chercher_ressources(); // Renvoie le nombre de ressources collectées (en fonction de son niveau)
        void reparer_batiment(int ressources, Batiment* batiment); // Répare un batiment en fonction des ressources du joueur
        void ameliorer_batiment(Batiment* batiment); // On ameliore un batiment
        void agir(Joueur& joueur, Joueur& deuxieme_joueur); // Méthode d'action. On copie le joueur en parametre 
};

class TroupeDeGuerre : public Troupe{
    protected:
        int _vie;
    public:
        TroupeDeGuerre(){}
        void attaquer_batiment(Batiment *batiment); // On attaque un batiment (dépend du niveau de la troupe)
        void se_fait_soigner(int qtt_soin){ _vie += qtt_soin;} // La troupe se fait soigner d'une quantité définie
        int se_fait_attaquer(int degats); // Renvoie le nombre de vie qu'il lui reste (possible négatif -> surplus de dégats)
        int getvie(){return _vie;}
        int getvie()const{return _vie;}
        void setvie(int vie){_vie = vie;}
};

class Soldat : public TroupeDeGuerre{
    public:
        Soldat(int niveau);
        std::string get_infos();
        void attaquer_troupe(TroupeDeGuerre &troupe); // On attaque une troupe (dépend du niveau de la troupe)
        void defendre_batiment(Batiment *batiment); // La troupe défend un batiment
        void agir(Joueur& joueur, Joueur& deuxieme_joueur); // Méthode d'action. On copie le joueur en parametre 
};

class Magicien : public TroupeDeGuerre{
    public:
        Magicien(int niveau);
        std::string get_infos();
        void attaquer_troupe(TroupeDeGuerre &troupe); // On attaque une troupe (dépend du niveau de la troupe)
        void soigner(TroupeDeGuerre &troupe); // On soigne la troupe en parametre (dépend du niveau du magicien)
        void agir(Joueur& joueur, Joueur& deuxieme_joueur); // Méthode d'action. On copie le joueur en parametre 
};

std :: ostream& operator<<(std::ostream& os, const Troupe& troupe); // Operator de flux Troupe
std :: ostream& operator<<(std::ostream& os, const Travailleur& trav); // Operator de flux Travailleur
std :: ostream& operator<<(std::ostream& os, const Soldat& sold); // Operator de flux Soldat
std :: ostream& operator<<(std::ostream& os, const Magicien& mag); // Operator de flux Magicien


#endif