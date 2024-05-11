#include "jeu.hpp"

// ----------------------------------------------------------------
// JEU

Jeu::Jeu(std::string joueur1, std::string joueur2){ // Définition des joueurs (ou IA)
    if (joueur1 != "IA")
        _joueur1 = new Joueur(joueur1);
    else 
        _joueur1 = new IA;
    if (joueur2 != "IA")
        _joueur2 = new Joueur(joueur2);
    else 
        _joueur2 = new IA;
}

void Jeu::run(){
    std::cout << "\n\nDEBUT DE LA PARTIE\n\n";
    while(_joueur1->est_vivant() and _joueur2->est_vivant()){
        std::cout << "\n\n\n\n TOUR DE " << _joueur1->get_name() << "\n\n\n"; 
        _joueur1->jouer(*_joueur2);
        if (not _joueur2->est_vivant())
            break;
        std::cout << "\n\n\n\n TOUR DE " << _joueur2->get_name() << "\n\n\n"; 
        _joueur2->jouer(*_joueur1);
    }
    std::string gagnant;
    if (_joueur1->est_vivant()){
        gagnant = _joueur1->get_name();
    } else {
        gagnant = _joueur2->get_name();
    }
    std::cout << "\n\nFIN DE LA PARTIE\n\nGagnant : " << gagnant << std::endl;
}