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
    // MISE A JOUR AFFICHAGE ICI
        DONNEES.texteinfo = "Voulez-vous former une troupe ?";
        std::cout << "Voulez-vous former une troupe ?\n\t0 : Non\n\t1 : Oui\n";
        action = get_action(0,1);
    } while (not (action == 0 or action == 1));

    if (action == 1){
        do { // Former des troupes
            std::cout << *this;
            std::cout << "Vous avez " << _ressources << " ressources\nVeuillez selectionner la troupe a former:\n\t0 : Arreter la formation de Troupes\n\t1 : Travailleur (" << _base->cout_formation() << ")\n\t2 : Soldat (" << _forteresse->cout_formation() << ")\n\t3 : Magicien (" << _ecole_magie->cout_formation() <<  ")\n";
            action = get_action(0,3);
            
            switch(action){
            case 1: // Villageois
                if (_base->getniveau() != 0){
                    if (_base->cout_formation() <= _ressources){
                        former_troupes(0);
                    } else {
                        std::cout << "Cout formation trop eleve...\n";
                        DONNEES.texteinfo = "Cout de formation trop eleve...";
                    }
                } else {
                    std::cout << "Votre base est detruite...\n";
                    DONNEES.texteinfo = "Votre base est detruite...";
                }
                break;
            case 2: // Soldat
                if (_forteresse->getniveau() != 0){
                    if (_forteresse->cout_formation() <= _ressources){
                        former_troupes(1);
                     } else {
                        std::cout << "Cout formation trop eleve...\n";
                        DONNEES.texteinfo = "Cout de formation trop eleve...";
                    }
                } else {
                    std::cout << "Veuillez tout d'abord construire la forteresse pour former un soldat...\n";
                    DONNEES.texteinfo = "Veuillez tout d'abord construire la forteresse pour former un soldat...";
                }
                break;
            case 3: // Magicien
                if (_ecole_magie->getniveau() != 0){
                    if (_ecole_magie->cout_formation() <= _ressources){
                        former_troupes(2);
                    } else {
                        std::cout << "Cout formation trop eleve...\n";
                        DONNEES.texteinfo = "Cout de formation trop eleve...";
                    }
                } else {
                    std::cout << "Veuillez tout d'abord construire l'ecole de magie pour former un magicien...\n";
                    DONNEES.texteinfo = "Veuillez tout d'abord construire l'ecole de magie pour former un magicien...";
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
        if (not deuxieme_joueur.est_vivant()){
            break;
        }
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

void Joueur::recuperer_ressources(int ressources){
    _ressources += ressources;
    if (joueur_courant == 1){
        DONNEES.j1.ressources = _ressources;
    }else{ 
        DONNEES.j2.ressources = _ressources;
    }
}


void Joueur::former_troupes(int batiment_index){ // L'index du batiment : 0 = base, 1 = forteresse, 2 = école magie
    int cout;

    if (batiment_index == 0){
        cout = _base->cout_formation();
        _troupes.push_back(_base->former_troupes());

    } else if (batiment_index == 1){
        cout = _forteresse->cout_formation();
        _troupes.push_back(_forteresse->former_troupes());

    } else if (batiment_index == 2){
        cout = _ecole_magie->cout_formation();
        _troupes.push_back(_ecole_magie->former_troupes());
    }
    
    if (joueur_courant == 1){
        DONNEES.j1.listesoldats.clear();
    }else{ 
        DONNEES.j2.listesoldats.clear();
    }


    int nb_trav = 0;
    
    for (Troupe* troupe : _troupes){
        if (troupe->gettroupe() == "Travailleur"){
            nb_trav += 1;
        } else if (troupe->gettroupe() == "Soldat"){
            Soldat* copie = dynamic_cast<Soldat*>(troupe);
            data_troupes_de_guerre sold;
            sold.vie = copie->getvie();
            sold.niveau = copie->getniveau();
            sold.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_SOLD;
            if (joueur_courant == 1){
                DONNEES.j1.listesoldats.push_back(sold);
            }else{ 
                DONNEES.j2.listesoldats.push_back(sold);
            }
            
        } else if (troupe->gettroupe() == "Magicien"){
            Magicien* copie = dynamic_cast<Magicien*>(troupe);
            data_troupes_de_guerre mag;
            mag.vie = copie->getvie();
            mag.niveau = copie->getniveau();
            mag.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_MAG;
            mag.soins = copie->getniveau() * FACTO_SOIN_TROUPE;
            if (joueur_courant == 1){
                DONNEES.j1.listesoldats.push_back(mag);
            }else{ 
                DONNEES.j2.listesoldats.push_back(mag);
            }
        }
    }

    _ressources -= cout;
    if (joueur_courant == 1){
        DONNEES.j1.ressources = _ressources;
        DONNEES.j1.nb_travailleurs = nb_trav;
    }else{ 
        DONNEES.j2.ressources = _ressources;
        DONNEES.j2.nb_travailleurs = nb_trav;
    }
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
        DONNEES.texteinfo = _nom_joueur +" ne peut plus se battre et a donc perdu..."; 
        return false;
    }
}

int Joueur::cout_amelioration(int index){
    switch (index){
    case 0:
        return _base->cout_amelioration();
        break;
    case 1:
        return _forteresse->cout_amelioration();
        break;
    case 2:
        return _ecole_magie->cout_amelioration();
        break;
    default:
        return 10000;
        break;
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