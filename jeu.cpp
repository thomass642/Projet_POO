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

    joueur_courant = 1;
    DONNEES.j1.nomj = _joueur1->get_name();
    DONNEES.j2.nomj = _joueur2->get_name();
    DONNEES.j1.base.niveau = 1;
    DONNEES.j2.base.niveau = 1;
    DONNEES.j1.base.vie = FACTO_VIE_BASE;
    DONNEES.j2.base.vie = FACTO_VIE_BASE;
    

    if (JOUER_AVEC_AFFICHAGE_GRAPHIQUE){
        // DEBUT DU THREAD D INTERFACE
        std::thread thread_interface(interface);
        // DEBUT DU THREAD MOTEUR DE JEU
        std::thread thread_moteur(&Jeu::run, this);
        thread_interface.join();
        thread_moteur.join();
    } else {
        // DEBUT DU THREAD MOTEUR DE JEU
        std::thread thread_moteur(&Jeu::run, this);
        thread_moteur.join();
    }
}

void Jeu::run(){
    // JEU
    
    std::cout << "\n\nDEBUT DE LA PARTIE\n\n";

    while(_joueur1->est_vivant() and _joueur2->est_vivant()){
        std::cout << "\n\n\n\n TOUR DE " << _joueur1->get_name() << "\n\n\n"; 
        // MISE A JOUR AFFICHAGE ICI
        joueur_courant = 1;
        DONNEES.tour_joueur = 1;
        _joueur1->jouer(*_joueur2);
        if (not _joueur2->est_vivant())
            break;
        // MISE A JOUR AFFICHAGE ICI
        std::cout << "\n\n\n\n TOUR DE " << _joueur2->get_name() << "\n\n\n"; 
        joueur_courant = 2;
        DONNEES.tour_joueur = 2;
        _joueur2->jouer(*_joueur1);
    }



    // Affichage gagnant
    std::string gagnant;
    if (_joueur1->est_vivant()){
        gagnant = _joueur1->get_name();
    } else {
        gagnant = _joueur2->get_name();
    }
    std::cout << "\n\nFIN DE LA PARTIE\n\nGagnant : " << gagnant << std::endl;
    // MISE A JOUR AFFICHAGE ICI

}