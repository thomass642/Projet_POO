#include "joueur.hpp"

// ----------------------------------------------------------------
// JOUEUR

Joueur::Joueur(std::string nom){
    _nom_joueur = nom;
    _ressources = 10;
    _village.push_back(Base()) // On rajoute la base
    _village.push_back(Forteresse()) // On rajoute la forteresse
    _village.push_back(EcoleDeMagie()) // On rajoute une école de magie
}

void Joueur::jouer(); // Le joueur joue son tour

void Joueur::former_troupes(int batiment_index){ // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie

}

void Joueur::mobiliser_troupes(){ // Mobilise chaque troupe dans _troupes

}

void Joueur::ameliorer_batiment(int index){ // On améliore ou construit un batiment

}

// ----------------------------------------------------------------
// IA