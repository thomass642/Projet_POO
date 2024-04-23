#include "batiment.hpp"

// ----------------------------------------------------------------
// BATIMENT

Troupe Batiment::former_troupes(){ // On forme une troupe à partir des ressources du joueur

}

void Batiment::se_fait_attaquer(int degats){ // Le batiment perd de la vie, a moins qu'il soit défendu. Dans ce cas c'est un défenseur qui prend les dégats

}

// ----------------------------------------------------------------
// BASE

Base::Base(){ // Constructeur base
    _vie = 500;
    _niveau = 1;
    _type_batiment = "Base"
}

Travailleur Base::former_troupes(){ // Renvoie un travailleur 

}

// ----------------------------------------------------------------
// FORTERESSE

Forteresse::Forteresse(){ // Constructeur forteresse
    _vie = 0;
    _niveau = 0;
    _type_batiment = "Forteresse"
}

Soldat Forteresse::former_troupes(){ // Renvoie un soldat

}

// ----------------------------------------------------------------
// ECOLE DE MAGIE

EcoleDeMagie::EcoleDeMagie(){ // Constructeur forteresse
    _vie = 0;
    _niveau = 0;
    _type_batiment = "Ecole de Magie"
}

Magicien EcoleDeMagie::former_troupes(){ // Renvoie un magicien 

}
