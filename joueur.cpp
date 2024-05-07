#include "joueur.hpp"

// ----------------------------------------------------------------
// JOUEUR

Joueur::Joueur(std::string nom){
    _nom_joueur = nom;
    _ressources = 10;
    _village.push_back(Base()); // On rajoute la base
    _village.push_back(Forteresse()); // On rajoute la forteresse
    _village.push_back(EcoleDeMagie()); // On rajoute une école de magie
    srand(time(NULL));
}

void Joueur::jouer(Joueur& deuxieme_joueur){ // Le joueur joue son tour
    // LE JOUEUR REGARDE S'IL VEUT FORMER DES TROUPES
    int action; // Commande  du joueur pour agir sur le jeu
    std::cout << *this;
    do {
        std::cout << "Voulez-vous former une troupe ?\n0 : Non\n1 : Oui\n";
        action = get_action(0,1);
    } while(not (action == 0 or action == 1));

    if (action == 1){
        do { // Former des troupes
            std::cout << *this;
            std::cout << "Veuillez selectionner la troupe a former:\n\t0 : Arreter la formation de Troupes\n\t1 : Travailleur\n\t2 : Soldat\n\t3 : Magicien\n";
            action = get_action(0,3);

            switch(action){
            case 1: // Villageois
                former_troupes(0);
                break;
            case 2: // Soldat
                former_troupes(1);
                break;
            case 3: // Magicien
                former_troupes(2);
                break;
            
            default:
                std::cout << "Mauvaise selection\n";
                break;
            }
        } while(action != 0); // Tant que le joueur ne souhaite pas arreter la formation
    } 

    for(Troupe troupe : _troupes){
        troupe.agir(*this, deuxieme_joueur);
    }

    std::cout << "Fin du tour\n";

}

void Joueur::former_troupes(int batiment_index){ // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
    int cout = _village[batiment_index].getniveau() * 10;
    _ressources -= cout;
    _troupes.push_back(_village[batiment_index].former_troupes());
    // std::cout << "Taille de la troupe : " << _troupes.size();
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

int Joueur::get_action(int inf, int max){ // le joueur choisit un nombre
    int action;
    std::cin >> action;
    return action;
}

// ----------------------------------------------------------------
// IA 

int IA::get_action(int inf, int max){ // Bornes inferieures et max
    return rand()%(max-inf+1)+inf; // On renvoie un nombre entre inf et max
}




// ---------------------------------------------------------------
// Affichage : 


std :: ostream& operator<<(std::ostream& os, Joueur& joueur){ // Operator de flux Joueur
    os << joueur.get_name() << " " << joueur.get_ressources() << " Ressources" <<std::endl;
    for (int i = 0; i < 3; i++){
        os << joueur.get_batiment(i);
    }
    os << "\nTroupes :";

    for (int i = 0; i < joueur.get_size_troupes(); i++){
        std::string text = (joueur.get_troupe(i)).get_infos();
        os << text;
        std::cout << "GRAGRGRAGAGRAGRGAGAR" << text << "GRAGARAGARGAGAGARAA" << std::endl;        
    }
    os << "--" << std::endl;
    os << "-------------------------" << std::endl;
    return os;
}