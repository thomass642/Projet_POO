#include "joueur.hpp"


// ----------------------------------------------------------------
// JOUEUR

Joueur::Joueur(std::string nom){
    _nom_joueur = nom;
    _ressources = 10;
    _base = new Base;
    _forteresse = new Forteresse;
    _ecole_magie = new EcoleDeMagie;
    srand(time(NULL));
}

void Joueur::jouer(Joueur& deuxieme_joueur){ // Le joueur joue son tour
    // LE JOUEUR REGARDE S'IL VEUT FORMER DES TROUPES
    int action; // Commande  du joueur pour agir sur le jeu
    std::vector<int> elems_to_remove;

    for (int i = 0; i < _troupes.size(); i++){
        if (_troupes[i]->gettroupe() != "Travailleur"){
            if (dynamic_cast<TroupeDeGuerre*>(_troupes[i])->getvie() <= 0){
                elems_to_remove.push_back(i);
            }
        }
    }

    for (auto it = elems_to_remove.rbegin(); it != elems_to_remove.rend(); ++it) {
        delete _troupes[*it];
        _troupes.erase(_troupes.begin() + *it);
    }

    std::cout << *this;
    do {
        std::cout << "Voulez-vous former une troupe ?\n\t0 : Non\n\t1 : Oui\n";
        action = get_action(0,1);
    } while (not (action == 0 or action == 1));

    if (action == 1){
        do { // Former des troupes
            std::cout << *this;
            std::cout << "Vous avez " << _ressources << " ressources\nVeuillez selectionner la troupe a former:\n\t0 : Arreter la formation de Troupes\n\t1 : Travailleur\n\t2 : Soldat\n\t3 : Magicien\n";
            action = get_action(0,3);

            switch(action){
            case 1: // Villageois
                former_troupes(0);
                break;
            case 2: // Soldat
                if (_forteresse->getniveau() != 0){
                    former_troupes(1);
                } else {
                    std::cout << "Veuillez tout d'abord construire la forteresse pour former un soldat...\n";
                }
                break;
            case 3: // Magicien
                if (_ecole_magie->getniveau() != 0){
                    former_troupes(2);
                } else {
                    std::cout << "Veuillez tout d'abord construire l'ecole de magie pour former un magicien...\n";
                }
                break;
            
            default:
                std::cout << "Mauvaise selection\n";
                break;
            }
        } while(action != 0); // Tant que le joueur ne souhaite pas arreter la formation
    } 
    for(Troupe *troupe : _troupes){
        troupe->agir(*this, deuxieme_joueur);
    }

    for (int i = 0; i < _troupes.size(); i++){
        if (_troupes[i]->gettroupe() == "Defend"){
            elems_to_remove.push_back(i);
        }
    }

    for (auto it = elems_to_remove.rbegin(); it != elems_to_remove.rend(); ++it) {
        _troupes.erase(_troupes.begin() + *it);
    }

    std::cout << "Fin du tour\n";
    std::cout << *this;

}

void Joueur::former_troupes(int batiment_index){ // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
    int cout;

    if (batiment_index == 0){

        cout = _base->getniveau() * 10;

        _troupes.push_back(_base->former_troupes());

    } else if (batiment_index == 1){
        cout = _forteresse->getniveau() * 10;
        _troupes.push_back(_forteresse->former_troupes());

    } else if (batiment_index == 2){
        cout = _ecole_magie->getniveau() * 10;
        _troupes.push_back(_ecole_magie->former_troupes());

    }
    _ressources -= cout;
    // std::cout << "Taille de la troupe : " << _troupes.size();
}

void Joueur::show_troupes(){ // Affiche toutes les troupes avec index
    std::cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\nVoici la liste des troupes du joueur :\n";
    int index = 1;
    for (Troupe* troupe : _troupes){
        std::cout << "Index :" << index << std::endl << troupe->get_infos() << std::endl;
        index+=1;
    }
    std::cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n";
}

int Joueur::get_action(int inf, int max){ // le joueur choisit un nombre
    int action;
    std::cin >> action;
    return action;
}

Batiment* Joueur::get_batiment(int index){
    switch (index) {
    case 0:
        return _base;
        break;
    case 1:
        return _forteresse;
        break;
    case 2:
        return _ecole_magie;
        break;
    default:
        return _base;
    }
}

bool Joueur::est_vivant(){ // Regarde si le joueur peut continuer a jouer
    if (_base->getvie() > 0 or _forteresse->getvie() > 0 or _ecole_magie->getvie() > 0){
        return true;
    } else {
        std::cout << _nom_joueur << " ne peut plus se battre et a donc perdu...\n"; 
        return false;
    }
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
        os << *joueur.get_batiment(i);
    }
    os << "\nTroupes :" << std::endl;

    for (int i = 0; i < joueur.get_size_troupes(); i++){
        std::string text = (joueur.get_troupe(i)).get_infos();
        os << text;
    }
    os << "--" << std::endl;
    os << "-------------------------" << std::endl;
    return os;
}