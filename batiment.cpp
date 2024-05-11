#include "batiment.hpp"
#include "DefParam.h"

// ----------------------------------------------------------------

Troupe* Batiment::former_troupes(){ Troupe* troupe = new Troupe(0); return troupe;} // On forme une troupe à partir des ressources du joueur


void Batiment::se_fait_attaquer(int degats){ // Le batiment perd de la vie, a moins qu'il soit défendu. Dans ce cas c'est un défenseur qui prend les dégats
    if (_defenseurs.size() == 0){
        _vie -= degats;
        std::cout << "La " << _type_batiment << " n'a pas de defenseur et a subi " << degats << ". Il lui reste " << _vie << " points de vie..." << std::endl;
    } else {
        int vie_apres_degats = _defenseurs[0]->se_fait_attaquer(degats); // Défenseur mort si degats <= 0
        std::cout << "Le defenseur a subi " << degats << " degats.. Il lui reste donc " << vie_apres_degats << "points de vie..." << std::endl; 
        while (vie_apres_degats <=0){ // Tant que les degats infliges excedent les degats du defenseur courant
            _defenseurs.erase(_defenseurs.begin()); // On supprime le defenseur courant (car mort)
            if (_defenseurs.size() == 0){ // S'il n'y a plus de defenseur le batiment est attaque
                std::cout << "Le dernier defenseur est mort et le batiment encaisse " << -vie_apres_degats << ".Il lui reste " << _vie << " points de vie..." << std::endl;
                _vie -= -vie_apres_degats;
                break;
            } else {
                std::cout << "Le deuxieme defenseur a subi " << -vie_apres_degats << " degats..";
                vie_apres_degats = _defenseurs[0]->se_fait_attaquer(-vie_apres_degats);
                std::cout <<" Il lui reste donc " << vie_apres_degats << "points de vie..." << std::endl; 
            }
        }
    }

    if (_vie > 0){
        std::cout << "La " << _type_batiment << " a tenu bon face a l'attaque. Il lui reste " << _vie << " points de vie." << std::endl;  
    } else{
        std::cout << "La " << _type_batiment << " a ete detruite..." << std::endl;
        _niveau = 0;
    }
}

void Batiment::se_fait_defendre(Soldat* troupe){ // Le batiment se fait défendre par un défenseur
    _defenseurs.push_back(troupe);
    std::cout << "Le batiment se fait defendre par " << *troupe << "!" << std::endl;
}

void Batiment::se_fait_reparer(int reparation){ // reparation du batiment
    int vie_avant_rep = _vie;
    _vie += reparation;
}

// ----------------------------------------------------------------
// BASE

Base::Base(){ // Constructeur base
    _niveau = 1;
    _vie = FACTO_VIE_BASE;
    _type_batiment = "Base";
}

Travailleur* Base::former_troupes(){ // Renvoie un travailleur 
    Travailleur* travailleur = new Travailleur(_niveau);
    std:: cout << "La base de niveau " << _niveau << " a forme un travailleur de niveau " << _niveau << " !" << std::endl; 
    return travailleur;
}

// ----------------------------------------------------------------
// FORTERESSE

Forteresse::Forteresse(){ // Constructeur forteresse
    _vie = 0;
    _niveau = 0;
    _type_batiment = "Forteresse";
}

Soldat* Forteresse::former_troupes(){ // Renvoie un soldat
    Soldat* soldat = new Soldat(_niveau);
    std:: cout << "La forteresse de niveau " << _niveau << " a forme un soldat de niveau " << _niveau << " !" << std::endl; 
    return soldat;
}

// ----------------------------------------------------------------
// ECOLE DE MAGIE

EcoleDeMagie::EcoleDeMagie(){ // Constructeur forteresse
    _vie = 0;
    _niveau = 0;
    _type_batiment = "Ecole de Magie";
}

Magicien* EcoleDeMagie::former_troupes(){ // Renvoie un magicien 
    Magicien* magicien = new Magicien(_niveau);
    std:: cout << "L'Ecole de Magie de niveau " << _niveau << " a forme un magicien de niveau " << _niveau << " !" << std::endl; 
    return magicien;
}

// ----------------------------------------------------------------
// Affichage

std :: ostream& operator<<(std::ostream& os, Batiment& batiment){ // Operator de flux Batiment
    os << batiment.getbatiment() << ": Niveau " << batiment.getniveau() << " Vie " << batiment.getvie() << std::endl << "Liste de defenseurs :\n";
    for (TroupeDeGuerre* defenseur : batiment.getdefenseurs()){
        os <<  *dynamic_cast<Soldat*>(defenseur);
    }
    os << "--" << std::endl;
    return os;
}