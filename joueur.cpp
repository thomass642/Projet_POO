#include "joueur.hpp"

// ----------------------------------------------------------------
// JOUEUR

Joueur::Joueur(std::string nom){
    _nom_joueur = nom;
    _ressources = 10;
    _village.push_back(Base()); // On rajoute la base
    _village.push_back(Forteresse()); // On rajoute la forteresse
    _village.push_back(EcoleDeMagie()); // On rajoute une école de magie
}

void Joueur::jouer(Joueur& deuxieme_joueur){ // Le joueur joue son tour
    // LE JOUEUR REGARDE S'IL VEUT FORMER DES TROUPES
    int action; // Commande  du joueur pour agir sur le jeu

    for(Troupe troupe : _troupes){
        troupe.agir(*this, deuxieme_joueur);
    }

}

void Joueur::former_troupes(int batiment_index){ // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie

}

void Joueur::mobiliser_troupes(){ // Mobilise chaque troupe dans _troupes

}

int Joueur::get_action(){
    int action;
    std::cin >> action;
    return action;
}

void Joueur::show_troupes(){ // Affiche toutes les troupes avec index
    std::cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\nVoici la liste des troupes du joueur :\n";
    int index = 1;
    for (Troupe troupe : _troupes){
        std::cout << "Index :" << index << std::endl << troupe << std::endl;
        index+=1;
    }
    std::cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n";
}

// ----------------------------------------------------------------
// IA => Juste modifier get_action




// ---------------------------------------------------------------
// Affichage : 


